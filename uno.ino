//Bibliotecas importadas
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h> 

//Definições do wireless

RF24 radio(12,11);  //Define os pinos do módulo

const byte endereco[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0x12, 0x34};  //Define o endereço do módulo NRF24

//Definições dos joysticks
int joyX = A0;      //seta a porta do joystick(eixo X)
int joyY = A1;      // Seta a porta do joystick(eixo Y)

void setup() {
    radio.begin();  //Inicializa a comunicação wireless
    radio.openWritingPipe(endereco);    //Define o endereço da comunicação so receptor 
    radio.setPALevel(RF24_PA_HIGH); //Define a potência do transmissor
    radio.setDataRate(RF24_2MBPS);  //Define a velocidade de transmissão do módulo
    radio.stopListening(); //Define o módulo transmissor para não receber dados
}


void loop() {

    //Define a leitura analógica dos joysticks
    int joyXVal = analogRead(joyX); 
    int joyYVal = analogRead(joyY);

    //Escrevendo ou seja enviando os dados da leitura feitos acima do joystick
    radio.write(&joyXVal, sizeof(joyXVal)); 
    radio.write(&joyYVal, sizeof(joyYVal)); 
}