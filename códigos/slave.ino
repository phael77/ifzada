#include <SPI.h> //Biblioteca para comunicação SPI
#include <LiquidCrystal.h> //Biblioteca para comunicação com o display LCD

LiquidCrystal lcd2(7, 8, 5, 4, 3, 2); //pinos digitais do Arduino Uno para comunicação com o display LCD
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); //pinos analógicos do Arduino Uno para comunicação com o display LCD
volatile boolean received; //variável para verificar se houve recepção de dados
volatile byte Slave_received,Slave_send; //variáveis para armazenar os dados recebidos e enviados
int x;

//vetor de strings com as mensagens a serem exibidas no display LCD
String mensagens[] = {
  "420 GYN 04:20 AR",
  "692 CWB 05:14 CH",
  "666 GRU 12:15 IN",
  "541 BSB 13:54 TX",
};

//função de setup, executada uma única vez quando o Arduino é ligado
void setup()
{
  Serial.begin(115200); //inicializa a comunicação serial com taxa de transmissão de 115200 bps
  pinMode(MISO,OUTPUT);  //pino MISO = Master In Slave Out               
  SPCR |= _BV(SPE);     //                 
  received = false;

  randomSeed(analogRead(0));  

  SPI.attachInterrupt();                
  lcd.begin(16, 2);
  lcd2.begin(16, 2);
}

//função de interrupção para comunicação SPI
ISR (SPI_STC_vect)                    
{
   Slave_received = SPDR;                 
   received = true;                       
}

//função de loop, executada continuamente após a função setup
void loop()
{ 

  int indice = random(sizeof(mensagens) / sizeof(mensagens[0])); //gera um índice aleatório para a primeira mensagem
  int indice2; //variável para armazenar o índice da segunda mensagem

  lcd.clear(); //limpa o display LCD1
  lcd2.clear(); //limpa o display LCD2

//gera um índice aleatório para a segunda mensagem, garantindo que seja diferente do primeiro
  do {
    indice2 = random(sizeof(mensagens) / sizeof(mensagens[0]));
  } while (indice == indice2);

   if(received)                          
   {
      if (Slavereceived==1) 
      {
        lcd.setCursor(0, 0); //posiciona o cursor na primeira linha do display LCD1
        lcd.print("--- PARTIDAS ---"); //exibe a mensagem no display LCD1
        lcd.setCursor(0, 1); //posiciona o cursor na segunda linha do display LCD1
        lcd.print("VOO CIA PREV. ST"); //exibe a mensagem no display LCD1
        lcd2.setCursor(0, 0); //posiciona o cursor na primeira linha do display LCD2
        lcd2.print(mensagens[indice]); //exibe a mensagem no display LCD2
        lcd2.setCursor(0, 1); //posiciona o cursor na segunda linha do display LCD2
        lcd2.print(mensagens[indice2]); //exibe a mensagem no display LCD2
        Serial.println("Dado recebido"); //exibe a mensagem no monitor serial
        delay(2000);
      } else {
        lcd.setCursor(0, 0); 
        lcd2.setCursor(0, 0);
        lcd.print("ERRO NO SISTEMA"); //se der errado a condição, então essa será a mensagem exibida no display LCD1
        lcd2.print("ERRO NO SISTEMA"); //a mesma mensagem para LCD2
        Serial.println("Dado não recebido"); //exibe a mensagem no monitor serial
        delay(2000);
      }
      
      Slave_send=x;           // o valor de x é atrbuido para a variavel Slave_send que                   
      SPDR = Slave_send;    //o pino registrador de dados recebe o valor da variável Slave_send
      delay(1000); //espera de 1 segundo antes de exibir a próxima mensagem
   }
}
