#include <iostream>
#include "ArduinoDummy.h"

using namespace ArduinoDummy;

class SerialTest : ArduinoDummyUno {

    // This part of code can be copied into Arduino without modifying

    void setup() {
        Serial.begin(9600);
    };

    void loop() {
        Serial.println("hello ");
        delay(10000);
        Serial.println("world");
    };

    //

public:
    void run() {
        setup();
        loop();
    }
};


int main() {
    SerialTest test;
    test.run();
    return 0;
}
