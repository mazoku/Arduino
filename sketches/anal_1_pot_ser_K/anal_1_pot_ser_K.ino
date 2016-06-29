const byte pot = A0; // potenciometr

void setup() {
  pinMode(pot, INPUT);  // potenciometr
  
  // seriova linka
  Serial.begin(9600);
}

void loop() {
}
