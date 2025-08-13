# 🎛️ TouchDuino: Modular Tape Emulator for Retro Systems

TouchDuino is a robust, modular tape emulator designed for retro computing platforms like ZX Spectrum, Amstrad CPC, and MSX. It supports multiple tape formats and integrates a folder-aware file browser, capacitive touchscreen UI, and banner/logo rendering.

---

## 🚀 Features

- 🎞️ **Multi-format playback**: Supports `.tap`, `.tzx`, `.cdt`, `.cas`, and `.tsx` formats
- 📁 **Folder-aware file browser**: Navigate SD card directories with recursive listing and file selection
- 🖼️ **Touchscreen UI**: Capacitive display with banner/logo rendering and file selection interface
- 🧠 **Modular architecture**: Clean `.cpp/.h` separation for maintainability and format extensibility
- 🔊 **Signal generation**: Accurate bit-level playback with timing control
- 🛠️ **Hardware-ready**: Designed for Arduino-compatible boards with reliable pinouts

---

## 📂 Source Modules

| Module                | Purpose                              |
|-----------------------|--------------------------------------|
| `maxduino.cpp`        | Main playback controller             |
| `format_dispatcher.cpp` | Routes playback based on file extension |
| `tzx_player.cpp`      | TZX format playback engine           |
| `tap_player.cpp`      | TAP format playback engine           |
| `cdt_player.cpp`      | CDT format playback engine           |
| `cas_player.cpp`      | CAS format playback engine           |
| `tsx_player.cpp`      | TSX format playback engine           |
| `file_browser.cpp`    | Recursive SD file listing and selection UI |
| `tft_ui.cpp`          | Touchscreen UI rendering and input   |
| `userconfig.h`        | Customization and pin definitions    |

---

## 📁 SD File Browser

TouchDuino includes a recursive file browser that:

- Lists all files and folders on the SD card
- Supports nested directories
- Filters supported tape formats (`.tap`, `.tzx`, etc.)
- Allows selection via touchscreen
- Passes selected file to `dispatchPlayback()` for format-specific handling

---

## 🧰 Hardware Requirements

- Arduino-compatible board (e.g. Mega, ESP32)
- Capacitive touchscreen (e.g. ILI9341)
- SD card reader (SPI-based)
- Audio output circuitry (PWM or DAC-based)

---

## 🧪 Status

✅ All playback engines implemented  
✅ Folder-aware browser and UI integrated  
✅ Modular format routing via dispatcher  
🔜 Banner/logo rendering polish  
🔜 Optional progress bar and signal calibration

---

## 🤝 Contributing

Pull requests welcome! Please follow modular coding practices and ensure compatibility with the existing UI and hardware abstraction layers.

---

## 📸 Screenshots & Diagrams

Coming soon: wiring diagrams, UI screenshots, and banner/logo previews.


# 🎮 MaxDuino Touchscreen UI

A modern touchscreen interface for MaxDuino running on Arduino Mega, replacing physical buttons with a full-colour TFT and touch input. Includes a scrollable file browser, playback progress bar, and customizable banner image.

---

## 🧱 Hardware Requirements

| Component                  | Description                                      |
|---------------------------|--------------------------------------------------|
| Arduino Mega 2560         | Main MCU with enough flash and RAM               |
| ILI9341 TFT (240×320)     | SPI-based display                                |
| FT6206 Capacitive Touch   | I2C-based touch controller                       |
| SD Card Module            | SPI-based, or integrated with TFT                |
| Audio Output              | Digital pin (e.g. D9) for tape signal            |

---

## 📦 Firmware Base

- **MaxDuino**: Latest version from [rcmolina/MaxDuino](https://github.com/rcmolina/MaxDuino)
- Supports `.tap`, `.tzx`, `.cdt`, `.cas`, and other formats

---

### 🖥️ UI Layout

| Section                  | Description                          |
|--------------------------|--------------------------------------|
| **Full-width Banner**    | `logo.bmp` loaded from SD            |
| **Playback Progress Bar**| Green bar shows file progress        |
| **Scrollable File List** | Touch to select/play                 |
| **Control Buttons**      | ⏮ Prev ▶ Play ⏹ Stop ⏭ Next ☰ Menu   |

---

## 🧩 Features

- ✅ Full MaxDuino playback engine
- ✅ Touchscreen replaces 5 physical buttons
- ✅ Scrollable file list (excludes `logo.bmp`)
- ✅ Playback progress bar
- ✅ Cancel playback via Stop button
- ✅ Modular code structure (`tft_ui.cpp/h`)
- ✅ Customizable banner via `logo.bmp` in SD root

---

### 📁 SD Card Structure

| Path             | Description                                      |
|------------------|--------------------------------------------------|
| `/logo.bmp`      | Banner image (24-bit BMP, 320×64 recommended)    |
| `/game1.tap`     | Tape file for playback                           |
| `/demo.tzx`      | Another supported tape format                    |
| `/loader.cdt`    | CDT format file                                  |
| `/games/game2.tap` | File inside subfolder (if folder support enabled) |
| `/demos/demo2.tzx` | Another file in subfolder                      |

---

## 🧪 Touch Zones

| Button | Function        | X Range (px) |
|--------|------------------|--------------|
| ⏮ Prev | Scroll up        | 0–64         |
| ▶ Play | Start playback   | 65–128       |
| ⏹ Stop | Cancel playback  | 129–192      |
| ⏭ Next | Scroll down      | 193–256      |
| ☰ Menu | Config/info      | 257–320      |

---

## 🛠️ Setup Instructions

1. Format SD card as FAT32
2. Place `logo.bmp` in root directory
3. Add `.tap`, `.tzx`, `.cdt`, `.cas` files
4. Upload sketch to Arduino Mega
5. Connect TFT and touchscreen via SPI
6. Power up and enjoy the retro-modern interface!

---

## 🧠 Customization Ideas

- Swap `logo.bmp` for different branding
- Add icons or animations to buttons
- Extend Menu button for settings or diagnostics
