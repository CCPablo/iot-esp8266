#include "DeviceData.hpp"
#include "MQTTProtocol.hpp"

extern Data data;

void tSensorCallback() {
  static int rr = 0;
  rr++;
  MqttWrapper::publish("outTopic", "scheduledTask");
  Serial.println(rr);
  Serial.println(data.units[1].name);
}