#include <gtest/gtest.h>
#include <mocks/JoystickMock.h>
#include <JoystickLibraryAdapter.h>

TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInSetXYZ)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    constexpr int axisCount{3};
    EXPECT_CALL(j, setXAxis(0)).Times(testing::AtLeast(1));
    EXPECT_CALL(j, setYAxis(0)).Times(testing::AtLeast(1));
    EXPECT_CALL(j, setZAxis(0)).Times(testing::AtLeast(1));
    for (size_t axis = 0; axis < axisCount; axis++)
    {
        joystick.setXYZ(axis, 0);
    }
}

TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInSetRXRYRZ)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    constexpr int axisCount{3};
    EXPECT_CALL(j, setRxAxis(0)).Times(testing::AtLeast(1));
    EXPECT_CALL(j, setRyAxis(0)).Times(testing::AtLeast(1));
    EXPECT_CALL(j, setRzAxis(0)).Times(testing::AtLeast(1));
    for (size_t axis = 0; axis < axisCount; axis++)
    {
        joystick.setRXRYRZ(axis, 0);
    }
}

TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInSend)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    EXPECT_CALL(j, sendState()).Times(testing::AtLeast(1));
    joystick.send();
}

TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInBegin)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    EXPECT_CALL(j, begin(true)).Times(testing::AtLeast(1));
    joystick.begin();
}
TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInSetXAxisRange)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    EXPECT_CALL(j, setXAxisRange(1, 1)).Times(testing::AtLeast(1));
    joystick.setXAxisRange(1, 1);
}
TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInSetYAxisRange)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    EXPECT_CALL(j, setYAxisRange(1, 1)).Times(testing::AtLeast(1));
    joystick.setYAxisRange(1, 1);
}
TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInSetZAxisRange)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    EXPECT_CALL(j, setZAxisRange(1, 1)).Times(testing::AtLeast(1));
    joystick.setZAxisRange(1, 1);
}
TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInSetRXAxisRange)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    EXPECT_CALL(j, setRxAxisRange(1, 1)).Times(testing::AtLeast(1));
    joystick.setRxAxisRange(1, 1);
}
TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInSetRYAxisRange)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    EXPECT_CALL(j, setRyAxisRange(1, 1)).Times(testing::AtLeast(1));
    joystick.setRyAxisRange(1, 1);
}
TEST(JoystickLibraryAdapterTests, ProperMethodsBeingInvokedInSetRZAxisRange)
{
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    EXPECT_CALL(j, setRzAxisRange(1, 1)).Times(testing::AtLeast(1));
    joystick.setRzAxisRange(1, 1);
}