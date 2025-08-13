#ifndef TFT_UI_H
#define TFT_UI_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <SD.h>

// TFT and Touchscreen objects
extern Adafruit_ILI9341 tft;
extern XPT2046_Touchscreen touch;

// UI constants
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define BUTTON_HEIGHT 40
#define PROGRESS_HEIGHT 8
#define BANNER_HEIGHT 64
#define FILE_LIST_Y (BANNER_HEIGHT + PROGRESS_HEIGHT)
#define FILE_LIST_HEIGHT (SCREEN_HEIGHT - FILE_LIST_Y - BUTTON_HEIGHT)

// Touch zones
enum TouchAction {
  TOUCH_NONE,
  TOUCH_PREV,
  TOUCH_PLAY,
  TOUCH_STOP,
  TOUCH_NEXT,
  TOUCH_MENU
};

// UI functions
void initUI();
void drawBanner();
void drawProgressBar(float progress);
void drawFileList();
void drawButtons();
TouchAction detectTouchAction();
void scrollFileList(int direction);
void listTapeFiles();                      
void listTapeFilesRecursive(File dir, String pathPrefix = "");
String loadFileFromList(); // ✅ Reintroduced for modular file access

#endif
