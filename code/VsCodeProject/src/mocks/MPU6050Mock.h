#ifndef MPU6050_MOCK
#define MPU6050_MOCK
#include <gmock/gmock.h>
#include <mocks/MPUInterface.h>
class MPU6050Mock : public MPUInterface
{
public:
    MOCK_METHOD(uint8_t, dmpGetCurrentFIFOPacket, (uint8_t * data), (override));
    MOCK_METHOD(uint8_t, dmpGetQuaternion, (Quaternion * q, const uint8_t *packet), (override));
    MOCK_METHOD(uint8_t, dmpGetGravity, (VectorFloat * v, Quaternion *q), (override));
    MOCK_METHOD(uint8_t, dmpGetYawPitchRoll, (float *data, Quaternion *q, VectorFloat *gravity), (override));
};

#endif // MPU6050_MOCK