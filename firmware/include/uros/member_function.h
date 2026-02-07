#pragma once

#include "definitions.h"

namespace uros {

class MemberFunction {
public:
    virtual ~MemberFunction() { }

    virtual rcl_ret_t init();
    virtual rcl_ret_t fini();

protected:
    explicit MemberFunction(const rmw_qos_profile_t* qosProfile = &rmw_qos_profile_default) 
        :   qosProfile_(qosProfile) { }

    const rmw_qos_profile_t* qosProfile_;

private:

};
} // namespace uros