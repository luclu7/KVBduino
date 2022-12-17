#ifndef BUTTONS_H
#define BUTTONS_H
// pour le debouncing
#include <Bounce2.h>
#include "buttonsSend.hpp"


class KVBButtons
{
private:
    Bounce VALbtn, MVbtn, FCbtn, TESTbtn, SFbtn;
public:
    KVBButtons(int BP_VAL, int BP_MV, int BP_FC, int BP_TEST, int BP_SF);
    ~KVBButtons();
    void updateAllButtons(void);
    bool hasChanged(void);
    ButtonsSend readButtons(void);
};

void updateButtons(void);
ButtonsSend getButtons(void);
bool haveButtonsChanged(void);

#endif