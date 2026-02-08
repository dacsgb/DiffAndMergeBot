# Micro-ROS Extra Packages

Include extra ROS2 packages here that need to be compiled with micro-ROS.
For example, extra interfaces like `ros2/example_interfaces`.

***NOTE:*** The micro-ROS library needs to be rebuilt when a new `extra_package` is added.
This can be done by deleting the entire `.pio/libdeps` folder, or by executing the custom `Clean Micro-ROS` or `Clean libmicroros` PlatformIO commands.