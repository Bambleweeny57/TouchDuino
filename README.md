# 🎛️ TouchDuino: Modular Tape Emulator for Retro Systems

TouchDuino is a robust, modular tape emulator designed for retro computing platforms like the ZX Spectrum, Amstrad CPC, and MSX. It supports multiple tape formats and integrates a folder-aware file browser, capacitive touchscreen UI, and banner/logo rendering.

---

## 🚀 Features

- 🎞️ **Multi-format playback**: Supports `.tap`, `.tzx`, `.cdt`, `.cas`, and `.tsx` formats  
- 📁 **Folder-aware file browser**: Navigate SD card directories with recursive listing and file selection  
- 🖼️ **Touchscreen UI**: Capacitive display with banner/logo rendering and file selection interface  
- 🔊 **Signal generation**: Accurate bit-level playback with timing control  
- 🧠 **Modular architecture**: Clean `.cpp/.h` separation for maintainability and format extensibility  
- 🛠️ **Hardware-ready**: Now targets the Waveshare ESP32-S3-Touch-LCD-2.8 board  
- 🎞️ **Customizable banner** via `logo.bmp` in SD root  

---

## 🧱 Hardware Requirements (Rev2.0)

TouchDuino now runs on the [Waveshare ESP32-S3-Touch-LCD-2.8](https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-2.8), a 2.8" capacitive touchscreen board with integrated ESP32-S3 MCU, SD card slot, and onboard DAC audio.

### 🔌 Core Specs

| Component             | Description                                  |
|----------------------|----------------------------------------------|
| MCU                  | ESP32-S3 dual-core LX7 @ 240MHz              |
| Display              | 2.8" capacitive touchscreen (240×320)        |
| Flash / PSRAM        | 16MB Flash / 8MB PSRAM                       |
| SD Card              | SPI-based, onboard slot                      |
| Audio                | DAC + onboard speaker (I2S output)           |
| USB                  | Type-C for power and flashing                |

### 📐 Pin Mapping

| Function         | ESP32-S3 Pin | Notes                          |
|------------------|--------------|--------------------------------|
| TFT MOSI         | GPIO45       | Display data                   |
| TFT SCLK         | GPIO40       | Display clock                  |
| TFT CS           | GPIO42       | Chip select                    |
| TFT DC           | GPIO41       | Data/command                   |
| TFT RST          | GPIO39       | Reset                          |
| TFT BL           | GPIO5        | Backlight                      |
| Touch SDA        | GPIO1        | I2C data                       |
| Touch SCL        | GPIO3        | I2C clock                      |
| Touch INT        | GPIO4        | Interrupt                      |
| SD MOSI          | GPIO17       | Shared with TFT                |
| SD SCK           | GPIO14       | Shared with TFT                |
| SD CS            | GPIO21       | Dedicated                      |
| SD MISO          | GPIO16       | Dedicated                      |
| Audio DIN        | GPIO47       | I2S data input                 |
| Audio LRCK       | GPIO38       | I2S left/right clock           |
| Audio BCK        | GPIO48       | I2S bit clock                  |

---

## 🖥️ UI Layout

| Section               | Description                                  |
|-----------------------|----------------------------------------------|
| Full-width Banner     | `logo.bmp` loaded from SD root               |
| Playback Progress Bar | Green bar shows file progress                |
| Scrollable File List  | Touch to select/play                         |
| Control Buttons       | ⏮ Prev ▶ Play ⏹ Stop ⏭ Next ☰ Menu           |

---

## 🛠️ Setup Instructions

1. Format SD card as FAT32  
2. Place `logo.bmp` in root directory (240×64 recommended)  
3. Add `.tap`, `.tzx`, `.cdt`, `.cas`, `.tsx` files  
4. Flash firmware via USB Type-C using Arduino IDE or ESP-IDF  
5. Power up and enjoy the retro-modern interface  

---

## 🧪 Status

✅ Playback engines implemented  
✅ Folder-aware browser and UI integrated  
✅ Modular format routing via dispatcher  
🔜 LVGL polish and banner rendering updates  
🔜 Optional progress bar and signal calibration  

---

## 🤝 Contributing

Pull requests welcome! Please follow modular coding practices and ensure compatibility with the existing UI and hardware abstraction layers.

---

## 📦 Firmware Base

TouchDuino builds on the latest MaxDuino playback engines and format dispatching logic.

---

