#include <gtest/gtest.h>
#include <mocks/XInputMock.h>
#include <XInputAdapter.h>

TEST(XInputAdapterTests, ProperMethodsBeingInvokedInSetXYZ)
{
    XInputMock XInput;
    JoystickEmulator &&joystick = XInputAdapter(XInput);
    constexpr int axisCount{3};
    EXPECT_CALL(XInput, setJoystickX(JOY_LEFT, 0, false)).Times(testing::AtLeast(1));
    EXPECT_CALL(XInput, setJoystickY(JOY_LEFT, 0, false)).Times(testing::AtLeast(1));
    for (size_t axis = 0; axis < axisCount; axis++)
    {
        joystick.setXYZ(axis, 0);
    }
}

TEST(XInputAdapterTests, ProperMethodsBeingInvokedInSetRXRYRZ)
{
    XInputMock XInput;
    JoystickEmulator &&joystick = XInputAdapter(XInput);
    constexpr int axisCount{3};
    EXPECT_CALL(XInput, setJoystickX(JOY_RIGHT, 0, false)).Times(testing::AtLeast(1));
    EXPECT_CALL(XInput, setJoystickY(JOY_RIGHT, 0, false)).Times(testing::AtLeast(1));

    for (size_t axis = 0; axis < axisCount; axis++)
    {
        joystick.setRXRYRZ(axis, 0);
    }
}

TEST(XInputAdapterTests, ProperMethodsBeingInvokedInSend)
{
    XInputMock XInput;
    JoystickEmulator &&joystick = XInputAdapter(XInput);
    EXPECT_CALL(XInput, send()).Times(testing::AtLeast(1));
    joystick.send();
}

TEST(XInputAdapterTests, ProperMethodsBeingInvokedInBegin)
{
    XInputMock XInput;
    JoystickEmulator &&joystick = XInputAdapter(XInput);
    EXPECT_CALL(XInput, begin()).Times(testing::AtLeast(1));
    joystick.begin();
}

TEST(XInputAdapterTests, ProperMethodsBeingInvokedInSetXAxisRange)
{
    XInputMock XInput;
    JoystickEmulator &&joystick = XInputAdapter(XInput);
    EXPECT_CALL(XInput, setRange(JOY_LEFT, 1, 1)).Times(testing::AtLeast(1));
    joystick.setXAxisRange(1, 1);
}

TEST(XInputAdapterTests, ProperMethodsBeingInvokedInSetYAxisRange)
{
    XInputMock XInput;
    JoystickEmulator &&joystick = XInputAdapter(XInput);
    EXPECT_CALL(XInput, setRange(JOY_LEFT, 1, 1)).Times(testing::AtLeast(1));
    joystick.setYAxisRange(1, 1);
}

TEST(XInputAdapterTests, ProperMethodsBeingInvokedInSetRXAxisRange)
{
    XInputMock XInput;
    JoystickEmulator &&joystick = XInputAdapter(XInput);
    EXPECT_CALL(XInput, setRange(JOY_RIGHT, 1, 1)).Times(testing::AtLeast(1));
    joystick.setRxAxisRange(1, 1);
}

TEST(XInputAdapterTests, ProperMethodsBeingInvokedInSetRYAxisRange)
{
    XInputMock XInput;
    JoystickEmulator &&joystick = XInputAdapter(XInput);
    EXPECT_CALL(XInput, setRange(JOY_RIGHT, 1, 1)).Times(testing::AtLeast(1));
    joystick.setRyAxisRange(1, 1);
}