import cv2
import numpy as np

font = cv2.FONT_HERSHEY_SIMPLEX
cap = cv2.VideoCapture(0)

width = 640
height = 480

xmlpath = r"C:\Users\jlukas\Desktop\My Projects\JetsonNano\Robotic Project\Face_Recognition_Robot\XML\haarcascade_frontalface_default.xml"
def findface():
    minW = 0.1 * cap.get(3)
    minH = 0.1 * cap.get(4)
    faceCascade = cv2.CascadeClassifier(xmlpath)
    while True:
        success,img = cap.read()
        if not success:
            break
        myFaceListCentre = []
        myFaceListArea = []
        img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        faces = faceCascade.detectMultiScale(
            img_gray,
            scaleFactor=1.2,
            minNeighbors=5,
            minSize=(int(minW), int(minH)))

        for (x,y,w,h) in faces:
            cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0),2)
            cx = x + w//2
            cy = y + h//2
            area = w*h
            myFaceListArea.append(area)
            myFaceListCentre.append([cx,cy])
            cv2.line(img,(width//2, cx), (cx,cy), (255,0,255),4)

        if len(myFaceListArea) !=0:
            i = myFaceListArea.index(max(myFaceListArea)) #Take the highest one
            return img, [myFaceListCentre[i], myFaceListArea[i]]
        else:           
            return img, [[0,0],0]
 
def drawOverlay(img):
    cv2.line(img, (width//2,0), (width//2,height),(255,0,255),3)

    return img


def trackObject(img, info, pid, pError):
    if int(info[1]) !=0 and int(info[1]) < 130000:
        error = width//2 - info[0][0]
        posX = int(pid[0]*error + pid[1]*(error-pError))
        posX = int(np.interp(posX,[-width//4,width//4], [-20,20])) # Map Pos X with (x1,x2), (y1,y2)
        pError = error
        print("PError :" + str(pError) +  " Area :" + str(info[1]) + " TRACKING")

    elif int(info[1]) > 130000:
        print("PError :" + str(0) + " Area :"+ str(0) + " REVERSE")

    else:
        print("PError :" + str(0) + " Area :"+ str(0) + " NO MASK FOUND")
    
    return img, pError

if __name__ == "__main__":
    findface()

