#include <Servo.h> 

const byte srv = 9;  // servo pin
const byte pot = A0;  // potenciometr

Servo servo;  // vytvoreni objektu servo
int hodnotaPot = 0;  // promenna pro ulozeni hodnoty potenciometru
int poz = 0;  // promenna pro ulozeni pozice serva
 
void setup(){
    servo.attach(srv);  // pripojeni serva
} 
 
void loop(){
  // nacteni hodnoty potenciometru
  hodnotaPot = analogRead(pot);
  
  // premapovani hodnoty potenciometru na uhel otoceni serva
  poz = map(hodnotaPot, 0, 1023, 0, 179);
  
  // otoceni serva
  servo.write(poz);
  
  // zpozdeni
  delay(15);
} 
