import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node

import xacro


def generate_launch_description():
    pkg_path = get_package_share_directory('robot_description')

    # Paths
    xacro_file = os.path.join(pkg_path, 'urdf', 'robot.urdf.xacro')
    # rviz_file = os.path.join(pkg_path, 'rviz', 'tank_bot.rviz')

    # Process xacro
    robot_description_xml = xacro.process_file(xacro_file).toxml()

    # Nodes
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description_xml}]
    )

    joint_state_publisher_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        output='screen'
    )

    # Gazebo
    gazebo_server = ExecuteProcess(cmd=['gz sim', '--verbose', '-s', 'libgazebo_ros_factory.so'],
                                    output='screen'
                    )

    # RViz (optional)
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen'
        # arguments=['-d', rviz_file]
    )

    return LaunchDescription([
        gazebo_server,
        robot_state_publisher_node,
        joint_state_publisher_node,
        spawn_entity,
        rviz_node
    ])
