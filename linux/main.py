import socket
from time import sleep
import threading
import json
import pyautogui

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
ECHO_PORT = 5560
SERVER_PORT = 5559
cursorSen = [10, 10]
scrollSen = [2, 2]

def echo():
    while(True):
        sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) 
        sock2.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock2.bind((ip_broadcast, ECHO_PORT))
        sock2.sendto(b'x', ("255.255.255.255", ECHO_PORT))
        print('---- Sending echo ---')
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
    print(input)

    if inputType == 1:
        xDisp = int(obj['dx']) * cursorSen[0]
        yDisp = int(obj['dy']) * cursorSen[1]
        pyautogui.move(xDisp, yDisp)

    if inputType == 2:
        print('Left Mouse down')
        pyautogui.mouseDown()
    
    if inputType == 4:
        print('Left Mouse up')
        pyautogui.mouseUp()
    
    if inputType == 8:
        print('Right Mouse down')
        pyautogui.mouseDown(button='right')
        
    if inputType == 16:
        print('Right Mouse up')
        pyautogui.mouseUp(button='right')

    if inputType == 2048:
        pyautogui.vscroll(int(obj['mouseData']) * scrollSen[0])

    if inputType == 4096:
        pyautogui.hscroll(int(obj['mouseData']) * scrollSen[1])

x1 = threading.Thread(target=echo)
x2 = threading.Thread(target=server)

x1.start()
x2.start()
