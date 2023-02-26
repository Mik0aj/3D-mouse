#ifndef XINPUT_INTERFACE
#define XINPUT_INTERFACE

typedef bool boolean;

enum XInputControl : uint8_t
{
    BUTTON_LOGO = 0,
    BUTTON_A = 1,
    BUTTON_B = 2,
    BUTTON_X = 3,
    BUTTON_Y = 4,
    BUTTON_LB = 5,
    BUTTON_RB = 6,
    BUTTON_BACK = 7,
    BUTTON_START = 8,
    BUTTON_L3 = 9,
    BUTTON_R3 = 10,
    DPAD_UP = 11,
    DPAD_DOWN = 12,
    DPAD_LEFT = 13,
    DPAD_RIGHT = 14,
    TRIGGER_LEFT = 15,
    TRIGGER_RIGHT = 16,
    JOY_LEFT,
    JOY_RIGHT,
};

class XInputInterface
{
public:
    virtual ~XInputInterface(){};
    virtual void setJoystickX(XInputControl joy, int32_t x, boolean invert = false) = 0;
    virtual void setJoystickY(XInputControl joy, int32_t y, boolean invert = false) = 0;
    virtual void begin() = 0;
    virtual int send() = 0;
    virtual void setRange(XInputControl ctrl, int32_t rangeMin, int32_t rangeMax) = 0;
};

#endif // XINPUT_INTERFACE