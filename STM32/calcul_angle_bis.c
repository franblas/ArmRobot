/*	****** Written by Luc Fourtinon
 	****** Last Modification: 25/05/13 	
	
	Using the stm32f10x lib needs a configuration. You need to put STM32F10X_LD_VL in 
	Project\Option for Target\C/C++\Define 										
	
	The datasheet is needed to find the best option for your project and to know the global 
	fonctionnement of each peripherial.	*/ 

#include <math.h>
#include "calcul_angle_bis.h"

//---------------------------------------------------------
//----------------------calcul_y---------------------------
//---------------------------------------------------------

double calcul_y(double pd)
{ 
	double y;
	y = asin((pd-c)/b);
	return y;	// Renvoie un angle entre [-0.26, Pi/2]
}

//---------------------------------------------------------
//----------------------calcul_x---------------------------
//---------------------------------------------------------

double calcul_x(double pe, double pf)
{ 
	double x;
		if (pe<0){x = -atan((pf-4)/pe);}
		else if (pe>=0){x = (PI) - atan((pf-4)/pe);}
		else {x = (PI) - atan((pf-4)/pe);}
	return x;
}

//---------------------------------------------------------
//--------------------conversionraddeg---------------------
//---------------------------------------------------------

double conversionraddeg(double rad)
{
double deg=0;
deg = (rad*180)/(PI); 	
return deg;
}

//---------------------------------------------------------
//--------------------conversiondegrad---------------------
//---------------------------------------------------------

double conversiondegrad(double deg)
{
double rad=0;
rad = (deg*PI)/(180); 	
return rad;
}

//---------------------------------------------------------
//--------------------positionner_x------------------------
//---------------------------------------------------------

double positionner_x(double x)
{
	double i;
	i = (conversionraddeg(x)+60)*17/5;
		if (i>817){i=817;}
		else if (i<205){i=205;}
		else {i=i;}
	return i;
}

//---------------------------------------------------------
//--------------------positionner_y------------------------
//---------------------------------------------------------

double positionner_y(double y)
{
	double j;
	j = (150-conversionraddeg(y))*17/5;
		if (j>866){j=866;}
		else if (j<460){j=460;}
		else {j=j;}
	return j;
}

//---------------------------------------------------------
//--------------------positionner_z------------------------
//---------------------------------------------------------

//il faut rentrer l'angle y comme paramètre;
double positionner_z(double z)
{  
	double k;
	k = (60 + conversionraddeg(z))*17/5;
	return k;
}
		
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------

