from PIL import Image
import cv2
import numpy as np
import os

dataset = r'/home/pi/Desktop/My_Project/Projects/Face_Recognition_Using_Haarcascade/Face-Recognition/Dataset'
trainerpath = r'/home/pi/Desktop/My_Project/Projects/Face_Recognition_Using_Haarcascade/Face-Recognition/Trainer'
xmlpath = r'/home/pi/Desktop/My_Project/Projects/Face_Recognition_Using_Haarcascade/Face-Recognition/Cascades/haarcascade_frontalface_default.xml'

recognizer = cv2.face.LBPHFaceRecognizer_create()
detector = cv2.CascadeClassifier(xmlpath)

#Function to get images and label data
def getImagesAndLabels(dataset):
    imagePaths = [os.path.join(dataset, f) for f in os.listdir(dataset)]
    faceSamples=[]
    ids = []
    
    for imagePath in imagePaths:
        PIL_img = Image.open(imagePath).convert('L') #Convert it to Grayscale
        img_numpy = np.array(PIL_img, 'uint8')
        id = int(os.path.split(imagePath)[-1].split(".")[1])
        faces = detector.detectMultiScale(img_numpy)

        for (x,y,w,h) in faces:
            faceSamples.append(img_numpy[y:y+h,x:x+w])
            ids.append(id)

    return faceSamples, ids


print("\n [INFO] Training face dataset. It will a few seconds. Wait....")
faces, ids = getImagesAndLabels(dataset)
recognizer.train(faces, np.array(ids))

#Save the model into trainer/trainer.yml
recognizer.write(trainerpath + '/trainer.yml')

#Print the number of faces trained and End Program
print("\n [INFO] {0} faces trained. Exiting Program".format(len(np.unique(ids))))