//Definição dos botões

#define lemo_bot_ad  0; //Botão que adiciona graus ao lemo
#define lemo_bot_rem 0; //Botão que remove graus ao lemo

#define flap_bot_ad  0; //Botão que adiciona graus ao flap
#define flap_bot_rem 0; //BOtão que remove graus ao flap

#define prof_bot_ad 0; //Botão que adicona graus ao profunder
#define prof_bot_rem 0; //Botão que remove graus ao profunder

//Estrutura para armazenar os valores das posições
struct PosInc {
    int flap = 0; // Talvez tenha q ser flapD e flapE
    int lemo = 0;
    int prof = 0;
};

//Cria uma variavel que chama a estrutura PosInc
PosInc posInc;

//Estrutura para armazenar os valores 
struct Valores  {
    int flap = LOW;
    int lemo = LOW; 
    int prof = LOW;
};

//Cria uma variavel que chama a estrutura Valores
Valores valor;

//Função para trimagem dos flaps
void flap_trimagem() {
    if (digitalRead(flap_bot_ad) != valor.flap) {
        valor.flap = digitalRead(flap_bot_ad);
        posInc.flap += 30; // Incrementa 30 graus quando o primeiro botão é pressionado
        delay(500);
    }
}

void setup() {
  pinMode(flap_bot_ad, INPUT); //Define o flapbot com Input
}

void loop(){
    flap_trimagem();

    int aeleronAngle = map(joyXVal, 0, 1023, posInc.flap, 180);
}