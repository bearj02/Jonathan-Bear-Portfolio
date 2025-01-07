from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():

    return LaunchDescription([
        DeclareLaunchArgument('imu_port'),
        DeclareLaunchArgument('gps_port'),
        Node(
            package='gps_driver',
            executable='gps_puck',
            name='GPSPuck',
            output='screen',
            emulate_tty=True,
            parameters=[
                {'port':LaunchConfiguration('gps_port')},
                {'baudrate':4800},
                {'sampling_rate':10.0}
            ],
            arguments=['--ros-args','--log-level','debug']
        ),
        Node(
            package='imu_driver',
            executable='imu',
            name='IMU',
            output='screen',
            emulate_tty=True,
            parameters=[
                {'port':LaunchConfiguration('imu_port')},
                {'baudrate':115200}
            ],
            arguments=['--ros-args','--log-level','debug']
        )
    ])