#ifndef JOYSTICK_PROTOTHREAD
#define JOYSTICK_PROTOTHREAD
#ifndef ARDUINO
#include <mocks/MPU6050Mock.h>
typedef MPU6050Mock MPU6050;
#endif // !ARDUINO
#include <JoystickEmulator.h>

class JoystickStrategy
{
public:
    virtual ~JoystickStrategy() = default;
    virtual void execute(const float *ypr, JoystickEmulator &joystick) = 0;
};

class JoystickProtothread : public Protothread
{
private:
    const float *ypr;
    JoystickEmulator *j;
    JoystickStrategy *strat;

public:
    void setStrategy(JoystickStrategy *newStrat)
    {
        strat = newStrat;
    }
    JoystickProtothread(const float *yawPitchRollArray, JoystickEmulator &joystick)
    {
        ypr = yawPitchRollArray;
        j = &joystick;
    }
    void operation() override
    {
        strat->execute(ypr, *j);
    }
    ~JoystickProtothread()
    {
        delete strat;
    }
};

class XYZ : public JoystickStrategy
{
    void execute(const float *ypr, JoystickEmulator &joystick)
    {
        for (int setterIndex = 0; setterIndex < 3; setterIndex++)
        {
            joystick.setXYZ(setterIndex, ypr[setterIndex]);
        }
    }
};

class RXRYRZ : public JoystickStrategy
{
    void execute(const float *ypr, JoystickEmulator &joystick)
    {
        for (int setterIndex = 0; setterIndex < 3; setterIndex++)
        {
            joystick.setRXRYRZ(setterIndex, ypr[setterIndex]);
        }
    }
};

class DoNothing : public JoystickStrategy
{
    void execute(const float *ypr, const JoystickEmulator &joystick) {}
};

#endif // !JOYSTICK_PROTOTHREAD