#include "HC06.hpp"

HC06::HC06(const byte tx, const byte rx){
    hc_tx = tx;
    hc_rx = rx;
    delete_bt();
}

HC06::~HC06(){
    delete_bt();
}

void HC06::delete_bt(){
    if(bt != nullptr){
        delete bt;
        bt = nullptr;
    }
}

void HC06::set_tx(const byte tx){
    hc_tx = tx;
    activated = false;
    delete_bt();
}

void HC06::set_rx(const byte rx){
    hc_rx = rx;
    activated = false;
    delete_bt();
}

void HC06::begin(const long baud){
    bt = new SoftwareSerial(hc_tx, hc_rx);
    delay(15);
    this->baud = baud;
    bt->begin(this->baud);
    activated = true;
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
    //Serial.println("HC06 write( " + msg + " )");
    if(activated){
        //Serial.println("Serial -> " + msg + " -> HC06");
        bt->print(msg);
    } else {
        //Serial.println("activar el HC06");
        begin();
        write(msg);
    }
}
