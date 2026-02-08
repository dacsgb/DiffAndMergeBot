#pragma once

#include <Arduino.h>

// The micro_ros_platformio library provides the functions to communicate with ROS2
#include <micro_ros_platformio.h>

// These are core ROS2 libraries for creating nodes, publishers, and executors
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rclc_parameter/rclc_parameter.h>
#include <micro_ros_utilities/type_utilities.h>
#include <micro_ros_utilities/string_utilities.h>
#include <rmw/qos_profiles.h>

// ROS2 message definitions
#include <std_msgs/msg/string.h>
#include <std_msgs/msg/int32.h>
#include <example_interfaces/srv/add_two_ints.h>

using std_msg_string_t = std_msgs__msg__String;
using std_msg_int32_t = std_msgs__msg__Int32;
using add_two_ints_request_t = example_interfaces__srv__AddTwoInts_Request;
using add_two_ints_response_t = example_interfaces__srv__AddTwoInts_Response;

// Define macros for checking function success
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){ while(1); }} // Blocking
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){ }} // Non-blocking
#define RCRETCHECK(fn) { rcl_ret_t temp_rc = fn; return temp_rc != RCL_RET_OK} // Returns RCL_RET_OK

// Define macros for executing a task every interval
#define EXECUTE_EVERY_N_MS(MS, X)  do { \
    static volatile int64_t init = -1; \
    if (init == -1) { init = uxr_millis();} \
    if (uxr_millis() - init > MS) { X; init = uxr_millis();} \
} while (0) \

# define TEST 1
