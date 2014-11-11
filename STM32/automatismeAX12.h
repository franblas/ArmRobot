/*	****** Written by François Blas
 	****** Last Modification: 25/05/13 	
	
	Using the stm32f10x lib needs a configuration. You need to put STM32F10X_LD_VL in 
	Project\Option for Target\C/C++\Define 										
	
	The datasheet is needed to find the best option for your project and to know the global 
	fonctionnement of each peripherial.	*/

#ifndef AUTOMATISMEAX12_H_INCLUDED
#define AUTOMATISMEAX12_H_INCLUDED

#include "ax12.h"

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
/////////////////// Fonctions ////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/**
---------------------- Reset Arm ----------------------------
Positionne le bras a la verticale 
(Les positions des 3 AX12 sont a 511)
-> usartx : Choix de l'USART
--------------------------------------------------------------
**/
void resetarm(int usartx);

/**
---------------------- Automatisme AX12 ----------------------
Positionne l'organe terminal du bras jusqu'a un point (x,y,z)
-> usartx : Choix de l'USART
-> pd : coordonnées X (en cm)
-> pe : coordonnées Y (en cm)
-> pf : coordonnées Z (en cm)
--------------------------------------------------------------
**/
void automatisme(int usartx, double pd, double pe, double pf);

/**
---------------------- Config joystick bouton -----------------
Configure les ports pour les 6 boutons de la manette + un bouton STM32
-> PA 0 correspond a resetarm
-> PA 4 correspond a +X
-> PA 5 correspond a -X
-> PA 6 correspond a +Y
-> PA 7 correspond a -Y
-> PC 4 correspond a +Z
-> PC 5 correspond a -Z
--------------------------------------------------------------
**/
void joystick_button_config(void);

/**
---------------------- Config LEDs STM32 ---------------------
Configure les ports pour les 2 LEDs de la STM32
-> LED bleue sur PC 8
-> LED bleue sur PC 9
--------------------------------------------------------------
**/
void led_stm32_init(void);

/**
---------------------- Config joystick bouton -----------------
Definit les actions a effectuer pour chaque bouton de la manette
-> usartx : Choix de l'USART
---------------------------------------------------------------
**/
void joystick(int usartx);

/**
--------------- Config joystick bouton (demo) -----------------
Definit les actions a effectuer pour chaque bouton de la manette
Fonction de demonstration
-> usartx : Choix de l'USART
---------------------------------------------------------------
**/
void joystickDemo(int usartx);

/**
------------------------ Move the arm -------------------------
Bouge le bras avec la manette
-> usartx : Choix de l'USART
---------------------------------------------------------------
**/
void moveARM(int usartx);

/**
-------------------- Move the arm (Demo) ----------------------
Bouge le bras avec la manette
Fonction de demonstration
-> usartx : Choix de l'USART
---------------------------------------------------------------
**/
void moveARMDemo(int usartx);

#endif // AUTOMATISMEAX12_H_INCLUDED

