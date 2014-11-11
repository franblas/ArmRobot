/*	****** Written by François Blas
 	****** Last Modification: 27/04/13 	
	
	Using the Arduino Mega 2560 										
*/

/*
>>>>> Connecter le TX1 (port 18 Arduino Mega 2560) et le RX1 (port 19 Arduino Mega 2560)
sur le data de l'AX12 (TX1 et RX1 ensemble)
>>>>> Pas besoin de resistance de pull-up !!!!!!!!!
*/

/*
Decommenter la ligne sous "Changer l'identifiant de l'AX12" puis mettre le nouvel identifiant de l'AX12 a la place de newID
Televerser vers l'AX12
Recommenter la ligne
Tester le nouvel identifiant (changer id dans setup)
Decommenter la ligne sous "Mettre baudrate a 500k" avec id=votre nouvel identifiant
Televerser vers l'AX12
Recommenter la ligne
Modifier BioloidController(1000000) par BioloidController(500000)
Tester l'AX12
*/

//Biblio AX12 Arduino
#include <ax12.h>
#include <BioloidController.h>

int pos;    // position AX12 
int id;     // Identifiant AX12

//Initialisation de la communication
//Une fois le baudrate d'un AX12 modifié, changer la valeur contenue dans BioloidController() 
BioloidController bioloid=BioloidController(1000000);


void setup()
{
  pinMode(13, OUTPUT);
    pos = 511;
    id = 4;
}

void loop()
{
    digitalWrite(13,HIGH);
    SetPosition(id,pos); //Changment position 
    delay(25);
    SetPosition(id,402); //Changment position 
    delay(100);
    /* Changer l'identifiant de l'AX12 */
    //ax12SetRegister(id,3,newID);
    delay(100);
    /* Mettre baudrate a 500k */
    //ax12SetRegister(id,4,3);
    delay(25);
    
    digitalWrite(13, LOW);
    delay(200);

    //ax12SetRegister(servo_id, regstart, data);
}
