#define DRUM_HAT_PEDAL 44
#define DRUM_HAT_CLOSE 42
#define DRUM_HAT_OPEN 46
#define DRUM_CROSS_STICK 37
#define DRUM_SNARE 38
#define DRUM_ROD 91
#define DRUM_FLOOR_TOM 43
#define DRUM_LOW_TOM 47
#define DRUM_HI_TOM 48
#define DRUM_BASS 35
#define DRUM_KICK 36
#define DRUM_COWBELL 56

KeyDefinition midiKeypad[13] = {
  { USB_MIDI, HID_KEY_NONE },
  { USB_MIDI, DRUM_HAT_PEDAL, NULL, drawBlank },
  { USB_MIDI, DRUM_HAT_CLOSE, NULL, drawBlank },
  { USB_MIDI, DRUM_HAT_OPEN, NULL, drawBlank },
  { USB_MIDI, DRUM_CROSS_STICK, NULL, drawBlank },
  { USB_MIDI, DRUM_SNARE, NULL, drawBlank },
  { USB_MIDI, DRUM_ROD, NULL, drawBlank },
  { USB_MIDI, DRUM_FLOOR_TOM, NULL, drawBlank },
  { USB_MIDI, DRUM_LOW_TOM, NULL, drawBlank },
  { USB_MIDI, DRUM_HI_TOM, NULL, drawBlank },
  { USB_MIDI, DRUM_BASS, NULL, drawBlank },
  { USB_MIDI, DRUM_KICK, NULL, drawBlank },
  { USB_MIDI, DRUM_COWBELL, NULL, drawBlank }
};

void midiDrawGrid() {
  macroPad.display.setTextSize(1);
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 3; j++) {
      int key = ((i - 1) * 3) + (j);
      int x = (j - 1) * 16;
      int y = (i - 1) * 16;
      if (midiKeypad[key].characterCallback != NULL) {
        if (macroPad.buttonState[key - 1] == HIGH) {
          midiKeypad[key].characterCallback(x+64, y, 1, SH110X_BLACK, SH110X_WHITE);
        } else {
          midiKeypad[key].characterCallback(x+64, y, 1, SH110X_WHITE, SH110X_BLACK);
        }
      }
    }
  }
  macroPad.display.display();
}

void midiDisplayCallback() {
  macroPad.display.clearDisplay();
  macroPad.display.setCursor(0, 0);
  macroPad.display.setTextSize(1);
  macroPad.display.print(modes[mode].title);
  if (dateTimeSet) {
    macroPad.display.setTextSize(1);
    macroPad.display.setCursor(0, 16);
    macroPad.display.print(getDateTime());
  }
  midiDrawGrid();
  macroPad.display.display();
}
void midiKeyPressCallback(int key) {
  if (midiKeypad[key].hidType == USB_MIDI && midiKeypad[key].key != HID_KEY_NONE) {
    usbMIDI.sendNoteOn(midiKeypad[key].key, 127, 1);
  } else {
  }
}

void midiKeyDownCallback(int key) {
}

void midiKeyUpCallback(int key) {
  if (usb_hid.ready()) {
    if (midiKeypad[key].hidType == USB_MIDI && midiKeypad[key].key != HID_KEY_NONE) {
      usbMIDI.sendNoteOff(midiKeypad[key].key, 127, 1);
    } else {
    }
  }
}

void midiEncoderPressCallback() {
  if (usb_hid.ready()) {
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_MUTE);
    delay(10);
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
  }
}

void midiEncoderLongPressCallback() {
}

void midiEncoderCallback(int position, int direction) {
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

Mode midiMode = {
  "Midi",
  midiDisplayCallback,
  midiKeyPressCallback,
  midiKeyDownCallback,
  midiKeyUpCallback,
  midiEncoderPressCallback,
  midiEncoderLongPressCallback,
  midiEncoderCallback
};
