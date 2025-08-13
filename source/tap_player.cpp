// tap_player.cpp
#include "tap_player.h"

void playTAP(File &file) {
  // Simple TAP playback logic
  while (file.available()) {
    byte b = file.read();
    delayMicroseconds(100);
  }
}
