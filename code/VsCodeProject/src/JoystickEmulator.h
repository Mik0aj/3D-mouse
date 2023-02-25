
#ifndef JOYSTIC_EMULATOR
#define JOYSTIC_EMULATOR

class JoystickEmulator
{
public:
    virtual void setXYZ(int index, long value) = 0;
    virtual void setRXRYRZ(int index, long value) = 0;
    virtual void send() = 0;
    virtual void begin() = 0;

    virtual void setXAxisRange(int MIN_X, int MAX_X) = 0;
    virtual void setYAxisRange(int MIN_X, int MAX_X) = 0;
    virtual void setZAxisRange(int MIN_X, int MAX_X) = 0;

    virtual void setRxAxisRange(int MIN_X, int MAX_X) = 0;
    virtual void setRyAxisRange(int MIN_X, int MAX_X) = 0;
    virtual void setRzAxisRange(int MIN_X, int MAX_X) = 0;

    virtual ~JoystickEmulator(){};
};

#endif // JOYSTIC_EMULATOR