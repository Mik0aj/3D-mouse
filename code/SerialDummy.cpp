#include <iostream>
#include "SerialDummy.h"

void SerialDummy::begin(int newbaud) {
    baud = newbaud;
}

void SerialDummy::println(std::string val) {
    if (checkBaud()){
        std::cout << val << std::endl;
    }
}

void SerialDummy::print(std::string val) {
    if (checkBaud()){
        std::cout << val;
    }
}

bool SerialDummy::checkBaud() const {
    try {
    switch (baud) {
        case 0:
            throw 0;
        case 300:
            return true;
        case 600:
            return true;
        case 1200:
            return true;
        case 2400:
            return true;
        case 4800:
            return true;
        case 9600:
            return true;
        case 14400:
            return true;
        case 19200:
            return true;
        case 28800:
            return true;
        case 38400:
            return true;
        case 57600:
            return true;
        case 115200:
            return true;
        default:
            throw baud;
    }
    }catch(int invalidbaud) {
        if (invalidbaud==0){
            std::cout << "Serial not started";
        }
        else{
            std::cout << "Invalid baud rate";
        }
    }
}

void SerialDummy::write(std::string val) {
    if (checkBaud()){
        std::cout << "Arduino write "<< val;
    }
}
