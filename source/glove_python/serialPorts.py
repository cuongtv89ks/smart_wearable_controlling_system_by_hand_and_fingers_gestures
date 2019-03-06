import sys
import serial
from serial.tools import list_ports


def getSerialPorts():
    portList = []
    try:
        for port in list_ports.comports():
            portList.append(port[0])
        return portList
    except Exception as e:
        print("Error: ",e)
        sys.exit(1)

if __name__ == '__main__':
    print(getSerialPorts())
