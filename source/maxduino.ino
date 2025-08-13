#include <SPI.h>
#include <SD.h>
#include "tft_ui.h"
#include "userconfig.h"

// Touchscreen CS pin
#define CS_PIN 8

// Playback control
bool isPlaying = false;
File currentFile;
unsigned long playbackStart = 0;
unsigned long playbackSize = 0;

// Audio output pin
#define AUDIO_PIN 9

void setup() {
  Serial.begin(115200);
  pinMode(AUDIO_PIN, OUTPUT);

  if (!SD.begin()) {
    Serial.println("SD init failed!");
    while (true);
  }

  initUI();
  listTapeFiles();
}

void listTapeFiles() {
  File root = SD.open("/");
  fileCount = 0;

  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;

    String name = entry.name();
    name.toLowerCase();

    if (name != "logo.bmp" && (name.endsWith(".tap") || name.endsWith(".tzx") ||
        name.endsWith(".cdt") || name.endsWith(".cas"))) {
      if (fileCount < MAX_FILES) {
        fileList[fileCount++] = name;
      }
    }
    entry.close();
  }

  drawFileList();
}

void playFile(String filename) {
  currentFile = SD.open(filename);
  if (!currentFile) {
    Serial.println("Failed to open file: " + filename);
    return;
  }

  isPlaying = true;
  playbackStart = millis();
  playbackSize = currentFile.size();

  while (currentFile.available()) {
    byte b = currentFile.read();
    analogWrite(AUDIO_PIN, b); // Replace with MaxDuino signal logic
    delayMicroseconds(100);    // Adjust timing as needed

    float progress = (float)(currentFile.position()) / playbackSize;
    drawProgressBar(progress);

    TouchAction action = detectTouchAction();
    if (action == TOUCH_STOP) {
      currentFile.close();
      isPlaying = false;
      drawProgressBar(0);
      return;
    }
  }

  currentFile.close();
  isPlaying = false;
  drawProgressBar(1);
}

void loop() {
  if (!isPlaying) {
    TouchAction action = detectTouchAction();
    switch (action) {
      case TOUCH_PREV:
        scrollFileList(-1);
        break;
      case TOUCH_NEXT:
        scrollFileList(1);
        break;
      case TOUCH_PLAY:
        playFile(fileList[selectedFile]);
        break;
      case TOUCH_MENU:
        // Future config screen
        break;
      default:
        break;
    }
  }
}
