"""
Grant Permission to the port
sudo chmod 666 /dev/ttyACM0

Change the mode to 5W for using with USB power
sudo nvpmodel -m1
sudo nvpmodel -q

by: Murtaza Hassan
Website: www.murtazahassan.com
Youtube: Murtaza's Workshop - Robotics and AI
"""


import cv2
import time
import SerialModule as sm

ser = sm.initConnection('/dev/ttyACM0', 9600)

frameWidth = 640
frameHeight= 480
flip =  0
## The camera parameters should be in a single line
camSet='nvarguscamerasrc !  video/x-raw(memory:NVMM), width=3264,height=2464, format=NV12, framerate=21/1 ! nvvidconv flip-method='+str(flip)+'! video/x-raw, width='+str(frameWidth)+', height='+str(frameHeight)+',format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink'
cap = cv2.VideoCapture(camSet)

while True:
    sccuess, img = cap.read()
    cv2.imshow("Result", img)
    key = cv2.waitKey(1)

    if key == ord('w'):sm.sendData(ser,[50,0],4)
    elif key == ord('s'):sm.sendData(ser,[-50,0],4)
    elif key == ord('a'):sm.sendData(ser,[50,15],4)
    elif key == ord('d'):sm.sendData(ser,[50,-15],4)
    elif key == ord('q'):break
    else: sm.sendData(ser,[0,0],4)
