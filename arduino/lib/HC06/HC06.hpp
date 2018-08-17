#ifndef HC_06
#define HC_06
#include <Arduino.h>
#include <SoftwareSerial.h>

class HC06 {
    private:
        byte hc_tx, hc_rx;
        long baud;
        SoftwareSerial *bt;
        char end_char = '\n';
        bool activated = false;
    public:
        HC06();
        HC06(const byte tx, const byte rx);
        ~HC06();
        void set_tx(const byte tx);
        void set_rx(const byte rx);
        void begin(const long baud=9600);
        String read();
        void write(const String msg);
};
#endif
