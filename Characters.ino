#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8
#define CHAR_PADDING 4

void drawGrid(){
  for(int i = 64; i < 112; i += 16){
    Serial.println(i);
    
  }
  for(int i = 0; i < 64; i += 16){
    Serial.println(i);
    macroPad.display.drawFastHLine(64, i, 48, SH110X_WHITE);
  }
}

void drawBlank(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  macroPad.display.fillRect(startX, startY, size * (CHAR_WIDTH + (CHAR_PADDING * 2)), size * (CHAR_HEIGHT + (CHAR_PADDING * 2)), bg_color);
  macroPad.display.drawRect(startX, startY, size * (CHAR_WIDTH + (CHAR_PADDING * 2)), size * (CHAR_HEIGHT + (CHAR_PADDING * 2)), color);
}

void drawMediaPrev(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  int x0, y0, x1, y1, x2, y2;
  int width = CHAR_WIDTH / (CHAR_WIDTH * size) * 2;
  int height = CHAR_HEIGHT;
  x0 = startX + CHAR_PADDING;
  y0 = startY + CHAR_PADDING;
  macroPad.display.fillRect(x0, y0, width, height, color);
  x0 = startX + CHAR_PADDING + width;
  y0 = startY + CHAR_PADDING + (CHAR_HEIGHT * size / 2);
  x1 = x0 + (CHAR_WIDTH * size) - width;
  y1 = startY + CHAR_PADDING;
  x2 = x1;
  y2 = y1 + (CHAR_HEIGHT);
  macroPad.display.fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

void drawMediaNext(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  int x0, y0, x1, y1, x2, y2;
  int width = CHAR_WIDTH / (CHAR_WIDTH * size) * 2;
  int height = CHAR_HEIGHT;
  x0 = startX + CHAR_PADDING;
  y0 = startY + CHAR_PADDING;
  x1 = x0;
  y1 = y0 + (CHAR_HEIGHT * size);
  x2 = x0 + (CHAR_WIDTH * size) - width;
  y2 = y0 + (CHAR_HEIGHT * size / 2);
  macroPad.display.fillTriangle(x0, y0, x1, y1, x2, y2, color);
  x0 = startX + CHAR_PADDING + CHAR_WIDTH - width;
  y0 = startY + CHAR_PADDING;
  x1 = x0 + (CHAR_WIDTH / (CHAR_WIDTH * size));
  y1 = y0 + CHAR_HEIGHT;
  macroPad.display.fillRect(x0, y0, width, height, color);
}

void drawMediaPlay(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  int x0, y0, x1, y1, x2, y2;
  int width = CHAR_WIDTH / (CHAR_WIDTH * size) * 2;
  int height = CHAR_HEIGHT;
  x0 = startX + CHAR_PADDING;
  y0 = startY + CHAR_PADDING;
  x1 = x0;
  y1 = y0 + (CHAR_HEIGHT * size);
  x2 = x0 + (CHAR_WIDTH * size) - width;
  y2 = y0 + (CHAR_HEIGHT * size / 2);
  macroPad.display.fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

void drawArrowLeft(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY, 0x1B, color, bg_color, size + 1);
}

void drawArrowRight(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY, 0x1A, color, bg_color, size + 1);
}

void drawArrowUp(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY, 0x18, color, bg_color, size + 1);
}

void drawArrowDown(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY, 0x19, color, bg_color, size + 1);
}

void draw1(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x31, color, bg_color, size + 1);
}

void draw2(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x32, color, bg_color, size + 1);
}

void draw3(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x33, color, bg_color, size + 1);
}

void draw4(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x34, color, bg_color, size + 1);
}

void draw5(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x35, color, bg_color, size + 1);
}

void draw6(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x36, color, bg_color, size + 1);
}

void draw7(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x37, color, bg_color, size + 1);
}

void draw8(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x38, color, bg_color, size + 1);
}

void draw9(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x39, color, bg_color, size + 1);
}

void draw0(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x30, color, bg_color, size + 1);
}

void drawPeriod(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x2E, color, bg_color, size + 1);
}

void drawEnter(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x1C, color, bg_color, size + 1);
}

void drawC(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x43, color, bg_color, size + 1);
}

void drawCs(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING), 0x43, color, bg_color, size);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2) + (CHAR_WIDTH), startY + (CHAR_PADDING), 0x23, color, bg_color, size);
}
void drawD(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x44, color, bg_color, size + 1);
}

void drawDs(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING), 0x44, color, bg_color, size);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2) + (CHAR_WIDTH), startY + (CHAR_PADDING), 0x23, color, bg_color, size);
}

void drawE(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x45, color, bg_color, size + 1);
}

void drawF(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x46, color, bg_color, size + 1);
}

void drawFs(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING), 0x46, color, bg_color, size);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2) + (CHAR_WIDTH), startY + (CHAR_PADDING), 0x23, color, bg_color, size);
}

void drawG(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x47, color, bg_color, size + 1);
}

void drawGs(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING), 0x47, color, bg_color, size);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2) + (CHAR_WIDTH), startY + (CHAR_PADDING), 0x23, color, bg_color, size);
}

void drawA(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x41, color, bg_color, size + 1);
}

void drawAs(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING), 0x41, color, bg_color, size);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2) + (CHAR_WIDTH), startY + (CHAR_PADDING), 0x23, color, bg_color, size);
}

void drawB(int startX, int startY, int size, uint16_t bg_color, uint16_t color) {
  drawBlank(startX, startY, size, bg_color, color);
  macroPad.display.drawChar(startX + (CHAR_PADDING / 2), startY + (CHAR_PADDING / 2), 0x42, color, bg_color, size + 1);
}