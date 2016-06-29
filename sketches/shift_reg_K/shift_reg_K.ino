const byte pot = A0;  // potenciometr

const byte st= 8;  // latch
const byte data = 11;  // data
const byte sh = 12;  // casovani

int hodnotaPot = 0;  // promenna pro ulozeni hodnoty potenciometru
byte index = 0;  // index do pole znaku

//  pole s ulozenymi jednotlivymi znaky
const byte znak[18] = {0b11000000, //0
                       0b11111001, //1
                       0b10100100, //2
                       0b10110000, //3
                       0b10011001, //4
                       0b10010010, //5
                       0b10000010, //6
                       0b11111000, //7
                       0b10000000, //8
                       0b10011000, //9
                       0b10001000, //A
                       0b10000011, //b
                       0b11000110, //C
                       0b10100001, //d
                       0b10000110, //E
                       0b10001110, //F
                       0b00000000, //all
                       0b11111111};//nic

void setup(){
  // nastaveni pinMode
}

void loop(){
  // nacist hodnotu z potenciometru a zobrazit znak na displej
}
