// tsx_player.cpp
#include "tsx_player.h"

void playTSX(File &file) {
  // TSX decoding logic
  while (file.available()) {
    byte b = file.read();
    delayMicroseconds(100);
  }
}
