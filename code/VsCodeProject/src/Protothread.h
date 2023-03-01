#ifndef PROTOTHREAD
#define PROTOTHREAD

#include <pt.h>
#ifndef ARDUINO
#include <chrono>

class myTimer
{
public:
    myTimer() { start = std::chrono::steady_clock::now(); }
    unsigned long operator()()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        ;
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> start;
};

myTimer millis;
#endif

class Protothread
{
    unsigned long threadTimer{10};
    unsigned long timer{0};
    pt thread;

public:
    Protothread() {}
    Protothread(const Protothread &p)
    {
        threadTimer = p.threadTimer;
        thread = p.thread;
    };
    void setThreadTimer(unsigned long newTimer)
    {
        threadTimer = newTimer;
    }
    void init()
    {
        PT_INIT(&thread);
    }
    void run()
    {
        PT_BEGIN(&thread);
        while (1)
        {
            timer = millis();
            PT_WAIT_UNTIL(&thread, millis() - timer > threadTimer);
            operation();
        }
        PT_END(&thread);
    }
    virtual void operation() = 0;
};

#endif // PROTOTHREAD