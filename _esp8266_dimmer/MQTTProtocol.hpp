
#ifndef _PROTOCOL_HPP_
#define _PROTOCOL_HPP_

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DeviceData.hpp"

#include "GlobalDefinitions.h"
#include "Topic.h"


class MqttWrapper {
    private:
        static WiFiClient wifiClient;
        static PubSubClient mqttClient;

        void setupWiFi();
        void tryConnect();

        void subscribeAll() {
            for( int i= 0; i < SubTopics::SubTopicsSize; i++ ) {
                mqttClient.subscribe(SUB_TOPIC[i]);
            }
        }

        static void onMsgArrived(char* topic, byte* payload, unsigned int length);

    public:
        void setup();
        void loop();

        static void publish(const char* topic, const char* payload) {
            mqttClient.publish(topic, payload);
            Serial.print("Mqtt message sent in topic:");
            Serial.println(topic);
        }
};

#endif