#ifndef MAXDUINO_H
#define MAXDUINO_H

#include <Arduino.h>
#include <SD.h>
#include "tft_ui.h"

bool isPlaying();
void playTapeFile(File &tapeFile, const String &filename);
void stopPlayback();
void handleTouchAction(TouchAction action);

#endif
