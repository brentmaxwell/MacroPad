#include <Arduino.h>
#ifndef _MODE_H
#define _MODE_H

struct Mode {
  String title;
  void (*displayCallback)();
  void (*keyPressCallback)(int key);
  void (*keyDownCallback)(int key);
  void (*keyUpCallback)(int key);
  void (*encoderPressCallback)();
  void (*encoderLongPressCallback)();
  void (*encoderCallback)(int position, int direction);
};

struct KeyDefinition {
  uint8_t hidType;
  uint16_t key;
  uint32_t color;
  void (*characterCallback)(int startX, int startY, int size, uint16_t bgColor, uint16_t color);
};

#endif