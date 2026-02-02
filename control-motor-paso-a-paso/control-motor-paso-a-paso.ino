#include <Stepper.h>
#include <BluetoothSerial.h>

String device_name = "ESP32-BT-PASOAPASO";

BluetoothSerial SerialBT;

int stepsPerRevolution = 2048;
int motSpeed = 10;

#define in1 21
#define in2 22
#define in3 23
#define in4 33

Stepper myStepper(stepsPerRevolution, in3,in1,in2,in4); 

int pinButton = 2;
int pinButton_2 = 4; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinButton, INPUT);
  myStepper.setSpeed(motSpeed);
  SerialBT.begin(device_name);
  Serial.print("Iniciando comunicacion\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  int valButon = digitalRead(pinButton);
  int valButon2 = digitalRead(pinButton_2);
  //Serial.print("Boton1: ");
  //Serial.print(valButon);
  //Serial.print(" ; Boton2: ");
  //Serial.println(valButon2);

  if(valButon == 1){
    for(int i=0; i<10; i++){
      myStepper.step(5);
    }
  }else if(valButon2 == 1){
    for(int i=0;i<10; i++){
      myStepper.step(-5);
    }
  }
  if(SerialBT.available()) {
    Serial.print("Bluetooth disponible.\n");
    char c = SerialBT.read();
    Serial.write(c);
    switch(c){
      case 'B': for(int i=0; i<20; i++){
                  myStepper.step(5);
                }
                break;
      case 'D': for(int i=0;i<20;i++){
                  myStepper.step(-5);
                }
                break;
              
    }
  }  
  delay(200);
}
