
#ifndef _SCHEDULER_HPP_
#define _SCHEDULER_HPP_

#define _TASK_SLEEP_ON_IDLE_RUN

#include <TaskSchedulerDeclarations.h>

#include "GlobalDefinitions.h"
#include "MQTTProtocol.hpp"
#include "DeviceData.hpp"
#include <Arduino.h>

void tSensorCallback();

class SchedulerWrapper {
    private:
        Scheduler scheduler;

    public:
        SchedulerWrapper() :
            scheduler() {};

        void setup();
        void loop();
        
        void enableAll();
        void disableAll();
        
        void setInterval(int unitId, int inveral);
};

#endif