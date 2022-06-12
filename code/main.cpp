#include <iostream>
#include "SerialDummy.h"
#include "ArduinoDummy.h"
using namespace ArduinoDummy;
SerialDummy Serial;


void setup(){
    Serial.begin(9600);
};

void loop(){
    Serial.println("hello");
    delay(1000);
    Serial.print("hello");
};


int main() {
    setup();
    loop();
    return 0;
}
