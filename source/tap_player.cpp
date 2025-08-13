#include "tap_player.h"
#include "signal_generator.h"
#include "tft_ui.h"

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

        uint32_t currentPos = file.position();
        uint32_t totalSize = file.size();
        drawProgressBar(currentPos, totalSize);    
    }
}

void sendBit(bool bit) {
#if ENABLE_CALIBRATION
    digitalWrite(DATA_PIN, bit ? HIGH : LOW);
    delayMicroseconds(PULSE_WIDTH_US);
    digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(INTER_BIT_DELAY_US);
#else
    // Original timing logic
#endif
}

