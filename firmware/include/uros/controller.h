#include "definitions.h"

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
    Controller();
    ~Controller() { destroyEntities(); }

    bool begin();

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

    virtual void handleConnectionState();
    virtual bool createEntities() { return true; }
    virtual void destroyEntities() {}

private:
    static Controller* instance_;
    TaskHandle_t microRosTask;

    // ROS node configuration
    const char* publisherTopic="micro_ros_response";
    const char* subscriberTopic="micro_ros_name";

    // ROS entities
    rcl_publisher_t publisher;
    rcl_subscription_t subscriber;
    rcl_timer_t timer;

    // Message buffers
    std_msgs__msg__String received_msg;
    std_msgs__msg__String response_msg;
    char received_buffer[50];
    char response_buffer[100];

    void _subscriptionCallback(const void* msgin);
    void _publishResponse();

    static void _subscriptionCallbackStatic(const void* msgin) { instance_->_subscriptionCallback(msgin); }

    static void microRosTaskCallbackStatic(void* pvParameters) {
        for (;;) {
            instance_->handleConnectionState();
            vTaskDelay(pdMS_TO_TICKS(10));  // Yield to scheduler every 10 ms
        }
    }
};
} // namespace uros

extern Controller controllerUros;