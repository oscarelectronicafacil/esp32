//#include <DHT.h>
#include <DHT_U.h>


//#include <DHT11.h>

//#include "DHT.h" 
#define PinSensor 4   // Pin digital al que se conecta el sensor
#define Tipo DHT11    // Tipo de sensor
DHT dht(PinSensor, Tipo);

#include <BluetoothSerial.h>

String device_name = "ESP32-BT-DHT11";

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600); 
  dht.begin();
  SerialBT.begin(device_name);
}

void loop(){
  delay(5000);   
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  Serial.print("Humedad: "); 
  Serial.println(humedad);
  Serial.print("Temperatura:"); 
  Serial.println(temperatura);
  if(isnan(humedad) || isnan(temperatura)){
    Serial.println("Error al leer el sensor DHT11.");
  }else{
    String mensaje = String((int)humedad) + "," + String((int)temperatura);
    SerialBT.print(mensaje);
    //delay(3000);
  }
}