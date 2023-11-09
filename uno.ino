//Bibliotecas importadas
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h> 

//Definições do wireless

RF24 radio(12,11);  //Define os pinos do módulo

const uint64_t endereco = 0xE8E8F0F0E1LL;     //Define o endereço do módulo NRF24

//Definições dos joysticks
int joyX = A2;      //Seta a porta do joystick(eixo X)  Flaps
int joyY = A1;      //Seta a porta do joystick(eixo Y) - Profunder
int joyL = A0;      //Seta a porta do joystick - Lemo
int poten = A4;     //Seta a porta do potenciomentro responsável pela aceleração

//Cria uma estrutura com bytes
struct Dados_para_enviar {
    byte ch1;   //Flap Direita
    byte ch2;   //Flap Esquerda
    byte ch3;   //Profunder
    byte ch4;   //Lemo
    byte ch5;   //Acelerador
    byte ch6;   //Botão
};

//Cria uma variavel para dados_para_enviar
Dados_para_enviar dados_enviados;

void setup() {
    radio.begin();  //Inicializa a comunicação wireless
    radio.setAutoAck(false)
    radio.openWritingPipe(endereco);    //Define o endereço da comunicação do receptor 
    radio.setPALevel(RF24_PA_HIGH); //Define a potência do transmissor
    radio.setDataRate(RF24_2MBPS);  //Define a velocidade de transmissão do módulo
    radio.stopListening(); //Define o módulo transmissor para não receber dados

    //Define os valores padrões dos canais
    dados_enviados.ch1 = 127;
    dados_enviados.ch2 = 127;
    dados_enviados.ch3 = 127;
    dados_enviados.ch4 = 127;
    dados_enviados.ch5 = 0;
}


void loop() {

    //Define a leitura analógica dos joysticks
    int joyXVal = analogRead(joyX); 
    int joyYVal = analogRead(joyY);
    int joyLVal = analogRead(joyL);
   
    //Faz a leitura do potenciomentro
    int potenVal = analogRead(poten); 

    dados_enviados.ch1 = map(joyXVal, 0, 1023, 255, 0);
    dados_enviados.ch2 = map(joyXVal, 0, 1023, 0, 255);
    dados_enviados.ch3 = map(joyYVal, 0, 1023, 255, 0);
    dados_enviados.ch4 = map(joyLVal, 0, 1023, 255, 0);
    dados_enviados.ch5 = map(potenVal, 0, 1023, 255, 0);

    //Escrevendo ou seja enviando os dados da leitura feitos acima do joystick
    radio.write(&dados_enviados, sizeof(Dados_para_enviar));
}