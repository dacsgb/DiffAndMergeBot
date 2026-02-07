#include "uros/publisher.h"

using namespace uros;

Publisher::Publisher(
    rcl_node_t* node, 
    const rosidl_message_type_support_t* typeSupport, 
    const char* topicName,
    const rmw_qos_profile_t* qosProfile)
    :   publisher_(),
        node_(node),
        typeSupport_(typeSupport),
        topicName_(topicName),
        MemberFunction(qosProfile) {
    
    // Check node, type support, and topic name are not nullptrs
    assert(node_);
    assert(typeSupport_);
    assert(topicName_);
}

Publisher::~Publisher() {
    RCLC_UNUSED(fini());
}

rcl_ret_t Publisher::init() {
    rcl_ret_t rc = rclc_publisher_init(
        &publisher_,
        node_,
        typeSupport_,
        topicName_,
        qosProfile_
    );
    return rc;
}

rcl_ret_t Publisher::fini() {
    return rcl_publisher_fini(&publisher_, node_);
}

