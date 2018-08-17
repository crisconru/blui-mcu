#include "HC06.hpp"

HC06::HC06(){}

HC06::HC06(const byte tx, const byte rx){
    hc_tx = tx;
    hc_rx = rx;
}

HC06::~HC06(){}

void HC06::set_tx(const byte tx){
    hc_tx = tx;
    activated = false;
}

void HC06::set_rx(const byte rx){
    hc_rx = rx;
    activated = false;
}

void HC06::begin(const long baud){
    bt = new SoftwareSerial(hc_tx, hc_rx);
    delay(15);
    this->baud = baud;
    bt->begin(this->baud);
    activated = true;
    Serial.println("BT -> activado");
}

String HC06::read(){
    if(activated){
        String msg = "";
        while(bt->available()){
            msg += (char)bt->read();
        }
        return msg;
    } else {
        begin();
        return read();
    }
    
}

void HC06::write(String msg){
    if(activated){
        bt->print(msg);
    } else {
        begin();
        write(msg);
    }
}
