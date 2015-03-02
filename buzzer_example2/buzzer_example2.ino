#include <ZumoBuzzer.h>
#include <Pushbutton.h>

#define MELODY_LENGTH 5

unsigned char note[MELODY_LENGTH] = 
{
  NOTE_E(5), SILENT_NOTE, NOTE_E(5), SILENT_NOTE, NOTE_E(5)
};

unsigned int duration[MELODY_LENGTH] =
{
  100, 25, 125, 125, 125
};

ZumoBuzzer buzzer;
Pushbutton button(ZUMO_BUTTON);
unsigned char currentIdx;

void setup() {
  currentIdx = 0;
  button.waitForButton();
}

void loop() {
  if (currentIdx < MELODY_LENGTH)
  {
    // play note at max volume
    buzzer.playNote(note[currentIdx], duration[currentIdx], 15);
    currentIdx++;
  }
}
