#include <iostream>
#include "SerialDummy.h"
#include "ArduinoDummy.h"
using namespace ArduinoDummy;

class SerialTest{

    // This part of code can be copied into Arduino without modifying

    void setup(){
        Serial.begin(9600);
    };

    void loop(){
        Serial.println("hello ");
        delay(10000);
        Serial.println("world");
    };

    //
    SerialDummy Serial;
    void before(){
        Serial=SerialDummy();
    }
public:
    void run(){
        before();
        setup();
        loop();
    }
};

class SerialTestNoBaud{

    // This part of code can be copied into Arduino without modifying

    void setup(){
        //Serial.begin(9600);
    };

    void loop(){
        Serial.println("TEST");
    };

    //
    SerialDummy Serial;
    void before(){
        Serial=SerialDummy();
    }
public:
    void run(){
        before();
        setup();
        loop();
    }
};

int main() {
    SerialTest test = SerialTest();
    test.run();
    SerialTestNoBaud test_two = SerialTestNoBaud();
    test_two.run();
    return 0;
}
