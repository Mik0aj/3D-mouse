#ifndef JOYSTICK_MOCK
#define JOYSTICK_MOCK
#include <gmock/gmock.h>
#include <mocks/JoystickInterface.h>

class JoystickMock : public JoystickInterface
{
public:
    MOCK_METHOD(void, begin, (bool initAutoSendState), (override));
    MOCK_METHOD(void, end, (), (override));
    MOCK_METHOD(void, pressButton, (uint8_t button));
    MOCK_METHOD(void, releaseButton, (uint8_t button), (override));
    MOCK_METHOD(void, sendState, (), (override));
    MOCK_METHOD(void, setAccelerator, (int32_t value), (override));
    MOCK_METHOD(void, setBrake, (int32_t value), (override));
    MOCK_METHOD(void, setButton, (uint8_t button, uint8_t value), (override));
    MOCK_METHOD(void, setHatSwitch, (int8_t hatSwitch, int16_t value), (override));
    MOCK_METHOD(void, setRudder, (int32_t value), (override));
    MOCK_METHOD(void, setXAxis, (int32_t value), (override));
    MOCK_METHOD(void, setYAxis, (int32_t value), (override));
    MOCK_METHOD(void, setZAxis, (int32_t value), (override));
    MOCK_METHOD(void, setRxAxis, (int32_t value), (override));
    MOCK_METHOD(void, setRyAxis, (int32_t value), (override));
    MOCK_METHOD(void, setRzAxis, (int32_t value), (override));
    MOCK_METHOD(void, setRxAxisRange, (int32_t MIN_X, int32_t MAX_X), (override));
    MOCK_METHOD(void, setRyAxisRange, (int32_t MIN_Y, int32_t MAX_Y), (override));
    MOCK_METHOD(void, setRzAxisRange, (int32_t MIN_Z, int32_t MAX_Z), (override));
    MOCK_METHOD(void, setXAxisRange, (int32_t MIN_X, int32_t MAX_X), (override));
    MOCK_METHOD(void, setYAxisRange, (int32_t MIN_Y, int32_t MAX_Y), (override));
    MOCK_METHOD(void, setZAxisRange, (int32_t MIN_Z, int32_t MAX_Z), (override));
    MOCK_METHOD(void, setSteering, (int32_t value), (override));
    MOCK_METHOD(void, setThrottle, (int32_t value), (override));
};

#endif // JOYSTICK_MOCK