/*	****** Written by Luc Fourtinon
 	****** Last Modification: 25/05/13 	
	
	Using the stm32f10x lib needs a configuration. You need to put STM32F10X_LD_VL in 
	Project\Option for Target\C/C++\Define 										
	
	The datasheet is needed to find the best option for your project and to know the global 
	fonctionnement of each peripherial.	*/ 
	
#ifndef CALCUL_ANGLE_BIS_H_INCLUDED
#define CALCUL_ANGLE_BIS_H_INCLUDED

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////// Macros //////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/* Longueurs des parties du bras du robot */
#define a 17.5
#define b 17.5
#define c 2.6

/* Utiles */
#define PI 3.1416

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
/////////////////// Fonctions ////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/** 
---------------------- Calculs Angles ----------------------------
Calculs des angles a partir des coordonnées de l'organe terminal 
-> pd : (en cm)
-> pe : (en cm)
-> pf : (en cm)
------------------------------------------------------------------
**/
double calcul_y(double pd);
double calcul_x(double pe, double pf);

/**
------------------ Conversion Radian\Degre -----------------------
Conversion d'un angle en radian vers un angle en degre
-> rad : angle a convertir en degre
------------------------------------------------------------------
**/
double conversionraddeg(double rad);

/**
------------------ Conversion Degre\Radian -----------------------
Conversion d'un angle en degre vers un angle en radian
-> deg : angle a convertir en radian 
------------------------------------------------------------------
**/
double conversiondegrad(double deg);

/**
------------------ Conversion Radian\AX12 ------------------------
Conversion des angles (en radian) en valeurs entières AX12
-> x : (en rad)
-> y : (en rad)
-> z : (en rad)
------------------------------------------------------------------
**/
double positionner_x(double x);
double positionner_y(double y);
double positionner_z(double z);

#endif // CALCUL_ANGLE_BIS_H_INCLUDED

