#ifndef ARDUINO_MOCK
#define ARDUINO_MOCK

int analogRead(uint8_t pin);
void analogReference(uint8_t mode);
void analogWrite(uint8_t pin, int val);
int atexit(void (*func)()) __attribute__((weak));
void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode);
void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);
void detachInterrupt(uint8_t interruptNum);
int digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t val);
void init(void);
void initVariant(void);
void loop(void);
uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);
long map(long, long, long, long, long);
unsigned long micros(void);
unsigned long millis(void);
void noTone(uint8_t _pin);
void pinMode(uint8_t pin, uint8_t mode);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
long random(long);
long random(long, long);
void randomSeed(unsigned long);
void setup(void);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0);
void yield(void);

#endif // !ARDUINO_MOCK