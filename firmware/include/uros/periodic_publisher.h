#pragma once

#include "publisher.h"

namespace uros {

class PeriodicPublisher : public Publisher {
public:
    PeriodicPublisher(
        rcl_node_t* node,
        const rosidl_message_type_support_t* typeSupport, 
        const char* topicName,
        rclc_executor_t* executor,
        rclc_support_t* support,
        unsigned int period=1000,
        const rmw_qos_profile_t* qosProfile=&rmw_qos_profile_default);
    ~PeriodicPublisher();

    void start() { isRunning_ = true; }
    void stop() { isRunning_ = false; }

    void setTimerCallback(rcl_timer_callback_t cb) { cb_ = cb; }

protected:
    rclc_executor_t* executor_; 
    rclc_support_t* support_;
    rcl_timer_t timer_;

    rcl_ret_t init() override;
    rcl_ret_t fini() override;

private:
    unsigned int period_;
    bool isRunning_;
    rcl_timer_callback_t cb_;
};
} // namespace uros