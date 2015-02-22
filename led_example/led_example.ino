#include <Pushbutton.h>

#define LED_PIN 13

Pushbutton button(ZUMO_BUTTON);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  button.waitForButton();
}

void loop() {
  
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(250);
}
