#include "helper.h"
#include "pins.h"

#include "Arduino.h"
#include "ArduinoJson.h"

String lastReadThumbSwitch = "";
unsigned long lastCheckedThumbSwitches = millis();

StaticJsonDocument<128> BPOutput;

String lastSentStringsBP = "";

void setLamp(const int input, const int led) {
  if (input == 0) {
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
  }
}

void sendButtonToSerial(ButtonsSend buttons) {
  String toPrint;
  
  BPOutput["VAL"] = buttons.VAL;
  BPOutput["MV"] = buttons.MV;
  BPOutput["FC"] = buttons.FC;
  BPOutput["TEST"] = buttons.TEST;
  BPOutput["SF"] = buttons.SF;
  
  serializeJson(BPOutput, toPrint);

  //if (toPrint != lastSentStrings[0]) {
    Serial.println(toPrint);
    #if !DEBUG
    lastSentStringsBP = toPrint;
    #endif
  //}

  /*
  if(TESTbtn) {
    digitalWrite(BEEP_V, HIGH);
      player.playSpecified(5);
  } else {
    digitalWrite(BEEP_V, LOW);
  }*/
}

void configurePins(void) {

  for (int i = 0; i < 10; i++ ) {
    pinMode(pins[i], OUTPUT);
  }

  pinMode(BEEP_V, OUTPUT);

  for (int i = 0; i < 6; i++ ) {
    pinMode(digits[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 3; i++ ) {
    pinMode(BPlightPins[i], OUTPUT);
  }

}

String readAllThumbWheels(void) {

  unsigned long now = millis();
  unsigned long timeDifference = now-lastCheckedThumbSwitches;
  if(timeDifference < 300) {
    //Serial.println(String(timeDifference));
    return lastReadThumbSwitch;
  }

  String toPrint[] = {"", "", "", "", "", ""};
  int pin;
  int count[] = {0, 0, 0, 0, 0};

  for (int i = 0; i < 10; i++ ) {
    pin = pins[i];
    digitalWrite(pin, HIGH);

    for (int j = 0; j < 6; j++ ) {
      int valeur = digitalRead(digits[j]);
      if (valeur == 1) {
        toPrint[j] = String(i);
        //Serial.println(String(i));
        count[j]++;
      }
    }
    //delay(1);
    digitalWrite(pin, LOW);
  }


  String toReturn = "";
  /*toReturn = "V:";
    toReturn += toPrint[0];
    toReturn += toPrint[1];
    toReturn += " L:";
    toReturn += toPrint[2];
    toReturn += " D:";
    toReturn += toPrint[3];
    toReturn += toPrint[4];
    toReturn += toPrint[5];*/

  /*
    char Vstring = strcat(toPrint[0], toPrint[1]);
    int V = atoi(Vstring);
    toReturn.V = V;

    toReturn.L = atoi(toPrint[2]);

    char Dstring = strcat(toPrint[3], toPrint[4]);
    int D = atoi(Dstring);
    toReturn.D = D;
  */



  toReturn += toPrint[0];
  toReturn += toPrint[1];
  toReturn += toPrint[2];
  toReturn += toPrint[3];
  toReturn += toPrint[4];
  toReturn += toPrint[5];

  //Serial.println(toReturn);

  lastCheckedThumbSwitches = now;

  return toReturn;


}

int getSwitchState(void) {
  for (int i = 0; i < 2; i++ ) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }

  // state:
  // 0: VO
  // 1: ME, default
  // 2: MA
  int state = 2;

  for (int i = 0; i < 2; i++ ) {
    digitalWrite(switchPins[i], HIGH);

    // lecture de l'état du COM switch
    int value = digitalRead(SW_COM);

    //Serial.println(String(i) + ":" + String(value));

    // s'il est positif, on part du principe qu'il est set sur l'état actuellement selectionné
    if (value == 1) {

      state = i;


    }

    // et on éteint le pin scanné précédemment
    digitalWrite(switchPins[i], LOW);
  }

  for (int i = 0; i < 2; i++ ) {
    pinMode(switchPins[i], OUTPUT);
  }


  return state;
}

void blinkVAL(void) {
  digitalWrite(LS_BP_VAL, HIGH);
  
  delay(200);
  digitalWrite(LS_BP_VAL, LOW);
  delay(200);
}

void bipTest(void) {
  // simple test du beep de survitesse

  // pour des raisons de pas le temps, il sera aussi utilisé au démarrage

  // 10 bip

  //digitalWrite(BEEP_V, HIGH);
#if DEBUG && !SKIPTEST
  delay(1600);
#else
  delay(1600);
#endif
  //digitalWrite(BEEP_V, LOW);
}

