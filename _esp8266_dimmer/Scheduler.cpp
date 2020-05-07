#include "Scheduler.hpp"

extern Data data;
extern SchedulerWrapper scheduler;

void SchedulerWrapper::setup() {
  this->scheduler.init();
  for(Unit unit : data.units) {
    if(unit.task != nullptr) {
      scheduler.addTask(*unit.task);
      unit.task->enable();
      Serial.print("Added task for unit: ");Serial.println(unit.name);
    } else {
      Serial.print("No task for unit: ");Serial.println(unit.name);
    }
  }
}

void SchedulerWrapper::loop() {
  this->scheduler.execute();
}

void SchedulerWrapper::setInterval(int unitId, int interval) {
  for(Unit unit : data.units) {
    if(unit.id == unitId && unit.task != nullptr) {
      unit.task->setInterval(interval);
      break;
    }
  }
}

void SchedulerWrapper::disableAll() {
  scheduler.disableAll();
}

void SchedulerWrapper::enableAll() {
  scheduler.enableAll();
}