# 🎮 MaxDuino Touchscreen UI

A modern touchscreen interface for MaxDuino running on Arduino Mega, replacing physical buttons with a full-colour TFT and touch input. Includes a scrollable file browser, playback progress bar, and customizable banner image.

---

## 🧱 Hardware Requirements

- **Microcontroller**: Arduino Mega 2560
- **Display**: ILI9341 TFT (240×320 or 320×240)
- **Touchscreen**: XPT2046 (SPI interface)
- **SD Card**: FAT32 formatted, contains tape files and `logo.bmp`
- **Audio Output**: Digital pin (e.g. D9) for tape signal

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
