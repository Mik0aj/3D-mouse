#ifndef MPU_INTERFACE
#define MPU_INTERFACE

class Quaternion;
class VectorFloat;

class MPUInterface
{
public:
    virtual ~MPUInterface(){};
    virtual uint8_t dmpGetCurrentFIFOPacket(uint8_t *data) = 0;
    virtual uint8_t dmpGetQuaternion(Quaternion *q, const uint8_t *packet) = 0;
    virtual uint8_t dmpGetGravity(VectorFloat *v, Quaternion *q) = 0;
    virtual uint8_t dmpGetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity) = 0;
};

#endif // MPU_INTERFACE