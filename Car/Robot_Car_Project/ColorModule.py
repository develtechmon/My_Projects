"""
Color Module 
Finds color in an image based on hsv values
Can run as stand alone to find relevant hsv values

by: Murtaza Hassan
Website: www.murtazahassan.com
Youtube: Murtaza's Workshop - Robotics and AI
"""


import cv2
import numpy as np 

hsvVals = [[0,110,153],[19,240,255]]

def empty(a):
    pass

def initTrackbars():
    """
    To intialize Trackbars . Need to run only once
    """

    cv2.namedWindow("TrackBars")
    cv2.resizeWindow("TrackBars",640,240)
    cv2.createTrackbar("Hue Min","TrackBars",0,179,empty)
    cv2.createTrackbar("Hue Max","TrackBars",179,179,empty)
    cv2.createTrackbar("Sat Min","TrackBars",0,255,empty)
    cv2.createTrackbar("Sat Max","TrackBars",255,255,empty)
    cv2.createTrackbar("Val Min","TrackBars",0,255,empty)
    cv2.createTrackbar("Val Max","TrackBars",255,255,empty)

def getTrackbarValues():
    """
    Gets the trackbar values in runtime
    :return: hsv values from the trackbar window
    """
    hmin = cv2.getTrackbarPos("Hue Min", "TrackBars")
    smin= cv2.getTrackbarPos("Sat Min", "TrackBars")
    vmin = cv2.getTrackbarPos("Val Min", "TrackBars")
    hmax = cv2.getTrackbarPos("Hue Max", "TrackBars")
    smax = cv2.getTrackbarPos("Sat Max", "TrackBars")
    vmax = cv2.getTrackbarPos("Val Max", "TrackBars")

    return [[hmin,smin,vmin],[hmax,smax,vmax]]


def findColor(img, hsvVals):
    """
    :param img: Image in which color needs to be found
    :param hsvVals: List of lower and upper hsv range 
    :return: (mask) bw image with white regions where color is detected
             (imgColor) colored image only showing regions detected
    """
    
    imgHSV = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
    lower = np.array(hsvVals[0])
    upper = np.array(hsvVals[1])
    mask = cv2.inRange(imgHSV,lower,upper)
    imgColor = cv2.bitwise_and(img, img, mask=mask)

    return mask, imgColor

def main():

    #img = cv2.imread("../Resources/shapes.png")
    success, img = cap.read()
    hsvVals = getTrackbarValues()
    print(hsvVals)
    mask, imgColor =  findColor(img, hsvVals)

    cv2.imshow("Image",img)
    #cv2.imshow("Image HSV",imgHSV)
    #cv2.imshow("Mask",mask)
    cv2.imshow("Image Color",imgColor)


if __name__ == "__main__":
    initTrackbars()
    camSet=' nvarguscamerasrc ! video/x-raw(memory:NVMM),width=3820, height=2464, framerate=21/1, format=NV12 ! nvvidconv flip-method=0 ! video/x-raw,width=640, height=480, format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink'
    cap = cv2.VideoCapture(camSet)
    cap.set(3,640)
    cap.set(4,480)
    while True:
        main()
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
