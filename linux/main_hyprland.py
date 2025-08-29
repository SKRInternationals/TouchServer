from keys import app_keys, system_keys

import socket
from time import sleep
import threading
import json

ECHO_PORT = 5560
SERVER_PORT = 5559
cursorSen = [1, 1]
scrollSen = [1, 1]

# True  = printing activities
# False = no printing
PRINT_LOGS = True;


# -------------------------------------------

import subprocess


# 🖱️ Move Mouse
def move_mouse(x, y):
    subprocess.run(["ydotool", "mousemove", f"-x {x}", f"-y {y}"])

# 🖱️ Left Mouse
def left_mouse_down():
    subprocess.run(["ydotool","click","0x40"])

def left_mouse_up():
    subprocess.run(["ydotool","click","0x80"])

# 🖱️ Right Mouse
def right_mouse_down():
    subprocess.run(["ydotool", "click", "0x41"])

def right_mouse_up():
    subprocess.run(["ydotool", "click", "0x81"])

# 🖱️ Scroll
# https://github.com/ReimuNotMoe/ydotool/blob/b0c5da3cc1fcfcf3a20fa0c184f721d386945b6a/Client/tool_mousemove.c#L45
def scroll_up():
    subprocess.run(["ydotool", "mousemove", "-w", "--", "0", str(scrollSen[1])])

def scroll_down():
    subprocess.run(["ydotool", "mousemove", "-w", "--", "0", "-"+str(scrollSen[1])])


# -------------------------------------------






def getNetworkIp():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    s.connect(('<broadcast>', 0))
    return s.getsockname()[0]

def getBroadcastAdd(ip):
    block = ip.split('.')
    return block[0]+'.'+block[1]+'.'+block[2]+'.255'

ip_server = getNetworkIp()
ip_broadcast = getBroadcastAdd(ip_server)


def logPrint(*text,end="\n"):
    if(PRINT_LOGS):
        print(*text,end=end)



def echo():
    logPrint()
    while(True):
        sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock2.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock2.bind((ip_broadcast, ECHO_PORT))
        sock2.sendto(b'x', ("255.255.255.255", ECHO_PORT))
        logPrint('\n---- Sending echo ---\n')
        sock2.close()
        sleep(3)

def server():
    while(True):
        sock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock1.bind((ip_server, SERVER_PORT))
        data, addr = sock1.recvfrom(1024)
        parseInputCommand(data)

def parseInputCommand(input):
    obj = json.loads(input)
    inputType = int(obj['dwFlags'])
    inputKeyboard = int(obj['type'])

    logPrint("\n\n"+("_ "*10)+"\n\n")
    logPrint(f'>> type: {obj["type"]} \t dwFlags: {obj["dwFlags"]} \t wVk: {obj["wVk"]} ')
    logPrint(f'>> dx: {obj["dx"]} \t dy: {obj["dy"]}')
    logPrint(f'>> wScan: {obj["wScan"]} \t time: {obj["time"]} \t dwExtraInfo: {obj["dwExtraInfo"]} \t mouseData: {obj["mouseData"]}',end="\n  "+(". "*10)+"\n")

    # --------------------
    # Keyboard settings here
    if inputKeyboard == 1:
        # default value (-1) means no key founded
        systemKeyId = "-1"
        appKeyId = obj["wVk"]

        # use this for exporting keys ids into ./keys/app_key.py (manualy :D)
        # HERE TO FIX YOUR PROBLEM (inshallah) uncomment one line below this
        # subprocess.run(["ydotool", "type", str(appKeyId)])

        # HERE U START COMMENTING
        logPrint(f'Keyboard\t id: {appKeyId} ',end="\t")
        if appKeyId in app_keys.appKeys:
            key_pressed_name = app_keys.appKeys[appKeyId]
            logPrint(f'name: {key_pressed_name} ',end="\t")
            if key_pressed_name in system_keys.systemKeys:
                systemKeyId=system_keys.systemKeys[key_pressed_name]
                logPrint(f'system key id: {systemKeyId} ',end="\t-> ")

        if systemKeyId != "-1":
            # this var format is like: "keyId:press/release(1/0)" -> "46:1" , "46:0"
            key_id_with_action = f"{systemKeyId}:"
            if inputType == 0: # pressing
                key_id_with_action +="1"
                logPrint(f'DOWN')
            elif inputType == 2: # releasing
                key_id_with_action +="0"
                logPrint(f'UP')

            subprocess.run(["ydotool", "key", key_id_with_action])
        else:
            logPrint(f"\n----------\nkey not found!!!\n{appKeyId}")
        # HERE U END COMMENTING
    # --------------------
    else:
        # move mouse
        if inputType == 1:
            xDisp = int(obj['dx']) * cursorSen[0]
            yDisp = int(obj['dy']) * cursorSen[1]

            logPrint(f"Move Mouse, Cursor Sens[x,y]: {cursorSen}\t-> \t X: {xDisp} \tY: {yDisp}")

            move_mouse(xDisp, yDisp)

        # lmb down
        if inputType == 2:
            logPrint('Left Mouse \t-> DOWN')
            left_mouse_down()

        # lmb up
        if inputType == 4:
            logPrint('Left Mouse \t-> UP')
            left_mouse_up()

        # rmb down
        if inputType == 8:
            logPrint('Right Mouse \t-> DOWN')
            right_mouse_down()

        # rmb up
        if inputType == 16:
            logPrint('Right Mouse \t-> UP')
            right_mouse_up()

        # scroll
        if inputType == 4096:
            logPrint(f'Scroll Mouse, Sens[x,y]: {scrollSen}',end=" \t-> ")

            # mouseData == 1 : scroll up ,  -1 : scroll down
            if(obj["mouseData"]=="1"):
                logPrint("UP")
                scroll_up()
            else:
                logPrint("DOWN")
                scroll_down()


x1 = threading.Thread(target=echo)
x2 = threading.Thread(target=server)

x1.start()
x2.start()


