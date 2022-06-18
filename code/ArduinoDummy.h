#ifndef CODE_ARDUINODUMMY_H
#define CODE_ARDUINODUMMY_H

#include<unistd.h>
#include <string>
#include "iostream"

namespace ArduinoDummy {
    const int HIGH = 1;
    const int LOW = 0;
    // Analog pins
    const int A0=14;
    const int A1=15;
    const int A2=16;
    const int A3=17;
    const int A4=18;
    const int A5=19;

    void delay(int time);

    void pinMode();

    class SerialDummy {
    public:
        int baud;

        void begin(int baud);

        void println(std::string val);

        void print(std::string val);

        void write(std::string val);

    private:
        bool checkBaud();
    };

    class ArduinoDummyUno {

    protected:
        SerialDummy Serial;
    public:
        virtual void setup();

        virtual void loop();

        virtual void run();
    };
}

#endif //CODE_ARDUINODUMMY_H
