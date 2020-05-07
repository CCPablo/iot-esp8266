
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "MQTTProtocol.hpp"
#include "DeviceData.hpp"
#include "Topic.h"
#include "Scheduler.hpp"
#include <RBDdimmer.h>

extern Data data;
extern SchedulerWrapper scheduler;
extern dimmerLamp dimmer; 

void onGateWayConnected(StaticJsonDocument<100> doc) {
  const boolean connected = doc["connected"];
  if(connected) {
    MqttWrapper::publish(PUB_TOPIC[deviceConnect], data.getConfigurationSerialized());
    scheduler.enableAll();
  } else {
    scheduler.disableAll();
  }
}

void onUnitValueUpdate(StaticJsonDocument<100> doc) {
  if(doc["deviceId"] != DEVICE_ID) {
    return;
  }
  const int unitId = doc["unitId"];
  const long value = doc["value"];
  data.updateValue(unitId, value);
}
