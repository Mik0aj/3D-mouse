#ifndef XINPUT_MOCK
#define XINPUT_MOCK
#include <gmock/gmock.h>
#include <mocks/XInputInterface.h>
class XInputMock : public XInputInterface
{
public:
    MOCK_METHOD(void, setJoystickX, (XInputControl joy, int32_t x, boolean invert), (override));
    MOCK_METHOD(void, setJoystickY, (XInputControl joy, int32_t y, boolean invert), (override));
    MOCK_METHOD(void, begin, (), (override));
    MOCK_METHOD(int, send, (), (override));
    MOCK_METHOD(void, setRange, (XInputControl ctrl, int32_t rangeMin, int32_t rangeMax), (override));
};
// extern XInputMock XInput;
#endif // XINPUT_MOCK