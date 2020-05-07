
#ifndef _CONFIG_DATA_HPP_
#define _CONFIG_DATA_HPP_

#include <ArduinoJson.h>
#include <Arduino.h>
#include "Scheduler.hpp"
#include "DeviceModel.hpp"

struct Data {
    Device device;
    std::vector<Unit> units;

	Data(std::vector<Unit> units) : units(units){}
 
    const char* getConfigurationSerialized();

    Unit getUnit(int unitId);
    void updateValue(const int unitId, const long value);
    void setup();
};

#endif