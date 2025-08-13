#include "cas_player.h"
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
}
