const byte mFwd = 3;  // motor vpred
const byte mBwd = 4;  // motor vzad
const byte mEnb = 5;  // motor povolit

const byte tl1 = 2;  // tlacitko 1
const byte tl2 = 6;  // tlacitko 2

const byte pot = A0;  // potenciometr

const byte rLed = 13;  // cervena LED
const byte gLed = 10;  // zelena LED

boolean stiskTl1 = false;  // promenna pro ulozeni stavu tlacitka 1
boolean stiskTl2 = false;  // promenna pro ulozeni stavu tlacitka 2

int valPot = 0;  // promenna pro ulozeni hodnoty potenciometru

void setup(){
    pinMode(mFwd, OUTPUT);
    pinMode(mBwd, OUTPUT);
    pinMode(mEnb, OUTPUT);
    
    pinMode(rLed, OUTPUT);
    pinMode(gLed, OUTPUT);
    
    pinMode(tl1, INPUT);
    pinMode(tl2, INPUT);
    pinMode(pot, INPUT);
} 
 
void loop(){
  // nacist stav tlacitek
  
  // bylo stisknuto tlacitko?
  // pokud ano - rozjet motor prislusnym smerem a rozsvitit prislusnou LEDku
  
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

