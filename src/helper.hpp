#include "Arduino.h"
#include "buttons/buttonsSend.hpp"

void setLamp(const int input, const int led);
void sendButtonToSerial(ButtonsSend buttons);
String readAllThumbWheels(void);
void configurePins(void);
int getSwitchState(void);
void blinkVAL(void);
void bipTest(void);


enum SwitchValues {
    VO = 0,
    ME = 1,
    MA = 2
};


