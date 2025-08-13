#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <SD.h>
#include "tft_ui.h"
#include "userconfig.h"

#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   7
#define TOUCH_CS  8

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen touch(TOUCH_CS);

String fileList[MAX_FILES];
int fileCount = 0;
int selectedFile = 0;

void initUI() {
  tft.begin();
  touch.begin();
  touch.setRotation(1);
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  drawBanner();
  drawButtons();
}

void drawBanner() {
  File bmpFile = SD.open("logo.bmp");
  if (!bmpFile) return;

  int x = 0, y = 0;
  bmpFile.seek(54); // Skip BMP header
  for (int row = 0; row < 64; row++) {
    for (int col = 0; col < 320; col++) {
      byte b = bmpFile.read();
      byte g = bmpFile.read();
      byte r = bmpFile.read();
      uint16_t color = tft.color565(r, g, b);
      tft.drawPixel(x + col, y + row, color);
    }
  }
  bmpFile.close();
}

void drawProgressBar(float progress) {
  int barWidth = (int)(progress * SCREEN_WIDTH);
  tft.fillRect(0, 64, SCREEN_WIDTH, 10, ILI9341_DARKGREY);
  tft.fillRect(0, 64, barWidth, 10, ILI9341_GREEN);
}

void drawFileList() {
  tft.fillRect(0, 74, SCREEN_WIDTH, SCREEN_HEIGHT - 74 - BUTTON_HEIGHT, ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  int start = max(0, selectedFile - 2);
  int end = min(fileCount, start + 5);

  for (int i = start; i < end; i++) {
    int y = 74 + (i - start) * 24;
    if (i == selectedFile) {
      tft.fillRect(0, y, SCREEN_WIDTH, 24, ILI9341_BLUE);
      tft.setTextColor(ILI9341_YELLOW);
    } else {
      tft.setTextColor(ILI9341_WHITE);
    }
    tft.setCursor(5, y + 4);
    tft.print(fileList[i]);
  }
}

void drawButtons() {
  int y = SCREEN_HEIGHT - BUTTON_HEIGHT;
  tft.fillRect(0, y, SCREEN_WIDTH, BUTTON_HEIGHT, ILI9341_BLUE);

  // Prev ◀
  tft.fillTriangle(20, y + 10, 20, y + 30, 10, y + 20, ILI9341_WHITE);

  // Play ►
  tft.fillTriangle(80, y + 10, 80, y + 30, 95, y + 20, ILI9341_WHITE);

  // Stop ■
  tft.fillRect(140, y + 15, 20, 20, ILI9341_WHITE);

  // Next ▶
  tft.fillTriangle(200, y + 10, 200, y + 30, 215, y + 20, ILI9341_WHITE);

  // Menu ≡
  tft.fillRect(260, y + 15, 30, 3, ILI9341_WHITE);
  tft.fillRect(260, y + 22, 30, 3, ILI9341_WHITE);
  tft.fillRect(260, y + 29, 30, 3, ILI9341_WHITE);
}

TouchAction detectTouchAction() {
  if (!touch.touched()) return TOUCH_NONE;
  TS_Point p = touch.getPoint();
  int x = map(p.x, 200, 3800, 0, SCREEN_WIDTH);

  if (x < 64) return TOUCH_PREV;
  if (x < 128) return TOUCH_PLAY;
  if (x < 192) return TOUCH_STOP;
  if (x < 256) return TOUCH_NEXT;
  return TOUCH_MENU;
}

void scrollFileList(int direction) {
  selectedFile += direction;
  if (selectedFile < 0) selectedFile = 0;
  if (selectedFile >= fileCount) selectedFile = fileCount - 1;
  drawFileList();
}

void listTapeFilesRecursive(File dir, String pathPrefix = "") {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;

    String name = entry.name();
    name.toLowerCase();

    if (entry.isDirectory()) {
      listTapeFilesRecursive(entry, pathPrefix + name + "/");
    } else {
      if (name != "logo.bmp" && (name.endsWith(".tap") || name.endsWith(".tzx") ||
          name.endsWith(".cdt") || name.endsWith(".cas"))) {
        if (fileCount < MAX_FILES) {
          fileList[fileCount++] = pathPrefix + name;
        }
      }
    }
    entry.close();
  }
}

void listTapeFiles() {
  fileCount = 0;
  File root = SD.open("/");
  listTapeFilesRecursive(root);
  drawFileList();
}
