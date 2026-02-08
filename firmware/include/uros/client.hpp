#pragma once

#include "definitions.h"
#include "member_function.h"

namespace uros {

template<typename ResponseType>
class Client : public MemberFunction {
public:
    Client(
        rcl_node_t* node,
        const rosidl_service_type_support_t* typeSupport,
        const char* serviceName,
        rclc_executor_t* executor,
        const rmw_qos_profile_t* qosProfile=&rmw_qos_profile_default)
        :   client_(),
            node_(node),
            typeSupport_(typeSupport),
            serviceName_(serviceName),
            executor_(executor),
            MemberFunction(qosProfile) {
        
        // Check node, type support, and topic name are not nullptrs
        assert(node_);
        assert(typeSupport_);
        assert(serviceName_);
    }

    ~Client() { RCLC_UNUSED(fini()); }

    rcl_ret_t sendRequest(const void* req_msg, int64_t* seq_number) { return rcl_send_request(&client_, req_msg, seq_number); }

    void setClientCallback(rclc_client_callback_t cb) { cb_ = cb; }

protected:
    rcl_node_t* node_;
    rcl_client_t client_;
    const char* serviceName_;
    const rosidl_service_type_support_t* typeSupport_;
    rclc_executor_t* executor_;
    ResponseType responseMsg_;
    rclc_client_callback_t cb_;

    rcl_ret_t init() override {
        rcl_ret_t rc = rclc_client_init(
            &client_,
            node_,
            typeSupport_,
            serviceName_,
            qosProfile_);
        if (rc != RCL_RET_OK) {
            // TODO: Handle error
            return rc; // Exit function
        }

        rc = rclc_executor_add_client(
            executor_,
            &client_,
            &responseMsg_,
            cb_);
        if (rc != RCL_RET_OK) {
            // TODO: Handle error
            return rc; // Exit function
        }        
        return rc;
    }

    rcl_ret_t fini() override { return rcl_client_fini(&client_, node_); }

private:
};
} // namespace uros