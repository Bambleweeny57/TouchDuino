#include "cas_player.h"
#include "tft_ui.h"
#include "signal_generator.h"

void playCAS(File &file) {
    while (file.available()) {
        uint8_t byte = file.read();        
        // MSX CAS uses 1 start bit, 8 data bits, 1 stop bit
        sendBit(0); // Start bit
        for (int b = 0; b < 8; b++) {
            sendBit((byte >> b) & 1);
        }
        sendBit(1); // Stop bit

        delayMicroseconds(100); // Inter-byte delay
    }

    delay(1000); // Final pause

    uint32_t currentPos = file.position();
    uint32_t totalSize = file.size();
    drawProgressBar(currentPos, totalSize);
}

void sendBit(bool bit) {
#if ENABLE_CALIBRATION
    digitalWrite(DATA_PIN, bit ? HIGH : LOW);
    delayMicroseconds(PULSE_WIDTH_US);
    digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(INTER_BIT_DELAY_US);
#else
    // CAS-specific logic
#endif
}
