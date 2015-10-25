#!/usr/bin/env python2
# -*- coding: utf-8 -*-

### H27 10 23

import rospy

#----- gamepad_node() -----#
def led_node():
    rospy.init_node('led_node', log_level=rospy.DEBUG, anonymous=True)
    rate = rospy.Rate(1)

    fd = open("/sys/class/gpio/export", "w")
    fd.write('2')
    fd.close()

    fd = open("/sys/class/gpio/gpio2/direction", "w")
    fd.write('out')
    fd.close()

    flag = 0

    while not rospy.is_shutdown():

        fd = open("/sys/class/gpio/gpio2/value", "w")
        if (flag == 0):
            fd.write('0')
            flag = 1
        else:
            fd.write('1')
            flag = 0
        fd.close()

        rate.sleep()

if __name__ == '__main__':
    try:
        led_node()
    except rospy.ROSInterruptException:
        pass
