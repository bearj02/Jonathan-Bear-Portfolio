#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import rclpy
from rclpy.node import Node
from rclpy.parameter import Parameter
import serial
from imu_interfaces.msg import IMUmsg
import time
import math

def quaternion(yaw, pitch, roll):
    cy, sy = math.cos(math.radians(yaw)/2), math.sin(math.radians(yaw)/2)
    cp, sp = math.cos(math.radians(pitch)/2), math.sin(math.radians(pitch)/2)
    cr, sr = math.cos(math.radians(roll)/2), math.sin(math.radians(roll)/2)
    
    w = cr*cp*cy + sr*sp*sy
    x = sr*cp*cy - cr*sp*sy
    y = cr*sp*cy + sr*cp*sy
    z = cr*cp*sy - sr*sp*cy
    
    q = [x,y,z,w]

    return q

class IMU(Node):
    def __init__(self):
        super().__init__('imu')
        SENSOR_NAME = "IMU"
        self.declare_parameter('port', '/dev/pts/2')
        self.declare_parameter('baudrate', 115200)
        self.declare_parameter('sampling_rate', 40.0)
        
        serial_port = self.get_parameter('port').value
        serial_baud = self.get_parameter('baudrate').value
        sampling_rate = 40

        try:
            self.port = serial.Serial(serial_port, serial_baud, timeout = 3.0)
        except serial.serialutil.SerialException:
            self.get_logger().warn("Port is open")
        self.get_logger().debug("Using IMU sensor on port " + serial_port + " at " + str(serial_baud))

        self.gps_pub = self.create_publisher(IMUmsg, 'imu',10)
        self.get_logger().debug("Initialization complete")
        self.get_logger().info("Publishing IMU readings.")

        self.imu_msg = IMUmsg()
        self.imu_msg.header.frame_id = "IMU1_Frame"
        self.imu_msg.imu.header.frame_id = "IMU1_Frame"
        self.imu_msg.mag_field.header.frame_id = "IMU1_Frame"
        self.sleep_time = 1 / sampling_rate
        self.timer = self.create_timer(self.sleep_time, self.timer_callback)

    def timer_callback(self):
        line = ''
        try:
            line = self.port.readline().decode('utf-8').strip()
        except Exception as e:
            self.get_logger().warn(str(e))
        if line == '':
            self.get_logger().warn("IMU: No data")
        else:
            self.get_logger().debug(line)
            data = line.split(',')
            if data[0] == '$VNYMR':
                self.imu_msg.raw = line
                self.imu_msg.header.stamp = self.get_clock().now().to_msg()
                self.imu_msg.imu.header.stamp = self.get_clock().now().to_msg()
                self.imu_msg.mag_field.header.stamp = self.get_clock().now().to_msg()
                try:
                    yaw, pitch, roll = float(data[1]), float(data[2]), float(data[3])
                    magX, magY, magZ = (10**-4)*float(data[4]), (10**-4)*float(data[5]), (10**-4)*float(data[6])
                    accelX, accelY, accelZ = float(data[7]), float(data[8]), float(data[9])
                    gyroX, gyroY, gyroZ = float(data[10]), float(data[11]), float(data[12][:-3])

                    q = quaternion(yaw, pitch, roll)
                    self.imu_msg.imu.orientation.x = q[0]
                    self.imu_msg.imu.orientation.y = q[1]
                    self.imu_msg.imu.orientation.z = q[2]
                    self.imu_msg.imu.orientation.w = q[3]
                    self.imu_msg.imu.linear_acceleration.x = float(accelX)
                    self.imu_msg.imu.linear_acceleration.y = float(accelY)
                    self.imu_msg.imu.linear_acceleration.z = float(accelZ)
                    self.imu_msg.imu.angular_velocity.x = float(gyroX)
                    self.imu_msg.imu.angular_velocity.y = float(gyroY)
                    self.imu_msg.imu.angular_velocity.z = float(gyroZ)
                    self.imu_msg.mag_field.magnetic_field.x = float(magX)
                    self.imu_msg.mag_field.magnetic_field.y = float(magY)
                    self.imu_msg.mag_field.magnetic_field.z = float(magZ)
                    
                except Exception as e:
                    self.get_logger().warn("Data exception: " + line + " " + str(e))
                    return
                
            self.gps_pub.publish(self.imu_msg)

def main(args=None):
    rclpy.init(args=args)
    imu_node = IMU()
    try:
        rclpy.spin(imu_node)
    except KeyboardInterrupt:
        pass
    finally:
        imu_node.port.close()
        imu_node.destroy_node()
        rclpy.shutdown()
    

if __name__ == '__main__':
    main()