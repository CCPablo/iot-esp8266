#include "DeviceData.hpp"
#include "Dimmer.hpp"

extern Dimmer dimmer;

extern void tSensorCallback();

Task newTask(S_TEMPERATURE_MEASURE_RATE_MS, TASK_FOREVER, tSensorCallback);

Data data({
    Unit(DIMMER_ID, DIMMER_NAME, DIMMER_TYPE, DIMMER_PIN, 1023),       
    Unit(S_TEMPERATURE_ID, S_TEMPERATURE_NAME, S_TEMPERATURE_DESCRIPTION, 
    S_TEMPERATURE_TYPE, 0, 1023, S_TEMPERATURE_MEASURE_RATE_MS, &newTask)});

const char* Data::getConfigurationSerialized() {
    char buffer[700];
    StaticJsonDocument<700> doc;
    doc["id"] = device.id;
    doc["name"] = device.name;
    doc["description"] = device.description;
    doc["status"] = device.status;
    
    JsonArray arr = doc.createNestedArray("units");
    for(Unit unit : units) {
        JsonObject unitJson = arr.createNestedObject();
        unitJson["deviceId"] = device.id;
        unitJson["id"] = unit.id;
        unitJson["name"] = unit.name;
        unitJson["description"] = unit.description;
        unitJson["type"] = unit.type;
        unitJson["value"] = unit.value;
        unitJson["measureRate"] = unit.measureRate;
        unitJson["status"] = device.status;
    }

    serializeJsonPretty(doc, buffer, 700);
    return buffer;
}

void Data::setup() {
    for(Unit unit: units) {
        if(unit.type == DIMMER && unit.value != -1) {
            analogWrite(unit.pin, unit.value);
        }
    }
}

Unit Data::getUnit(int unitId) {
    for(Unit unit: units) {
        if(unitId == unit.id) {
            return unit;
        }
    }
}

void Data::updateValue(int unitId, long value) {
    for(Unit unit: units) {
        if(unitId == unit.id) {
            if(unit.type == DIMMER) {
                dimmer.setValue(value);
            }
        }
    }
}