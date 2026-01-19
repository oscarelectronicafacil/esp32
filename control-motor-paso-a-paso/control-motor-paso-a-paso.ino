#include <Stepper.h>
int stepsPerRevolution = 2048;
int motSpeed = 10;
Stepper myStepper(stepsPerRevolution, 23,21,22,19);

int pinButton = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinButton, INPUT);
  myStepper.setSpeed(motSpeed);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valButon = digitalRead(pinButton);
  Serial.println(valButon);
  myStepper.step(stepsPerRevolution);
  delay(1000);
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
