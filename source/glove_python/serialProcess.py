from multiprocessing import Process, Event, Queue
import numpy as np
from time import time
import serial
from collections import deque

from log import Log

class SerialProcess(Process):
    def __init__(self, queue):
        Process.__init__(self)
        self.exit = Event()
        # local variables
        self.ser = serial.Serial()
        self.queue = queue
        #logging
        self.log = Log('SerialProcess')

    def run(self):
        #self.init_time = time()
        try:
            while self.ser.isOpen() and not self.exit.is_set():
                data = self.ser.readline().strip()
                print(data)
                try:
                    data = map(float, data.split(','))
                    #self.queue.put([time() - self.init_time] + data)
                    #print(self.queue.size())
                    if len(data) == 4:
                        print(data)
                        self.queue.put(data)

                        #print([time() - self.init_time] + data)

                except:
                    pass
            return
        except:
            self.log.e("Exception in SerialProcess")
            raise
        finally:
            self.closePort()
            self.log.i("Finished SerialProcess normally")

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
            self.log.i("Opened serial port" + str(port))
            return True
        except:
            self.log.e("Failed to open Serial port" + str(port))
            return False

    def closePort(self):
        self.log.i("Exiting process...")
        #self.ser.close()
        self.exit.set()

N_SAMPLES = 1000

if __name__ == "__main__":
    queue = Queue(N_SAMPLES)
    TIME = deque([], maxlen=N_SAMPLES)
    DATA0 = deque([], maxlen=N_SAMPLES)
    DATA1 = deque([], maxlen=N_SAMPLES)
    DATA2 = deque([], maxlen=N_SAMPLES)
    data = SerialProcess(queue)
    data.openPort(port='COM4', bd=115200)
    #data.start()
    data.run()
    """
    while queue.qsize() != 0:
        data = queue.get(True, 1)
        print(data)
        TIME.append(data[0])
        DATA0.append(float(data[1]))
        DATA1.append(float(data[2]))
        DATA2.append(float(data[3]))
    """
    print(queue.get())
    data.join()
