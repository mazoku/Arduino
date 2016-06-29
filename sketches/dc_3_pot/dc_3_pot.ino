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
  
  valPot = map(analogRead(pot), 0, 1023, -255, 255);
  
  if (valPot > 50){
      motorVpred(valPot);
      digitalWrite(rLed, HIGH);
      digitalWrite(gLed, LOW);
  }
  else if (valPot < -50){
      motorVzad(-valPot);
      digitalWrite(rLed, LOW);
      digitalWrite(gLed, HIGH);
  }
  else{
    motorStop();
    digitalWrite(gLed, LOW);
    digitalWrite(rLed, LOW);
  }
  
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

