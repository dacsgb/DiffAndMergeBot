#include "definitions.h"
#include "member_function.h"

namespace uros {

template<typename RequestType, typename ResponseType>
class Service : public MemberFunction {
public:
    Service(
        rcl_node_t* node,
        const rosidl_service_type_support_t* typeSupport,
        const char* serviceName,
        rclc_executor_t* executor,
        const rmw_qos_profile_t* qosProfile=&rmw_qos_profile_default)
        :   service_(),
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

    ~Service() { RCLC_UNUSED(fini()); }

    void setServiceCallback(rclc_service_callback_t cb) { cb_ = cb; }

protected:
    rcl_node_t* node_;
    rcl_service_t service_;
    const char* serviceName_;
    const rosidl_service_type_support_t* typeSupport_;
    rclc_executor_t* executor_;
    RequestType requestMsg_;
    ResponseType responseMsg_;
    rclc_service_callback_t cb_;

    rcl_ret_t init() override {
        rcl_ret_t rc = rclc_service_init(
            &service_,
            node_,
            typeSupport_,
            serviceName_,
            qosProfile_);
        if (rc != RCL_RET_OK) {
            // TODO: Handle error
            return rc; // Exit function
        }

        rc = rclc_executor_add_service(
            executor_,
            &service_,
            &requestMsg_,
            &responseMsg_,
            cb_);
        if (rc != RCL_RET_OK) {
            // TODO: Handle error
            return rc; // Exit function
        }
        return rc;
    }

    rcl_ret_t fini() override { return rcl_service_fini(&service_, node_); }
private:
};
} // namespace uros