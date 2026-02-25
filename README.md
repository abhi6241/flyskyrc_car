# ESP32 RC Differential Drive Robot

A lightweight, efficient C++ Arduino project for controlling a differential-drive (skid-steer) robot using an ESP32, dual BTS7960 high-power motor drivers, and a standard PWM RC receiver (e.g., FlySky). 

Perfect for ECE hardware projects and custom robotics, this code implements arcade-style mixing (translating X/Y joystick movements into independent left/right track speeds) and includes a dedicated channel for a master speed limit.

## ✨ Features
* **Arcade Mixing Logic:** Seamlessly translates single-joystick (or split-joystick) RC signals into differential drive movements.
* **Master Speed Limiter:** Uses a third RC channel (knob or switch) to dynamically scale the maximum speed of the robot.
* **Deadband Protection:** Ignores minor joystick drift near the center to prevent motor whine.
* **Modern ESP32 PWM API:** Utilizes the updated `ledcAttach()` and `ledcWrite()` functions for precise, hardware-level motor control.

---

## 🛠️ Hardware Requirements
* **Microcontroller:** ESP32 Development Board
* **Motor Drivers:** 2x BTS7960 (43A High-Power H-Bridges)
* **Receiver:** Any standard PWM RC Receiver (e.g., FlySky FS-iA6B)
* **Motors:** 2x DC Motors (Left and Right tracks/wheels)
* **Power:** Battery pack (e.g., LiPo) + Buck Converter (for stepping down voltage to the receiver/ESP32)

---

## 🔌 Pin Connections & Wiring

Ensure all components share a **Common Ground (GND)** to prevent floating PWM signals.

### 📡 RC Receiver (PWM Inputs)
*Note: ESP32 pins are 3.3V logic. If your receiver is powered by 5V, it is highly recommended to use a voltage divider on these signal lines to protect the ESP32.*

| Receiver Channel | ESP32 Pin | Variable in Code | Function |
| :--- | :--- | :--- | :--- |
| **CH_Speed** (Knob) | `D34` | `chSpeed` | Master speed limit (0-255) |
| **CH_Move** (Y-Axis) | `D35` | `chMove` | Forward / Backward |
| **CH_Turn** (X-Axis) | `D39` | `chTurn` | Left / Right Turning |
| **VCC (Middle)** | `Vin` / `5V` (Buck) | N/A | Receiver Power |
| **GND (Bottom)** | `GND` | N/A | Common Ground |

### ⚙️ Left Motor Driver (BTS7960 - Driver 1)
| BTS7960 Pin | ESP32 Pin | Code Definition |
| :--- | :--- | :--- |
| **R_EN** | `D27` | `REN1` |
| **L_EN** | `D14` | `LEN1` |
| **R_PWM** | `D25` | `RPWM1` |
| **L_PWM** | `D26` | `LPWM1` |
| **VCC** | `3V3` | Logic Power |
| **GND** | `GND` | Common Ground |
| **B+ / B-** | Battery + / - | High-Power Source |
| **M+ / M-** | Left Motor | Motor Output |

### ⚙️ Right Motor Driver (BTS7960 - Driver 2)
| BTS7960 Pin | ESP32 Pin | Code Definition |
| :--- | :--- | :--- |
| **R_EN** | `D12` | `REN2` |
| **L_EN** | `D13` | `LEN2` |
| **R_PWM** | `D32` | `RPWM2` |
| **L_PWM** | `D33` | `LPWM2` |
| **VCC** | `3V3` | Logic Power |
| **GND** | `GND` | Common Ground |
| **B+ / B-** | Battery + / - | High-Power Source |
| **M+ / M-** | Right Motor | Motor Output |

---

## 📦 Libraries to Install

**Zero external libraries are required!** This project relies purely on standard Arduino C++ functions (`pulseIn`, `map`, `constrain`) and the built-in ESP32 hardware PWM library. 

**However, you MUST ensure you have the correct ESP32 Board Core installed:**
1. Open the Arduino IDE.
2. Go to **Tools** > **Board** > **Boards Manager**.
3. Search for **esp32** by Espressif Systems.
4. Install **version 3.0.0 or newer**. *(Older 2.x versions use a deprecated `ledcSetup` syntax and will throw a compilation error).*

---

## 🚀 Installation & Usage

1. Clone or download this repository.
2. Open the `.ino` file in the Arduino IDE.
3. Connect your ESP32 via USB.
4. Select your ESP32 board from the **Tools > Board** menu (e.g., "DOIT ESP32 DEVKIT V1").
5. Select the correct COM port. *(If you are compiling this on a MacBook, look for a port named `/dev/cu.usbserial-XXXX` or `/dev/cu.SLAB_USBtoUART`).*
6. Click **Upload**.
7. Turn on your RC Transmitter, power up the robot, and test the movements!

---

## ⚠️ Important Safety Notes
* **Prop up your robot** so the wheels/tracks are off the ground during your first test. This prevents the robot from driving off the table if a channel is reversed.
* Ensure your high-power battery is connected securely to the `B+` and `B-` terminals of the BTS7960 drivers, **never** through the ESP32.
* Verify your deadband settings (`abs(moveValue) < 20`) match the natural resting jitter of your specific RC controller. If the motors hum while the sticks are centered, increase the `20` value slightly.