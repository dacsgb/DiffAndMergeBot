#include <Arduino.h>

#include "uros/controller.h"

uros::Controller controller;

void setup() {
    Serial.begin(115200);
    set_microros_serial_transports(Serial);
    controller.begin();
    pinMode(13, OUTPUT);
}

void setup1() {

}

/**
 * Code executed on Core 0
 * Reserved for MicroROS since most USB/Serial transport is handled by Core 0
 */
void loop() {    
    controller.handleConnectionState();
}

/**
 * Code executed on Core 1
 * Reserved for speed estimated on control algorithms since most of the existing IRQs are handled by Core 0
*/ 
void loop1() {

}