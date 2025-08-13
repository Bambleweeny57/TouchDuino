#ifndef USERCONFIG_H
#define USERCONFIG_H

// Enable TFT display
#define USE_TFT

// Disable OLED display
#undef USE_OLED

// Audio output pin
#define AUDIO_PIN 9

// Capacitive touch uses I2C — no CS pin needed
// #define CS_PIN 8

#define DEFAULT_BAUD_RATE     1200     // bits per second
#define PULSE_WIDTH_US        350      // microseconds per bit pulse
#define INTER_BIT_DELAY_US    50       // microseconds between bits
#define ENABLE_CALIBRATION    true     // toggle calibration mode

#endif
