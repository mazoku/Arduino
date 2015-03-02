#include <ZumoBuzzer.h>
#include <Pushbutton.h>

ZumoBuzzer buzzer;
Pushbutton button(ZUMO_BUTTON);

void setup() {
  button.waitForButton();
}

void loop() {
  
  // nota(oktáva), délka [us], hlasitost (max 15)
  buzzer.playNote(NOTE_E(5), 100, 15);
  delay(100);
  buzzer.playNote(SILENT_NOTE, 25, 15);
  delay(25);
  }
}
