from threading import Thread
import numpy as np
from time import time
import serial
from collections import deque
from queue import Queue

class SerialThread(Thread):
    def __init__(self, queue):
        Thread.__init__(self)
        self.ser = serial.Serial()
        self.queue = queue

    def run(self):
        print("hello")
        while self.ser.isOpen():
            data = str(self.ser.readline(), 'utf-8')
            #data = self.ser.readline().strip()
            #data = map(float, data.split(','))
            data = data.strip().split(',')
            #print(data)
            if len(data) == 10:
                self.queue.put(data)

    def openPort(self, port='', bd=9600):
        self.ser.port = port
        self.ser.baudrate = bd
        self.ser.stopbits = serial.STOPBITS_ONE
        self.ser.bytesize = serial.EIGHTBITS
        self.ser.rtscts = 1
        self.ser.timeout = 0.5

        if self.ser.isOpen():
            return False
        try:
            self.ser.open()
            self.ser.flushInput()
            #self.log.i("Opened serial port" + str(port))
            return True
        except:
            #self.log.e("Failed to open Serial port" + str(port))
            return False

    def closePort(self):
        #self.log.i("Exiting process...")
        self.ser.close()
        #self.exit.set()

N_SAMPLES = 1000

if __name__ == "__main__":
    q = Queue(N_SAMPLES)
    TIME = deque([], maxlen=N_SAMPLES)
    DATA0 = deque([], maxlen=N_SAMPLES)
    DATA1 = deque([], maxlen=N_SAMPLES)
    DATA2 = deque([], maxlen=N_SAMPLES)

    DATA3 = deque([], maxlen=N_SAMPLES)
    DATA4 = deque([], maxlen=N_SAMPLES)
    DATA5 = deque([], maxlen=N_SAMPLES)

    DATA6 = deque([], maxlen=N_SAMPLES)
    DATA7 = deque([], maxlen=N_SAMPLES)
    DATA8 = deque([], maxlen=N_SAMPLES)
    data = SerialThread(q)
    #print(data.openPort(port='/dev/rfcomm0', bd=9600))
    print(data.openPort(port='COM4', bd=115200))
    data.start()
    #data.run()
    """
    while queue.qsize() != 0:
        data = queue.get(True, 1)
        print(data)
        TIME.append(data[0])
        DATA0.append(float(data[1]))
        DATA1.append(float(data[2]))
        DATA2.append(float(data[3]))
    """
    while True:
        print(q.get())

    data.join()
