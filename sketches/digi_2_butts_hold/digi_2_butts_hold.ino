const byte rLed = 13; // cervena LED
const byte tl1 = 2; // tlacitko 1

void setup(){
  pinMode(rLed, OUTPUT);
  pinMode(tl1, INPUT);
}

void loop(){
  if (digitalRead(tl1))
    digitalWrite(rLed, HIGH);
  else
    digitalWrite(rLed, LOW);
}
