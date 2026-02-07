#include "uros/periodic_publisher.h"

using namespace uros;

PeriodicPublisher::PeriodicPublisher(
    rcl_node_t* node, 
    const rosidl_message_type_support_t* typeSupport, 
    const char* topicName,
    rclc_executor_t* executor,
    rclc_support_t* support,
    unsigned int period,
    const rmw_qos_profile_t* qosProfile)
    :   Publisher(node, typeSupport, topicName, qosProfile),
        executor_(executor),
        support_(support),
        period_(period),
        isRunning_(false) {
}

PeriodicPublisher::~PeriodicPublisher() {
    // Implicitly calls the superclass deconstructor (Publisher::~Publisher()) as well
    RCSOFTCHECK(rcl_timer_fini(&timer_));
}

rcl_ret_t PeriodicPublisher::init() {
    rcl_ret_t ret = Publisher::init();
    if (ret != RCL_RET_OK) {
        // TODO: Handle error
        return ret; // Exit function
    }

    ret = rclc_timer_init_default2(
        &timer_,
        support_,
        RCL_MS_TO_NS(period_),
        cb_,
        true
    );
    if (ret != RCL_RET_OK) {
        // TODO: Handle error
        return ret; // Exit function
    }

    ret = rclc_executor_add_timer(executor_, &timer_);
    if (ret != RCL_RET_OK) {
        // TODO: Handle error
        return ret; // Exit function
    }

    return RCL_RET_OK;
}

rcl_ret_t PeriodicPublisher::fini() {
    RCSOFTCHECK(rcl_timer_fini(&timer_));
    Publisher::fini();
}