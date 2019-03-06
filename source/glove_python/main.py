from PyQt5.QtWidgets import QMainWindow, QWidget, QApplication, QMessageBox, QComboBox, QFileDialog
from PyQt5 import QtCore
from PyQt5.QtCore import QTimer, QObject
from PyQt5.QtGui import QPixmap

import pyqtgraph
import pyqtgraph.exporters

import numpy as np
import scipy
import time
import sys
import serial
from multiprocessing import Queue, Process
from collections import deque

from serialPorts import getSerialPorts
from serialProcess import SerialProcess
from serialThread import SerialThread
from main_ui import Ui_MainWindow

import pandas as pd

import mlpy

from myApplication import Presentation

import os

# @brief Buffer size for the data (number of points in the plot)
N_SAMPLES = 256

# @brief Update time of the plot, in ms
PLOT_UPDATE_TIME = 30
##
# @brief Point to update in each redraw
PLOT_UPDATE_POINTS = -10


class App(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(App, self).__init__(parent)
        self.setupUi(self)

        pyqtgraph.setConfigOption('background', 'w')
        self.graphicsView.plotItem.showGrid(True, True, 0.1)
        #self.curve = self.graphicsView.plot(pen='r')

        self.queue = Queue(N_SAMPLES)
        self.data = None

        self.IMU1_X = deque([], maxlen=N_SAMPLES)
        self.IMU1_Y = deque([], maxlen=N_SAMPLES)
        self.IMU1_Z = deque([], maxlen=N_SAMPLES)

        self.IMU2_X = deque([], maxlen=N_SAMPLES)
        self.IMU2_Y = deque([], maxlen=N_SAMPLES)
        self.IMU2_Z = deque([], maxlen=N_SAMPLES)

        self.IMU3_X = deque([], maxlen=N_SAMPLES)
        self.IMU3_Y = deque([], maxlen=N_SAMPLES)
        self.IMU3_Z = deque([], maxlen=N_SAMPLES)

        self.eulerX = 0.0
        self.eulerY = 0.0
        self.TIME = deque([], maxlen=N_SAMPLES)

        # Euler calibration for mapping btw IMU and pointer
        self.IMU_X_MIN = None
        self.IMU_X_MAX = None
        self.IMU_Y_MIN = None
        self.IMU_Y_MAX = None

        # variable for myApplication class
        self.myApp = None

        self.resetBuffers()

        self.counter = 0

        self.gestureItems = []

        ports = getSerialPorts()
        if len(ports) <= 0:
            #ans = QMessageBox.question(self, "No device detected", QWidget)
            print('Error')

        self.cbComPort.addItems(ports)
        #self.cbComPort.setCurrentIndex(1)
        #self.cbComPort.currentText("COM14")
        self.cbBaudRate.addItems(["9600", "38400", "57600", "115200"])
        self.cbBaudRate.setCurrentIndex(1)

        self.cbApplications.addItems(["Power Point", "Game Controller"])

        self.btnStart.clicked.connect(self.start)
        self.btnStop.clicked.connect(self.stop)

        self.btnTraining.clicked.connect(self.trainingState)
        self.btnTesting.clicked.connect(self.testingState)

        self.btnEnter.clicked.connect(self.applicationStart)

        self.btnUpLeft.clicked.connect(self.calibUpLeft)
        self.btnBottomRight.clicked.connect(self.calibBottomRight)

        self.isBtnTraining = False
        self.isBtnTesting = False


        self.btnAdd.clicked.connect(self.addGesture)
        self.btnRemove.clicked.connect(self.removeGesture)

        pix = QPixmap("plot.png")
        w = self.imageTesting.width()
        h = self.imageTesting.height()
        self.imageTesting.setPixmap(pix.scaled(w, h,
                            transformMode=QtCore.Qt.SmoothTransformation))
        self.imageTraining.setPixmap(pix.scaled(w, h,
                            transformMode=QtCore.Qt.SmoothTransformation))

        self.txtGestureInput.returnPressed.connect(self.addGesture)

        self.setUILocked(False)

        self.show()

    def start(self):
        #self.data = SerialProcess(self.queue)
        self.data = SerialThread(self.queue)
        self.data.openPort(str(self.cbComPort.currentText()),
                            int(self.cbBaudRate.currentText()))
        self.setUILocked(True)

        if self.data.start() is False:
            QMessageBox.question(self, "Can't open Serial Port",
                                        "Serial port is already opened.",
                                        QMessageBox.Ok)
        else:
            QTimer.singleShot(30, self.updatePlot)

    def updatePlot(self):
        #print(self.queue.qsize())
        if (self.queue.qsize() == 0):
            self.resetBuffers()
            self.counter = 0

        while self.queue.qsize() != 0:
            data = self.queue.get(True, 1)
            #print(data)
            self.TIME.append(float(data[0]))
            self.IMU1_X.append(float(data[1]))
            self.IMU1_Y.append(float(data[2]))
            self.IMU1_Z.append(float(data[3]))
            self.IMU2_X.append(float(data[4]))
            self.IMU2_Y.append(float(data[5]))
            self.IMU2_Z.append(float(data[6]))
            self.IMU3_X.append(float(data[7]))
            self.IMU3_Y.append(float(data[8]))
            self.IMU3_Z.append(float(data[9]))
            #self.eulerX = float(data[4])
            #self.eulerY = float(data[5])
            self.counter += 1
            if (self.counter > 75):
                fname = ""
                for selectedItem in self.listGesture.selectedItems():
                    fname=self.gestureItems[self.listGesture.row(selectedItem)]
                if (fname in self.gestureItems) and (self.isBtnTraining == True):
                    self.getGestureTemplate(fname)
                    exp = pyqtgraph.exporters.ImageExporter(self.graphicsView.plotItem)
                    exp.parameters()['width'] = 1000
                    exp.export(fname + ".png")
                    print("saved ", fname)

                if self.isBtnTesting == True:
                    exp = pyqtgraph.exporters.ImageExporter(self.graphicsView.plotItem)
                    exp.parameters()['width'] = 1000
                    exp.export("testing.png")
                    pix = QPixmap("testing.png")
                    w = self.imageTesting.width()
                    h = self.imageTesting.height()
                    self.imageTesting.setPixmap(pix.scaled(w, h,
                                        transformMode=QtCore.Qt.SmoothTransformation))

                    self.updateTesting()

                self.resetBuffers()
                self.counter = 0

        self.graphicsView.clear()
        self.graphicsView.plot(x=list(self.TIME)[-PLOT_UPDATE_POINTS:],
                        y=list(self.IMU1_X)[-PLOT_UPDATE_POINTS:], pen='r')
        self.graphicsView.plot(x=list(self.TIME)[-PLOT_UPDATE_POINTS:],
                        y=list(self.IMU1_Y)[-PLOT_UPDATE_POINTS:], pen='g')
        self.graphicsView.plot(x=list(self.TIME)[-PLOT_UPDATE_POINTS:],
                        y=list(self.IMU1_Z)[-PLOT_UPDATE_POINTS:], pen='b')

        self.graphicsView.plot(x=list(self.TIME)[-PLOT_UPDATE_POINTS:],
                        y=list(self.IMU2_X)[-PLOT_UPDATE_POINTS:], pen='c')
        self.graphicsView.plot(x=list(self.TIME)[-PLOT_UPDATE_POINTS:],
                        y=list(self.IMU2_Y)[-PLOT_UPDATE_POINTS:], pen='m')
        self.graphicsView.plot(x=list(self.TIME)[-PLOT_UPDATE_POINTS:],
                        y=list(self.IMU2_Z)[-PLOT_UPDATE_POINTS:], pen='y')

        self.graphicsView.plot(x=list(self.TIME)[-PLOT_UPDATE_POINTS:],
                        y=list(self.IMU3_X)[-PLOT_UPDATE_POINTS:], pen='k')
        self.graphicsView.plot(x=list(self.TIME)[-PLOT_UPDATE_POINTS:],
                        y=list(self.IMU3_Y)[-PLOT_UPDATE_POINTS:], pen='w')
        self.graphicsView.plot(x=list(self.TIME)[-PLOT_UPDATE_POINTS:],
                        y=list(self.IMU3_Z)[-PLOT_UPDATE_POINTS:], pen='b')

        QTimer.singleShot(30, self.updatePlot)

    def setUILocked(self, enabled):
        self.btnStop.setEnabled(enabled)
        self.btnStart.setEnabled(not enabled)
        self.cbComPort.setEnabled(not enabled)
        self.cbBaudRate.setEnabled(not enabled)
        self.btnAdd.setEnabled(enabled)
        self.btnRemove.setEnabled(enabled)
        self.btnTesting.setEnabled(enabled)
        self.btnTraining.setEnabled(enabled)
        self.listGesture.setEnabled(enabled)
        self.txtGestureInput.setEnabled(enabled)
        self.labelPrediction.setEnabled(enabled)
        self.btnEnter.setEnabled(enabled)
        self.btnUpLeft.setEnabled(enabled)
        self.btnBottomRight.setEnabled(enabled)
        self.cbApplications.setEnabled(enabled)

    def stop(self):
        self.data.closePort()
        self.data.join()
        self.setUILocked(False)
        self.resetBuffers()

    def resetBuffers(self):
        self.TIME.clear()
        self.IMU1_X.clear()
        self.IMU1_Y.clear()
        self.IMU1_Z.clear()
        self.IMU2_X.clear()
        self.IMU2_Y.clear()
        self.IMU2_Z.clear()
        self.IMU3_X.clear()
        self.IMU3_Y.clear()
        self.IMU3_Z.clear()

    def testingState(self):
        self.isBtnTraining = False
        self.isBtnTesting = True
        self.btnTesting.setEnabled(False)
        self.btnTraining.setEnabled(True)
        QTimer.singleShot(30, self.updateTraining)

    def trainingState(self):
        self.isBtnTraining = True
        self.isBtnTesting = False
        self.btnTesting.setEnabled(True)
        self.btnTraining.setEnabled(False)
        QTimer.singleShot(30, self.updateTraining)

    def updateTraining(self):
        fname = ""
        for selectedItem in self.listGesture.selectedItems():
            fname=self.gestureItems[self.listGesture.row(selectedItem)]
        if fname in self.gestureItems:
            pix = QPixmap(fname + ".png")
            w = self.imageTraining.width()
            h = self.imageTraining.height()
            self.imageTraining.setPixmap(pix.scaled(w, h,
                                transformMode=QtCore.Qt.SmoothTransformation))
        else:
            pix = QPixmap("plot.png")
            w = self.imageTraining.width()
            h = self.imageTraining.height()
            self.imageTraining.setPixmap(pix.scaled(w, h,
                                transformMode=QtCore.Qt.SmoothTransformation))

        QTimer.singleShot(30, self.updateTraining)

    def getGestureTemplate(self, fname):
        inputFile = open(fname + '.txt', 'w')
        for i in range(len(self.IMU1_X)):
            inputFile.write(str(self.IMU1_X[i]) + ' ' +
                            str(self.IMU1_Y[i]) + ' ' +
                            str(self.IMU1_Z[i]) + ' ' +
                            str(self.IMU2_X[i]) + ' ' +
                            str(self.IMU2_Y[i]) + ' ' +
                            str(self.IMU2_Z[i]) + ' ' +
                            str(self.IMU3_X[i]) + ' ' +
                            str(self.IMU3_Y[i]) + ' ' +
                            str(self.IMU3_Z[i]) + '\n')

        inputFile.close()

    def updateTesting(self):
        dist = []
        text = ""
        for text_file in self.gestureItems:
            dist.append(self.myDTW(text_file + '.txt', self.IMU1_X, self.IMU1_Y, self.IMU1_Z,
                                                        self.IMU2_X, self.IMU2_Y, self.IMU2_Z,
                                                        self.IMU3_X, self.IMU3_Y, self.IMU3_Z))
        predict = min(dist)
        text = self.gestureItems[dist.index(predict)]

        print("dist_min = {}, prediction: {}".format(predict, text))
        self.labelPrediction.setText(text)
        if self.myApp != None:
            print("start power point")
            self.myApp.run(text, self.eulerX, self.eulerY)

    def addGesture(self):
        text = self.txtGestureInput.text()
        if text not in self.gestureItems:
            self.listGesture.addItem(text)
            self.gestureItems.append(text)
            self.txtGestureInput.setText('')
        else:
            QMessageBox.warning(self, "WARNING",
                "This item was already in the list. Please input another item",
                QMessageBox.Ok)


    def removeGesture(self):
        for selectedItem in self.listGesture.selectedItems():
            self.gestureItems.pop(self.listGesture.row(selectedItem))
            #print(self.gestureItems)
            self.listGesture.takeItem(self.listGesture.row(selectedItem))


    def myDTW(self, text_file, arr1, arr2, arr3, arr4, arr5, arr6, arr7, arr8, arr9):
        df = pd.read_csv(text_file, sep = ' ', header=None)
        x1 = df.iloc[0:75, 0].values
        y1 = df.iloc[0:75, 1].values
        z1 = df.iloc[0:75, 2].values
        x2 = df.iloc[0:75, 3].values
        y2 = df.iloc[0:75, 4].values
        z2 = df.iloc[0:75, 5].values
        x3 = df.iloc[0:75, 6].values
        y3 = df.iloc[0:75, 7].values
        z3 = df.iloc[0:75, 8].values

        dist1 = mlpy.dtw_std(x1, arr1, dist_only=True)
        #print(text_file + " distX: ", dist1)
        dist2 = mlpy.dtw_std(y1, arr2, dist_only=True)
        #print(text_file + " distY: ", dist2)
        dist3 = mlpy.dtw_std(z1, arr3, dist_only=True)
        #print(text_file + " distZ: ", dist3)

        dist4 = mlpy.dtw_std(x2, arr4, dist_only=True)
        #print(text_file + " distX: ", dist1)
        dist5 = mlpy.dtw_std(y2, arr5, dist_only=True)
        #print(text_file + " distY: ", dist2)
        dist6 = mlpy.dtw_std(z2, arr6, dist_only=True)
        #print(text_file + " distZ: ", dist3)

        dist7 = mlpy.dtw_std(x3, arr7, dist_only=True)
        #print(text_file + " distX: ", dist1)
        dist8 = mlpy.dtw_std(y3, arr8, dist_only=True)
        #print(text_file + " distY: ", dist2)
        dist9 = mlpy.dtw_std(z3, arr9, dist_only=True)
        #print(text_file + " distZ: ", dist3)

        return dist1 + dist2 + dist3 + dist4 + dist5 + dist6 + dist7 + dist8 + dist9

    def applicationStart(self):
        selectApp = str(self.cbApplications.currentText())
        fileName = ""
        if selectApp == "Power Point":
            self.myApp = Presentation(self.IMU_X_MIN, self.IMU_X_MAX,
                                        self.IMU_Y_MIN, self.IMU_Y_MAX)
            dlg = QFileDialog()
            dlg.setFileMode(QFileDialog.AnyFile)
            #dlg.setFilter("Power point files (*.ppt)")
            if dlg.exec_():
                fileName = dlg.selectedFiles()
                print(fileName)
            os.startfile(fileName[0])


    def calibUpLeft(self):
        self.IMU_X_MIN = self.eulerX
        self.IMU_Y_MIN = self.eulerY
        print(self.IMU_X_MIN)
        print(self.IMU_Y_MIN)

    def calibBottomRight(self):
        self.IMU_X_MAX = self.eulerX
        self.IMU_Y_MAX = self.eulerY
        print(self.IMU_X_MAX)
        print(self.IMU_Y_MAX)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    #ex.update()
    sys.exit(app.exec_())
