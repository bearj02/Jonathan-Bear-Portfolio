from pathlib import Path
from rosbags.highlevel import AnyReader
from rosbags.typesys import Stores, get_typestore, get_types_from_idl, get_types_from_msg

bagpath = Path(r"bag_files/walking_data.bag")

msg_text = Path('gps_interfaces/msg/GPSmsg.msg').read_text()

# Create a type store to use if the bag has no message definitions.
typestore = get_typestore(Stores.ROS2_HUMBLE)

add_types = {}
add_types.update(get_types_from_msg(msg_text, 'gps_interfaces/msg/GPSmsg'))

typestore.register(add_types)
print("Time,Latitude,Longitude,Altitude,Easting,Northing,Zone,Letter")
# Create reader instance and open for reading.
with AnyReader([bagpath], default_typestore=typestore) as reader:
    connections = [x for x in reader.connections if x.topic == '/gps']
    for connection, timestamp, rawdata in reader.messages(connections=connections):
         msg = reader.deserialize(rawdata, connection.msgtype)
         print("" + str(msg.header.stamp.sec) + "," + str(msg.latitude.data) + "," + str(msg.longitude.data) + "," + str(msg.altitude.data) + "," + str(msg.utm_easting.data) + "," + str(msg.utm_northing.data) + "," + str(msg.zone.data) + "," + msg.letter.data)