#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps_V6_12.h"
#include "Wire.h"
#include <Joystick.h>
#include "ArduinoSTL.h"
#include "array"
#include <deque>


MPU6050 mpu;
// only axis
Joystick_ joystick{ 0x06, JOYSTICK_TYPE_MULTI_AXIS, 0, 0, true, true, true, true, true, true, false, false, false, false, false };

// MPU control/status vars
bool dmpReady{ false };  // set true if DMP init was successful
uint8_t mpuIntStatus;    // holds actual interrupt status byte from MPU
uint8_t devStatus;       // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;     // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;      // count of all bytes currently in FIFO
uint8_t fifoBuffer[64];  // FIFO storage buffer
Quaternion q;            // [w, x, y, z]         quaternion container
VectorFloat gravity;     // [x, y, z]            gravity vector
float ypr[3];            // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

typedef std::deque<float> axis;
std::array<axis, 3> allAxis;
std::array<float, 3> filteredValues;  //Mpu for one iteration sends max values
std::array<float, 3> offsets;         //Mpu for one iteration sends max values
long mpuTime, joystickTime, timePrev, time = { 0 };
constexpr int MODE_BUTTON{ 7 };
constexpr int BROADCAST_BUTTON{ 8 };
volatile bool axisState{ false };
volatile bool broadcastState{ false };

void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000);  // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  Serial.begin(115200);
  delay(2500);
  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  Serial.println(devStatus);
  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(-101);
  mpu.setYGyroOffset(-48);
  mpu.setZGyroOffset(16);
  mpu.setXAccelOffset(1440);
  mpu.setYAccelOffset(2110);
  mpu.setZAccelOffset(1824);
  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // Calibration Time: generate offsets and calibrate our MPU6050
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    Serial.println();
    mpu.PrintActiveOffsets();
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
  // Braced initialiser does not work for deque
  for (auto &a : allAxis) {
    a.push_back(0);
    a.push_back(0);
    a.push_back(0);
  }
  pinMode(MODE_BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(MODE_BUTTON), modeChange, FALLING);  // trigger when button pressed, but not when released.
  pinMode(BROADCAST_BUTTON, INPUT_PULLUP);

  joystick.setXAxisRange(-4200, 4200);
  joystick.setYAxisRange(-4200, 4200);
  joystick.setZAxisRange(-5000, 5000);
  joystick.setRxAxisRange(-4200, 4200);
  joystick.setRyAxisRange(-4200, 4200);
  joystick.setRzAxisRange(-5000, 5000);
}

void modeChange() {
  static unsigned long last_interrupt_time = 0;
  if (time - last_interrupt_time > 100) {
    axisState = !axisState;
    // need to reset axis
    joystick.setXAxis(0);
    joystick.setYAxis(0);
    joystick.setZAxis(0);
    joystick.setRxAxis(0);
    joystick.setRyAxis(0);
    joystick.setRzAxis(0);
  }
  last_interrupt_time = time;
}

// void calculateMedian(std::deque<float> deq){
//   std::sort(xoffsetValues.begin(),xoffsetValues.end());
//   xoffset = deq.at(5);
// }

void loop() {
  timePrev = time;  // the previous time is stored before the actual time read
  time = millis();
  broadcastState = digitalRead(BROADCAST_BUTTON);
  if (time - mpuTime > 0.15) {
    if (broadcastState) {
      offsets = { filteredValues };
    }
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      for (int i = { 0 }; i < 3; i++) {
        axis &currentAxis = allAxis.at(i);
        currentAxis.pop_front();
        currentAxis.push_back(ypr[i] * 180 / M_PI);
        float min;
        float max;
        float middle{ 0 };
        for (auto &val : currentAxis) {
          max = (val > max) ? val : max;
          max = (val < min) ? val : max;
          middle += val;
        }
        filteredValues.at(i) = middle * 100;
      }

      analogWrite(A1, map(abs(filteredValues.at(0)) * 10, 0, 35, 200, 1024));
      analogWrite(A2, map(abs(filteredValues.at(1)) * 10, 0, 35, 200, 1024));
      analogWrite(A3, map(abs(filteredValues.at(2)) * 10, 0, 35, 200, 1024));

      mpuTime = time;
    }
  }
  if (!broadcastState && joystickTime - time < 0.05) {

    if (axisState) {
      joystick.setXAxis(filteredValues.at(2) - offsets.at(2));
      joystick.setYAxis(filteredValues.at(1) - offsets.at(1));
      joystick.setZAxis(filteredValues.at(0) - offsets.at(0));
    } else if (!axisState) {
      joystick.setRxAxis(filteredValues.at(2) - offsets.at(2));
      joystick.setRyAxis(filteredValues.at(1) - offsets.at(1));
      joystick.setRzAxis(filteredValues.at(0) - offsets.at(0));
    }
    joystick.sendState();
    joystickTime = time;
  }
  if (!broadcastState) {
    Serial.print("pushed");
  } else {
    Serial.print("notpushed");
  }
  Serial.print('\t');

  Serial.print(millis());
  Serial.print('\t');
  for (auto i = 0; i < 3; i++) {
    Serial.print(filteredValues.at(i) - offsets.at(i));
    Serial.print('\t');
  }
  Serial.print(axisState);
  Serial.print('\t');
  Serial.println(broadcastState);
}
