// format_dispatcher.h
#ifndef FORMAT_DISPATCHER_H
#define FORMAT_DISPATCHER_H

#include <Arduino.h>
#include <SD.h>

void dispatchPlayback(File &file, const String &filename);

#endif
