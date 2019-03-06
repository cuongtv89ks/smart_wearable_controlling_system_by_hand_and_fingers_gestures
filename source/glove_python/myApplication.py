import pyautogui



class Presentation:
    def __init__(self, IMU_X_MIN, IMU_X_MAX, IMU_Y_MIN, IMU_Y_MAX):
        self.screenWidth, self.screenHeight = pyautogui.size()
        self.IMU_X_MIN = 0
        self.IMU_X_MAX = 0
        self.IMU_Y_MIN = 0
        self.IMU_Y_MAX = 0

    def forwardSlide(self):
        pyautogui.press('right')
        print('press right')

    def backwardSlide(self):
        pyautogui.press('left')
        print('press left')

    def pointer(self, x_axis, y_axis):
        x = self.constrain(x_axis, self.IMU_X_MIN, self.IMU_X_MAX)
        y = self.constrain(y_axis, self.IMU_Y_MIN, self.IMU_Y_MAX)

        cursorX = self.mapMouse(x, self.IMU_X_MIN, self.IMU_X_MAX,
                                1, self.screenWidth)
        cursorY = self.mapMouse(y, self.IMU_Y_MIN, self.IMU_Y_MAX,
                                self.screenHeight, 1)

        pyautogui.moveTo(cursorX, cursorY)

    def clickLeft(self):
        pyautogui.click(button='left')

    def clickRight(self):
        pyautogui.click(button='right')

    def scrollUp(self, clicks):
        pyautogui.scroll(clicks)

    def scrollDown(self, clicks):
        pyautogui.scroll(0 - clicks)

    def quit(self):
        pyautogui.hotkey('altleft', 'f4')
        print('press quit program')

    def fullScreenMode(self):
        pyautogui.press('f5')
        print('full screen mode')

    def run(self, gesture, cursorX, cursorY):
        if gesture == "pointer":
            self.pointer(cursorX, cursorY)
        elif gesture == "forward":
            self.forwardSlide()
        elif gesture == "backward":
            self.backwardSlide()
        elif gesture == 'quit':
            self.quit()
        elif gesture == 'full':
            self.fullScreenMode()

    def mapMouse(self, x, in_min, in_max, out_min, out_max):
        return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

    def constrain(self, value, minValue, maxValue):
        if value > maxValue:
            return maxValue
        elif value < minValue:
            return minValue
        else:
            return value
