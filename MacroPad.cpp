#include <Adafruit_SH110X.h>
#include <Adafruit_NeoPixel.h>
#include <RotaryEncoder.h>

class MacroPad {
private:

  uint8_t _speakerPinEnable;
  uint8_t _speakerPin;
  int _lastButtonState[12];
  int _encoderButtonState;
  int _lastEncoderButtonState;
  int _encoderPos;
  uint32_t _color[12];
  uint16_t j;
  void (*_keyPressCallback)(int key);
  void (*_keyDownCallback)(int key);
  void (*_keyUpCallback)(int key);
  void (*_encoderPressCallback)();
  void (*_encoderLongPressCallback)();
  void (*_encoderCallback)(int position, int direction);
public:
  MacroPad(Adafruit_NeoPixel &pixels, Adafruit_SH1106G &display, RotaryEncoder &encoder, uint8_t speakerPinEnable, uint8_t speakerPin)
    : pixels(pixels), display(display), encoder(encoder), _speakerPinEnable(speakerPinEnable), _speakerPin(speakerPin) {
    j = 0;
  }
  void begin() {
    for (uint8_t i = 0; i <= 12; i++) {
      pinMode(i, INPUT_PULLUP);
    }
    pinMode(this->_speakerPinEnable, OUTPUT);
    digitalWrite(this->_speakerPinEnable, HIGH);
    pinMode(this->_speakerPin, OUTPUT);
    digitalWrite(this->_speakerPin, LOW);
    this->pixels.begin();
    this->pixels.setBrightness(255);
    this->pixels.show();
    this->display.begin(0, true);  // we dont use the i2c address but we will reset!
    this->display.display();
    this->display.setTextSize(1);
    this->display.setTextWrap(false);
    this->display.setTextColor(SH110X_WHITE, SH110X_BLACK);
  }
  void setKeyPressCallback(void (*keyPressCallback)(int key)) {
    this->_keyPressCallback = keyPressCallback;
  }
  void setKeyUpCallback(void (*keyUpCallback)(int key)) {
    this->_keyUpCallback = keyUpCallback;
  }
  void setKeyDownCallback(void (*keyDownCallback)(int key)) {
    this->_keyDownCallback = keyDownCallback;
  }
  void setEncoderCallback(void (*encoderCallback)(int position, int direction)) {
    this->_encoderCallback = encoderCallback;
  }
  void setEncoderPressCallback(void (*encoderPressCallback)()) {
    this->_encoderPressCallback = encoderPressCallback;
  }
  void setEncoderLongPressCallback(void (*encoderLongPressCallback)()) {
    this->_encoderLongPressCallback = encoderLongPressCallback;
  }
  void loop() {
    for (int i = 0; i < this->pixels.numPixels(); i++) {
      if (this->buttonState[i] == 0) {
        int k = j >> 3;
        this->pixels.setPixelColor(i, this->Wheel(((i * 256 / this->pixels.numPixels()) + k) & 255));
      }
    }
    this->read();
    this->pixels.show();
    this->display.display();
    j++;
  }
  void read() {
    this->readButtons();
    this->readEncoderButton();
    this->readEncoder();
  }
  void readButtons() {
    for (int i = 0; i < 12; i++) {
      this->buttonState[i] = digitalRead(i + 1);
      if (this->buttonState[i] == LOW) {
        if (this->_keyDownCallback != NULL) this->_keyDownCallback(i + 1);
        //this->_pixels.setPixelColor(i, 0xFF0000);  // make white
        if (this->buttonState[i] != this->_lastButtonState[i]) {
          if (this->_keyPressCallback != NULL) this->_keyPressCallback(i + 1);
        }
      } else if (this->buttonState[i] == HIGH && this->buttonState[i] != this->_lastButtonState[i]) {
        if (this->_keyUpCallback != NULL) this->_keyUpCallback(i + 1);
      } else {
        this->pixels.setPixelColor(i, 0x000000);
      }
      this->_lastButtonState[i] = this->buttonState[i];
    }
  }
  void readEncoder() {
    this->encoder.tick();  // check the encoder
    int newPos = this->encoder.getPosition();
    if (this->_encoderPos != newPos) {
      this->_encoderPos = newPos;
      if (this->_encoderCallback != NULL) this->_encoderCallback(newPos, (int)this->encoder.getDirection());
    }
  }
  void readEncoderButton() {
    static unsigned long timer = 0;
    this->_encoderButtonState = digitalRead(0);

    if (this->_encoderButtonState == LOW && this->_encoderButtonState != this->_lastEncoderButtonState) {
      timer = millis();
    }
    if (this->_encoderButtonState == LOW && this->_encoderButtonState == this->_lastEncoderButtonState && timer != 0 && timer + 1000 <= millis()) {
      if (this->_encoderLongPressCallback != NULL) this->_encoderLongPressCallback();
      timer = 0;
    } else if (this->_encoderButtonState == HIGH && this->_encoderButtonState != this->_lastEncoderButtonState && timer != 0) {
      if (this->_encoderPressCallback != NULL) this->_encoderPressCallback();
    }
    this->_lastEncoderButtonState = this->_encoderButtonState;
  }
  void play(unsigned int frequency, unsigned long duration) {
    tone(_speakerPin, frequency, duration);
  }
  uint32_t Wheel(byte WheelPos) {
    if (WheelPos < 85) {
      return this->pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
      WheelPos -= 85;
      return this->pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
      WheelPos -= 170;
      return this->pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
  }
  int buttonState[12];
  Adafruit_NeoPixel pixels;
  Adafruit_SH1106G display;
  RotaryEncoder encoder;
};
