#include <SPI.h> //instalação da biblioteca do protocolo SPI

int x; //variável que será enviada para o slave

void setup () //temos a função do nosso setup
{
  Serial.begin(115200);               //taxa de transmissão de dados do serial monitor
  SPI.begin();                        //inicialização do protocolo SPI
  SPI.setClockDivider(SPI_CLOCK_DIV8);   //divisão da frequência do clock do SPI em 8, ou seja, 16MHz/8 = 2MHz
  digitalWrite(SS,HIGH);      //inicialização do pino SS(Slave Select) como HIGH, ou seja, desabilitado
}

void loop() //função do loop, que será executada repetidamente após o setup
{
  byte Master_send, Master_receive;          //variáveis que serão utilizadas para enviar e receber dados do slave

  x = 1; //atribuindo o valor 1 à variável x, que será enviada para o slave
  
  digitalWrite(SS, LOW);                  //habilitando o pino SS(Slave Select) para comunicação com o slave
  
  Mastersend = x;                //atribuindo o valor da variável x à variável Mastersend, que será enviada para o slave
  Master_receive = SPI.transfer(Master_send); //enviando o valor da variável Mastersend para o slave e recebendo o valor enviado pelo slave na variável Mastereceive
  
  if(Master_receive == 1)                 //verificando se o valor recebido pelo slave é igual a 1
  {
    Serial.println("Dado enviado: 1"); //se o caso acima for verdade imprimimos no serial monitor a mensagem "Dado enviado: 1"
  }
  else
  {
    Serial.println("Nenhum dado enviado"); //se o caso acima for falso imprimimos no serial monitor a mensagem "Nenhum dado enviado"
  }
  delay(1000); //esperamos 1 segundo antes de repetir o loop
}

