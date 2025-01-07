from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():

    return LaunchDescription([
        DeclareLaunchArgument('port'),
        Node(
            package='imu_driver',
            executable='imu',
            name='IMU',
            output='screen',
            emulate_tty=True,
            parameters=[
                {'port':LaunchConfiguration('port')},
                {'baudrate':115200},
                {'sampling_rate':40.0}
            ],
            arguments=['--ros-args','--log-level','debug']
        )
    ])