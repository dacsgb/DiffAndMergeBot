from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import xacro

def generate_launch_description():
    pkg_path = get_package_share_directory('robot_description')

    # urdf_path = os.path.join(pkg_path, 'urdf', 'robot.urdf')
    xacro_path = os.path.join(pkg_path, 'urdf', 'robot.urdf.xacro')

    # robot_description = open(urdf_path).read()
    robot_description = xacro.process_file(xacro_path).toxml()

    nodes = []


    nodes.append(Node(package='robot_state_publisher',
                        executable='robot_state_publisher',
                        output='screen',
                        parameters=[{'robot_description': robot_description}])
    )

    nodes.append(Node(package='joint_state_publisher',
                        executable='joint_state_publisher',
                        output='screen')
    )

    nodes.append(Node(package='rviz2',
                        executable='rviz2',
                        output='screen')
    )

    return LaunchDescription([*nodes])