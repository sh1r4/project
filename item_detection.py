import cv2, math
import numpy as np
import serial
import time
import cvlib as cv
from cvlib.object_detection import draw_bbox


# open webcam
webcam = cv2.VideoCapture(1)

# prepare arduino
arduino = serial.Serial('COM4', 9600)
time.sleep(2) # waiting the initialization...
print("initializing")

if not webcam.isOpened():
    print("Could not open webcam")
    exit()
    
# loop through frames
while webcam.isOpened():
    # for the arduino
    time.sleep(0.05)

    # read frame from webcam 
    status, frame = webcam.read()

    # apply object detection
    bbox, label, conf = cv.detect_common_objects(frame)
    
    # #arduino management
    if(len(bbox) > 0):
        if("cell phone" in label or "remote" in label or "clock" in label):
            if(bbox[0][2] >= 400):
                print('RIGHT')
                arduino.write('R'.encode())
            else:
                print('LEFT')
                arduino.write('L'.encode())
            time.sleep(10)
        elif("bottle" in label):
            if(bbox[0][2] >= 400):
                print('RIGHT')
                arduino.write('A'.encode())
            else:
                print('LEFT')
                arduino.write('Z'.encode())
            time.sleep(10)
    else:
        arduino.write('S'.encode())

    # draw bounding box over detected objects
    output_image = draw_bbox(frame, bbox, label, conf)

    # display output
    cv2.imshow("Real-time object detection", output_image)

    # press "Q" to stop
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
# release resources
webcam.release()
cv2.destroyAllWindows() 