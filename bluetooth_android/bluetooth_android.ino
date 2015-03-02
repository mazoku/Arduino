
const int ledPin = 13;  // the pin that the LED is attached to
byte serialA;


void setup(){
  // initialize the serial communication:
  Serial.begin(6900); //baud rate - make sure it matches that of the module you got:
  // initialize the ledPin as an output:
  pinMode(ledPin, OUTPUT);
}


void loop(){
  if(Serial.available() > 0){
    serialA = Serial.read();
    Serial.print("value: ");
    Serial.println(serialA);
  }

  switch (serialA){
    case 1:
      digitalWrite(ledPin, HIGH);
      break;
    case 2:
      digitalWrite(ledPin, LOW);
      break;
    default:
      break;
  }

}
