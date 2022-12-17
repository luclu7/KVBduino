#ifndef BUTTONSSEND_H
#define BUTTONSSEND_H

#include <Arduino.h>

class ButtonsSend
{
private:
    bool VAL;
    bool MV;
    bool FC;
    bool TEST;
    bool SF;
public:
    ButtonsSend(bool VAL, bool MV, bool FC, bool TEST, bool SF);
    ~ButtonsSend();
    unsigned char toBytes(void);
    String toJSON(void);
};

#endif