#include "definitions.h"
#include "node.h"
#include "publisher.h"
#include "periodic_publisher.h"
#include "subscriber.hpp"

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
    if (timer != NULL) {
        ppub1.publish(&pubMsg1);
        pubMsg1.data++;
    }
}

std_msg_int32_t pubMsg2;
PeriodicPublisher ppub2(
    controller.getNode(),
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "micro_ros_publish_2",
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

Subscriber<std_msg_int32_t> sub1(
    controller.getNode(),
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "micro_ros_publish_3",
    controller.getExecutor()
);
void sub1_callback(const void* msgin) {
    const std_msg_int32_t* _msg = (const std_msg_int32_t*) msgin;
    Serial1.print("Received: "); Serial1.println(_msg->data);
}