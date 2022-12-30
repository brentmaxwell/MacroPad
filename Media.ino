KeyDefinition mediaKeypad[13] = {
  { RID_KEYBOARD, HID_KEY_NONE },
  { RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_SCAN_PREVIOUS, NULL, drawMediaPrev },
  { RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_PLAY_PAUSE, NULL, drawMediaPlay },
  { RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_SCAN_NEXT, NULL, drawMediaNext },
  { RID_KEYBOARD, HID_KEY_ARROW_LEFT, NULL, drawArrowLeft },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_ARROW_RIGHT, NULL, drawArrowRight },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_KEYBOARD, HID_KEY_NONE, NULL, drawBlank },
  { RID_CONSUMER_CONTROL, HID_KEY_NONE, NULL, drawBlank }
};

uint16_t mediaEncoder[3] = {
  HID_USAGE_CONSUMER_MUTE,
  HID_USAGE_CONSUMER_VOLUME_DECREMENT,
  HID_USAGE_CONSUMER_VOLUME_INCREMENT
};

void mediaDrawGrid() {
  macroPad.display.setTextSize(1);
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 3; j++) {
      int key = ((i - 1) * 3) + (j);
      int x = (j - 1) * 16;
      int y = (i - 1) * 16;
      if (mediaKeypad[key].characterCallback != NULL) {
        if (macroPad.buttonState[key - 1] == HIGH) {
          mediaKeypad[key].characterCallback(x+64, y, 1, SH110X_BLACK, SH110X_WHITE);
        } else {
          mediaKeypad[key].characterCallback(x+64, y, 1, SH110X_WHITE, SH110X_BLACK);
        }
      }
    }
  }
  macroPad.display.display();
}

void mediaDisplayCallback() {
  macroPad.display.clearDisplay();
  macroPad.display.clearDisplay();
  macroPad.display.setCursor(0, 0);
  macroPad.display.setTextSize(1);
  macroPad.display.print(modes[mode].title);
  if (dateTimeSet) {
    macroPad.display.setTextSize(1);
    macroPad.display.setCursor(0, 16);
    macroPad.display.print(getDateTime());
  }
  mediaDrawGrid();
  macroPad.display.display();
}

void mediaKeyPressCallback(int key) {
  if (usb_hid.ready()) {
    if (mediaKeypad[key].hidType == RID_CONSUMER_CONTROL) {
      usb_hid.sendReport16(RID_CONSUMER_CONTROL, mediaKeypad[key].key);
      delay(10);
      usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
    }
    if (mediaKeypad[key].hidType == RID_KEYBOARD) {
      uint8_t keycode[6] = { 0 };
      keycode[0] = mediaKeypad[key].key;
      usb_hid.keyboardReport(RID_KEYBOARD, 0, keycode);
      delay(10);
      usb_hid.keyboardReport(RID_KEYBOARD, 0, HID_KEY_NONE);
    }
  }
}

void mediaKeyDownCallback(int key) {}

void mediaKeyUpCallback(int key) {}

void mediaEncoderPressCallback() {
  if (usb_hid.ready()) {
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, mediaEncoder[0]);
    delay(10);
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
  }
}

void mediaEncoderLongPressCallback() {
}

void mediaEncoderCallback(int position, int direction) {
  if (usb_hid.ready()) {
    for (byte i = 0; i < 2; i++) {
      switch (direction) {
        case -1:
          usb_hid.sendReport16(RID_CONSUMER_CONTROL, mediaEncoder[2]);
          delay(10);
          usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
          delay(10);
          break;
        case 1:
          usb_hid.sendReport16(RID_CONSUMER_CONTROL, mediaEncoder[1]);
          delay(10);
          usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
          delay(10);
          break;
      }
    }
  }
}

Mode mediaMode = {
  "Media",
  mediaDisplayCallback,
  mediaKeyPressCallback,
  mediaKeyDownCallback,
  mediaKeyUpCallback,
  mediaEncoderPressCallback,
  mediaEncoderLongPressCallback,
  mediaEncoderCallback
};
