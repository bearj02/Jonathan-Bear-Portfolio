from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():

    return LaunchDescription([
        DeclareLaunchArgument('port'),
        Node(
            package='gps_driver',
            executable='gps_puck',
            name='GPSPuck',
            output='screen',
            emulate_tty=True,
            parameters=[
                {'port':LaunchConfiguration('port')},
                {'baudrate':4800},
                {'sampling_rate':10.0}
            ],
            arguments=['--ros-args','--log-level','debug']
        )
    ])