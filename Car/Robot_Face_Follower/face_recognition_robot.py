import cv2
import numpy as np
import os
import gpiozero 
from gpiozero import Buzzer
import time
from threading import Thread
import importlib.util

robot = gpiozero.Robot(left=(17,18), right=(27,22))
width = 640
height = 480

image_width = width
image_height = height
center_image_x = image_width/2
center_image_y = image_height/2

minimum_area = 250
maximum_area = 40000#100000

trainerpath = r'/home/pi/Desktop/My_Project/Projects/Face_Recognition_Using_Haarcascade/Face-Recognition/Trainer/trainer.yml'
xmlpath = r'/home/pi/Desktop/My_Project/Projects/Face_Recognition_Using_Haarcascade/Face-Recognition/Cascades/haarcascade_frontalface_default.xml'

recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read(trainerpath)
cascadePath = xmlpath
faceCascade = cv2.CascadeClassifier(cascadePath)

font = cv2.FONT_HERSHEY_SIMPLEX

#iniciate id counter
id = 0
 
# names related to ids: example ==> Marcelo: id=1,  etc
names = ['None', 'Lukas', 'Paula', 'Ilza', 'Z', 'W'] 

# Initialize and start realtime video capture
cam = cv2.VideoCapture(0)
cam.set(3, 640) # set video widht
cam.set(4, 480) # set video height

# Define min window size to be recognized as a face
minW = 0.1*cam.get(3)
minH = 0.1*cam.get(4)

def stopObject():
    robot.stop()
    print("here")

def detectObject(object_location):
    if object_location:
        if (object_location[0] > minimum_area) and (object_location[0] < maximum_area):
            if (object_location[1] > center_image_x + (image_width/7)):
                print("You are moving right ")
                robot.left(0.4)

                
            elif (object_location[1] < center_image_x - (image_width/7)):
                print("You are moving left ")
                robot.right(0.4)
        
            else:
                print("You are at centre")
                robot.forward(0.35)
                time.sleep(0.1)
                #robot.stop()
                
        elif(object_location[0] < minimum_area):
            robot.stop()
            print("Object is not large enough, searching..")
            
        else:
            robot.stop()
            print("Object is large enough, stopping ")
            
        #elif(object_location[0] > maximum_area):
            #robot.stop()
            #print("Object is large enough, stopping ")
            #print(object_location[0])
    else:
        #robot.left(0.5)
        robot.stop()
        print("No object found")
        
            
while True:
    object_x = 0
    object_y = 0
    object_area = 0
    
    ret, img =cam.read()
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale( 
        gray,
        scaleFactor = 1.2,
        minNeighbors = 5,
        minSize = (int(minW), int(minH)),
       )

    for(x,y,w,h) in faces:
        cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0), 2)
        id, confidence = recognizer.predict(gray[y:y+h,x:x+w])
        
        # Check if confidence is less them 100 ==> "0" is perfect match 
        if (confidence < 100):
            id = names[id]
            label = id
            confidence = "  {0}%".format(round(100 - confidence))

            found_area = w*h
            center_x = x + (w/2)
            center_y = y + (h/2)

            if (object_area < found_area):
                object_x = center_x
                object_y = center_y
                object_area = found_area
                                
        else:
            id = "Unknown"
            confidence = "  {0}%".format(round(100 - confidence))
            #stopObject()

        cv2.putText(img, str(id), (x+5,y-5), font, 1, (255,255,255), 2)
        cv2.putText(img, str(confidence), (x+18,y+h+27), font, 1, (255,255,0), 1)
    
    if (object_area > 0):
        object_location = [object_area, object_x, object_y]
        detectObject(object_location)  
        
    else:
        object_location = None
        stopObject()
        
    
    cv2.imshow('camera',img) 

    k = cv2.waitKey(10) & 0xff # Press 'ESC' for exiting video
    if k == 27:
        break

# Do a bit of cleanup
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv2.destroyAllWindows()