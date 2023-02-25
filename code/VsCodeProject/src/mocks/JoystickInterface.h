#ifndef JOYSTICK_INTERFACE
#define JOYSTICK_INTERFACE


class JoystickInterface
{
public:
    virtual ~JoystickInterface(){};
    virtual void begin(bool initAutoSendState = true)=0;
    virtual void end() = 0;
    virtual void pressButton(uint8_t button) = 0;
    virtual void releaseButton(uint8_t button) = 0;
    virtual void sendState() = 0;
    virtual void setAccelerator(int32_t value) = 0;
    virtual void setBrake(int32_t value) = 0;
    virtual void setButton(uint8_t button, uint8_t value) = 0;
    virtual void setHatSwitch(int8_t hatSwitch, int16_t value) = 0;
    virtual void setRudder(int32_t value) = 0;
    virtual void setRxAxis(int32_t value) = 0;
    virtual void setRyAxis(int32_t value) = 0;
    virtual void setRzAxis(int32_t value) = 0;
    virtual void setXAxis(int32_t value) = 0;
    virtual void setYAxis(int32_t value) = 0;
    virtual void setZAxis(int32_t value) = 0;
    virtual void setRxAxisRange(int32_t MIN_X, int32_t MAX_X) = 0;
    virtual void setRyAxisRange(int32_t MIN_Y, int32_t MAX_Y) = 0;
    virtual void setRzAxisRange(int32_t MIN_Z, int32_t MAX_Z) = 0;
    virtual void setXAxisRange(int32_t MIN_X, int32_t MAX_X) = 0;
    virtual void setYAxisRange(int32_t MIN_Y, int32_t MAX_Y) = 0;
    virtual void setZAxisRange(int32_t MIN_Z, int32_t MAX_Z) = 0;
    virtual void setSteering(int32_t value) = 0;
    virtual void setThrottle(int32_t value) = 0;
};

#endif // JOYSTICK_INTERFACE