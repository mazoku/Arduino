const byte rLed = 13; // cervena LED
const byte tl1 = 2; // tlacitko 1

int stavLed = LOW;        // soucasny stav LEDky
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
  // nacteni stavu tlacitka
  int stav = digitalRead(tl1); 

  // Pri zmene stavu tlacitka (stisk ci sum)...
  if (stav != poslStavTlac) {
    // reset debounce casovace
    poslCasDebounce = millis();
  } 
  
  // kontrola ustalenosti stavu
  if ((millis() - poslCasDebounce) > debounceSirka) {
    // pokud je stav beze zmeny dele nez debounceSirka, prijmeme jej

    // doslo-li ke zmene stavu tlacitka...
    if (stav != stavTlac) {
      stavTlac = stav;

      // zmenit stav LED pri stisku tlacitka a ne pri uvolneni (nabezna hrana)
      if (stavTlac == HIGH) {
        stavLed = !stavLed;
      }
    }
  }
  
  // zapsat stav na LED
  digitalWrite(rLed, stavLed);

  // ulozeni stavu pro dalsi zpracovani
  poslStavTlac = stav;
}
