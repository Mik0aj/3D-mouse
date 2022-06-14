#ifndef CODE_SERIALDUMMY_H
#define CODE_SERIALDUMMY_H


class SerialDummy {
public:
     int baud;
     void begin(int baud);
     void println(std::string val);
     void print(std::string val);
     void write(std::string val);
private:
    bool checkBaud() const;
};


#endif //CODE_SERIALDUMMY_H
