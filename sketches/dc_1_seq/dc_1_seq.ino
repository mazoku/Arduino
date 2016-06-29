const byte mFwd = 3;  // motor vpred
const byte mBwd = 4;  // motor vzad
const byte mEnb = 5;  // motor povolit

void setup(){
    pinMode(mFwd, OUTPUT);
    pinMode(mBwd, OUTPUT);
    pinMode(mEnb, OUTPUT);
} 
 
void loop(){
  // rozjezd motoru vpred
  for (byte rychlost = 0; rychlost < 250; rychlost = rychlost + 10){
    motorVpred(rychlost);
    delay(100);
  }
  delay(1000);
  
  // zastaveni motoru
  motorStop();
  delay(1000);
  
  // rozjezd motoru vzad
  for (byte rychlost = 0; rychlost < 250; rychlost = rychlost + 10){
    motorVzad(rychlost);
    delay(100);
  }
  delay(1000);

  // zastaveni motoru
  motorStop();
  delay(1000);
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

