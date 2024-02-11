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
    virtual void execute(float *ypr, float *offsets, float *calculated) = 0;
};

class MpuProtothread : public Protothread
{
private:
    uint8_t fifoBuffer[64]; // FIFO storage buffer
    Quaternion q;           // [w, x, y, z]         quaternion container
    VectorFloat gravity;    // [x, y, z]            gravity vector
    float ypr[3]{0};
    float calculated[3]{0};
    float offsets[3]{0};
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
    }
    void operation() override
    {
        if (mpu->dmpGetCurrentFIFOPacket(fifoBuffer))
        {
            mpu->dmpGetQuaternion(&q, fifoBuffer);
            mpu->dmpGetGravity(&gravity, &q);
            mpu->dmpGetYawPitchRoll(ypr, &q, &gravity);
            // currentAxis.push_back(ypr[i] * 180 / M_PI);
            strat->execute(ypr, offsets, calculated);
        }
    }
    const float *calculatedGetter()
    {
        return ypr;
    }
    ~MpuProtothread()
    {
        delete strat;
    }
};

class Calculate : public MpuStrategy
{
public:
    void execute(float *ypr, float *offsets, float *calculated) override
    {
        calculated[0] = ypr[0] - offsets[0];
        calculated[1] = ypr[1] - offsets[1];
        calculated[2] = ypr[2] - offsets[2];
    }
};

class SetOffsets : public MpuStrategy
{
public:
    void execute(float *ypr, float *offsets, float *calculated) override
    {
        offsets[0] = ypr[0];
        offsets[1] = ypr[1];
        offsets[2] = ypr[2];
    }
};

#endif // !MPU_PROTOTHREAD
