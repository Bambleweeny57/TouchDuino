#include <SPI.h>
#include <SD.h>
#include "tft_ui.h"
#include "userconfig.h"
#include "file_browser.h"
#include "maxduino.h"

#define MOTOR_PIN 2
#define AUDIO_PIN 11

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(AUDIO_PIN, OUTPUT);

  initUI();            // TFT + Touch + SD + Banner
  listTapeFiles("/");  // Populate file list from SD
}

void loop() {
  if (!isPlaying()) {
    TouchAction action = detectTouchAction();
    handleTouchAction(action);
  }
}
