#include<Servo.h>
// digital
const byte mFwd = 3; // motor vpred
const byte mBwd = 4; // motor vzad
const byte mEnb = 5; // motor povolit
const byte tl1 = 2; // tlacitko 1
const byte tl2 = 6; // tlacitko 2
const byte st= 8; // latch
const byte srv = 9;
const byte gLed = 10; // zelena LED
const byte data = 11; // data
const byte sh = 12; // casovani
const byte rLed = 13; // cervena LED
// analog
const byte pot = A0; // potenciometr
const byte lFotoRez = A1; // levy fotorezistor
const byte rFotoRez = A2; // pravy fotorezistor
const byte ir = A7; // IR cidlo vzdalenosti

Servo myServo;

const byte znak[18] = {0b11000000, //0
                       0b11111001, //1
                       0b10100100, //2
                       0b10110000, //3
                       0b10011001, //4
                       0b10010010, //5
                       0b10000010, //6
                       0b11111000, //7
                       0b10000000, //8
                       0b10011000, //9
                       0b10001000, //A
                       0b10000011, //b
                       0b11000110, //C
                       0b10100001, //d
                       0b10000110, //E
                       0b10001110, //F
                       0b00000000, //all
                       0b11111111};//nothing 

void setup() {
  pinMode(mFwd, OUTPUT);
  pinMode(mBwd, OUTPUT);
  pinMode(mEnb, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(tl1, INPUT);
  pinMode(tl2, INPUT);
  pinMode(st, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(sh, OUTPUT);
  
  digitalWrite(gLed, LOW);
  digitalWrite(rLed, LOW);
  shiftRegEas(znak[17]);
  
  Serial.begin(9600);
  myServo.attach(srv);
  myServo.write(40);
}

void loop() {
//  butts();
//  shiftReg(false);
  buttsShiftReg();
//  potenciometr();
//  rs232();
//  servo();
//  motor();
}

void butts() {
  if (digitalRead(tl1))
    digitalWrite(gLed, HIGH);
  else
    digitalWrite(gLed, LOW);

  if (digitalRead(tl2))
    digitalWrite(rLed, HIGH);
  else
    digitalWrite(rLed, LOW);
}

void buttsShiftReg() {
  if (digitalRead(tl1)) {
    digitalWrite(gLed, HIGH);
    shiftReg(true);
  }
  else {
    digitalWrite(gLed, LOW);
  }
  if (digitalRead(tl2)) {
    digitalWrite(rLed, HIGH);
    shiftReg(false);
  }
  else {
    digitalWrite(rLed, LOW);
  }
}

int irCidlo() {
  int vala = analogRead(ir);
  byte vald = map(vala, 300, 900, 0, 255);
  return vala;
}

int lFotoOdpor() {
  int vala = analogRead(lFotoRez);
  byte vald = map(vala, 300, 900, 0, 255);
  analogWrite(rLed, vald);
  return vala;
}

void motor() {
  byte val;
  boolean stiskTl1, stiskTl2;
  stiskTl1 = digitalRead(tl1);
  stiskTl2 = digitalRead(tl2);
  if (stiskTl1^stiskTl2) {
    val = map(analogRead(pot), 0, 1023, 0, 255);
    if (stiskTl1) {
      motorForward(val);
      digitalWrite(gLed, HIGH);
    }
    else {
      motorBackward(val);
      digitalWrite(rLed, HIGH);
    }
  }
  else {
    motorBreak();
    digitalWrite(gLed, LOW);
    digitalWrite(rLed, LOW);
  }
}

void motorBackward(byte speed) {
  motorBreak();
  digitalWrite(mFwd, LOW);
  digitalWrite(mBwd, HIGH);
  analogWrite(mEnb, speed);
}

void motorBreak() {
  analogWrite(mEnb, 0);
  digitalWrite(mFwd, LOW);
  digitalWrite(mBwd, LOW);
}

void motorForward(byte speed) {
  motorBreak();
  digitalWrite(mFwd, HIGH);
  digitalWrite(mBwd, LOW);
  analogWrite(mEnb, speed);
}

int rFotoOdpor() {
  int vala = analogRead(rFotoRez);
  byte vald = map(vala, 300, 900, 0, 255);
  analogWrite(gLed, vald);
  return vala;
}

void potenciometr() {
  int val = analogRead(pot);
  val = map(val, 0, 1023, 0, 17);
  shiftRegEas(znak[val]);
  delay(50);
}

void rs232() {
  Serial.print("Levy fotorezistor:");
  Serial.println(lFotoOdpor());
  Serial.print("Pravy fotorezistor:");
  Serial.println(rFotoOdpor());
  Serial.print("IR senzor:");
  Serial.println(irCidlo());
  Serial.println();
  delay(100);
}

void servo() {
  byte angel;
  angel = map(analogRead(pot), 0, 1023, 40, 120);
  angel = constrain(angel, 40, 120);
  myServo.write(angel);
  delay(200);
}

void shiftReg(boolean easy){
  int dt = 300;
  shiftRegEas(znak[16]);
  delay(2*dt);
  shiftRegEas(znak[17]);
  delay(2*dt);
  if (!easy) {
    for (char k = 0; k < 16; k++) {
      shiftRegDif(znak[k]);
      delay(dt);
    }
  }
  else {
    for (char k = 15; k >= 0; k--) {
      shiftRegEas(znak[k]);
      delay(dt);
    }
  }
  shiftRegEas(znak[17]);
}

void shiftRegDif(byte num) {
  digitalWrite(st, LOW);
  for (byte k = 0; k < 9; k++) {
    digitalWrite(sh, HIGH);
    if (num & 0b10000000)
      digitalWrite(data, HIGH);
    else
      digitalWrite(data, LOW);
    digitalWrite(sh, LOW);
    num = num << 1;
  }
  digitalWrite(st, HIGH);
}

void shiftRegEas(byte num) {
  digitalWrite(st, LOW);
  shiftOut(data, sh, MSBFIRST, num);
  digitalWrite(st, HIGH);
}

