#include "serial.hpp"

#include "../7segs/7segs.hpp"
#include "../definitions.hpp"
#include "../pins.hpp"
#include "../helper.hpp"


void handleSerialInput(SerialInput input) {
  
  if (input.autotestTS == 1 || input.autotestTS == 2 || input.autotestTS == 3)
  {
  switch (input.autotestTS)
  {
    case 1:
        setVisu(PA400);
/*          digitalWrite(FU_LED, LOW);
      digitalWrite(V_LED, LOW);
      digitalWrite(SOL_LED, LOW);
      digitalWrite(ENGIN_LED, LOW); 
*/         
        break;

    case 2:
      setVisu(UC512);
      /*          digitalWrite(FU_LED, LOW);
      digitalWrite(V_LED, LOW);
      digitalWrite(SOL_LED, HIGH);
      digitalWrite(ENGIN_LED, HIGH); 
*/ 
        break;

    case 3:
        break;
    }
  } else
  {
    Serial.println("visu: "+String(input.visu));
    switch (input.visu)
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
    Serial.println("LSSF: "+String(input.LSSF));
    setLamp(input.LSSF, LS_SF);
  }
}