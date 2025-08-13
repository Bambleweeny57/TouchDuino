#include "tsx_player.h"
#include "signal_generator.h"

void playTSX(File &file) {
    while (file.available()) {
        uint8_t blockID = file.read();

        switch (blockID) {
            case 0x10: { // Standard Speed Data Block
                uint16_t pauseAfter = file.read() | (file.read() << 8);
                uint16_t dataLen = file.read() | (file.read() << 8);
                uint32_t currentPos = file.position();
                uint32_t totalSize = file.size();
                drawProgressBar(currentPos, totalSize);

                for (uint16_t i = 0; i < dataLen; i++) {
                    uint8_t byte = file.read();
                    uint32_t currentPos = file.position();
                    uint32_t totalSize = file.size();
                    drawProgressBar(currentPos, totalSize);
                    
                    for (int b = 7; b >= 0; b--) {                        
                        sendBit((byte >> b) & 1);
                    }
                }
                delay(pauseAfter);
                break;
            }

            case 0x20: { // Pause block
                uint16_t pauseMs = file.read() | (file.read() << 8);
                uint32_t currentPos = file.position();
                uint32_t totalSize = file.size();
                drawProgressBar(currentPos, totalSize);
                delay(pauseMs);
                break;
            }

            default:
                // Skip unknown or metadata-only blocks
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
    // TSX-specific logic
#endif
}
