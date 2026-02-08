#pragma once

#include "definitions.h"
#include "member_function.h"

namespace uros {

class Publisher : public MemberFunction {
public:
    Publisher(
        rcl_node_t* node, 
        const rosidl_message_type_support_t* typeSupport, 
        const char* topicName, 
        const rmw_qos_profile_t* qosProfile=&rmw_qos_profile_default);

    ~Publisher();

    rcl_ret_t publish(void* msg) { return rcl_publish(&publisher_, msg, NULL ); }

protected:
    rcl_publisher_t publisher_;
    rcl_node_t* node_;
    const rosidl_message_type_support_t* typeSupport_;
    const char* topicName_;

    rcl_ret_t init() override;
    rcl_ret_t fini() override;

private:
    
};
} // namespace uros