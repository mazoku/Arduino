const byte pot = A0; // potenciometr

int hodnotaPot = 0;  // hodnota potenciometru

void setup() {
  pinMode(pot, INPUT);  // potenciometr
  
  // seriova linka
  Serial.begin(9600);
}

void loop() {
  // nacteni stavu potenciometru
  hodnotaPot = analogRead(pot);
  
  // zapis na serial
  Serial.println(hodnotaPot);
  
  // zpozdeni
  delay(200);
}
