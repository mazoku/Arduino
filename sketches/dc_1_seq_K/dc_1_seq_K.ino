const byte mFwd = 3;  // motor vpred
const byte mBwd = 4;  // motor vzad
const byte mEnb = 5;  // motor povolit

void setup(){
  // nastavit pinMody
} 
 
void loop(){
  // rozjezd motoru vpred
    
  // zastaveni motoru
    
  // rozjezd motoru vzad
  
  // zastaveni motoru
  
}

void motorVpred(byte rychlost) {
  digitalWrite(mFwd, HIGH);
  digitalWrite(mBwd, LOW);
  analogWrite(mEnb, rychlost);
}

void motorVzad(byte rychlost) {
  
}

void motorStop() {
  
}

