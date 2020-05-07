#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "DeviceData.hpp"
#include "MQTTProtocol.hpp"
#include "Scheduler.hpp"

#include "Topic.h"
#include <RBDdimmer.h>

#include "Dimmer.hpp"

//dimmerLamp dimmer(DIMMER_PIN, DIMMER_ZERO_CROSS); 
SchedulerWrapper scheduler;
MqttWrapper mqtt;

Dimmer dimmer(DIMMER_PIN, DIMMER_ZERO_CROSS);

extern Data data;

void setup() {
  Serial.begin(115200);
  mqtt.setup();
  scheduler.setup();
  data.setup();
  dimmer.setup();
  //dimmer.begin(NORMAL_MODE, OFF);
}

void loop() {
  mqtt.loop();
  scheduler.loop();
  dimmer.serialLoop();

  //dimmer.setPower(100);
}