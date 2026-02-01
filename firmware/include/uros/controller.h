#include "definitions.h"
#include <rcl/logging.h>

// TODO: Remove after testing
#include <Arduino.h>

typedef enum {
    INITIALIZING,
    WAITING_FOR_AGENT,
    AGENT_AVAILABLE,
    AGENT_CONNECTED,
    AGENT_DISCONNECTED
} agent_state_t;

typedef enum {
    LOG_SILENT,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_VERBOSE
} controller_log_level_t;

namespace uros {
class Controller {
public:
    Controller() { }
    ~Controller() { destroyEntities(); }

    bool begin();
    void handleConnectionState();
    bool createEntities();
    void destroyEntities();

    void setLogLevel(controller_log_level_t level) { currentLogLevel = level; }

    controller_log_level_t getLogLevel() { return currentLogLevel; }

protected:
    controller_log_level_t currentLogLevel = LOG_INFO;

    // ROS node configuration
    #ifdef CONTROLLER_NAME
    const char* nodeName = CONTROLLER_NAME;
    #else
    const char* nodeName = "micro_ros_controller_node";
    #endif
    #ifdef CONTROLLER_NAMESPACE
    const char* nodeNamespace = CONTROLLER_NAMESPACE;
    #else
    const char* nodeNamespace = "";
    #endif
    const int executorTimeout = 100;  // ms

    // ROS entities
    rclc_executor_t executor;
    rclc_support_t support;
    rcl_allocator_t allocator;
    rcl_node_t node; 
    
    // Micro-ROS configuration
    IPAddress agentIP;
    uint16_t agentPort;
    agent_state_t agentState;
    #ifdef ROS_DOMAIN_ID
    size_t domainID = ROS_DOMAIN_ID;
    #else
    size_t domainID=0;
    #endif

    void log(controller_log_level_t level, const char* message) {
        // TODO
    }

    void logf(controller_log_level_t level, const char* format, ...) {
        // TODO
    }

private:
    // ROS node configuration
    const char* publisherTopic="micro_ros_response";
    const char* subscriberTopic="micro_ros_name";

    // ROS entities
    rcl_publisher_t publisher;
    rcl_subscription_t subscriber;
    rcl_timer_t timer;

    // Message buffers
    std_msg_string_t received_msg;
    std_msg_string_t response_msg;
    std_msgs__msg__Int32 msg;
    char received_buffer[50];
    char response_buffer[100];

    void _subscriptionCallback(const void* msgin);
    void _publishResponse();
    void _timer_callback(rcl_timer_t*, int64_t);
    
    static Controller* instance_;
    static void timer_callback(rcl_timer_t* timer, int64_t last_call_time) { instance_->_timer_callback(timer, last_call_time); }

    // static void _subscriptionCallbackStatic(const void* msgin) { instance_->_subscriptionCallback(msgin); }
};

} // namespace uros