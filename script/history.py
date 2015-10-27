#!/usr/bin/env python3
# -*- coding: utf-8 -*-

### H27 10 26

import rospy
from ros_robo15.msg import Gamepad_cmd
from ros_robo15.msg import Spi_cmd

def button(data):
    if (str(data.button_x) == 'True'):
        rospy.loginfo(rospy.get_caller_id() + " X TRI")
    if (str(data.button_a) == 'True'):
        rospy.loginfo(rospy.get_caller_id() + " A CENT")
    if (str(data.button_b) == 'True'):
        rospy.loginfo(rospy.get_caller_id() + " B SNIP")

def spi_data(data):
    if (data.spi_cmd == 24):
        rospy.loginfo(rospy.get_caller_id() + " SPI : X")
    if (data.spi_cmd == 40):
        rospy.loginfo(rospy.get_caller_id() + " SPI : A")
    if (data.spi_cmd == 56):
        rospy.loginfo(rospy.get_caller_id() + " SPI : B")

def history_node():
    rospy.init_node('history_node', anonymous=False)

    rospy.Subscriber("gamepad", Gamepad_cmd, button)
    rospy.Subscriber("send_data", Spi_cmd, spi_data)

    rospy.spin()

if __name__ == '__main__':
    try:
        history_node()
    except rospy.ROSInterruptException:
        pass
