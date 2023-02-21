"""
Object detection Module 
Viola Jhones Method 

by: Murtaza Hassan
Website: www.murtazahassan.com
Youtube: Murtaza's Workshop - Robotics and AI
"""

import cv2


def findObjects(img, objectCascade, scaleF = 1.1, minN = 4):
    """
    finds objects using the haarcascade file 

    :param img: Image in which the objects needs to be found 
    :param objectCascade: Object Cascade created with Cascade Classifier
    :param scaleF: how much the image size is reduced at each image scale 
    :param minN: how many neighbours each rectangle should have to accept as valid 
    :return: image with the rectangles draw and the bounding box info  
    """

    imgObjects = img.copy()
    imgGray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    objects = objectCascade.detectMultiScale(imgGray,scaleF,minN)
    objectsOut = []
    for (x,y,w,h) in objects: 
        cv2.rectangle(imgObjects,(x,y),(x+w,y+h),(255,0,255),2)
        objectsOut.append([[x,y,w,h],w*h])
    
    objectsOut = sorted(objectsOut, key = lambda x:x[1], reverse = True)

    
    return imgObjects, objectsOut

def main():
    img = cv2.imread("test.png")
    faceCascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
    imgObjects, objects = findObjects(img, faceCascade)
    cv2.imshow("Output", imgObjects)
    cv2.waitKey(0)


if __name__ == "__main__":
    main()