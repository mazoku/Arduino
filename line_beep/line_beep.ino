#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Pushbutton.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>

#define QTR_THRESHOLD  1500

ZumoReflectanceSensorArray reflectanceSensors;
ZumoBuzzer buzzer;
Pushbutton button(ZUMO_BUTTON);

ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
#define N_SENSORS 6
unsigned int sensor_values[N_SENSORS];

//------------------------------------------------------------------
void setup(){
  //reflectanceSensors.init();
  Serial.begin(9600);
  button.waitForButton();
}

//------------------------------------------------------------------
void loop(){
  sensors.read(sensor_values);
  Serial.print(sensor_values[0]);
  Serial.print(", ");
  Serial.print(sensor_values[1]);
  Serial.print(", ");
  Serial.print(sensor_values[2]);
  Serial.print(", ");
  Serial.print(sensor_values[3]);
  Serial.print(", ");
  Serial.print(sensor_values[4]);
  Serial.print(", ");
  Serial.println(sensor_values[5]);
  Serial.println();
  
  if (contact_made()){
    buzzer.playNote(NOTE_G(4), 200, 15);
  }
  delay(200);
}

//-----------------------------------------------------------------
boolean contact_made(){
  boolean contact = false;
  
  for(int i = 0; i < N_SENSORS; i++){
    if(sensor_values[i] > QTR_THRESHOLD){
      contact = true;
      break;
    }
  }
  
  return(contact);
}
