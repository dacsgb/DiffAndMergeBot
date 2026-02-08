#include "definitions.h"
#include "node.h"
#include "publisher.h"
#include "periodic_publisher.h"
#include "subscriber.hpp"
#include "service.hpp"

using namespace uros;

Node controller;

// Periodic publisher 1
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

// Periodic Publisher 2
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

// Subsciber
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

// Service
Service<add_two_ints_request_t, add_two_ints_response_t> service(
    controller.getNode(),
    ROSIDL_GET_SRV_TYPE_SUPPORT(example_interfaces, srv, AddTwoInts),
    "add_two_ints",
    controller.getExecutor()
);
void service_callback(const void* request_msg, void* response_msg) {
    // Cast messages to expected types
    add_two_ints_request_t* req_in = (add_two_ints_request_t *) request_msg;
    add_two_ints_response_t* res_in = (add_two_ints_response_t *) response_msg;

    // Handle request message and set the response message values
    Serial1.print("Client requested sum of: ");
    Serial1.print((int) req_in->a); 
    Serial1.print(" and ");
    Serial1.print((int) req_in->b);
    Serial1.println(".");
    res_in->sum = req_in->a + req_in->b;
}