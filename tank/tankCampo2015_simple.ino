#include <Servo.h>
#include <NewPing.h>
#include <PinChangeInt.h>
#include <QTRSensors.h>

// Ultrazvukovy dalkomer
#define TRIGGER_PIN  8  
#define ECHO_PIN     7  
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Servo motor 1
#define SERVO_PIN 9
#define SERVO_CENTER 90
#define SERVO_MIN 45
#define SERVO_MIN_MS 1250
#define SERVO_MAX 135
#define SERVO_MAX_MS 1750
Servo servoSonar;

// ******* definice V/V pinu ********
// narazniky
#define pravyNaraznik 19
#define levyNaraznik 18
volatile boolean narazVpravo = false;
volatile boolean narazVlevo = false;

// rizeni motoru A (pravy motor)
#define AIN1 3  // pin ridici smer otaceni praveho motoru
#define AIN2 5  // pin ridici smer otaceni praveho motoru

// rizeni motoru B (levy motor)
#define BIN1 11// pin ridici smer otaceni leveho motoru
#define BIN2 6 // pin ridici smer otaceni leveho motoru

// nastavení rychlosti motoru
#define MAX_RYCHLOST 150
#define MAX_RYCHLOSTL 150
// line sensor definitions 
#define NUM_SENSORS             3  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             17  // emitter is controlled by digital pin 2
#define lineRight A0  
#define lineCenter A1
#define lineLeft A2
QTRSensorsAnalog qtr((unsigned char[]) {lineRight, lineCenter, lineLeft},NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

void setup (){  
  // vytvor seriovy kanal do PC
  Serial.begin(9600);
  
  // nastav servo
  servoSonar.attach(SERVO_PIN,SERVO_MIN_MS,SERVO_MAX_MS);
  servoSonar.write(SERVO_CENTER);
  
  ///inicializace radice motoru  
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  
  pinMode(BIN1,OUTPUT);
  pinMode(BIN1,OUTPUT);
  
  // inicializace narazniku  
  pinMode(pravyNaraznik,INPUT);
  pinMode(levyNaraznik,INPUT);
  digitalWrite(pravyNaraznik,HIGH); // zapnuti interniho pull-up odporu
  digitalWrite(levyNaraznik,HIGH);  // zapnuti interniho pull-up odporu
  
  // inicializace obsluhy preruseni od narazniku
  PCintPort::attachInterrupt(pravyNaraznik, &narazVpravoInt, RISING);
  PCintPort::attachInterrupt(levyNaraznik, &narazVlevoInt, RISING);
}


// HLAVNI ------------------------------------------------------
void loop () {

}


// -------------------------------------------------------------
void dopredu(){
}

// -------------------------------------------------------------
void dozadu(){
}

// -------------------------------------------------------------
void doleva(){
}

// -------------------------------------------------------------
void ostreDoleva() {
}

// -------------------------------------------------------------
void doprava(){
}

// -------------------------------------------------------------
void ostreDoprava() {
}

// -------------------------------------------------------------
void zastavit() {
}

// -------------------------------------------------------------
int vzdalenost(){
    int vzd = sonar.ping_cm();
    return vzd;
}

// -------------------------------------------------------------
int servoDoleva(){
    servo.write(SERVO_MIN);
}

// -------------------------------------------------------------
int servoDoprava(){
    servo.write(SERVO_MAX);
}

// -------------------------------------------------------------
int servoStred(){
    servo.write(SERVO_CENTER);
}

// -------------------------------------------------------------
// !! PRIPRAVENE - NEMENIT !!
// -------------------------------------------------------------
void pravyMotorVpred(int rychlost) {
  digitalWrite(AIN1, LOW);
  analogWrite(AIN2, rychlost);
}

// -------------------------------------------------------------
void pravyMotorVzad(int rychlost) {
  analogWrite(AIN1, rychlost);
  digitalWrite(AIN2, LOW);
}

// -------------------------------------------------------------
void pravyMotorStop() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
}

// -------------------------------------------------------------
void levyMotorVpred(int rychlost) {
  analogWrite(BIN1, rychlost);
  digitalWrite(BIN2, LOW);
}

// -------------------------------------------------------------
void levyMotorVzad(int rychlost) {
  digitalWrite(BIN1, LOW);
  analogWrite(BIN2, rychlost);
}

// -------------------------------------------------------------
void levyMotorStop() {
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
}

// -------------------------------------------------------------
void narazVpravoInt() {
}

// -------------------------------------------------------------
void narazVlevoInt() {
}