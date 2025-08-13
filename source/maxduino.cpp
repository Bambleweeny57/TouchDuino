#include "maxduino.h"
#include "file_browser.h"
#include "userconfig.h"

bool playbackActive = false;

bool isPlaying() {
  return playbackActive;
}

void playTapeFile(File &tapeFile, const String &filename) {
  playbackActive = true;
  // Actual playback logic here (e.g., bit-banging or DAC output)
  // Placeholder:
  while (tapeFile.available()) {
    byte b = tapeFile.read();
    // Output to AUDIO_PIN
    delayMicroseconds(100); // Simulate timing
  }
  playbackActive = false;
}

void stopPlayback() {
  playbackActive = false;
  // Additional cleanup if needed
}

void handleTouchAction(TouchAction action) {
  switch (action) {
    case TOUCH_PREV: scrollFileList(-1); break;
    case TOUCH_NEXT: scrollFileList(1); break;
    case TOUCH_PLAY: {
      String fullPath = loadFileFromList();
      if (fullPath.length() > 0) {
        File tapeFile = SD.open(fullPath);
        if (tapeFile) {
          digitalWrite(MOTOR_PIN, HIGH);
          playTapeFile(tapeFile, fullPath);
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
