#include "tzx_player.h"
#include "signal_generator.h"  // Assumes sendBit(), tone(), etc.

void playTZX(File &file) {
    while (file.available()) {
        uint8_t blockID = file.read();

        switch (blockID) {
            case 0x10: { // Standard Speed Data Block
                uint16_t pauseAfter = file.read() | (file.read() << 8);
                uint16_t dataLen = file.read() | (file.read() << 8);
                for (uint16_t i = 0; i < dataLen; i++) {
                    uint8_t byte = file.read();
                    for (int b = 7; b >= 0; b--) {
                        sendBit((byte >> b) & 1);
                    }
                }
                delay(pauseAfter);
                break;
            }

            case 0x11: { // Turbo Speed Data Block
                file.seek(file.position() + 15); // Skip header
                uint32_t dataLen = file.read() | (file.read() << 8) | (file.read() << 16);
                for (uint32_t i = 0; i < dataLen; i++) {
                    uint8_t byte = file.read();
                    for (int b = 7; b >= 0; b--) {
                        sendBit((byte >> b) & 1);
                    }
                }
                break;
            }

            case 0x20: { // Pause (silence) or Stop the Tape
                uint16_t pauseMs = file.read() | (file.read() << 8);
                delay(pauseMs);
                break;
            }

            default:
                // Skip unknown block
                break;
        }
    }
}
