// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device

#include "BluetoothSerial.h"

String device_name = "ESP32-BT-Esclavo";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

int ledRojo = 32;
int ledVerde = 2;
void setup() {
  pinMode(ledRojo,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());

  }
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.write(c);
    switch(c){
      case 'B': digitalWrite(ledRojo,HIGH);break;
      case 'C': digitalWrite(ledRojo,LOW);break;
      case 'D': digitalWrite(ledVerde, HIGH); break;
      case 'E': digitalWrite(ledVerde, LOW); break;
    }
  }
  delay(20);
}
