# TouchServer

TouchServer is part of [TouchDroid](https://github.com/SKRInternationals/TouchDroid).  
It captures input sent from the TouchDroid Android app over the network and registers them as mouse/keyboard events on Windows or Linux.

📱 Android app repo: [TouchDroid](https://github.com/SKRInternationals/TouchDroid)

---

## Table of Contents

- [Technologies](#technologies)
- [Setup](#setup)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)

---

## Technologies

- **Windows / Desktop**: C++, C#
- **Linux**: Python (3.8+), [ydotool](https://man.archlinux.org/man/ydotool.1.en)

---

## Setup

### Windows

1. Download and extract **MouseRemoteServer.zip**.
2. Run `UI.exe`.
3. Install the [TouchDroid APK](https://github.com/SKRInternationals/TouchDroid) on your phone.
4. Ensure both phone and PC are on the **same network**.
5. Open the Android app → and Select your Host device to connect

---

### Linux

1. Install Python 3.8+:
   ```bash
   sudo apt-get install python3.8
   ```
2. Install dependencies:
   ```bash
   sudo python3 -m pip install -r requirements.txt
   ```
3. Run the server:
   ```bash
   python main.py
   ```

⚠️ On some distros the cursor may not move properly (work in progress).

#### Hyprland Support

1. Install and run **ydotool**:
   ```bash
   sudo pacman -S ydotool
   sudo ydotoold &
   ```
2. Start the server:
   ```bash
   python main_hyprland.py
   ```

---

## Usage

- From the Windows GUI:
  - `Start` → Enable server
  - `Stop` → Disable server
- On Linux: Run the respective Python script.
- Control your desktop using your phone like a touchpad.

---

## Troubleshooting

- **Keyboard input issues (Linux/Hyprland):**
  ```bash
  cd ./linux/keys
  python export_system_keys.py
  ```
- If keys still don’t map correctly, edit `./linux/keys/app_keys.py` with your system’s key mappings.
- Advanced users: see inline comments in `main_hyprland.py` for manual fix options.
