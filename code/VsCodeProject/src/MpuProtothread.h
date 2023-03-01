#ifndef MPU_PROTOTHREAD
#define MPU_PROTOTHREAD
#include <Protothread.h>

#ifndef ARDUINO
#include <mocks/MPU6050Mock.h>
typedef MPU6050Mock MPU6050;
#endif // !ARDUINO


class MpuStrategy
{
public:
    virtual ~MpuStrategy() = default;
    virtual void execute(uint8_t *fifoBuffer, Quaternion q, VectorFloat gravity, float *ypr, MPU6050 &mpu) = 0;
};

class MpuProtothread : public Protothread
{
private:
    uint8_t fifoBuffer[64]; // FIFO storage buffer
    Quaternion q;           // [w, x, y, z]         quaternion container
    VectorFloat gravity;    // [x, y, z]            gravity vector
    float ypr[3];
    MPU6050 *mpu;
    MpuStrategy *strat;

public:
    void setStrategy(MpuStrategy *newStrat)
    {
        strat = newStrat;
    }
    MpuProtothread(MPU6050 *mpuPointer)
    {
        mpu = mpuPointer;
        ypr[0] = 0;
        ypr[1] = 0;
        ypr[2] = 0;
    }
    void operation() override
    {
        strat->execute(fifoBuffer, q, gravity, ypr, *mpu);
    }
    float *yawPitchRollGetter()
    {
        return ypr;
    }
    ~MpuProtothread()
    {
        delete strat;
    }
};

class ReadMPU : public MpuStrategy
{
public:
    void execute(uint8_t *fifoBuffer, Quaternion q, VectorFloat gravity, float *ypr, MPU6050 &mpu) override
    {
        if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
        {
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            // currentAxis.push_back(ypr[i] * 180 / M_PI);
        }
    }
};

class OutputZero : public MpuStrategy
{
public:
    void execute(uint8_t *fifoBuffer, Quaternion q, VectorFloat gravity, float *ypr, MPU6050 &mpu) override
    {
        ypr[0] = 0;
        ypr[1] = 0;
        ypr[2] = 0;
    }
};

#endif // !MPU_PROTOTHREAD
