#ifndef XINPUT_ADAPTER
#define XINPUT_ADAPTER

#include <JoystickEmulator.h>
#include <mocks/XInputInterface.h>

class XInputAdapter : public JoystickEmulator
{
    XInputInterface *XInput;

public:
    XInputAdapter(XInputInterface &x)
    {
        XInput = &x;
    }
    void setXYZ(int index, long value)
    {
        switch (index)
        {
        case 0:
            XInput->setJoystickX(JOY_LEFT, value, false);
            break;
        case 1:
            XInput->setJoystickY(JOY_LEFT, value, false);
            break;
        case 2:
            //        XInput.setTrigger(TRIGGER_LEFT, value);
            break;
        default:
            break;
        }
    }

    void setRXRYRZ(int index, long value)
    {
        switch (index)
        {
        case 0:
            XInput->setJoystickX(JOY_RIGHT, value, false);
            break;
        case 1:
            XInput->setJoystickY(JOY_RIGHT, value, false);
            break;
        case 2:
            //        XInput.setTrigger(TRIGGER_RIGHT, value);
            break;
        default:
            break;
        }
    }

    void begin()
    {
        XInput->begin();
    }

    void send()
    {
        XInput->send();
    }

    void setXAxisRange(int MIN_X, int MAX_X)
    {
        XInput->setRange(JOY_LEFT, MIN_X, MAX_X);
    }
    void setYAxisRange(int MIN_X, int MAX_X)
    {
        XInput->setRange(JOY_LEFT, MIN_X, MAX_X);
    }
    void setZAxisRange(int MIN_X, int MAX_X)
    {
        XInput->setRange(TRIGGER_LEFT, MIN_X, MAX_X);
    }

    void setRxAxisRange(int MIN_X, int MAX_X)
    {
        XInput->setRange(JOY_RIGHT, MIN_X, MAX_X);
    }
    void setRyAxisRange(int MIN_X, int MAX_X)
    {
        XInput->setRange(JOY_RIGHT, MIN_X, MAX_X);
    }
    void setRzAxisRange(int MIN_X, int MAX_X)
    {
        XInput->setRange(TRIGGER_RIGHT, MIN_X, MAX_X);
    }
};

#endif // XINPUT_ADAPTER