#include "maxduino.h"
#include "file_browser.h"
#include "format_dispatcher.h"

bool playbackActive = false;

bool isPlaying() {
  return playbackActive;
}

void playTapeFile(File &tapeFile, const String &filename) {
  playbackActive = true;
  dispatchPlayback(tapeFile, filename);
  playbackActive = false;
}

void stopPlayback() {
  playbackActive = false;
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
