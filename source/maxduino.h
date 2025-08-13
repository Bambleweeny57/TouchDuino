#ifndef MAXDUINO_H
#define MAXDUINO_H

#include <Arduino.h>
#include <SD.h>

void playTapeFile(File file, String name);
void playTAP(File file);
void playTZX(File file);
void playCDT(File file);
void playCAS(File file);
void sendByte(byte b);
void sendBit(bool bit);
void stopPlayback();

#endif
