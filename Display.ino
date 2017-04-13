#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Programa : Sensor de Temperatura
// Autor : Fabio
// Usando uma constante em C para guardar o valor do Pino
#define PINO_SENSOR 5
#define PINO_LED 3
LiquidCrystal lcd(2,4,10,11,12,13);

// Cria um objeto do tipo OneWire e passa o Pino pra ele
OneWire oneWire(PINO_SENSOR);
 
// Passando o objeto oneWire por referência para o objeto DallasTemperature
DallasTemperature sensors(&oneWire);

double temperatura;
void setup(void){
 
  // inicia o contato com a porta serial
  Serial.begin(9600);
  Serial.println("Controle de Temperatura");

  // inicia o objeto do DallasTemperature
  sensors.begin();
  lcd.begin(16,2);  
}
 
void loop(void){
 
  sensors.requestTemperatures(); // Envia o comando para obter temperaturas.
  temperatura = sensors.getTempCByIndex(0);
  exibeTempPortaSerial(temperatura);
  if(sensors.getTempCByIndex(0)>=28.0){
      lcd.println("Desligar Fogo!");
      acendeLed(PINO_LED);
   }else{
       desligaLed(PINO_LED);
       lcd.println("Temperatura:");
       lcd.setCursor(0,1);
       lcd.print(temperatura);
       
      }
  delay(500);
  lcd.clear();
}

void acendeLed(int pinoLed){
   pinMode(pinoLed,OUTPUT);
   digitalWrite(pinoLed, HIGH);
   delay(250);
   digitalWrite(pinoLed, LOW);
   delay(150);
  }

void desligaLed(int pinoLed){
  pinMode(pinoLed,INPUT);
  digitalWrite(pinoLed, LOW);
  }

void exibeTempPortaSerial(int temperatura){
   //Chama o método que faz o request da temperatura.
  Serial.print(" Buscando Temperatura....");
  Serial.println("Ok...");
  Serial.print("A temperatura eh: ");
  Serial.print(sensors.getTempCByIndex(0));
  }