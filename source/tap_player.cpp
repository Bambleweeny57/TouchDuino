#include "tap_player.h"
#include "signal_generator.h"

void playTAP(File &file) {
    while (file.available()) {
        uint16_t blockLen = file.read() | (file.read() << 8);
        for (uint16_t i = 0; i < blockLen; i++) {
            uint8_t byte = file.read();
            for (int b = 7; b >= 0; b--) {
                sendBit((byte >> b) & 1);
            }
        }
        delay(1000); // Standard pause after block
    }
}

