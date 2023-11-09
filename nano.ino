//Bibliotecas adicionadas
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h> 
#include <Servo.h>

//Definições wireless
RF24 radio(12,11);  //Define os pinos do módulo

const uint64_t endereco = 0xE8E8F0F0E1LL;     //Define o endereço do módulo NRF24

//Definições do motor


//Definições dos servos - Profundor, Flaps, Aileron, Lemo
Servo flapE;    //Define o nome do servo para FlapE
Servo flapD;    //Define o nome do servo para FlapD
servo profunder;    //Define o nome do servo para Profunder
Servo lemo;     //Define o nome do servo para Lemo

//Estrutura (função Dados recebidos)
struct Dados_recebidos{
    byte ch1;   //Flap Direita
    byte ch2;   //Flap Esquerda
    byte ch3;   //Profunder
    byte ch4;   //Lemo
    byte ch5;   //Acelerador
}

//Cria uma variavel para Dados_recebidos
Dados_recebidos dados_recebidos;

//Cria uma variável para armazenar os valores recebidos
int flapD_value = 0;
int lemo_value = 0;
int flapE_value = 0;
int prof_value = 0;
int acel_value = 0;

//Cria a função redefinir dados
void redefinir_dados(){
    //Redefini os dados
    dados_recebidos.ch1 = 127;
    dados_recebidos.ch2 = 127;
    dados_recebidos.ch3 = 127;
    dados_recebidos.ch4 = 127;
    dados_recebidos.ch5 = 0;
}

void setup(){
    flapE.attach(4);    // Pino do FlapE (Pode ser o 4 ou 5)
    flapD.attach(5);    // Pino do FlapD (Pode ser o 4 ou 5)
    lemo.attach(2);    // Pino do Lemo ()
    prof.attach(3);      // Pino do Profunder


    //Chama a função para redefinir os dados
    redefinir_dados();

    radio.begin();  //Inicializa a comunicação wireless
    radio.setAutoAck(false);    //Define o endereço da comunicação do transmissor 
    radio.setDataRate(RF24_2MBPS); //Define a velocidade de transmição  
    radio.openReadingPipe(1,endereco);
    radio.startListening();
}

//Variavel para armazenar tempo
unsigned long lastRecvTime = 0;

//Cria uma função que receberá os dados
void receber_os_dados(){
    //Inicia um loop se a conexão estiver ativa
    while ( radio.available() ) {
        radio.read(&dados_recebidos, sizeof(Dados_recebidos)); //Faz a leitura
        lastRecvTime = millis(); //Transfere para milissegundos
    }
}

void loop(){
    //Chama a função que recebe os dados
    receber_os_dados()
    
    //Cria variavel que conta tempo atual em milissegundos desde o início do programa
    unsigned long now = millis();
    if ( now - lastRecvTime > 1000 ) {
    //Sinal perdido?
    receber_os_dados();
  } 

    //Faz a conversão dos valores do joystick de graus para microssegundos
    flapD_value = map(dados_recebidos.ch1,0,255,1000,2000);
    flapE_value = map(dados_recebidos.ch2,0,255,1000,2000);
    prof_value = map(dados_recebidos.ch3,0,255,1000,2000);
    lemo_value = map(dados_recebidos.ch4,0,255,1000,2000);
    acel_value = map(dados_recebidos.ch5,0,255,1000,2000);



    //Escreve (envia) os valores já convertidos em microssegundos para os servos
    flapD.writeMicroseconds(flapD_value);  
    flapE.writeMicroseconds(flapE_value);  
    lemo.writeMicroseconds(lemo_value);  
    prof.writeMicroseconds(prof_value);
}