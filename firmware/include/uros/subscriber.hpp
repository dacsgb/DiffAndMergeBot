#pragma once

#include "definitions.h"
#include "member_function.h"

namespace uros {

template<class MessageType>
class Subscriber : public MemberFunction {
public:
    Subscriber<MessageType>(
        rcl_node_t* node,
        const rosidl_message_type_support_t* typeSupport, 
        const char* topicName,
        rclc_executor_t* executor,
        const rmw_qos_profile_t* qosProfile=&rmw_qos_profile_default)
        :   subscriber_(),
            node_(node),
            typeSupport_(typeSupport),
            topicName_(topicName),
            executor_(executor),
            MemberFunction(qosProfile) {
    
        // Check node, type support, and topic name are not nullptrs
        assert(node_);
        assert(typeSupport_);
        assert(topicName_);
    }
    
    ~Subscriber() { RCLC_UNUSED(fini()); }
    
    void setSubscriptionCallback(rclc_subscription_callback_t cb) { cb_ = cb; }

protected:
    rcl_subscription_t subscriber_;
    rcl_node_t* node_;
    const rosidl_message_type_support_t* typeSupport_;
    const char* topicName_;
    rclc_executor_t* executor_;
    MessageType msg_;

    rcl_ret_t init() override {
        rcl_ret_t rc = rclc_subscription_init(
            &subscriber_,
            node_,
            typeSupport_,
            topicName_,
            qosProfile_
        );
        if (rc != RCL_RET_OK) {
            // TODO: Handle error
            return rc; // Exit function
        }

        rc = rclc_executor_add_subscription(
            executor_,
            &subscriber_,
            &msg_,
            cb_,
            ON_NEW_DATA);
        if (rc != RCL_RET_OK) {
            // TODO: Handle error
            return rc; // Exit function
        }
        return rc;
    }

    rcl_ret_t fini() override {
        return rcl_subscription_fini(&subscriber_, node_);
    };

private:
    rclc_subscription_callback_t cb_;
    void execute(const void* msg_in, void*) { }
};
} // namespace uros