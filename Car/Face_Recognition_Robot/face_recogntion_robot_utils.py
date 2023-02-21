from face_recognition_robot_function import *

import numpy as np
import matplotlib.pyplot as plt

pError = 0
pid = [0.5,0.5] #PD only

def main():
    x = [1,2,3]
    y = [2,4,1]
    #plt.plot(x,y)
    xinter = [1,3]
    yinter = [1,4]
    interceptY = (np.interp(2.25,[1,3],[1,4])) # input,x,y
    #plt.xlim(interceptY)
    plt.plot(xinter,yinter)
    plt.xlabel('x-axis')
    plt.ylabel('y-axis')
    plt.title("Intercept Value : " + str(interceptY))
    plt.show()
    print(interceptY)

if __name__ == "__main__":
    #main()
    while True:
        # Step 1 Capture Image and Info
        img,info = findface()

        # Step 2 Track
        img, pError =  trackObject(img, info, pid, pError)

        # Step 3 Draw Overlay
        draw = drawOverlay(img)

        cv2.imshow("Frame", img)
        if cv2.waitKey(1) & 0XFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()
