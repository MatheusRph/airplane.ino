//Bibliotecas importadas
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h> 

//Definições do wireless

RF24 radio(12,11);  //Define os pinos do módulo

const uint64_t endereco = 0xE8E8F0F0E1LL;     //Define o endereço do módulo NRF24

//Definições dos joysticks
int joyX = A0;      //seta a porta do joystick(eixo X)
int joyY = A1;      // Seta a porta do joystick(eixo Y)

// //Cria uma estrutura com bytes
struct Dados_para_enviar {
    byte ch1;
    byte ch2;
    byte ch3;
};

// //Cria uma variavel para dados_para_enviar
Dados_para_enviar dados_enviados;

void setup() {
    radio.begin();  //Inicializa a comunicação wireless
    radio.openWritingPipe(endereco);    //Define o endereço da comunicação so receptor 
    radio.setPALevel(RF24_PA_HIGH); //Define a potência do transmissor
    radio.setDataRate(RF24_2MBPS);  //Define a velocidade de transmissão do módulo
    radio.stopListening(); //Define o módulo transmissor para não receber dados

    //Define os valores padrões dos canais
    dados_enviados.ch1 = 127;
    dados_enviados.ch2 = 127;
    dados_enviados.ch3 = 127;
}


void loop() {

    //Define a leitura analógica dos joysticks
    int joyXVal = analogRead(joyX); 
    int joyYVal = analogRead(joyY);

    dados_enviados.ch1 = map(joyXVal, 0, 1023, 255, 0);
    dados_enviados.ch2 = map(joyYVal, 0, 1023, 255, 0);

    //Escrevendo ou seja enviando os dados da leitura feitos acima do joystick
    radio.write(&dados_enviados, sizeof(Dados_para_enviar));
}