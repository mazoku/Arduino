const byte pot = A0; // potenciometr
const byte gLed = 10; // cervena LED na analogovem pinu

int hodnotaPot = 0;  // pocatecni hodnota potenciometru
int hodnotaLed = 0;  // pocatecni hodnota LED

void setup() {
  pinMode(pot, INPUT);  // potenciometr
  pinMode(gLed, OUTPUT);  // LED
  
  // seriova linka
  Serial.begin(9600);
}

void loop() {
  // nacteni stavu potenciometru
  hodnotaPot = analogRead(pot);
  
  // prevedeni hodnoty z intervalu <0, 1023> na interval <0, 255>
  hodnotaLed = map(hodnotaPot, 0, 1023, 0, 255);
  
  // zapis na LED
  analogWrite(gLed, hodnotaLed);
  
  // zapis na serial
  Serial.print(hodnotaPot);
  Serial.print(" -> ");
  Serial.println(hodnotaLed);
  
  // zpozdeni
  delay(200);
}
