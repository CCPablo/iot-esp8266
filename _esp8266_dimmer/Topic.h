
#ifndef _TOPIC_H_
#define _TOPIC_H_

extern void onGateWayConnected(StaticJsonDocument<100> doc);

extern void onUnitValueUpdate(StaticJsonDocument<100> doc);

/*
name: identificator of topic
topic: string value for topic
callback: callback function when topic arrive
*/
#define SUB_TOPIC_TABLE                                         \
  X(gatewayConnect, "/gateway/connect",  onGateWayConnected)    \
  X(deviceConfig, "/device/config",  onUnitValueUpdate)         \
  X(deviceUnitValue, "/device/unit/value",  onUnitValueUpdate)  \

#define PUB_TOPICS_TABLE                      \
  X(deviceConnect, "/device/connect")         \

enum SubTopics
{
  #define X(name, topic, callback) name,
    SUB_TOPIC_TABLE
  #undef X
  SubTopicsSize
};

enum PubTopicss
{
  #define X(name, topic) name,
    PUB_TOPICS_TABLE
  #undef X
  PubTopicsSize
};

static const char* SUB_TOPIC[SubTopicsSize] = 
{
  #define X(name, topic, callback) [name] = topic,
    SUB_TOPIC_TABLE
  #undef X
};

static const char* PUB_TOPIC[PubTopicsSize] = 
{
  #define X(name, topic) [name] = topic,
    PUB_TOPICS_TABLE
  #undef X
};

static void(*topicCallback[SubTopicsSize])(StaticJsonDocument<100>)= 
{
  #define X(name, topic, callback) [name] = callback,
    SUB_TOPIC_TABLE
  #undef X
};

#endif