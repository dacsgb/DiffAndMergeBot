#include "uros/controller.h"

using namespace uros;

Controller* Controller::instance_ = nullptr;

bool Controller::begin() {
    // TODO: Set microros serial transport
    agentState = agent_state_t::WAITING_FOR_AGENT;

    allocator = rcl_get_default_allocator();

    //create init_options
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

    // create node
    RCCHECK(rclc_node_init_default(&node, "micro_ros_platformio_node", "", &support));

    instance_ = this;

    msg.data = 0;

    return true;
}

void Controller::handleConnectionState() {
    // Handle Micro-ROS tasking
    switch (agentState) {
        case WAITING_FOR_AGENT:
            digitalWrite(13, LOW);
            if (RMW_RET_OK == rmw_uros_ping_agent(100, 3)) {
                // log(LOG_INFO, "Agent found, establishing connection...");
                agentState = AGENT_AVAILABLE;
            }
            else {
                // log(LOG_WARN, "Failed to find agent. Retrying...");
            }
            break;

        case AGENT_AVAILABLE:
            if (createEntities()) { // Update system state
                // log(LOG_INFO, "Connected and ready!");
                agentState = AGENT_CONNECTED;
            }
            else { // If entities are not properly created, destroy them
                // log(LOG_WARN, "Connection failed. Retrying...");
                agentState = WAITING_FOR_AGENT;
                destroyEntities();
            };
            break;
        
        case AGENT_CONNECTED:
            if (RMW_RET_OK == rmw_uros_ping_agent(100, 3)) {
                // Execute pending tasks in the executor. This will handle all ROS communications.
                RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
                digitalWrite(13, HIGH);
            }
            else {
                // log(LOG_WARN, "Agent disconnected!");
                agentState = AGENT_DISCONNECTED;
            }
            break;

        case AGENT_DISCONNECTED:
            // log(LOG_INFO, "Waiting for agent...");
            agentState = WAITING_FOR_AGENT;
            destroyEntities();
            break;
            
        default:
            break;
    }
}

bool Controller::createEntities() {
    // create publisher
    RCCHECK(rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "micro_ros_platformio_node_publisher"));

    // create timer,
    const unsigned int timer_timeout = 1000;
    RCCHECK(rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(timer_timeout),
        timer_callback));

    // create executor
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
    RCCHECK(rclc_executor_add_timer(&executor, &timer));

    return true;
}

void Controller::destroyEntities() {
    rmw_context_t* rmw_context = rcl_context_get_rmw_context(&support.context);
    (void)rmw_uros_set_context_entity_destroy_session_timeout(rmw_context, 0);

    rcl_ret_t rc = RCL_RET_OK;
    rc = rcl_subscription_fini(&subscriber, &node);
    rc = rcl_publisher_fini(&publisher, &node);
    rclc_executor_fini(&executor);
    rc = rcl_node_fini(&node);
    rclc_support_fini(&support);
}

void Controller::_timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
    RCLC_UNUSED(last_call_time);
    if (timer != NULL) {
        RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL));
        msg.data = 1;
    }
}