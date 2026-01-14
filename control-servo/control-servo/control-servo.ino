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

int valorPot;
int anguloServo=0;
int pot = 4;

String message="";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pot, INPUT);
  dht.begin();
  servo1.attach(pinServo, pulsoMin, pulsoMax);
  SerialBT.begin(device_name);
  // las entradas analogicas no necesitan inicializacion
}

void loop() {
  Serial.print("anguloServo:");
  Serial.println(anguloServo);
  Serial.println(".------------");
  servo1.write(anguloServo);
  //delay(5000);
  if (SerialBT.available()) {
    
    char incoming = SerialBT.read();
    while(incoming != '\n'){
      message += incoming;
      incoming  = SerialBT.read();
    }
    //Serial.println(message);
    anguloServo = message.toInt();
    message = "";
  }
   
  delay(200);
  
  
  
}