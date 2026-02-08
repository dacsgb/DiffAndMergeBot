# Colcon Meta

This directory should contain colcon meta files for modifying the parameters and behaviors of the Micro-ROS build environment.

***NOTE:*** The micro-ROS library needs to be rebuilt when `colcon.meta` file is modified.
This can be done by deleting the entire `.pio/libdeps` folder, or by executing the custom `Clean Micro-ROS` or `Clean libmicroros` PlatformIO commands.

#### Library configuration (from: [micro-ROS:jazzy README](https://github.com/micro-ROS/rmw_microxrcedds/blob/jazzy/README.md?plain=1))

This RMW implementation can be configured via CMake arguments, its usual to configure them via `colcon.meta` file in a micro-ROS enviroment.

Most of these configuration are related to memory management because this RMW implementation tries to fully rely on static memory assignations. This leads to an upper bound in memory assignations, which is configured by the user before the build process.
By default, the package sets the values for all memory bounded. The upper bound is configurable by a file that sets the values during the build process.

More details about RMW Micro XRCE-DDS can be found [here](https://micro.ros.org/docs/tutorials/advanced/microxrcedds_rmw_configuration/).
All the configurable parameters are:

| Name                                      | Description                                                                                                                                                                                    | Default |
| ----------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------- |
| RMW_UXRCE_TRANSPORT                       | Sets Micro XRCE-DDS transport to use. (udp, serial, custom)                                                                                                                                    | udp     |
| RMW_UXRCE_IPV                             | Sets Micro XRCE-DDS IP version to use. (ipv4, ipv6)                                                                                                                                            | ipv4    |
| RMW_UXRCE_CREATION_MODE                   | Sets creation mode in Micro XRCE-DDS. (bin, refs)                                                                                                                                              | bin     |
| RMW_UXRCE_MAX_HISTORY                     | This value sets the number of history slots available for RMW subscriptions, </br> requests and replies                                                                                        | 8       |
| RMW_UXRCE_MAX_SESSIONS                    | This value sets the maximum number of Micro XRCE-DDS sessions.                                                                                                                                 | 1       |
| RMW_UXRCE_MAX_NODES                       | This value sets the maximum number of nodes.                                                                                                                                                   | 4       |
| RMW_UXRCE_MAX_PUBLISHERS                  | This value sets the maximum number of topic publishers for an application.                                                                                                                           | 4       |
| RMW_UXRCE_MAX_SUBSCRIPTIONS               | This value sets the maximum number of topic subscriptions for an application.                                                                                                                        | 4       |
| RMW_UXRCE_MAX_SERVICES                    | This value sets the maximum number of service servers for an application.                                                                                                                             | 4       |
| RMW_UXRCE_MAX_CLIENTS                     | This value sets the maximum number of service clients for an application.                                                                                                                              | 4       |
| RMW_UXRCE_MAX_TOPICS                      | This value sets the maximum number of topics for an application. </br> If set to -1 RMW_UXRCE_MAX_TOPICS = RMW_UXRCE_MAX_PUBLISHERS + </br> RMW_UXRCE_MAX_SUBSCRIPTIONS + RMW_UXRCE_MAX_NODES. | -1      |
| RMW_UXRCE_MAX_WAIT_SETS                   | This value sets the maximum number of wait sets for an application.                                                                                                                            | 4       |
| RMW_UXRCE_MAX_GUARD_CONDITION             | This value sets the maximum number of guard conditions for an application.                                                                                                                     | 4       |
| RMW_UXRCE_NODE_NAME_MAX_LENGTH            | This value sets the maximum number of characters for a node name.                                                                                                                              | 60      |
| RMW_UXRCE_TOPIC_NAME_MAX_LENGTH           | This value sets the maximum number of characters for a topic name.                                                                                                                             | 60      |
| RMW_UXRCE_TYPE_NAME_MAX_LENGTH            | This value sets the maximum number of characters for a type name.                                                                                                                              | 100     |
| RMW_UXRCE_REF_BUFFER_LENGTH               | This value sets the maximum number of characters for a reference buffer.                                                                                                                       | 100     |
| RMW_UXRCE_ENTITY_CREATION_DESTROY_TIMEOUT | This value sets the default maximum time to wait for an XRCE entity creation </br> and destroy in milliseconds. If set to 0 best effort is used.                                               | 1000    |
| RMW_UXRCE_ENTITY_CREATION_TIMEOUT         | This value sets the maximum time to wait for an XRCE entity creation </br> in milliseconds. If set to 0 best effort is used.                                                                   | 1000    |
| RMW_UXRCE_ENTITY_DESTROY_TIMEOUT          | This value sets the maximum time to wait for an XRCE entity destroy </br> in milliseconds. If set to 0 best effort is used.                                                                    | 1000    |
| RMW_UXRCE_PUBLISH_RELIABLE_TIMEOUT        | This value sets the default time to wait for a publication in a </br> reliable mode in milliseconds.                                                                                           | 1000    |
| RMW_UXRCE_STREAM_HISTORY                  | This value sets the number of MTUs to buffer, both input and output. Must be a power-of-two.                                                                                                   | 4       |
| RMW_UXRCE_STREAM_HISTORY_INPUT            | This value sets the number of MTUs to input buffer. </br> It will be ignored if RMW_UXRCE_STREAM_HISTORY_OUTPUT is blank. If set, must be a power-of-two.                                      | -       |
| RMW_UXRCE_STREAM_HISTORY_OUTPUT           | This value sets the number of MTUs to output buffer. </br> It will be ignored if RMW_UXRCE_STREAM_HISTORY_INPUT is blank. If set, must be a power-of-two.                                      | -       |
| RMW_UXRCE_GRAPH                           | Allows to perform graph-related operations to the user                                                                                                                                         | OFF     |
| RMW_UXRCE_ALLOW_DYNAMIC_ALLOCATIONS       | Enables increasing static pools with dynamic allocation when needed.                                                                                                                           | OFF     |
