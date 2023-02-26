#include <Arduino.h>
#include <MPU6050_6Axis_MotionApps612.h>
#include <Wire.h>
#include <ArduinoSTL.h>
#include <array>
#include <deque>
#include <pt.h>

#define XINPUT_LIBRARY
#ifdef XINPUT_LIBRARY
#include <XInputAdapter.h>
#include <XInput.h>
XInputController x;
JoystickEmulator &&joystick = XInputAdapter(x);
#endif
//#define JOYSTICK_LIBRARY
#ifdef JOYSTICK_LIBRARY
#include <Joystick.h>
#include <JoystickLibraryAdapter.h>
Joystick_ j{0x06, JOYSTICK_TYPE_MULTI_AXIS, 0, 0, true, true, true, true, true, true, false, false, false, false, false};
JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
#endif

float median(std::deque<float> &currentAxis)
{
  float min{currentAxis.at(0)};
  float max{currentAxis.at(0)};
  float sum{0};
  for (auto &val : currentAxis)
  {
    max = (val > max) ? val : max;
    min = (val < min) ? val : min;
    sum += val;
  }
  return sum - max - min;
}

// only axis


// szablon uzupełnić napisać
// wstęp motywacja
// przegląd rozwiązań
// wykorzystane technologie
// implementacja
// uruchuchomienie/intrukcja obsługi
// wnioski rozwinięcie

MPU6050 mpu;
// MPU control/status vars
constexpr long int I2C_CLOCK{400000};
constexpr long int BAUD{115200};
constexpr int MODE_BUTTON{7};
constexpr int BROADCAST_BUTTON{8};
constexpr int GREEN_PIN{A1};
constexpr int RED_PIN{A2};
constexpr int BLUE_PIN{A3};
enum CALIBRATION_DATA
{
  GYRO_X = -101,
  GYRO_Y = -48,
  GYRO_Z = 16,
  ACCEL_X = 1440,
  ACCEL_Y = 2110,
  ACCEL_Z = 1824,
};
enum AXIS_RANGE
{
  MIN_X = -2000,
  MAX_X = 2000,
  MIN_Y = -2000,
  MAX_Y = 2000,
  MIN_Z = -2000,
  MAX_Z = 2000,
};
enum TIMING
{
  // in ms
  SERIAL_THREAD_TIMER = 15,
  JOYSTICK_THREAD_TIMER = 5,
  MPU_THREAD_TIMER = 2,
  MODE_BUTTON_INTERRUPT_TIMER = 100,
  RGB_THREAD_TIMER = 2,
};
enum class Mode
{
  XYZ,
  rXrYrZ,
  BROADCASTING,
  NOT_BROADCASTING,
};

static pt printThread, joystickThread, mpuThread, rgbThread;

uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
volatile Mode deviceMode{Mode::rXrYrZ};
volatile Mode broadcastMode{Mode::NOT_BROADCASTING};
typedef std::deque<float> axis;
std::array<axis, 3> allAxis;
std::array<float, 3> deviceValues;
std::array<int, 3> pinsRGB;

void deviceFailed(int code)
{
  // (if it's going to break, usually the code will be 1)
  // 1 = initial memory load failed
  // 2 = DMP configuration updates failed
  // 10 = Wrong mode detected
  while (1)
  {
    Serial.print(F("Device failed (code "));
    Serial.print(code);
    Serial.println(F(")"));
    delay(1000);
    analogWrite(RED_PIN, 255);
    delay(1000);
    analogWrite(RED_PIN, 0);
  }
}

void modeChange()
{
  static unsigned long last_interrupt_time = 0;
  if (millis() - last_interrupt_time > MODE_BUTTON_INTERRUPT_TIMER)
  {
    switch (deviceMode)
    {
    case Mode::XYZ:
      deviceMode = Mode::rXrYrZ;
      break;
    case Mode::rXrYrZ:
      deviceMode = Mode::XYZ;
      break;
    default:
      Serial.print("Wrong mode chceck: ");
      Serial.print(__LINE__);
      deviceFailed(10);
      break;
    }
    // need to reset axis
    for (int index = 0; index < 3; index++)
    {
      joystick.setXYZ(index, 0);
      joystick.setRXRYRZ(index, 0);
    }
  }
  last_interrupt_time = millis();
}

void deviceReady()
{
  Serial.print("Device ready ");
  for (int pinIndex; pinIndex < 3; pinIndex++)
  {
    analogWrite(pinsRGB.at(pinIndex), 255);
    delay(300);
    analogWrite(pinsRGB.at(pinIndex), 0);
  }
}

void rgbUpdate(int pinIndex, int value)
{
  analogWrite(pinsRGB.at(pinIndex), map(value, -2000, 2000, 0, 255));
}

static void protothreadPrintSerial(pt &protoThread, const std::array<float, 3> &deviceValues, volatile const Mode &deviceMode, volatile const Mode &broadcastMode)
{
  static unsigned long lastTimePrint = 0;
  PT_BEGIN(&protoThread);
  while (1)
  {
    lastTimePrint = millis();
    PT_WAIT_UNTIL(&protoThread, millis() - lastTimePrint > SERIAL_THREAD_TIMER);
    Serial.print(millis());
    Serial.print('\t');
    switch (broadcastMode)
    {
    case Mode::BROADCASTING:
      Serial.print("broadcasting");
      break;
    case Mode::NOT_BROADCASTING:
      Serial.print("not broadcasting");
      break;
    default:
      Serial.print("Wrong mode chceck: ");
      Serial.print(__LINE__);
      deviceFailed(10);
      break;
    }
    Serial.print('\t');
    switch (deviceMode)
    {
    case Mode::XYZ:
      Serial.print("XYZ");
      break;
    case Mode::rXrYrZ:
      Serial.print("rXrYrZ");
      break;
    default:
      Serial.print("Wrong mode chceck: ");
      Serial.print(__LINE__);
      deviceFailed(10);
      break;
    }
    Serial.print('\t');
    for (auto axisNumber = 0; axisNumber < 3; axisNumber++)
    {
      Serial.print(deviceValues.at(axisNumber) * 100);
      Serial.print('\t');
    }
    Serial.println();
    PT_END(&protoThread);
  }
}

static void protothreadJoystickBroadcast(pt &protoThread, const std::array<float, 3> &deviceValues, volatile const Mode &deviceMode, volatile const Mode &broadcastMode)
{
  static unsigned long JoystickBroadcast = 0;
  PT_BEGIN(&protoThread);
  while (1)
  {
    JoystickBroadcast = millis();
    PT_WAIT_UNTIL(&protoThread, millis() - JoystickBroadcast > JOYSTICK_THREAD_TIMER);
    switch (broadcastMode)
    {
    case Mode::BROADCASTING:
      for (int setterIndex{0}; setterIndex < 3; setterIndex++)
      {
        auto val = deviceValues.at(setterIndex) * 100;
        switch (deviceMode)
        {
        case Mode::XYZ:
          joystick.setXYZ(setterIndex, val);
          break;
        case Mode::rXrYrZ:
          joystick.setRXRYRZ(setterIndex, val);
          break;
        default:
          Serial.print("Wrong mode chceck: ");
          Serial.print(__LINE__);
          deviceFailed(10);
          break;
        }
        joystick.send();
      }
      break;
    case Mode::NOT_BROADCASTING:
      break;
    default:
      Serial.print("Wrong mode chceck: ");
      Serial.print(__LINE__);
      deviceFailed(10);
      break;
    }
  }
  PT_END(&protoThread);
}

static void protothreadRGB(pt &protoThread, const std::array<float, 3> &deviceValues, volatile const Mode &broadcastMode)
{
  static unsigned long rgbTimer = 0;
  PT_BEGIN(&protoThread);
  while (1)
  {
    rgbTimer = millis();
    PT_WAIT_UNTIL(&protoThread, millis() - rgbTimer > RGB_THREAD_TIMER);
    switch (broadcastMode)
    {
    case Mode::BROADCASTING:
      for (int pinIndex{0}; pinIndex < pinsRGB.size(); pinIndex++)
      {
        rgbUpdate(pinIndex, deviceValues.at(pinIndex));
      }
      break;
    case Mode::NOT_BROADCASTING:
      for (int pinIndex{0}; pinIndex < pinsRGB.size(); pinIndex++)
      {
        rgbUpdate(pinIndex, 0);
      }
      break;
    default:
      Serial.print("Wrong mode chceck: ");
      Serial.print(__LINE__);
      deviceFailed(10);
      break;
    }
  }
  PT_END(&protoThread);
}

static void protothreadMpuUpdate(pt &protoThread, std::array<float, 3> &deviceValues, volatile const Mode &broadcastMode)
{
  static unsigned long lastMpuUpdate = 0;
  static std::array<float, 3> offsets;
  PT_BEGIN(&protoThread);
  while (1)
  {
    lastMpuUpdate = millis();
    std::array<float, 3> filteredValues; // Mpu for one iteration sends max values
    // timing between 15 - 55 ms results in buffer error
    PT_WAIT_UNTIL(&protoThread, millis() - lastMpuUpdate > MPU_THREAD_TIMER);
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
    {
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      for (int i = {0}; i < allAxis.size(); i++)
      {
        axis &currentAxis = allAxis.at(i);
        currentAxis.pop_front();
        currentAxis.push_back(ypr[i] * 180 / M_PI);
        filteredValues.at(i) = median(currentAxis);
      }
      if (broadcastMode == Mode::NOT_BROADCASTING)
      {
        offsets = {filteredValues};
      }
      for (int axisIndex{0}; axisIndex < deviceValues.size(); axisIndex++)
      {
        deviceValues.at(axisIndex) = {filteredValues.at(axisIndex) - offsets.at(axisIndex)};
      }
    }
  }
  PT_END(&protoThread);
}

void setup()
{
  Wire.begin();
  Wire.setClock(I2C_CLOCK); // 400kHz I2C clock. Comment this line if having compilation difficulties
  Serial.begin(BAUD);
  while (!Serial)
    ; // wait to open serial
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  Serial.println(devStatus);
  if (devStatus != 0)
  {
    deviceFailed(devStatus);
  }
  mpu.setXGyroOffset(GYRO_X);
  mpu.setYGyroOffset(GYRO_Y);
  mpu.setZGyroOffset(GYRO_Z);

  mpu.setXAccelOffset(ACCEL_X);
  mpu.setYAccelOffset(ACCEL_Y);
  mpu.setZAccelOffset(ACCEL_Z);

  Serial.println(F("Enabling DMP..."));
  mpu.setDMPEnabled(true);
  packetSize = mpu.dmpGetFIFOPacketSize();
  // Braced initialiser does not work for deque
  for (auto &a : allAxis)
  {
    a.push_back(0);
    a.push_back(0);
    a.push_back(0);
  }

  pinMode(MODE_BUTTON, INPUT);                                              // todo lookup input pullup
  attachInterrupt(digitalPinToInterrupt(MODE_BUTTON), modeChange, FALLING); // trigger when button pressed, but not when released.
  pinMode(BROADCAST_BUTTON, INPUT_PULLUP);

  joystick.setXAxisRange(MIN_X, MAX_X);
  joystick.setYAxisRange(MIN_Y, MAX_Y);
  joystick.setZAxisRange(MIN_Z, MAX_Z);

  joystick.setRxAxisRange(MIN_X, MAX_X);
  joystick.setRyAxisRange(MIN_Y, MAX_Y);
  joystick.setRzAxisRange(MIN_Z, MAX_Z);

  pinsRGB.at(0) = {RED_PIN};
  pinsRGB.at(1) = {GREEN_PIN};
  pinsRGB.at(2) = {BLUE_PIN};

  PT_INIT(&printThread);
  PT_INIT(&joystickThread);
  PT_INIT(&mpuThread);
  PT_INIT(&rgbThread);

  deviceReady(); // device flashes RGB to signal its ready
}

void loop()
{
  broadcastMode = (digitalRead(BROADCAST_BUTTON)) ? Mode::NOT_BROADCASTING : Mode::BROADCASTING;
  protothreadMpuUpdate(mpuThread, deviceValues, broadcastMode);
  protothreadJoystickBroadcast(joystickThread, deviceValues, deviceMode, broadcastMode);
  protothreadPrintSerial(printThread, deviceValues, deviceMode, broadcastMode);
  protothreadRGB(rgbThread, deviceValues, broadcastMode);
}