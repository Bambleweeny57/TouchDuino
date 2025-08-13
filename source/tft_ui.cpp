#include "tft_ui.h"

// TFT and touchscreen objects
Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9); // CS, DC
XPT2046_Touchscreen touch(CS_PIN);              // Define CS_PIN in your main sketch

// File list
#define MAX_FILES 50
String fileList[MAX_FILES];
int fileCount = 0;
int selectedFile = 0;
int scrollOffset = 0;

void initUI() {
  tft.begin();
  tft.setRotation(1); // Landscape
  tft.fillScreen(ILI9341_BLACK);
  drawBanner();
  drawProgressBar(0);
  drawFileList();
  drawButtons();
}

void drawBanner() {
  File bmpFile = SD.open("/logo.bmp");
  if (!bmpFile) return;

  // Simple BMP loader (24-bit, no compression)
  uint16_t x = 0, y = 0;
  bmpFile.seek(54); // Skip BMP header
  for (y = 0; y < BANNER_HEIGHT; y++) {
    for (x = 0; x < SCREEN_WIDTH; x++) {
      uint8_t b = bmpFile.read();
      uint8_t g = bmpFile.read();
      uint8_t r = bmpFile.read();
      uint16_t color = tft.color565(r, g, b);
      tft.drawPixel(x, y, color);
    }
  }
  bmpFile.close();
}

void drawProgressBar(float progress) {
  int barWidth = SCREEN_WIDTH * progress;
  tft.fillRect(0, BANNER_HEIGHT, SCREEN_WIDTH, PROGRESS_HEIGHT, ILI9341_DARKGREY);
  tft.fillRect(0, BANNER_HEIGHT, barWidth, PROGRESS_HEIGHT, ILI9341_GREEN);
}

void drawFileList() {
  tft.fillRect(0, FILE_LIST_Y, SCREEN_WIDTH, FILE_LIST_HEIGHT, ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, FILE_LIST_Y);

  for (int i = 0; i < 5 && (i + scrollOffset) < fileCount; i++) {
    if ((i + scrollOffset) == selectedFile) {
      tft.setTextColor(ILI9341_YELLOW);
    } else {
      tft.setTextColor(ILI9341_WHITE);
    }
    tft.setCursor(10, FILE_LIST_Y + i * 20);
    tft.print(fileList[i + scrollOffset]);
  }
}

void drawButtons() {
  int y = SCREEN_HEIGHT - BUTTON_HEIGHT;
  tft.fillRect(0, y, SCREEN_WIDTH, BUTTON_HEIGHT, ILI9341_BLUE);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);

  tft.setCursor(10, y + 10);   tft.print("Prev");
  tft.setCursor(70, y + 10);   tft.print("Play");
  tft.setCursor(130, y + 10);  tft.print("Stop");
  tft.setCursor(190, y + 10);  tft.print("Next");
  tft.setCursor(250, y + 10);  tft.print("Menu");
}

TouchAction detectTouchAction() {
  if (!touch.touched()) return TOUCH_NONE;
  TS_Point p = touch.getPoint();
  int x = map(p.x, 200, 3800, 0, SCREEN_WIDTH); // Calibrate as needed
  int y = map(p.y, 200, 3800, 0, SCREEN_HEIGHT);

  if (y > SCREEN_HEIGHT - BUTTON_HEIGHT) {
    if (x < 64) return TOUCH_PREV;
    else if (x < 128) return TOUCH_PLAY;
    else if (x < 192) return TOUCH_STOP;
    else if (x < 256) return TOUCH_NEXT;
    else return TOUCH_MENU;
  }
  return TOUCH_NONE;
}

void scrollFileList(int direction) {
  scrollOffset += direction;
  if (scrollOffset < 0) scrollOffset = 0;
  if (scrollOffset > fileCount - 5) scrollOffset = fileCount - 5;
  drawFileList();
}

void loadFileFromList(int index) {
  selectedFile = index;
  drawFileList();
  // Trigger MaxDuino playback logic here
}

void refreshUI() {
  drawProgressBar(0);
  drawFileList();
  drawButtons();
}
