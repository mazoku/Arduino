const byte rLed = 13; // cervena LED
const byte tl1 = 2; // tlacitko 1

int stavLed = LOW;       // soucasny stav LEDky
int stavTlac;             // soucasny stav tlacitka
int poslStavTlac = LOW;   // predchozi stav tlacitka

long poslCasDebounce = 0;  // cas posledni zmeny stavu tlacitka
long debounceSirka = 50;    // sirka okna the debounce time; increase if the output flickers

void setup() {
  pinMode(tl1, INPUT);
  pinMode(rLed, OUTPUT);

  // vychozi stav LED
  digitalWrite(rLed, stavLed);
}

void loop() {
  // read the state of the switch into a local variable:
  int stav = digitalRead(tl1);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (stav != poslStavTlac) {
    // reset the debouncing timer
    poslCasDebounce = millis();
  } 
  
  if ((millis() - poslCasDebounce) > debounceSirka) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (stav != stavTlac) {
      stavTlac = stav;

      // only toggle the LED if the new button state is HIGH
      if (stavTlac == HIGH) {
        stavLed = !stavLed;
      }
    }
  }
  
  // set the LED:
  digitalWrite(rLed, stavLed);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  poslStavTlac = stav;
}
