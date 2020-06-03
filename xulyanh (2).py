#Import libraries
import cv2

import serial
import time
import numpy as np
import imutils
import matplotlib.pyplot as plt
#%matplotlib inline


MySerial  = serial.Serial('COM11' , 9600)
MySerial.timeout = 1

plt.rcParams['figure.figsize'] = [20, 10]

# Access camera and take, save photo
cap = cv2.VideoCapture(1)
cv2.namedWindow("Image")
img_counter = 0
 
while True:
    ret, frame = cap.read()
    cv2.imshow("Image", frame)

    if not ret:
        break
    k = cv2.waitKey(1)
    if k%256 == 32:
        # SPACE pressed to take
        img_name = "opencv_frame_{}.png".format(img_counter)
        cv2.imwrite(img_name, frame)
        MyImg1 = frame
        print("{} written!".format(img_name))
        img_counter += 1
        break
cap.release()
# cv2.imshow('Image',frame)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
# cv2.waitKey(1)


#Resize the image to size 1200x800
new_width = 1200
new_height = 800
img = cv2.resize(src=frame, dsize=(new_width, new_height))
MyImg2 = img
# cv2.imshow('Image(1200x800) after resizing' ,img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
# cv2.waitKey(1)

# find and draw contous of image
grayImg = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
binImg = cv2.adaptiveThreshold(grayImg, 
                                       maxValue=255, 
                                       adaptiveMethod=cv2.ADAPTIVE_THRESH_MEAN_C, 
                                       thresholdType=cv2.THRESH_BINARY,
                                       blockSize=11,
                                       C=8)
contours, hierarchy  = cv2.findContours(binImg, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

iContours = 0
for contour in contours:
    cv2.drawContours(img, contours, iContours, (0, 255, 0))
    iContours += 1

MyImg6= img
cv2.imshow("Image after determining coordinates of dirty points", MyImg6)

# cv2.waitKey(0)
# cv2.destroyAllWindows()
# cv2.waitKey(1)

# Grid on the image(20 cells)
print('Image have been meshed')
# plt.rc('grid', linestyle="-", color='white')
# f=plt.figure()
# f.add_subplot(4,5,2)
# plt.grid(True)
# img[:,:,::-1]

# Show image before determining dirty areas
# cv2.imshow("Image before determining dirty areas", img)

# Find dirty areas
listX=[]
listY=[]
listCell=[]
xDivisions=[0,250,500,750,1000,1200]
yDivisions=[0,200,400,600,800]
cells=[]
amountPointsOfCell=[]
for item in range((len(xDivisions)-1)*(len(yDivisions)-1)):
    amountPointsOfCell.append(0)
    
    
count=0
img_filledColor=img 
for i in range(len(xDivisions)-1):
    cells.append(count)
    count+=4
    

def fillColorDirtyArea(xMin, xMax, yMin,yMax):
    img_filledColor[yMin:yMax, xMin:xMax]=[255,0,0]
    return 
    
def checkYConditions(cell,listCell,xDivision, yCoordinate, yDivisions, status):
        listCell=listCell
        cells=[]
        if(status==True):
            for i in range(len(yDivisions)):
                cells.append(cell)
                cell+=1
        elif(status==False):
            for i in range(len(yDivisions)):
                cells.append(cell+3)
                cell-=1          
        if(yCoordinate<=yDivisions[1]):
            amountPointsOfCell[cells[0]]+=1
            if((amountPointsOfCell[cells[0]]/20000)*100>=1):
                fillColorDirtyArea(xDivision-250,xDivision, yDivisions[0],yDivisions[1])
                if(cells[0] not in listCell):
                    listCell.append(cells[0])
                  
        elif(yCoordinate<=yDivisions[2]):
            amountPointsOfCell[cells[1]]+=1
            if((amountPointsOfCell[cells[1]]/20000)*100>=1):
                fillColorDirtyArea(xDivision-250,xDivision, yDivisions[1],yDivisions[2])
                if(cells[1] not in listCell):
                    listCell.append(cells[1])
                  
        elif(yCoordinate<=yDivisions[3]):
            amountPointsOfCell[cells[2]]+=1
            if((amountPointsOfCell[cells[2]]/20000)*100>=1):
                fillColorDirtyArea(xDivision-250,xDivision, yDivisions[2],yDivisions[3])
                if(cells[2] not in listCell):
                    listCell.append(cells[2])

        elif(yCoordinate<=yDivisions[4]):
            amountPointsOfCell[cells[3]]+=1
            if((amountPointsOfCell[cells[3]]/20000)*100>=1):
                fillColorDirtyArea(xDivision-250,xDivision, yDivisions[3],yDivisions[4])
                if(cells[3] not in listCell):
                    listCell.append(cells[3])
        
                  
        return  listCell    
    
    
for contour in contours:
         for p in contour:
            if(p[0][0]<=xDivisions[1]):
                listCell=checkYConditions(cells[0],listCell,xDivisions[1], p[0][1],yDivisions,False)
            elif(p[0][0]<=xDivisions[2]):
                listCell=checkYConditions(cells[1],listCell,xDivisions[2], p[0][1],yDivisions,True)
            elif(p[0][0]<=xDivisions[3]):
                listCell=checkYConditions(cells[2],listCell,xDivisions[3], p[0][1],yDivisions,False)
            elif(p[0][0]<=xDivisions[4]):
                listCell=checkYConditions(cells[3],listCell,xDivisions[4], p[0][1],yDivisions,True)       
            elif(p[0][0]<=xDivisions[5]):
                listCell=checkYConditions(cells[4],listCell,xDivisions[5], p[0][1],yDivisions,False)
    

listCell.sort()

# Result    

print("Amount of amountPointsOfCell: ")
print(len(amountPointsOfCell))

print("Amount of dirty areas: ")
print(len(listCell))
print("Dirty areas are: ")
count=0
str1 =""
for i in range(len(listCell)):
    listCell[count]+=1
    str1 += str(listCell[count]) + ","
    print(listCell[count], end=' ')

    count+=1
print(str1)

MySerial.write(str1.encode() )
    # print(i)
time.sleep(0.1)
print(str("OK ") + MySerial.readline().decode('ascii'))

MySerial.close()

# plt.rc('grid', linestyle="-", color='white')
# f=plt.figure()
# f.add_subplot(4,1,1)
# plt.grid(True)
# print('Image afte determining dirty areas')
# MyImg = img_filledColor[:,:,::-1]
# plt.imshow(MyImg)
# cv2.imshow("Image after determining dirty areas", img_filledColor)
MyImg4 = img_filledColor

rows = 2
cols = 2
axes=[]
fig=plt.figure()

axes.append( fig.add_subplot(rows, cols, 1) )
subplot_title=("image"+str(1))
axes[-1].set_title(subplot_title)
plt.imshow(MyImg1)

axes.append( fig.add_subplot(rows, cols, 2) )
subplot_title=("image"+str(2))
axes[-1].set_title(subplot_title)
plt.imshow(MyImg2)

axes.append( fig.add_subplot(rows, cols, 3) )
subplot_title=("image"+str(3))
axes[-1].set_title(subplot_title)
plt.imshow(MyImg6)






axes.append( fig.add_subplot(rows, cols, 4) )
subplot_title=("image"+str(4))
axes[-1].set_title(subplot_title)
count=0
for i in range(len(listCell)):
    listCell[count]+=1

    count+=1


plt.rc('grid', linestyle="-", color='white')

# f.add_subplot(4,1,1)
plt.grid(True)
print('Image afte determining dirty areas')
MyImg = img_filledColor[:,:,::-1]


plt.imshow(MyImg)


fig.tight_layout()
plt.show()


# cv2.waitKey(0)
# cv2.destroyAllWindows()
# cv2.waitKey(1)

while True:

    i = input("input (on/off): please ").strip()
    if i == 'done':
        print('finished program ')
        break
    MySerial.write(i.encode() )
    # print(i)
    time.sleep(0.1)
    print(MySerial.readline().decode('ascii'))

MySerial.close()
