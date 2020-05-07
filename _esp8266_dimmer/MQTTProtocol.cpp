#include "MQTTProtocol.hpp"

extern Data data;

WiFiClient MqttWrapper::wifiClient;
PubSubClient MqttWrapper::mqttClient(wifiClient);

void MqttWrapper::setup() {
  setupWiFi();
  mqttClient.setServer(MQTT_BROKER, 1883);
  mqttClient.setCallback(onMsgArrived);
}

void MqttWrapper::loop() {
  while (!mqttClient.connected()) {
    tryConnect();
  }
  mqttClient.loop();
}

void MqttWrapper::onMsgArrived(char* topic, byte* payload, unsigned int length) {
  for(int i = 0; i < SubTopicsSize; i++) {
    if(strcmp(SUB_TOPIC[i], topic) == 0) {
      StaticJsonDocument<100> doc;
      deserializeJson(doc, payload, length);
      topicCallback[i](doc);
    }
  }
}

void MqttWrapper::setupWiFi() {
  delay(10);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);Serial.print(".");
  }
  Serial.println();
}

void MqttWrapper::tryConnect() {
  if (mqttClient.connect(MQTT_CLIENT_ID)) {
    publish(PUB_TOPIC[deviceConnect], data.getConfigurationSerialized());
    subscribeAll();
  } else {
    delay(500);Serial.print(".");
  }
}