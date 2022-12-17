
/*
   * structure utilisée pour stocker les informations reçues du PC
   * @param visu: valeur à afficher sur les 7 segments
   * @param autotestTS: autotest (7 segments)
   * @param LSFU: Lampe de Signalisation Freinage d'Urgence
   * @param LSV: Lampe de Signalisation de surVitesse
   * @param panneSol: panne sol
   * @param panneEngin: panne engin
   * @param FCLight: Lampe de Signalisation Franchissement Carré
   * @param VALLight: rétroéclairage bouton VAL
   * @param LSSF: Lampe de Signalisation Signal Fermé
*/
struct SerialInput
{
   int visu, autotestTS;
   bool LSFU, LSV, panneSol, panneEngin, FCLight, VALLight, LSSF;
};

void handleSerialInput(SerialInput input);

