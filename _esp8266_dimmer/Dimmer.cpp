#include "hw_timer.h"
#include <Arduino.h>
#include "Dimmer.hpp"

extern Dimmer dimmer;

void zcISR();
void dimmerISR();

void Dimmer::setup() {
  pinMode(zcPin, INPUT_PULLUP);
  pinMode(pwmPin, OUTPUT);
  digitalWrite(pwmPin, 0);
  attachInterrupt(zcPin, zcISR, RISING);    // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  hw_timer_init(NMI_SOURCE, 0);
  hw_timer_set_func( dimmerISR);
}

void Dimmer::serialLoop() {
    if (Serial.available()){
        int val = Serial.parseInt();
        Serial.println(val);
        if (val>0){
          targetBrightness =val;
        }
    }
}

void Dimmer::updateCurrentBrightness() {
    if (fade == 0) {
        currentBrightness = state ? targetBrightness : 0;
        return;
    }
    if (currentBrightness > targetBrightness || (state == 0 && currentBrightness > 0)) {
        currentBrightness -= fade;
    } else if (currentBrightness < targetBrightness && state == 1 && currentBrightness < 255) {
        currentBrightness += fade;
    }
}

void Dimmer::pwmWrite() {
    if (currentBrightness == 0) {
      digitalWrite(pwmPin, 0);
    } else {
      digitalWrite(pwmPin, 1);
    }
    
    zcState = 0;
}

void Dimmer::zcISRFunc() {
  if (zcState == 0) {
    zcState = 1;
  
    if (currentBrightness < 255 && currentBrightness > 0) {
      digitalWrite(pwmPin, 0);
      
      int dimDelay = 30 * (255 - currentBrightness) + 400;
      hw_timer_arm(dimDelay);
    }
  }
}

void dimmerISR() {
    dimmer.updateCurrentBrightness();
    dimmer.pwmWrite();
}

ICACHE_RAM_ATTR void zcISR() {
    dimmer.zcISRFunc();
}