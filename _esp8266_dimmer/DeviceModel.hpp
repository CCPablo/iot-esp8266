
#ifndef _DEVICE_MODEL_HPP_
#define _DEVICE_MODEL_HPP_

#define _TASK_SLEEP_ON_IDLE_RUN

#include "GlobalDefinitions.h"
#include <WString.h>
#include <TaskSchedulerDeclarations.h>

enum StatusType {
  UNIT_ON,
  UNIT_OFF
};

enum UnitType {
  SENSOR,
  RELAY,
  DIMMER
};

struct Device {
  const uint8_t id {DEVICE_ID};
  String name {NAME_OF_DEVICE};
  String description {DESCRIPTION_OF_DEVICE};
  StatusType status {STATUS_OF_DEVICE};
};

struct Unit {
  const uint8_t deviceId {DEVICE_ID};
  const uint8_t id;
  String name;
  String description {""};
  UnitType type;
  const uint8_t pin;
  long value {-1};
  int measureRate {-1};
  Task* task {nullptr};

  Unit(uint8_t id, String name, UnitType type, const uint8_t pin) : 
    id(id), 
    name(name), 
    type(type),
    pin(pin) {}

  Unit(uint8_t id, String name, UnitType type, const uint8_t pin, long value) : 
    id(id), 
    name(name), 
    type(type),
    pin(pin),
    value(value) {}

  Unit(uint8_t id, String name, String description, UnitType type, const uint8_t pin, long value, int measureRate, Task* task) :
    id(id), 
    name(name), 
    description(description), 
    type(type), 
    pin(pin),
    value(value), 
    measureRate(measureRate), 
    task(task) {}
};

#endif