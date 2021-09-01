import cv2 as c
import numpy as n
import serial
import time


arduino = serial.Serial('COM3', 115200, timeout=0.1)
arduino.close()
arduino.open()
#, c.CAP_DSHOW
# cap.set(3,640)
# cap.set(4,480)
# cap.set(1,150)
cap = c.VideoCapture('http://192.168.10.2:4747/video') 
error = 0
while True:
    
   
    success, img = cap.read()
    height, width = img.shape[:2]
    

    img2 = img.copy()

    imggray = c.cvtColor(img,c.COLOR_BGR2GRAY)
    imgblur = c.GaussianBlur(imggray, (5,5),1)
    imgthreshold = c.threshold(imgblur, 40, 255, c.THRESH_BINARY_INV)[1]
    
    contours, hierarchy = c.findContours(imgthreshold, c.RETR_EXTERNAL, c.CHAIN_APPROX_NONE)

    for cnt in contours:
        area = c.contourArea(cnt)

        if area>500:
            c.drawContours(img2, cnt, -1, (0,255,0), 2)

            # peri = c.arcLength(cnt,True)
                
            # approx = c.approxPolyDP(cnt, 0.02*peri, True)

            # x,y,w,h = c.boundingRect(approx)

            mo = c.moments(cnt)
            x = int(mo["m10"]/mo["m00"])
            y = int(mo["m01"]/mo["m00"])

            c.circle(img2, (x,y), 5, (0,255,0), -1)
            # c.circle(img2, (156,350), 5, (0,255,0), -1)
            # c.circle(img2, (156,270), 5, (0,255,0), -1)
            

            print(x)
            print(y)

            if y>350 :
                print("left")
                error = 350-y

            elif y<270 :
                print("right")
                error = 270-y

            else:
                print("straight")
                error = 0

    
    arduino.write(bytes(str(error), 'utf-8'))
    time.sleep(0.005)


    c.imshow("Result", img2)
    

    if c.waitKey(1) & 0xFF==ord('d'):     #if letter d is pressed, loop breaks and vid stops
        break

cap.release()
c.destroyAllWindows()