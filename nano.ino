//Bibliotecas adicionadas
#include <RF24.h>
#include <Servo.h>



//Definições dos servos - Profundor, Flaps, Aileron, Lemo
Servo FlapE;    //Define o nome do servo para FlapE
Servo FlapD;    //Define o nome do servo para FlapD
Servo Lemo;     //Define o nome do servo para Lemo

void setup(){

    FlapE.attach(9);  // Pino do FlapE
    FlapD.attach(10); // Pino do FlapD
    Lemo.attach(11);  // Pino do Lemo
}

void loop(){
    
}