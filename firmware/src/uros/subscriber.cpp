#include "uros/subscriber.h"

using namespace uros;

Subscriber::Subscriber(
    rcl_node_t* node,
    const rosidl_message_type_support_t* typeSupport, 
    const char* topicName,
    rclc_executor_t* executor,
    void* msg,
    const rmw_qos_profile_t* qosProfile)
    :   subscriber_(),
        node_(node),
        typeSupport_(typeSupport),
        topicName_(topicName),
        executor_(executor),
        msg_(msg),
        MemberFunction(qosProfile) {
    
    // Check node, type support, and topic name are not nullptrs
    assert(node_);
    assert(typeSupport_);
    assert(topicName_);
}

Subscriber::~Subscriber() {
    RCLC_UNUSED(fini());
}

rcl_ret_t Subscriber::init() {
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

    rc = rclc_executor_add_subscription_with_context

    rc = rclc_executor_add_subscription(
        executor_,
        &subscriber_,
        msg_,
        cb_,
        ON_NEW_DATA);
    if (rc != RCL_RET_OK) {
        // TODO: Handle error
        return rc; // Exit function
    }
    return rc;
}

rcl_ret_t Subscriber::fini() {
    return rcl_subscription_fini(&subscriber_, node_);
}