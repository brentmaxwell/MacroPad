#define ARRAY_SIZE(array) ((sizeof(array)) / (sizeof(array[0])))

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_NeoPixel.h>
#include <RotaryEncoder.h>
#include <Wire.h>
#include <Adafruit_TinyUSB.h>
#include <WiiChuck.h>
#include <RTClib.h>
#include <MIDI.h>

#include "MacroPad.cpp"
#include "Mode.h"

enum {
  RID_KEYBOARD = 1,
  RID_MOUSE,
  RID_CONSUMER_CONTROL,
  USB_MIDI,
  TONE
};

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(RID_KEYBOARD)),
  TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(RID_MOUSE)),
  TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(RID_CONSUMER_CONTROL))
};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &SPI1, OLED_DC, OLED_RST, OLED_CS);
RotaryEncoder encoder(PIN_ROTA, PIN_ROTB, RotaryEncoder::LatchMode::FOUR3);
MacroPad macroPad(pixels, display, encoder, PIN_SPEAKER_ENABLE, PIN_SPEAKER);
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, false);
Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, usbMIDI);
Accessory nunchuck;
RTC_Millis rtc;

bool dateTimeSet = false;

Mode modes[5];
int8_t mode = 0;
int8_t newMode;

void setup() {
  //TinyUSB_Device_Init(0);
  Serial.begin(115200);
  delay(100);
  usbMIDI.begin(0);
  usbMIDI.setHandleNoteOn(handleNoteOn);
  usbMIDI.setHandleNoteOff(handleNoteOff);
  usb_hid.begin();
  macroPad.begin();
  macroPad.setKeyPressCallback(keyPressCallback);
  macroPad.setKeyDownCallback(keyDownCallback);
  macroPad.setKeyUpCallback(keyUpCallback);
  macroPad.setEncoderCallback(encoderCallback);
  macroPad.setEncoderPressCallback(encoderPressCallback);
  macroPad.setEncoderLongPressCallback(encoderLongPressCallback);
  //nunchuck.begin();
  modes[0] = {
    "Media",
    mediaDisplayCallback,
    mediaKeyPressCallback,
    mediaKeyDownCallback,
    mediaKeyUpCallback,
    mediaEncoderPressCallback,
    mediaEncoderLongPressCallback,
    mediaEncoderCallback
  };
  modes[1] = {
    "KeyPad",
    keypadDisplayCallback,
    keypadKeyPressCallback,
    keypadKeyDownCallback,
    keypadKeyUpCallback,
    keypadEncoderPressCallback,
    keypadEncoderLongPressCallback,
    keypadEncoderCallback
  };
  modes[2] = {
    "NavPad",
    navDisplayCallback,
    navKeyPressCallback,
    navKeyDownCallback,
    navKeyUpCallback,
    navEncoderPressCallback,
    navEncoderLongPressCallback,
    navEncoderCallback
  };
  modes[3] = {
    "Midi",
    midiDisplayCallback,
    midiKeyPressCallback,
    midiKeyDownCallback,
    midiKeyUpCallback,
    midiEncoderPressCallback,
    midiEncoderLongPressCallback,
    midiEncoderCallback
  };
  modes[4] = {
    "Tone",
    toneDisplayCallback,
    toneKeyPressCallback,
    toneKeyDownCallback,
    toneKeyUpCallback,
    toneEncoderPressCallback,
    toneEncoderLongPressCallback,
    toneEncoderCallback
  };
}

void loop() {
  macroPad.loop();
  loopSerial();
  updateDisplay();
  usbMIDI.read();
}

void updateDisplay() {
  if (mode == -1) {
    macroPad.display.clearDisplay();
    macroPad.display.setCursor(0, 0);
    macroPad.display.setTextSize(1);
    macroPad.display.print("Set Mode");
    macroPad.display.setCursor(0, 16);
    macroPad.display.setTextSize(1);
    macroPad.display.print(modes[newMode].title);
    display.display();
  } else {
        
    if (modes[mode].displayCallback != NULL) modes[mode].displayCallback();
  }
}

void keyPressCallback(int key) {
  if (mode != -1) {
    if (modes[mode].keyPressCallback != NULL) modes[mode].keyPressCallback(key);
  }
}

void keyDownCallback(int key) {
  if (mode != -1) {
    if (modes[mode].keyDownCallback != NULL) modes[mode].keyDownCallback(key);
  }
}

void keyUpCallback(int key) {
  if (mode != -1) {
    if (modes[mode].keyUpCallback != NULL) modes[mode].keyUpCallback(key);
  }
}

void encoderPressCallback() {
  if (mode == -1) {
    mode = newMode;
  } else {
    if (modes[mode].encoderPressCallback != NULL) modes[mode].encoderPressCallback();
  }
}

void encoderLongPressCallback() {
  if (mode != -1) {
    newMode = mode;
    mode = -1;
  }
}

void encoderCallback(int position, int direction) {
  if (mode == -1) {
    int nextMode = newMode;
    switch (direction) {
      case -1: nextMode++; break;
      case 1: nextMode--; break;
    }
    if (nextMode < 0) {
      nextMode = ARRAY_SIZE(modes) - 1;
    }
    if (nextMode >= ARRAY_SIZE(modes)) {
      nextMode = 0;
    }
    newMode = nextMode;
  } else {
    if (modes[mode].encoderCallback != NULL) modes[mode].encoderCallback(position, direction);
  }
}

String getDateTime() {
  if (dateTimeSet) {
    DateTime now = rtc.now();
    char dateTime[19];
    sprintf(dateTime, "%04d/%02d/%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    return String(dateTime);
  } else {
    return String(micros());
  }
}
void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // Log when a note is pressed.
  Serial.print("Note on: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  // Log when a note is released.
  Serial.print("Note off: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);
}
