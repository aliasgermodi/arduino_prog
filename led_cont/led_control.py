from PyQt4.QtGui import *
from PyQt4.QtCore import *
import sys
import serial
  
def printNumber(number):
    print number
    ser = serial.Serial('/dev/ttyACM0', 9600)
    ser.write(unichr(number))
 
  
if __name__=="__main__":
    #First we create a QApplication and QSlider
    app=QApplication(sys.argv)
    slider=QSlider(Qt.Horizontal)
    slider.setRange(0,127)
    slider.setFixedWidth(400)
  
    QObject.connect(slider,SIGNAL("valueChanged(int)"),printNumber)
  
  
    slider.show()
    #Start the evnt loop
    sys.exit(app.exec_())
