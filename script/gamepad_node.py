#!/usr/bin/env python2
# -*- coding: utf-8 -*-

### H27 Oug23 

import rospy
from std_msgs.msg import String
from ros_robo15.msg import Gamepad_cmd

import get_gamepad

#----- gamepad_node() -----#
def gamepad_node():
    #pub = rospy.Publisher('gamepad_data', String, queue_size=10)
    pub = rospy.Publisher('gamepad', Gamepad_cmd, queue_size=10)
    rospy.init_node('gamepad_node', log_level=rospy.DEBUG, anonymous=True)
    rate = rospy.Rate(50)

    gamepad_dev = get_gamepad.LogicoolGamepad()

    while not rospy.is_shutdown():
        gamepad_dev.update()

        hello_str = "hello gamepad_node ! %s" % rospy.get_time()
        rospy.logdebug(hello_str)
        pub.publish(hello_str)


        gamepad_cmd = Gamepad_cmd()

        gamepad_cmd.left_axis_x = gamepad_dev.left_Axis_X
        gamepad_cmd.left_axis_y = gamepad_dev.left_Axis_Y
        gamepad_cmd.right_axis_x = gamepad_dev.rigt_Axis_X
        gamepad_cmd.right_axis_y = gamepad_dev.rigt_Axis_Y

        gamepad_cmd.button_x = gamepad_dev.Button_X
        gamepad_cmd.button_a = gamepad_dev.Button_A
        gamepad_cmd.button_b = gamepad_dev.Button_B
        gamepad_cmd.button_y = gamepad_dev.Button_Y

        gamepad_cmd.hat_x = gamepad_dev.Hat_X
        gamepad_cmd.hat_y = gamepad_dev.Hat_Y

        gamepad_cmd.left_bumper = gamepad_dev.left_Bumper
        gamepad_cmd.right_bumper = gamepad_dev.rigt_Bumper

        gamepad_cmd.left_trigger = gamepad_dev.left_Trigger
        gamepad_cmd.right_trigger = gamepad_dev.rigt_Trigger

        gamepad_cmd.button_back = gamepad_dev.Button_Back
        gamepad_cmd.button_start = gamepad_dev.Button_Strt

        gamepad_cmd.left_axis_push = gamepad_dev.left_Push
        gamepad_cmd.right_axis_push = gamepad_dev.rigt_Push

        pub.publish(gamepad_cmd)


        rate.sleep()

if __name__ == '__main__':
    try:
        gamepad_node()
    except rospy.ROSInterruptException:
        pass
