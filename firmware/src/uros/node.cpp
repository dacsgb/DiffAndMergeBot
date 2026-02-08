#include "uros/node.h"

using namespace uros;

bool Node::begin() {
    // TODO: Set microros serial transport
    agentState = agent_state_t::WAITING_FOR_AGENT;

    allocator = rcl_get_default_allocator();

    return true;
}

void Node::handleConnectionState() {
    // Handle Micro-ROS tasking
    switch (agentState) {
        case WAITING_FOR_AGENT:
            digitalWrite(13, LOW);
            if (RMW_RET_OK == rmw_uros_ping_agent(100, 3)) {
                agentState = AGENT_AVAILABLE;
            }
            else {
            }
            break;

        case AGENT_AVAILABLE:
            if (createEntities()) { // Update system state
                agentState = AGENT_CONNECTED;
            }
            else { // If entities are not properly created, destroy them and abort
                agentState = WAITING_FOR_AGENT;
                destroyEntities();
                while(true) {} // Block further code execution. TODO: Do better
            };
            break;
        
        case AGENT_CONNECTED:
            if (RMW_RET_OK == rmw_uros_ping_agent(100, 3)) {
                // Execute pending tasks in the executor. This will handle all ROS communications.
                RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
                digitalWrite(13, HIGH);
            }
            else {
                agentState = AGENT_DISCONNECTED;
            }
            break;

        case AGENT_DISCONNECTED:
            agentState = WAITING_FOR_AGENT;
            destroyEntities();
            break;
            
        default:
            break;
    }
}

bool Node::createEntities() {
    bool _success = true;

    //create init_options
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

    // create node
    RCCHECK(rclc_node_init_default(&node, "micro_ros_platformio_node", "", &support));

    // create executor
    RCCHECK(rclc_executor_init(&executor, &support.context, functions.size(), &allocator));

    for (auto& func : functions) { // Iterate over all member functions and initialize
        if (!func) { // Null member found
            // TODO: Handle error with log message or similar
            _success = false;
            continue;
        }
        rcl_ret_t ret = func->init();
        if (ret != RCL_RET_OK) {
            Serial1.println("Function init failed!");
            return false;
        }
        Serial1.println("Function init succeeded");
    }

    return _success;
}

rcl_ret_t Node::destroyEntities() {
    rmw_context_t* rmw_context = rcl_context_get_rmw_context(&support.context);
    (void)rmw_uros_set_context_entity_destroy_session_timeout(rmw_context, 0);

    rcl_ret_t rc = RCL_RET_OK;
    rclc_executor_fini(&executor);
    rc = rcl_node_fini(&node);
    rclc_support_fini(&support);

    return rc;
}