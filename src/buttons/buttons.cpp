#include "buttons.h"
#include "pins.h"

KVBButtons Buttons(BP_VAL, BP_MV, BP_FC, BP_TEST, BP_SF);

void updateButtons(void) {
  Buttons.updateAllButtons();
}

bool haveButtonsChanged(void) {
  return Buttons.hasChanged();
}

ButtonsSend getButtons(void) {
    return Buttons.readButtons();
}

/* implémentation des méthodes de la classe KVBButtons */
KVBButtons::KVBButtons(int VAL, int MV, int FC, int TEST, int SF)
{

    this->VALbtn.attach(VAL, INPUT_PULLUP);
    this->MVbtn.attach(MV, INPUT_PULLUP);
    this->FCbtn.attach(FC, INPUT_PULLUP);
    this->TESTbtn.attach(TEST, INPUT_PULLUP);
    this->SFbtn.attach(SF, INPUT_PULLUP);
}

KVBButtons::~KVBButtons()
{
}

void KVBButtons::updateAllButtons(void) {
    this->VALbtn.update();
    this->MVbtn.update();
    this->FCbtn.update();
    this->TESTbtn.update();
    this->SFbtn.update();
}

bool KVBButtons::hasChanged(void) {
    return this->VALbtn.changed() || this->MVbtn.changed() || this->FCbtn.changed() || this->TESTbtn.changed() || this->SFbtn.changed();
}

ButtonsSend KVBButtons::readButtons(void) {
    ButtonsSend toSend;

    /* lecture de tous les boutons */
    toSend.VAL  = !this->VALbtn.read();
    toSend.MV   = !this-> MVbtn.read();
    toSend.FC   = !this->FCbtn.read();
    toSend.TEST = !this->TESTbtn.read();
    toSend.SF   = !this->SFbtn.read();

    return toSend;
}