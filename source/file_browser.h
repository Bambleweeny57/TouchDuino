#ifndef FILE_BROWSER_H
#define FILE_BROWSER_H

#include <Arduino.h>

extern String currentPath;

void listTapeFiles(String path);
String loadFileFromList();

#endif
