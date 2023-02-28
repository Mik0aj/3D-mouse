#include <gtest/gtest.h>
#include <Protothread.h>
#include <thread>
#include <mocks/MPU6050Mock.h>

TEST(MyTimer, ConstructorTest)
{
    constexpr unsigned long EXPECTED {50};
    std::this_thread::sleep_for(std::chrono::milliseconds(EXPECTED));
    EXPECT_EQ(millis(), EXPECTED);
}

TEST(MPUProtothreadTests,ThreadConstruction)
{
    MPU6050Mock mpu;
    //MpuProtothread unitUnderTest(MPU6050 mpu);
}

