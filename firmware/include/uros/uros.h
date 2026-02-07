#include "definitions.h"
#include "node.h"
#include "publisher.h"
#include "periodic_publisher.h"

using namespace uros;

Node controller;

std_msg_int32_t pubMsg1;
PeriodicPublisher ppub1(
    controller.getNode(),
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "micro_ros_publish_1",
    controller.getExecutor(),
    controller.getSupport()
);
void ppub1_callback(rcl_timer_t* timer, int64_t last_call_time) {
    RCLC_UNUSED(last_call_time);
    Serial1.print("pubMsg1.data: "); Serial1.println(pubMsg1.data);
    if (timer != NULL) {
        Serial1.println(ppub1.publish(&pubMsg1));
        pubMsg1.data++;
    }
    Serial1.print("pubMsg1.data++: "); Serial1.println(pubMsg1.data);
}

std_msg_int32_t pubMsg2;
PeriodicPublisher ppub2(
    controller.getNode(),
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "Micro-ROS Publish Topic 2",
    controller.getExecutor(),
    controller.getSupport()
);
void ppub2_callback(rcl_timer_t* timer, int64_t last_call_time) {
    RCLC_UNUSED(last_call_time);
    if (timer != NULL) {
        RCSOFTCHECK(ppub2.publish(&pubMsg2));
        pubMsg2.data++;
    }
}