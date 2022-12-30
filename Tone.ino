#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494

#define WHOLE         2000       // Length of time in milliseconds of a whole note (i.e. a full bar).
#define HALF          WHOLE/2
#define QUARTER       HALF/2
#define EIGHTH        QUARTER/2
#define EIGHTH_TRIPLE QUARTER/3
#define SIXTEENTH     EIGHTH/2

KeyDefinition toneKeypad[13] = {
  { TONE, HID_KEY_NONE },
  { TONE, NOTE_C4, NULL, drawC },
  { TONE, NOTE_CS4, NULL, drawCs },
  { TONE, NOTE_D4, NULL, drawD },
  { TONE, NOTE_DS4, NULL, drawDs },
  { TONE, NOTE_E4, NULL, drawE },
  { TONE, NOTE_F4, NULL, drawF },
  { TONE, NOTE_FS4, NULL, drawFs },
  { TONE, NOTE_G4, NULL, drawG },
  { TONE, NOTE_GS4, NULL, drawGs },
  { TONE, NOTE_A4, NULL, drawA},
  { TONE, NOTE_AS4, NULL, drawAs },
  { TONE, NOTE_B4, NULL, drawB }
};

void toneDrawGrid() {
  macroPad.display.setTextSize(1);
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 3; j++) {
      int key = ((i - 1) * 3) + (j);
      int x = (j - 1) * 16;
      int y = (i - 1) * 16;
      if (toneKeypad[key].characterCallback != NULL) {
        if (macroPad.buttonState[key - 1] == HIGH) {
          toneKeypad[key].characterCallback(x+64, y, 1, SH110X_BLACK, SH110X_WHITE);
        } else {
          toneKeypad[key].characterCallback(x+64, y, 1, SH110X_WHITE, SH110X_BLACK);
        }
      }
    }
  }
  macroPad.display.display();
}
void toneDisplayCallback() {
  macroPad.display.clearDisplay();
  macroPad.display.setCursor(0, 0);
  macroPad.display.setTextSize(1);
  macroPad.display.print(modes[mode].title);
  if (dateTimeSet) {
    macroPad.display.setTextSize(1);
    macroPad.display.setCursor(0, 16);
    macroPad.display.print(getDateTime());
  }
  toneDrawGrid();
  macroPad.display.display();
}

void toneKeyPressCallback(int key) {
  uint8_t keycode[6] = { 0 };
  if (usb_hid.ready()) {
    if (toneKeypad[key].hidType == TONE && keypad[key].key != HID_KEY_NONE) {
      macroPad.play(toneKeypad[key].key, QUARTER);
    } else {
    }
  }
}

void toneKeyDownCallback(int key) {}

void toneKeyUpCallback(int key) {}

void toneEncoderPressCallback() {
  if (usb_hid.ready()) {
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_MUTE);
    delay(10);
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
  }
}

void toneEncoderLongPressCallback() {
}

void toneEncoderCallback(int position, int direction) {
  if (usb_hid.ready()) {
    for (byte i = 0; i < 2; i++) {
      switch (direction) {
        case -1:
          usb_hid.sendReport16(RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_VOLUME_INCREMENT);
          delay(10);
          usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
          delay(10);
          break;
        case 1:
          usb_hid.sendReport16(RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_VOLUME_DECREMENT);
          delay(10);
          usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
          delay(10);
          break;
      }
    }
  }
}

Mode toneMode = {
  "Tone",
  toneDisplayCallback,
  toneKeyPressCallback,
  toneKeyDownCallback,
  toneKeyUpCallback,
  toneEncoderPressCallback,
  toneEncoderLongPressCallback,
  toneEncoderCallback
};
