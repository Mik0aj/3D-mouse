#ifndef XINPUT_ADAPTER
#define XINPUT_ADAPTER

#include <JoystickEmulator.h>
#include <XInput.h>

class XinputAdapter : public JoystickEmulator
{
public:
    void setXYZ(int index, long value) override;
    void setRXRYRZ(int index, long value) override;
    void begin() override;
    void send() override;

    void setXAxisRange(int MIN_X, int MAX_X) override;
    void setYAxisRange(int MIN_X, int MAX_X) override;
    void setZAxisRange(int MIN_X, int MAX_X) override;

    void setRxAxisRange(int MIN_X, int MAX_X) override;
    void setRyAxisRange(int MIN_X, int MAX_X) override;
    void setRzAxisRange(int MIN_X, int MAX_X) override;
};

#endif // XINPUT_ADAPTER