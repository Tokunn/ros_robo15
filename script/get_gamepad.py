#!/usr/bin/env python2

### This program is made for DEMAEROBOT and UKETORIROBOT by Tokunn
### 2014 OyNCT Robocon Ateam Tsushin
### H26 Jul. 5

import time
import pygame
import decimal
from pygame.locals import *

class LogicoolGamepad():

    def __init__(self):
        pygame.joystick.init()
        pygame.init()
        if pygame.joystick.get_count() == 0:
            raise GamepadError('Gamepad not found')

        self.joys = pygame.joystick.Joystick(0)
        self.joys.init()

    def __del__(self):
        pygame.quit()

    def update(self):
        self.eventlist = pygame.event.get()

        self.raw_left_Axis_X = self.joys.get_axis(0)
        self.raw_left_Axis_Y = self.joys.get_axis(1)
        self.raw_rigt_Axis_X = self.joys.get_axis(2)
        self.raw_rigt_Axis_Y = self.joys.get_axis(3)

        self.raw_Button_X = self.joys.get_button(0)
        self.raw_Button_A = self.joys.get_button(1)
        self.raw_Button_B = self.joys.get_button(2)
        self.raw_Button_Y = self.joys.get_button(3)

        self.raw_Hat_X = self.joys.get_hat(0)[0]
        self.raw_Hat_Y = self.joys.get_hat(0)[1]

        self.raw_left_Bumper = self.joys.get_button(4)
        self.raw_rigt_Bumper = self.joys.get_button(5)

        self.raw_left_Trigger = self.joys.get_button(6)
        self.raw_rigt_Trigger = self.joys.get_button(7)

        self.raw_Button_Back = self.joys.get_button(8)
        self.raw_Button_Strt = self.joys.get_button(9)
        self.raw_left_Push = self.joys.get_button(10)
        self.raw_rigt_Push = self.joys.get_button(11)

        self.convart_rawvalue()

    def convart_rawvalue(self):
        self.left_Axis_X = self.rounds(self.raw_left_Axis_X)
        self.left_Axis_Y = self.rounds(self.raw_left_Axis_Y * -1)
        self.rigt_Axis_X = self.rounds(self.raw_rigt_Axis_X)
        self.rigt_Axis_Y = self.rounds(self.raw_rigt_Axis_Y * -1)

        self.Button_X = self.raw_Button_X
        self.Button_A = self.raw_Button_A
        self.Button_B = self.raw_Button_B
        self.Button_Y = self.raw_Button_Y

        self.Hat_X = self.raw_Hat_X
        self.Hat_Y = self.raw_Hat_Y

        self.left_Bumper = self.raw_left_Bumper
        self.rigt_Bumper = self.raw_rigt_Bumper

        self.left_Trigger = self.raw_left_Trigger
        self.rigt_Trigger = self.raw_rigt_Trigger

        self.Button_Back = self.raw_Button_Back
        self.Button_Strt = self.raw_Button_Strt
        self.left_Push = self.raw_left_Push
        self.rigt_Push = self.raw_rigt_Push

    def rounds(self, raw_Axiss):
        self.handred_Axiss = raw_Axiss * 100
        self.round_Axiss = round(self.handred_Axiss)
        self.converted_Axiss = self.round_Axiss / 100
        return self.converted_Axiss

    def prints(self):
        print("\n")
        print(self.Hat_X)
        print(self.Hat_Y)
        print("\n")

class LogicoolGamepad_int( LogicoolGamepad ):
    def rounds( self, raw_Axiss ):
        self.__handred_Axis = raw_Axiss * 10
        self.__round_Axiss = int(round( self.__handred_Axis ))
        return self.__round_Axiss

class GamepadError(Exception):
    def __init__(self, message):
        self.message = message
    def __str__(self):
        return repr(self.message)
        
if __name__ == '__main__':
    try:
        F710 = LogicoolGamepad()
        while True:
            F710.update()
            F710.prints()
            time.sleep(0.05)
    except GamepadError:
        print("\nGamepadDevice not found !!")
        print("Please connect GamepadDevice\n")
        quit
    except KeyboardInterrupt:
        print("\nInput ctrl+C\nquit q(-_-)")
        quit
