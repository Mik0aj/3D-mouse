#ifndef JOYSTICK_LIBRARY_ADAPTER
#define JOYSTICK_LIBRARY_ADAPTER
#ifdef ARDUINO
#include <Joystick.h>
#endif
#include <JoystickEmulator.h>
#include <mocks/JoystickInterface.h>

typedef void (JoystickInterface::*Setter)(int32_t value);

class JoystickLibraryAdapter : public JoystickEmulator
{
    Setter joystickXYZsetters[3];
    Setter joystickRXRYRZsetters[3];
    JoystickInterface *joystick;

public:
    JoystickLibraryAdapter(JoystickInterface &j)
    {
        joystick = &j;
        joystickXYZsetters[0] = &JoystickInterface::setXAxis;
        joystickXYZsetters[1] = &JoystickInterface::setYAxis;
        joystickXYZsetters[2] = &JoystickInterface::setZAxis;
        joystickRXRYRZsetters[0] = &JoystickInterface::setRxAxis;
        joystickRXRYRZsetters[1] = &JoystickInterface::setRyAxis;
        joystickRXRYRZsetters[2] = &JoystickInterface::setRzAxis;
    }

    void setXYZ(int index, long value)
    {
        (joystick->*joystickXYZsetters[index])(value);
    }
    void setRXRYRZ(int index, long value)
    {
        (joystick->*joystickRXRYRZsetters[index])(value);
    }

    void send()
    {
        joystick->sendState();
    }
    void begin()
    {
        joystick->begin(true);
    }

    void setXAxisRange(int MIN_X, int MAX_X)
    {
        joystick->setXAxisRange(MIN_X, MAX_X);
    }
    void setYAxisRange(int MIN_Y, int MAX_Y)
    {
        joystick->setYAxisRange(MIN_Y, MAX_Y);
    }
    void setZAxisRange(int MIN_Z, int MAX_Z)
    {
        joystick->setZAxisRange(MIN_Z, MAX_Z);
    }

    void setRxAxisRange(int MIN_X, int MAX_X)
    {
        joystick->setRxAxisRange(MIN_X, MAX_X);
    }
    void setRyAxisRange(int MIN_Y, int MAX_Y)
    {
        joystick->setRyAxisRange(MIN_Y, MAX_Y);
    }
    void setRzAxisRange(int MIN_Z, int MAX_Z)
    {
        joystick->setRzAxisRange(MIN_Z, MAX_Z);
    }
    ~JoystickLibraryAdapter(){};
};

#endif // JOYSTICK_LIBRARY_ADAPTER