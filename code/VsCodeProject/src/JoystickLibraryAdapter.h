#ifndef JOYSTICK_LIBRARY_ADAPTER
#define JOYSTICK_LIBRARY_ADAPTER
#include <JoystickEmulator.h>
#include <array>
#ifdef ARDUINO
#include <ArduinoSTL.h>
#endif
#include <mocks/JoystickInterface.h>

class JoystickLibraryAdapter : public JoystickEmulator
{
    std::array<void (JoystickInterface::*)(int32_t), 3> joystickXYZsetters;
    std::array<void (JoystickInterface::*)(int32_t), 3> joystickRXRYRZsetters;
    JoystickInterface *joystick;

public:
    JoystickLibraryAdapter(JoystickInterface &j)
    {
        joystick = &j;
        // axis numbers set to my preference
        joystickXYZsetters.at(2) = &JoystickInterface::setXAxis;
        joystickXYZsetters.at(1) = &JoystickInterface::setYAxis;
        joystickXYZsetters.at(0) = &JoystickInterface::setZAxis;
        joystickRXRYRZsetters.at(0) = &JoystickInterface::setRxAxis;
        joystickRXRYRZsetters.at(1) = &JoystickInterface::setRyAxis;
        joystickRXRYRZsetters.at(2) = &JoystickInterface::setRzAxis;
    }

    void setXYZ(int index, long value)
    {
        (joystick->*joystickXYZsetters.at(index))(value);
    }
    void setRXRYRZ(int index, long value)
    {
        (joystick->*joystickRXRYRZsetters.at(index))(value);
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
        joystick->setZAxisRange(MIN_Y, MAX_Y);
    }
    void setZAxisRange(int MIN_Z, int MAX_Z)
    {
        joystick->setYAxisRange(MIN_Z, MAX_Z);
    }

    void setRxAxisRange(int MIN_X, int MAX_X)
    {
        joystick->setRxAxisRange(MIN_X, MAX_X);
    }
    void setRyAxisRange(int MIN_Y, int MAX_Y)
    {
        joystick->setRzAxisRange(MIN_Y, MAX_Y);
    }
    void setRzAxisRange(int MIN_Z, int MAX_Z)
    {
        joystick->setRyAxisRange(MIN_Z, MAX_Z);
    }
    ~JoystickLibraryAdapter(){};
};

#endif // JOYSTICK_LIBRARY_ADAPTER