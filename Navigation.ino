KeyDefinition navKeypad[13] = {
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_PAGE_UP, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_ARROW_UP, NULL, drawArrowUp },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_ARROW_LEFT, NULL, drawArrowLeft },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_ARROW_RIGHT, NULL, drawArrowRight },
  { RID_KEYBOARD, HID_KEY_PAGE_DOWN, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_ARROW_DOWN, NULL, drawArrowDown },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank }
};

void navDrawGrid() {
  macroPad.display.setTextSize(1);
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 3; j++) {
      int key = ((i - 1) * 3) + (j);
      int x = (j - 1) * 16;
      int y = (i - 1) * 16;
      if (navKeypad[key].characterCallback != NULL) {
        if (macroPad.buttonState[key - 1] == HIGH) {
          navKeypad[key].characterCallback(x+64, y, 1, SH110X_BLACK, SH110X_WHITE);
        } else {
          navKeypad[key].characterCallback(x+64, y, 1, SH110X_WHITE, SH110X_BLACK);
        }
      }
    }
  }
  macroPad.display.display();
}

void navDisplayCallback() {
  macroPad.display.clearDisplay();
  macroPad.display.setCursor(0, 0);
  macroPad.display.setTextSize(1);
  macroPad.display.print(modes[mode].title);
  if (dateTimeSet) {
    macroPad.display.setTextSize(1);
    macroPad.display.setCursor(0, 16);
    macroPad.display.print(getDateTime());
  }
  navDrawGrid();
  macroPad.display.display();
}

void navKeyPressCallback(int key) {
  uint8_t keycode[6] = { 0 };
  if (usb_hid.ready()) {
    if (navKeypad[key].hidType == RID_KEYBOARD && navKeypad[key].key != HID_KEY_NONE) {
      keycode[0] = navKeypad[key].key;
      usb_hid.keyboardReport(RID_KEYBOARD, 0, keycode);
      delay(10);
      usb_hid.keyboardReport(RID_KEYBOARD, 0, HID_KEY_NONE);
    } else {
    }
  }
}

void navKeyDownCallback(int key) {}
void navKeyUpCallback(int key) {}

void navEncoderPressCallback() {
  if (usb_hid.ready()) {
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_MUTE);
    delay(10);
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
  }
}

void navEncoderLongPressCallback() {
}

void navEncoderCallback(int position, int direction) {
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

Mode navMode = {
  "NavPad",
  navDisplayCallback,
  navKeyPressCallback,
  navKeyDownCallback,
  navKeyUpCallback,
  navEncoderPressCallback,
  navEncoderLongPressCallback,
  navEncoderCallback
};
