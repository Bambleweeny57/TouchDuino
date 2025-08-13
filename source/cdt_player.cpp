#include "cdt_player.h"
#include "signal_generator.h"

void playCDT(File &file) {
    while (file.available()) {
        uint8_t blockID = file.read();
        uint32_t currentPos = file.position();
        uint32_t totalSize = file.size();
        drawProgressBar(currentPos, totalSize);
        
        switch (blockID) {
            case 0x00: { // Header block
                file.seek(file.position() + 0x10); // Skip header
                break;
            }

            case 0x01: { // Data block
                uint16_t dataLen = file.read() | (file.read() << 8);
                uint32_t currentPos = file.position();
                uint32_t totalSize = file.size();
                drawProgressBar(currentPos, totalSize);

                for (uint16_t i = 0; i < dataLen; i++) {
                    uint8_t byte = file.read();
                    for (int b = 7; b >= 0; b--) {
                        sendBit((byte >> b) & 1);
                    }
                }
                delay(1000); // Pause after block
                break;
            }

            default:
                // Skip unknown block
                break;
        }
    }
}

void sendBit(bool bit) {
#if ENABLE_CALIBRATION
    digitalWrite(DATA_PIN, bit ? HIGH : LOW);
    delayMicroseconds(PULSE_WIDTH_US);
    digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(INTER_BIT_DELAY_US);
#else
    // CDT-specific timing
#endif
}
