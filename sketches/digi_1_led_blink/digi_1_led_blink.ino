const byte rLed = 13; // cervena LED

void setup(){
  pinMode(rLed, OUTPUT);
}

void loop(){
  digitalWrite(rLed, HIGH);
  delay(500);
  digitalWrite(rLed, LOW);
  delay(1000);
}
