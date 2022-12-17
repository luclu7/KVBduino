#include <stdio.h>
#include <string.h>
#include <Arduino.h>

#include "helper.hpp"
#include "definitions.hpp"
#include "7segs/7segs.hpp"
#include "buttons/buttons.hpp"
#include "serial/serial.hpp"

// TEMP
#include "pins.hpp"

// audio
#include "DYPlayerArduino.h"
#include "SoftwareSerial.h"
DY::Player player(&Serial2);


// pour la transmission PC
#include <ArduinoJson.h>

#define DEBUG 0
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

	/* lecture de l'état des boutons */
	updateButtons();

	/* on regarde si les boutons ont changé d'état depuis le dernier cycle */
	if (haveButtonsChanged()) {
		sendButtonToSerial(getButtons());
	}


/*  String vldInfo = readAllThumbWheels(); */


		
	/* on regarde si on a reçu quelque chose sur le port série */
	char received = Serial.read();
	if (received != 255 && received != (signed)0xFFFFFFFF) // on filtre les valeurs incohérentes
	{
		inData += received; // on ajoute le caractère reçu à la chaîne de caractères
		#if DEBUG
		Serial.println("# debug : " + received); // on affiche le caractère reçu, debug
		#endif
	}
	// Process message when new line character is received
	if (received == '\n')
	{
		Serial.println("#"+ inData);
		deserializeJson(doc, inData);
		int visu = doc["visu"];       // 1
		int autotestTS = doc["autotest"]; // 3
		int LSFU = doc["LSFU"];         // 1
		int LSV = doc["LSV"];         // 1
		int panneSol = doc["SOL"];         // 1
		int panneEngin = doc["ENGIN"];         // 1
		int FCLight = doc["FC"];         // 1
		int VALLight = doc["VAL"];         // 1
		int LSSF = doc["LSSF"];         // 1

		Serial.println("#"+received);

		// print visu, autotestTS, LSFU, LSV, panneSol, panneEngin, CG, FCLight, VALLight in serial
	/*	Serial.print("# visu: "+String(visu));
		Serial.print(" autotestTS: "+String(autotestTS));
		Serial.print(" LSFU: "+String(LSFU));
		Serial.print(" LSV: "+String(LSV));
		Serial.print(" panneSol: "+String(panneSol));
		Serial.print(" panneEngin: "+String(panneEngin));
		Serial.print(" CG: "+String(CG));
		Serial.print(" FCLight: "+String(FCLight));
		Serial.print(" VALLight: "+String(VALLight));
		Serial.print(" LSSF: "+String(LSSF));
		Serial.println();
		*/

		// create object
		SerialInput input = {visu, autotestTS, LSFU, LSV, panneSol, panneEngin, FCLight, VALLight, LSSF};

		handleSerialInput(input);

		inData = ""; // Clear received buffer
	}
}