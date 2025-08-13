// format_dispatcher.cpp
#include "format_dispatcher.h"
#include "tzx_player.h"
#include "tap_player.h"
#include "cas_player.h"
#include "tsx_player.h"

void dispatchPlayback(File &file, const String &filename) {
  if (filename.endsWith(".tzx") || filename.endsWith(".cdt")) {
    playTZX(file);
  } else if (filename.endsWith(".tap")) {
    playTAP(file);
  } else if (filename.endsWith(".cas")) {
    playCAS(file);
  } else if (filename.endsWith(".tsx")) {
    playTSX(file);
  } else {
    Serial.println("Unsupported format: " + filename);
  }
}
