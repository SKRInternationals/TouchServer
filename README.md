# TouchServer

- TouchServer is part of [TouchDroid](https://www.github.com/Akshayaap/TouchDroid). This is Linux/Windows Server to capture data from the Network sent by TouchDroid Application and Register Appropreate Events to the Operating System. 
- Repositoty to Android Application is [Here](https://www.github.com/Akshayaap/TouchDroid).

  ## Table of Content
  - [Technologies](#technologies)
  - [Setup](#setup)
  - [Working](#working)
  
  ## Technologies
  ### For Desktop Server Applicarion
  - C++.
  - C#.
  
  ## Setup
  ### For Users
  - Download the zip file.
  - Install android [TouchDroid](https://www.github.com/Akshayaap/TouchDroid) apk.
  - Extract MouseRemoteServer.zip at your favorite location in your Windows PC.
  - Run `UI.exe`.
  - Now you will be able to control Server.
  - Open MouseRemote application in android.
  - The app will connect to server automatically.
  <br/><br/>
  Note: **The mobile and server must be in same network**
  For More See: [Documentation](https://www.github.com/Akshayaap/Documentation).
  
  ## Working (Windows)
  How the program works:-
  - Press `Start` from Desktop-GUI to start.
  - Press `Stop` from Desktop-GUI to stop.
  - You can then Easily control your Computer by using your phone as touchpad.

  ## Working (Linux)

  - Install python using `sudo apt-get install python3.8`.
  - Open terminal in **linux** folder.
  - Use `sudo python3 -m pip install -r requirements.txt` to install all required libraries.
  - Run **main.py** file and control your linux device.
    **_Note:-_** _Cursor might not move on some linux distros. Under progress_

  ### Hyprland

  - Install [ydotool](https://man.archlinux.org/man/ydotool.1.en):
    > - arch linux:
    >
    > `sudo pacman -S ydotool`
  - Run **ydotool**:
    > `sudo ydotoold &`
  - Open terminal in **linux** folder.
  - Run **main_hyprland.py** file and control your Linux device
    > `python main_hyprland.py`

  ### Keyboard Problem?

  - Open terminal in `./linux/keys`
  - Run `python export_system_keys.py`
  - Try running `./linux/main_hyprland.py` again

  - (i hope u not need to read this section below)
  - If still not works try :
    > - Edit `./linux/main_hyprland.py`:
    > - find "HERE TO FIX YOUR PROBLEM" and uncomment one line under that
    > - find `# HERE U START COMMENTING` and start commenting
    > - until u reach to the `# HERE U END COMMENTING`
    > - save and run the `./linux/main_hyprland.py` file
    > - edit `./linux/keys/app_keys.py` and replce every "key" in dictionary
    > - save the file and ...
    > - **you should undo comment/uncomment after alll**


