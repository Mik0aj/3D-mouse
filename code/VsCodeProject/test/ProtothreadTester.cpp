#include <gtest/gtest.h>
#include <Protothread.h>
#include <thread>
#include <mocks/MPU6050Mock.h>
#include <MpuProtothread.h>
#include <JoystickProtothread.h>
#include <JoystickLibraryAdapter.h>
#include <mocks/JoystickMock.h>
// TEST(MyTimer, ConstructorTest)
// {
//     constexpr unsigned long EXPECTED{25};
//     std::this_thread::sleep_for(std::chrono::milliseconds(EXPECTED));
//     EXPECT_LE(millis(), EXPECTED);
// }

TEST(MPUProtothreadTests, SetOffsetsEqualToZero)
{
    float ypr[3]{0, 0, 0};
    float calculated[3];
    float offsets[3]{1, 1, 1};
    SetOffsets unitUnderTest;
    unitUnderTest.execute(ypr, offsets, calculated);
    EXPECT_EQ(ypr[0], offsets[0]);
    EXPECT_EQ(ypr[1], offsets[1]);
    EXPECT_EQ(ypr[2], offsets[2]);
}


TEST(MPUProtothreadTests, OperationCallback)
{                                           
    MPU6050 mpu;                            
    MpuProtothread unitUnderTest(&mpu);     
    unitUnderTest.setStrategy(new SetOffsets);
    unitUnderTest.operation();              
}

TEST(MPUProtothreadTests, SetOffsetThanCalculateEqualZero)
{
    constexpr float EXPECTED{0};
    float ypr[3]{0, 0, 0};
    float calculated[3]{2, 2, 2};
    float offsets[3]{1, 1, 1};
    SetOffsets setOffsets;
    setOffsets.execute(ypr, offsets, calculated);
    Calculate calculate;
    calculate.execute(ypr, offsets, calculated);
    EXPECT_EQ(calculated[0], EXPECTED);
    EXPECT_EQ(calculated[1], EXPECTED);
    EXPECT_EQ(calculated[2], EXPECTED);
}

TEST(ProtothreadTests, RunFunctionInTheLoop)
{
    struct ProtothreadTester : Protothread
    {
        int count{0};
        void operation() override
        {
            count++;
        }
    };
    ProtothreadTester unitUnderTest;
    unsigned long int timer = millis();
    while (millis() - timer < 50)
    {
        unitUnderTest.run();
    }
    EXPECT_GT(unitUnderTest.count, 1);
}

TEST(JoystickProtothreadTests, XYZStrategyCallingJoystickAdapter)
{
    constexpr float EXPECTED{1};
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    float ypr[3];
    ypr[0] = EXPECTED;
    ypr[1] = EXPECTED;
    ypr[2] = EXPECTED;
    JoystickProtothread unitUnderTest(ypr, joystick);
    unitUnderTest.setStrategy(new XYZ);
    EXPECT_CALL(j, setXAxis(EXPECTED)).Times(1);
    EXPECT_CALL(j, setYAxis(EXPECTED)).Times(1);
    EXPECT_CALL(j, setZAxis(EXPECTED)).Times(1);
    unitUnderTest.operation();
}

TEST(JoystickProtothreadTests, RXRYRZStrategyCallingJoystickAdapter)
{
    constexpr float EXPECTED{1};
    JoystickMock j;
    JoystickEmulator &&joystick = JoystickLibraryAdapter(j);
    float ypr[3];
    ypr[0] = EXPECTED;
    ypr[1] = EXPECTED;
    ypr[2] = EXPECTED;
    JoystickProtothread unitUnderTest(ypr, joystick);
    unitUnderTest.setStrategy(new RXRYRZ);
    EXPECT_CALL(j, setRxAxis(EXPECTED)).Times(1);
    EXPECT_CALL(j, setRyAxis(EXPECTED)).Times(1);
    EXPECT_CALL(j, setRzAxis(EXPECTED)).Times(1);
    unitUnderTest.operation();
}