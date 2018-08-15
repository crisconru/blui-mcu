#include <Arduino.h>
#include <HC06.hpp>

// HC05
#define HC05_EN  13
#define HC05_VCC 12
#define HC05_TX  11
#define HC05_RX  10
#define HC05_ST   9
// HC06
#define HC06_TX  14
#define HC06_RX  15
HC06 hc06(HC06_TX, HC06_RX);
// Variables
String msg;
// Funciones
String leer_serial();
char end_char = 'x';

void setup() {
    Serial.begin(9600);
    //hc06.set_tx(HC06_TX);
    //hc06.set_rx(HC06_RX);
    hc06.begin(9600);
    Serial.println("Enviar comandos AT");
}

void loop() {
    msg = hc06.read();
    if(msg != ""){
        Serial.println("BT -> " + msg);
    }
    if(Serial.available()){
        msg = leer_serial();
        Serial.println("Serial -> " + msg);
        hc06.write(msg);
    }
    delay(15);
    msg = "";
}

String leer_serial(){
    String m = "";
    char in_char;
    while(Serial.available()){
        in_char = (char)Serial.read();
        if(in_char != end_char){
            m += in_char;
        } else {
            break;
        }
    }
    return m;
}