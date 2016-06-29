#include <Servo.h> 
 
const byte srv = 9;  // servo pin
Servo servo;  // vytvoreni objektu servo 
 
int poz = 0;  // promenna pro ulozeni pozice serva
 
void setup(){ 
  servo.attach(srv);  // pripojeni serva
} 
 
 
void loop(){ 
  // postupne otaceni serva 0 -> 180 po 1 stupni
  for(poz = 0; poz < 180; poz += 1){
    servo.write(poz);  // zapsani pozice na servo
    delay(15);  // zpozdeni aby se mohlo servo ustalit
  }
  
  // postupne otaceni serva 180 -> 0 po 1 stupni
  for(poz = 180; poz >= 1; poz -=1 ){                                
    servo.write(poz);  // zapsani pozice na servo
    delay(15);  // zpozdeni aby se mohlo servo ustalit
  } 
} 
