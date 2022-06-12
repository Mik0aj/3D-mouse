
#include "ArduinoDummy.h"

namespace ArduinoDummy{
    void delay(int time){
        usleep(time * 1000);//need to multiply by 1000 to have delay in miliseconds like in arduino
    };
}