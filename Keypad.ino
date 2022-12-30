KeyDefinition keypad[13] = {
  { RID_KEYBOARD, HID_KEY_NONE },
  { RID_KEYBOARD, HID_KEY_KEYPAD_1, NULL, draw1 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_2, NULL, draw2 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_3, NULL, draw3 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_4, NULL, draw4 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_5, NULL, draw5 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_6, NULL, draw6 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_7, NULL, draw7 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_8, NULL, draw8 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_9, NULL, draw9 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_DECIMAL, NULL, drawPeriod },
  { RID_KEYBOARD, HID_KEY_KEYPAD_0, NULL, draw0 },
  { RID_KEYBOARD, HID_KEY_KEYPAD_ENTER, NULL, drawEnter }
};

void keypadDrawGrid() {
  macroPad.display.setTextSize(1);
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 3; j++) {
      int key = ((i - 1) * 3) + (j);
      int x = (j - 1) * 16;
      int y = (i - 1) * 16;
      if (keypad[key].characterCallback != NULL) {
        if (macroPad.buttonState[key - 1] == HIGH) {
          keypad[key].characterCallback(x+64, y, 1, SH110X_BLACK, SH110X_WHITE);
        } else {
          keypad[key].characterCallback(x+64, y, 1, SH110X_WHITE, SH110X_BLACK);
        }
      }
    }
  }
  macroPad.display.display();
}
void keypadDisplayCallback() {
  macroPad.display.clearDisplay();
  macroPad.display.setCursor(0, 0);
  macroPad.display.setTextSize(1);
  macroPad.display.print(modes[mode].title);
  if (dateTimeSet) {
    macroPad.display.setTextSize(1);
    macroPad.display.setCursor(0, 16);
    macroPad.display.print(getDateTime());
  }
  keypadDrawGrid();
  macroPad.display.display();
}

void keypadKeyPressCallback(int key) {
  uint8_t keycode[6] = { 0 };
  if (usb_hid.ready()) {
    if (keypad[key].hidType == RID_KEYBOARD && keypad[key].key != HID_KEY_NONE) {
      keycode[0] = keypad[key].key;
      usb_hid.keyboardReport(RID_KEYBOARD, 0, keycode);
      delay(10);
      usb_hid.keyboardReport(RID_KEYBOARD, 0, HID_KEY_NONE);
    } else {
    }
  }
}

void keypadKeyDownCallback(int key) {}

void keypadKeyUpCallback(int key) {}

void keypadEncoderPressCallback() {
  if (usb_hid.ready()) {
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_MUTE);
    delay(10);
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
  }
}

void keypadEncoderLongPressCallback() {
}

void keypadEncoderCallback(int position, int direction) {
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

Mode keypadMode = {
  "Keypad",
  keypadDisplayCallback,
  keypadKeyPressCallback,
  keypadKeyDownCallback,
  keypadKeyUpCallback,
  keypadEncoderPressCallback,
  keypadEncoderLongPressCallback,
  keypadEncoderCallback
};
