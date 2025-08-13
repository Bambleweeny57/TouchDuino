#include <SPI.h>
#include <SD.h>
#include "tft_ui.h"
#include "userconfig.h"

#define MOTOR_PIN 2
#define AUDIO_PIN 11

bool isPlaying = false;
File currentFile;
unsigned long playbackSize = 0;
String currentPath = "/";

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(AUDIO_PIN, OUTPUT);
  initUI();            // TFT + Touch + SD + Banner
  listTapeFiles("/");
}

void loop() {
  if (!isPlaying) {
    TouchAction action = detectTouchAction();
    switch (action) {
      case TOUCH_PREV: scrollFileList(-1); break;
      case TOUCH_NEXT: scrollFileList(1); break;
      case TOUCH_PLAY: {
        String selected = fileList[selectedFile];
        if (selected == "...") {
          int slashIndex = currentPath.lastIndexOf('/');
          currentPath = (slashIndex <= 0) ? "/" : currentPath.substring(0, slashIndex);
          listTapeFiles(currentPath);
        } else if (selected.startsWith(">")) {
          String folderName = selected.substring(1);
          String newPath = currentPath + "/" + folderName;
          listTapeFiles(newPath);
        } else {
          String fullPath = currentPath + "/" + selected;
          File tapeFile = SD.open(fullPath);
          if (tapeFile) {
            digitalWrite(MOTOR_PIN, HIGH);
            playTapeFile(tapeFile, selected);
            digitalWrite(MOTOR_PIN, LOW);
            tapeFile.close();
          }
        }
        break;
      }
      case TOUCH_STOP: stopPlayback(); break;
      default: break;
    }
  }
}

void listTapeFiles(String path) {
  currentPath = path;
  File dir = SD.open(path);
  fileCount = 0;

  if (path != "/") {
    fileList[fileCount++] = "...";
  }

  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;
    String name = entry.name();
    name.toLowerCase();

    if (entry.isDirectory()) {
      if (fileCount < MAX_FILES) {
        fileList[fileCount++] = String(">") + name;
      }
    } else if (name != "logo.bmp" && (
        name.endsWith(".tap") || name.endsWith(".tzx") ||
        name.endsWith(".cdt") || name.endsWith(".cas"))) {
      if (fileCount < MAX_FILES) {
        fileList[fileCount++] = name;
      }
    }
    entry.close();
  }

  drawFileList();
}

void playTapeFile(File file, String name) {
  isPlaying = true;
  playbackSize = file.size();

  if (name.endsWith(".tap")) playTAP(file);
  else if (name.endsWith(".tzx")) playTZX(file);
  else if (name.endsWith(".cdt")) playCDT(file);
  else if (name.endsWith(".cas")) playCAS(file);

  isPlaying = false;
  drawProgressBar(1);
}

void playTAP(File file) {
  while (file.available()) {
    uint16_t len = file.read() | (file.read() << 8);
    for (uint16_t i = 0; i < len; i++) {
      sendByte(file.read());
    }
    drawProgressBar((float)file.position() / playbackSize);
  }
}

void playTZX(File file) {
  while (file.available()) {
    byte blockID = file.read();
    switch (blockID) {
      case 0x10: playStandardBlock(file); break;
      case 0x11: playTurboBlock(file); break;
      case 0x20: playPauseBlock(file); break;
      default: skipUnknownBlock(file); break;
    }
    drawProgressBar((float)file.position() / playbackSize);
  }
}

void playCDT(File file) {
  while (file.available()) {
    byte blockID = file.read();
    switch (blockID) {
      case 0x10: playStandardBlock(file); break;
      case 0x11: playTurboBlock(file); break;
      case 0x20: playPauseBlock(file); break;
      default: skipUnknownBlock(file); break;
    }
    drawProgressBar((float)file.position() / playbackSize);
  }
}

void playCAS(File file) {
  while (file.available()) {
    sendByte(file.read());
    drawProgressBar((float)file.position() / playbackSize);
  }
}

void playStandardBlock(File file) {
  uint16_t pause = file.read() | (file.read() << 8);
  uint16_t len = file.read() | (file.read() << 8);
  for (uint16_t i = 0; i < len; i++) sendByte(file.read());
  delay(pause);
}

void playTurboBlock(File file) {
  file.seek(file.position() + 15); // Skip turbo header
  uint16_t len = file.read() | (file.read() << 8);
  for (uint16_t i = 0; i < len; i++) sendByte(file.read());
}

void playPauseBlock(File file) {
  uint16_t pause = file.read() | (file.read() << 8);
  delay(pause);
}

void skipUnknownBlock(File file) {
  uint32_t len = file.read() | (file.read() << 8) | (file.read() << 16) | (file.read() << 24);
  file.seek(file.position() + len);
}

void sendByte(byte b) {
  for (int i = 0; i < 8; i++) {
    sendBit(b & (1 << (7 - i)));
  }
}

void sendBit(bool bit) {
  int pulse = bit ? 2168 : 667;
  digitalWrite(AUDIO_PIN, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(AUDIO_PIN, LOW);
  delayMicroseconds(pulse);
}

void stopPlayback() {
  digitalWrite(MOTOR_PIN, LOW);
  isPlaying = false;
  drawProgressBar(0);
}
