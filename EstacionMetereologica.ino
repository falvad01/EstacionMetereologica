#include <Adafruit_Sensor.h>

//Incluir adafruir unified sensors
#include "DHT.h"

#include <SFE_BMP180.h> ////https://github.com/sparkfun/BMP180_Breakout


/*TODO

    Calcular el Ã­ndice de calor en grados centÃ­grados
   float hic = dht.computeHeatIndex(t, h, false);




*/


#define DHTTYPE DHT11

/*Definimos pines*/
int DHTpin = 3;
int rainDetectorPin = 4;
int LuzPin = A1;


/*Variables globales*/
float temperature;
float humidity;
float presure;
bool rain;
int luz;

DHT dht(DHTpin, DHTTYPE);//Inicializamos DHT
SFE_BMP180 bmp180;

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (bmp180.begin())
    Serial.println("BMP180 iniciado");
  else
  {
    Serial.println("Error al iniciar BMP180");
    while (1); // bucle infinito
  }
  pinMode(rainDetectorPin, INPUT);


}

void loop() {
   temperature = readTemperature();
   humidity = readHumidity();
   presure = readPresure();
   rain = rainDetectorFunc();
   luz = readLuz();
   

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.print(" %\t");
  Serial.print("Presion: ");
  Serial.print(presure);
  Serial.print(" mb");
  Serial.print("    Is raining:  ");
  Serial.print(rain);
  Serial.print("    Ligth:  ");
  Serial.print(luz);
  Serial.println();
  Serial.print(" %\n");

  delay(1000);


}

/*Fundiones*/
float readTemperature() {
  return dht.readTemperature();
}

float readHumidity() {
  return dht.readHumidity();
}

double readPresure() {

  char status;
  double T, P;

  status = bmp180.startTemperature();//Inicio de lectura de temperatura

  if (status != 0)
  {
    delay(status); //Esperamos a que finalice la lectura

    status = bmp180.getTemperature(T);
    if (status != 0)
    {
      status = bmp180.startPressure(3);
      if (status != 0)
      {
        delay(status);//Esperamos a que finalice la lectura
        status = bmp180.getPressure(P, T);
        if (status != 0)
        {
          return P;
        }
      }
    }
  }
}

bool rainDetectorFunc(){
  
 int value = digitalRead(rainDetectorPin);  //lectura digital de pin
 
  if (value == LOW) {
      return true;
  }else{
    return false;
  }
}
int readLuz(){

  int value = analogRead(LuzPin);
  return value;
}



