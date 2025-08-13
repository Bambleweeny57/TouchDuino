#include <SPI.h>
#include <SD.h>
#include "tft_ui.h"
#include "userconfig.h"
#include "file_browser.h"
#include "maxduino.h"

#define MOTOR_PIN 2
#define AUDIO_PIN 11

#define MODE_CALIBRATION 99

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

    // Example dispatcher
    switch (playMode) {
      case MODE_TAP:
        playTAP(file);
        break;
      case MODE_TZX:
        playTZX(file);
        break;
      case MODE_CDT:
        playCDT(file);
        break;
      case MODE_CAS:
        playCAS(file);
        break;
      case MODE_TSX:
        playTSX(file);
        break;
      case MODE_CALIBRATION:
        runCalibration();
        break;
    }
  }
}

void runCalibration() {
  Serial.println("Running signal calibration...");
  for (int i = 0; i < 100; i++) {
    sendBit(i % 2); // alternating bits
  }
  Serial.println("Calibration complete.");
}
