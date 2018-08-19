#include <Arduino.h>
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
// HC06
#define HC06_TX  14
#define HC06_RX  15
const char begin_06 = '*';
const char end_06 = '#';
boolean reading_06 = false;
boolean completed_06 = false;
HC06 hc06(HC06_TX, HC06_RX);
// Variables
String msg;
// Funciones
void leer_serial();
unsigned int nuevo_mensaje(const char c);
void mensaje_05();
void mensaje_06();

void setup() {
    Serial.begin(9600);
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

unsigned int nuevo_mensaje(const int c){
    unsigned int respuesta;
    switch(c){
        case begin_05:
        case end_05:
            respuesta = 5;
            break;
        case begin_06:
        case end_06:
            respuesta = 6;
            break;
        default:
            respuesta = 0;
    }
    return respuesta;
}

void mensaje_05(){
    String msg = "";
    char in_char;
    while(Serial.available()){
        in_char = (char)Serial.read();

    }
}

void mensaje_06(){
    String m = "";
    char in_char;
    while(Serial.available()){
        in_char = (char)Serial.read();
        switch(nuevo_mensaje(in_char)){
            case 5:

        }
            m += in_char;
        } else {

        }
    }
}

/* Si se manda mensaje de flag inicio 06
    si se recibe flag de inicio 06 -> reiniciar el mensaje
    si se recibe flag de fin    06 -> enviar el mensaje al HC-06
    si se recibe flags de 05       -> salir de la función y mandar leer el HC-05
    sino                           -> leer mensaje


void leer_serial(){
    String m = "";
    char in_char;
    while(Serial.available()){
        in_char = (char)Serial.read();
        switch(in_char){
            case begin_05:
                // Leer mensaje para HC-05
                Serial.println("Leyendo comando AT para HC-05 ...");
                break;
            case end_05:
                // Escribir mensaje a HC-05
                Serial.println("HC-05 <- " + m);
                break;
            case begin_06:
                // Leer mensaje HC-06
                Serial.println("Leyendo comando AT para HC-06 ...");
                reading_06 = true;
                break;
            case end_06:
                // Escribir mensaje a HC-06
                reading_06 = false;
                completed_06 = true;
                Serial.println("HC-06 <- " + m);
                hc06.write(msg);
                break;
            default:
                m += in_char;
        }
        if(reading_06 && completed_06 ){
            break;
        }
    }
    return m;
}