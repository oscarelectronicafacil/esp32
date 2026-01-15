#include <Arduino_JSON.h>

#include <ESP32Servo.h>
#include <DHT_U.h>
#include <BluetoothSerial.h>

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

String device_name = "ESP32-BT-SERVO-CONTROL";

BluetoothSerial SerialBT;

Servo servo1;
#define PinSensor 23   // Pin digital al que se conecta el sensor
#define Tipo DHT11    // Tipo de sensor
DHT dht(PinSensor, Tipo);
int pinServo = 22;
int pulsoMin = 600;
int pulsoMax = 2600;

int ledVerde = 21;
int valorPot;
int anguloServo=0;
int pot = 4;

String message="";

const char input[] = "[true, 42, \"apple\"]";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pot, INPUT);
  pinMode(ledVerde, OUTPUT);
  dht.begin();
  servo1.attach(pinServo, pulsoMin, pulsoMax);
  SerialBT.begin(device_name);
  // las entradas analogicas no necesitan inicializacion
  digitalWrite(ledVerde, LOW);

}

void loop() {
  
  //delay(2000);
  //Serial.print("anguloServo:");
  //Serial.println(anguloServo);
  //Serial.println(".------------");
  //servo1.write(anguloServo);
  //delay(5000);
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  //Serial.print("Humedad: "); 
  //Serial.println(humedad);
  //Serial.print("Temperatura:"); 
  //Serial.println(temperatura);
  if(isnan(humedad) || isnan(temperatura)){
    Serial.println("Error al leer el sensor DHT11.");
  }else{
    String mensaje = String((int)humedad) + "," + String((int)temperatura)+",0";
    SerialBT.print(mensaje);
    Serial.println(mensaje);
    //delay(3000);
  }
 
  if (SerialBT.available()) {
    
    char incoming = SerialBT.read();
    while(incoming != '\n'){
      message += incoming;
      incoming  = SerialBT.read();
    }
    Serial.println(message);
    
    //anguloServo = message.toInt();
 
   
    byte pos1 = message.indexOf('{') + 1; // Posición después de la primera coma (índice 4)
    byte pos2 = message.indexOf(',', pos1); // Posición de la segunda coma (índice 8)
    String numeroStr = message.substring(pos1, pos2); // "456"
  //float numero = numeroStr.toFloat();
  //Serial.println(numeroStr); // Imprime 456.0 
    if(numeroStr == "servo1"){
      byte pos1 = message.indexOf(',') + 1; // Posición después de la primera coma (índice 4)
      byte pos2 = message.indexOf('}', pos1); // Posición de la segunda coma (índice 8)
      String numeroStr = message.substring(pos1, pos2); // "456"
      //Serial.println(numeroStr);
      anguloServo = numeroStr.toInt();
      servo1.write(anguloServo);
    }
    if(numeroStr == "ledverde"){
      byte pos1 = message.indexOf(',') + 1; // Posición después de la primera coma (índice 4)
      byte pos2 = message.indexOf('}', pos1); // Posición de la segunda coma (índice 8)
      String numeroStr = message.substring(pos1, pos2); // "456"
      //Serial.println(numeroStr);
      int estado = numeroStr.toInt();
      
      if(estado == 1){
        digitalWrite(ledVerde, HIGH);
      }else digitalWrite(ledVerde, LOW);
    }
    message = "";
  }
   
  delay(200);
  

  
}