#pragma once

#include <vector>

#include <rcl/logging.h>

#include "member_function.h"
#include "definitions.h"

namespace uros {

typedef enum {
    INITIALIZING,
    WAITING_FOR_AGENT,
    AGENT_AVAILABLE,
    AGENT_CONNECTED,
    AGENT_DISCONNECTED
} agent_state_t;

class Node {    
public:
    Node() { }
    ~Node() { destroyEntities(); }

    bool begin();
    void spin() { handleConnectionState(); }
    void handleConnectionState();
    bool createEntities();
    rcl_ret_t destroyEntities();

    void addFunction(MemberFunction* mf) { functions.push_back(std::unique_ptr<MemberFunction>(mf)); }

    rclc_executor_t* getExecutor() { return &executor; }
    rclc_support_t* getSupport() { return &support; }
    rcl_allocator_t* getAllocator() { return &allocator; }
    rcl_node_t* getNode() { return &node; }

protected:
    // ROS node configuration
    const char* kNodeName = "Micro-ROS Controller";
    const char* kNodeNamespace = "";
    const size_t kDomainID=0;
    const int kExecutorTimeout = 100;  // ms

    agent_state_t agentState;

    // ROS entities
    rclc_executor_t executor;
    rclc_support_t support;
    rcl_allocator_t allocator;
    rcl_node_t node; 

private:
    std::vector<std::unique_ptr<MemberFunction>> functions;
};

} // namespace uros