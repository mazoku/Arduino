const byte mFwd = 3;  // motor vpred
const byte mBwd = 4;  // motor vzad
const byte mEnb = 5;  // motor povolit

const byte pot = A0;  // potenciometr

const byte rLed = 13;  // cervena LED
const byte gLed = 10;  // zelena LED

int valPot = 0;  // promenna pro ulozeni hodnoty potenciometru

void setup(){
    pinMode(mFwd, OUTPUT);
    pinMode(mBwd, OUTPUT);
    pinMode(mEnb, OUTPUT);
    
    pinMode(rLed, OUTPUT);
    pinMode(gLed, OUTPUT);

    pinMode(pot, INPUT);
} 
 
void loop(){
  
  // nacist hodnotu z potenciometru
  
  // rozhodnout se vhodne o smeru a roztocit motor
  
  // zpozdeni
  delay(15);
}

void motorVpred(byte rychlost) {
  digitalWrite(mFwd, HIGH);
  digitalWrite(mBwd, LOW);
  analogWrite(mEnb, rychlost);
}

void motorVzad(byte rychlost) {
  digitalWrite(mFwd, LOW);
  digitalWrite(mBwd, HIGH);
  analogWrite(mEnb, rychlost);
}

void motorStop() {
  analogWrite(mEnb, 0);
  digitalWrite(mFwd, LOW);
  digitalWrite(mBwd, LOW);
}

