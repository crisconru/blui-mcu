#include <Arduino.h>
//#include <HC05.hpp>
#include <HC06.hpp>
// HC05
#define HC05_EN  13
#define HC05_VCC 12
#define HC05_TX  11
#define HC05_RX  10
#define HC05_ST   9
const char begin_05 = '/';
const char end_05 = '\\';
boolean reading_05 = false;
boolean completed_05 = true;
//HC05 hc05(HC05_EN, HC05_VCC, HC05_TX, HC05_RX, HC05_ST);
// HC06
#define HC06_TX  14
#define HC06_RX  15
const char begin_06 = '*';
const char end_06 = '#';
boolean reading_06 = false;
boolean completed_06 = false;
HC06 hc06(HC06_TX, HC06_RX);
// Variables
String msg, m;
// Funciones
String leer_serial();

void setup() {
    Serial.begin(9600);
    //hc05.begin(1200);
    //hc05.begin(2400);
    //hc05.begin(4800);
    //hc05.begin(9600);
    //hc05.begin(19200);
    //hc05.begin(38400);
    //hc05.begin(57600);
    //hc05.begin(115200);
    //Serial.println("HC-05 activado");
    hc06.begin(9600);
    Serial.println("HC-06 activado");
    Serial.println("Enviar comandos AT");
}

void loop() {
    // Leer respuesta del HC-06
    msg = hc06.read();
    if(msg != "")
        Serial.println("HC06 -> " + msg);
    /*
    // Leer respuesta del HC-05
    msg = hc05.read();
    if(msg != "")
        Serial.println("HC05 -> " + msg);
    */
    // Leer del Serial
    msg = leer_serial();
    if(msg != "")
        Serial.println(msg);
    delay(15);
}

String leer_serial(){
    //String m = "";
    char in_char;
    while(Serial.available()){
        in_char = (char)Serial.read();
        switch(in_char){
            /*
            case begin_05:
                // Leer mensaje para HC-05
                Serial.println("Leyendo comando AT para HC-05 ...");
                reading_05 = true;
                reading_06 = false;
                m = "";
                break;
            case end_05:
                // Escribir mensaje a HC-05
                Serial.println("HC-05 <- " + m);
                hc05.write(m);
                completed_05 = true;
                break;
            */
            case begin_06:
                // Leer mensaje HC-06
                Serial.println("Leyendo comando AT para HC-06 ...");
                reading_06 = true;
                reading_05 = false;
                m = "";
                break;
            case end_06:
                // Escribir mensaje a HC-06
                Serial.println("HC-06 <- " + m);
                hc06.write(m);
                completed_06 = true;
                break;
            default:
                m += in_char;
        }
        // Salir del bucle
        if(completed_05 || completed_06 ){
            m = "";
            reading_05 = false;
            completed_05 = false;
            reading_06 = false;
            completed_06 = false;
            break;
        }
    }
    return m;
}
