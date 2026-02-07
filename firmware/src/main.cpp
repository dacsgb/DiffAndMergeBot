#include "uros/uros.h"

void setup() {
    Serial.begin(115200);
    Serial1.begin(115200);
    set_microros_serial_transports(Serial);

    pubMsg1.data = 0;

    ppub1.setTimerCallback(ppub1_callback);
    ppub2.setTimerCallback(ppub2_callback);

    controller.begin();

    controller.addFunction(&ppub1);
    // controller.addFunction(&ppub2);
}

void setup1() {

}

/**
 * Code executed on Core 0
 * Reserved for MicroROS since most USB/Serial transport is handled by Core 0
 */
void loop() {    
    controller.spin();
}

/**
 * Code executed on Core 1
 * Reserved for speed estimated on control algorithms since most of the existing IRQs are handled by Core 0
*/ 
void loop1() {

}