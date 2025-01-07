#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import rclpy
from rclpy.node import Node
from rclpy.parameter import Parameter
import serial
from std_msgs.msg import Float64, Int32, String
from gps_interfaces.msg import GPSmsg
import utm
import psutil

def DM_to_deg(latitude, lat_dir, longitude, lon_dir):
    lat_delim = latitude.index('.') - 2
    lon_delim = longitude.index('.') - 2

    lat_deg = (-1 if lat_dir == 'S' else 1) * (float(latitude[:lat_delim]) + float(latitude[lat_delim:])/60)
    lon_deg = (-1 if lon_dir == 'W' else 1)*(float(longitude[:lon_delim]) + float(longitude[lon_delim:])/60)
    return lat_deg, lon_deg

def time_converter(utc_time):
    sec = int(utc_time[:2])*3600 + int(utc_time[2:4])*60 + int(utc_time[4:6])
    res = utc_time[7:].ljust(9, '0')
    nano = int(res)
    return sec, nano

class GPSPuck(Node):
    def __init__(self):
        super().__init__('gps_puck')
        SENSOR_NAME = "GPS"
        self.declare_parameter('port', '/dev/pts/2')
        self.declare_parameter('baudrate', 4800)
        self.declare_parameter('sampling_rate', 4.0)
        
        serial_port = self.get_parameter('port').value
        serial_baud = self.get_parameter('baudrate').value
        sampling_rate = self.get_parameter('sampling_rate').value

        try:
            self.port = serial.Serial(serial_port, serial_baud, timeout = 3.0)
        except serial.serialutil.SerialException:
            self.get_logger().warn("Port is open")
        self.get_logger().debug("Using GPS sensor on port " + serial_port + " at " + str(serial_baud))

        self.gps_pub = self.create_publisher(GPSmsg, 'gps',10)
        self.get_logger().debug("Initialization complete")
        self.get_logger().info("Publishing GPS readings.")
        self.gps_msg = GPSmsg()
        self.gps_msg.header.frame_id = "GPS1_Frame"
        self.sleep_time = 1 / sampling_rate - 0.025
        self.timer = self.create_timer(self.sleep_time, self.timer_callback)


    def timer_callback(self):
        line = ''
        try:
            line = self.port.readline().decode('utf-8').strip()
        except Exception as e:
            self.get_logger().warn(str(e))
        if line == '':
            self.get_logger().warn("GPS: No data")
        else:
            self.get_logger().debug(line)
            data = line.split(',')
            if data[0] == '$GPGGA':
                if data[1].strip() == '':
                    seconds, nano = 0
                else: seconds, nano = time_converter(data[1].strip())
                self.gps_msg.header.stamp.sec = seconds
                self.gps_msg.header.stamp.nanosec = nano
                try:
                    latitude, longitude, altitude = 0, 0, 0
                    if data[2].strip() == '' or data[4].strip() == '' or data[9].strip() == '':
                        pass
                    else:
                        latitude, longitude = DM_to_deg(data[2].strip(),data[3].strip(),data[4].strip(),data[5].strip())
                        altitude = float(data[9].strip())
                    self.gps_msg.latitude = float(latitude)
                    self.gps_msg.longitude = float(longitude)
                    self.gps_msg.altitude = float(altitude)
                    easting, northing, zone, letter = utm.from_latlon(latitude, longitude)
                    self.gps_msg.utm_easting = float(easting)
                    self.gps_msg.utm_northing = float(northing)
                    self.gps_msg.zone = int(zone)
                    self.gps_msg.letter = letter
                    
                    self.get_logger().info("UTM Time: " + str(seconds) 
                        + ", Latitude: " + str(latitude) + ", Longitude: " + str(longitude) 
                        + ", Altitude: " + str(altitude) + ", Easting: " + str(easting) 
                        + ", Northing: " + str(northing) + ", Zone: " + str(zone) + ", Letter: " + str(letter))
                    
                except Exception as e:
                    self.get_logger().warn("Data exception: " + line + " " + str(e))
                    return
                
            self.gps_pub.publish(self.gps_msg)

def main(args=None):
    rclpy.init(args=args)
    gps_node = GPSPuck()
    try:
        rclpy.spin(gps_node)
    except KeyboardInterrupt:
        pass
    finally:
        gps_node.port.close()
        gps_node.destroy_node()
        rclpy.shutdown()
    

if __name__ == '__main__':
    main()