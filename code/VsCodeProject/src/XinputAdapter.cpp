#include <XinputAdapter.h>

void XinputAdapter::setXYZ(int index, long value)
{
    switch (index)
    {
    case 0:
        XInput.setJoystickX(JOY_LEFT, value, false);
        break;
    case 1:
        XInput.setJoystickY(JOY_LEFT, value, false);
        break;
    case 2:
        XInput.setTrigger(TRIGGER_LEFT, value);
        break;
    default:
        break;
    }
}

void XinputAdapter::setRXRYRZ(int index, long value)
{
    switch (index)
    {
    case 0:
        XInput.setJoystickX(JOY_RIGHT, value, false);
        break;
    case 1:
        XInput.setJoystickY(JOY_RIGHT, value, false);
        break;
    case 2:
        XInput.setTrigger(TRIGGER_RIGHT, value);
        break;
    default:
        break;
    }
}

void XinputAdapter::begin()
{
    XInput.begin();
}

void XinputAdapter::send()
{
    XInput.send();
}

void XinputAdapter::setXAxisRange(int MIN_X, int MAX_X)
{
    XInput.setRange(JOY_LEFT, MIN_X, MAX_X);
}
void XinputAdapter::setYAxisRange(int MIN_X, int MAX_X)
{
    XInput.setRange(JOY_LEFT, MIN_X, MAX_X);
}
void XinputAdapter::setZAxisRange(int MIN_X, int MAX_X)
{
    XInput.setRange(TRIGGER_LEFT, MIN_X, MAX_X);
}

void XinputAdapter::setRxAxisRange(int MIN_X, int MAX_X)
{
    XInput.setRange(JOY_RIGHT, MIN_X, MAX_X);
}
void XinputAdapter::setRyAxisRange(int MIN_X, int MAX_X)
{
    XInput.setRange(JOY_RIGHT, MIN_X, MAX_X);
}
void XinputAdapter::setRzAxisRange(int MIN_X, int MAX_X)
{
    XInput.setRange(TRIGGER_RIGHT, MIN_X, MAX_X);
}