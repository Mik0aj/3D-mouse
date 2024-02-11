#ifndef RGB_PROTOTHREAD
#define RGB_PROTOTHREAD
#include <mocks/ArduinoMock.h>

class RGBStrategy
{
public:
    virtual ~RGBStrategy() = default;
    virtual void execute(int redPin, int greenPin, int bluePin) = 0;
};

class RGBProtohread : public Protothread
{
private:
    int red, green, blue;
    RGBStrategy *strat;

public:
    void setStrategy(RGBStrategy *newStrat)
    {
        strat = newStrat;
    }
    RGBProtohread(int redPin, int greenPin, int bluePin)
    {
        red = redPin;
        green = greenPin;
        blue = bluePin;
    }
    void operation() override
    {
        strat->execute(ypr, *j);
    }
    ~RGBProtohread()
    {
        delete strat;
    }
};

class RGBCalculatedValues : RGBStrategy
{
public:
    void execute(int redPin, int greenPin, int bluePin)
    {
        analogWrite(redPin, calculated);
        analogWrite(greenPin, calculated);
        analogWrite(bluePin, calculated);
 
    }
};

#endif // !RGB_PROTOTHREAD