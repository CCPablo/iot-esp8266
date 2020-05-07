
#ifndef _DIMMER_HPP_
#define _DIMMER_HPP_

class Dimmer {
    private:
        const uint8_t zcPin;
        const uint8_t pwmPin;

        uint16_t fade = 1;
        uint8_t state = 1;
        uint8_t targetBrightness = 255;
        uint8_t currentBrightness = 0;
        uint8_t zcState = 0;

    public:
        Dimmer(const uint8_t pwmPin, const uint8_t zeroCrossingPin) :
            pwmPin(pwmPin),
            zcPin(zeroCrossingPin) {}
        
        void setup();
        void serialLoop();

        void setValue(uint8_t value) {
            targetBrightness = value;
        }
        
        void updateCurrentBrightness();
        void pwmWrite();

        void zcISRFunc();
        
};

#endif