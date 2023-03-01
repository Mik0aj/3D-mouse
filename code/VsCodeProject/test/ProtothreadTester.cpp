#include <gtest/gtest.h>
#include <Protothread.h>
#include <thread>
#include <mocks/MPU6050Mock.h>
#include <MpuProtothread.h>
#include <iostream>
// TEST(MyTimer, ConstructorTest)
// {
//     constexpr unsigned long EXPECTED{25};
//     std::this_thread::sleep_for(std::chrono::milliseconds(EXPECTED));
//     EXPECT_LE(millis(), EXPECTED);
// }

TEST(MPUProtothreadTests, OutputZeroStrategyYawPitchRollValuesEqualZero)
{
    constexpr float EXPECTED{0};
    uint8_t fifoBuffer[64];
    Quaternion q;
    VectorFloat gravity;
    float ypr[3];
    MPU6050 mpu;
    OutputZero unitUnderTest;
    unitUnderTest.execute(fifoBuffer, q, gravity, ypr, mpu);
    EXPECT_EQ(ypr[0], EXPECTED);
    EXPECT_EQ(ypr[1], EXPECTED);
    EXPECT_EQ(ypr[2], EXPECTED);
}

TEST(MPUProtothreadTests, OperationCallback)
{
    MPU6050 mpu;
    MpuProtothread unitUnderTest(&mpu);
    unitUnderTest.setStrategy(new OutputZero());
    unitUnderTest.operation();
}

TEST(ProtothreadTests, RunFunctionInTheLoop)
{
    struct ProtothreadTester :  Protothread
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