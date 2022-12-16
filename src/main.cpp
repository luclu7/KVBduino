#include <stdio.h>
#include <string.h>
#include <Arduino.h>

#include "helper.h"
#include "definitions.h"
#include "7segs/7segs.h"
#include "buttons/buttons.h"

// TEMP
#include "pins.h"

// audio
#include "DYPlayerArduino.h"
#include "SoftwareSerial.h"
DY::Player player(&Serial2);


// pour la transmission PC
#include <ArduinoJson.h>

#define DEBUG 1
#define SKIPTEST 1

// utilisé pour stocker l'entrée serial
String inData;

// utilisé pour générer les JSON de d'entrée/sortie
StaticJsonDocument<256> doc;
StaticJsonDocument<128> docOutput;


void setup() {
  
  /*    Initialisation serial    */
  Serial.begin(115200);
  Serial.println("# Initialisation du KVB en cours...");

  configurePins();
  //configureButtons();


  /*   Initialisation DYPlayer   */
  player.begin();
  player.setVolume(15); // 50% Volume


  /*    Initialisation TM1637    */
 

  initSevenSegments();
  setVisu(tirets);

 // bipTest();
 // testVisu();


  /*    Fin de l'initialisation    */
  Serial.println("# Initialisation du KVB terminée");

  // on attend que le port série soit prêt
  while (Serial.available())
  {
    Serial.println("!");
  }

}

void loop(void) {
  String toPrint;

  /* on regarde si les boutons ont changé d'état depuis le dernier cycle */
  updateButtons();

/*  readAllButtons(); */
/*  String vldInfo = readAllThumbWheels(); */


  /* on regarde si les boutons ont changé d'état depuis le dernier cycle */
  if (haveButtonsChanged()) {
    sendButtonToSerial(getButtons());
  }
    
  /* on regarde si on a reçu quelque chose sur le port série */
  char received = Serial.read();
  if (received != 255 && received != (signed)0xFFFFFFFF) // on filtre les valeurs incohérentes
  {
    inData += received; // on ajoute le caractère reçu à la chaîne de caractères
    #if DEBUG
    Serial.println(received); // on affiche le caractère reçu, debug
    #endif
  }
  // Process message when new line character is received
  if (received == '\n')
  {
    Serial.println(inData);
    deserializeJson(doc, inData);
    int visu = doc["visu"];       // 1
    int autotestTS = doc["autotest"]; // 3
    int LSFU = doc["LSFU"];         // 1
    int LSV = doc["LSV"];         // 1
    int panneSol = doc["SOL"];         // 1
    int panneEngin = doc["ENGIN"];         // 1
    int CG = doc["CG"];         // 1
    int FCLight = doc["FC"];         // 1
    int VALLight = doc["VAL"];         // 1

    Serial.println(received);

    // print visu, autotestTS, LSFU, LSV, panneSol, panneEngin, CG, FCLight, VALLight in serial
    Serial.print("visu: "+String(visu));
    Serial.print(" autotestTS: "+String(autotestTS));
    Serial.print(" LSFU: "+String(LSFU));
    Serial.print(" LSV: "+String(LSV));
    Serial.print(" panneSol: "+String(panneSol));
    Serial.print(" panneEngin: "+String(panneEngin));
    Serial.print(" CG: "+String(CG));
    Serial.print(" FCLight: "+String(FCLight));
    Serial.print(" VALLight: "+String(VALLight));
    Serial.println();


    if (autotestTS == 1 || autotestTS == 2 || autotestTS == 3)
    {
      switch (autotestTS)
      {
        case 1:
          setVisu(PA400);
/*          digitalWrite(FU_LED, LOW);
          digitalWrite(V_LED, LOW);
          digitalWrite(SOL_LED, LOW);
          digitalWrite(ENGIN_LED, LOW); 
 */         break;

        case 2:
          setVisu(UC512);
/*          digitalWrite(FU_LED, LOW);
          digitalWrite(V_LED, LOW);
          digitalWrite(SOL_LED, HIGH);
          digitalWrite(ENGIN_LED, HIGH); 
 */     }
    }
    else
    {
      Serial.println("visu: "+String(visu));
      switch (visu)
      {
        case 0: // éteint
          setVisu(eteint);
          break;

        case 1: // contrôle de vitesse actif (la vitesse maximale autorisée ne dépasse pas 160 km/h)
          setVisu(tirets);
          break;

        case 2: // contrôle d'annonce d'un signal d'arrêt fermé avec vitesse d'approche 30 km/h
          setVisu(zeroZeroAux);
          break;

        case 3: // contrôle de vitesse à 30 km/h
          setVisu(zeroZeroPrincipal);
          break;

        case 4: // contrôle d'annonce d'un signal d'arrêt fermé avec vitesse d'approche 10 km/h
          setVisu(tripleZeroAux);
          break;

        case 5: // contrôle de vitesse à 160 km/h
          setVisu(preannonce);
          break;

        case 6: // contrôle de pré-annonce
          setVisu(preannonceAux);
          break;

        case 7: // contrôle de vitesse actif (la vitesse maximale autorisée est supérieure à 160 km/h si rien ne s'y oppose) "b" affiché
          setVisu(vitesseSup160);
          break;

        case 8: // autotest ou test en cours
          setVisu(autotest);
          break;

        case 9: // données incompatibles avec le tableau de cohérence
          setVisu(faute);
          break;

       case 16:
          setVisu(uwu); // ^_^
          break;

        default:
          break;
      }
      /*setLamp(LSV, V_LED);
      setLamp(LSFU, FU_LED);
      setLamp(panneSol, SOL_LED);
      setLamp(panneEngin, ENGIN_LED);
      setLamp(FCLight, FC_LIGHT); */
      Serial.println("VAL: "+String(VALLight));
      setLamp(VALLight, LS_BP_VAL);
    }


    //Serial.println(visu);
    inData = ""; // Clear received buffer
  }
  
  //delay(250);
}



