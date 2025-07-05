# 🔐 STM32F407 Digital Keypad Lock

A bare-metal firmware project for STM32F407VG that implements a 4-digit keypad lock using GPIO and matrix scanning. Built using embedded C and CMSIS — no HAL, no CubeMX.

## 💡 Features
- 4x3 matrix keypad input
- 4-digit passcode entry
- Green LED for success (PD12)
- Red LED for failure (PD13)
- Debounced key detection

## 🔧 Tools
- STM32F407 Discovery board
- STM32CubeIDE
- ST-Link for flashing

