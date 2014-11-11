/*	****** Written by François Blas
 	****** Last Modification: 25/05/13

	Using the stm32f10x lib needs a configuration. You need to put STM32F10X_LD_VL in
	Project\Option for Target\C/C++\Define

	The datasheet is needed to find the best option for your project and to know the global
	fonctionnement of each peripherial.	*/

#include "ax12.h"
#include "calcul_angle_bis.h"
#include "automatismeAX12.h"
#include "gpio.h"

/* Variables globales */
//Coordonées (X,Y,Z)
double posX=0;
double posY=0;
double posZ=0;

//---------------------------------------------------------
//----------------------resetarm---------------------------
//---------------------------------------------------------

void resetarm(int usartx)
{
	//Initialisation de la communication avec AX12
	ax12_init(usartx);

    //Reduction du couple sur l'AX12 de la base pour limiter les appels de courant
	delay(1300000);
	ax12_torquelimit(usartx,3,700);
	delay(1300000);

	//Move the arm
	delay(1300000);
	ax12_position(usartx,1,511); //AX12 numero 1 (top of the arm) positione a la verticale
	delay(1300000);
	ax12_position(usartx,2,511); //AX12 numero 2 (mid of the arm) positione a la verticale
	delay(1300000);
	ax12_position(usartx,3,511); //AX12 numero 3 (bot of the arm) positione a la verticale
	delay(1300000);

	//coordonées organe terminal quand bras est a la verticale
	posX=0;
	posY=0;
	posZ=39;
}

//---------------------------------------------------------
//----------------------automatisme------------------------
//---------------------------------------------------------

void automatisme(int usartx, double pd, double pe, double pf)
{
	//Initialisation variables
	double g=0,h=0; //angles en radians
	int k=0,l=0,m=0; //angles en valeurs AX12

	//Verifications des coordonées
	//Position X
	if (pd>20.1){pd=20.1;}
	else if (pd<-1.9){pd = -1.9;}

  //Position Y
	if (pe>35){pe=35;}
	else if (pe<-35){pe=-35;}

  //Position Z
	if (pf>39){pf=39;}
	else if (pf<4){pf=4;}

	//Calculs
	g = calcul_x(pe, pf); //Calcul du 1er angle
	h = calcul_y(pd); //Calcul du 2nd angle

	//Conversion des valeurs (cast explicite)
	k=(int)positionner_x(g);
	l=(int)positionner_y(h);
	m=(int)positionner_z(h);

	//Initialisation de la communication avec AX12
	ax12_init(usartx);

	//Move the arm
	delay(1300000);
	ax12_position(usartx,1,m); //AX12 numero 1 (top of the arm) positione en m
	delay(1300000);
	ax12_position(usartx,2,l); //AX12 numero 2 (mid of the arm) positione en l
	delay(1300000);
	ax12_position(usartx,3,k); //AX12 numero 3 (bot of the arm) positione en k
	delay(1300000);
}

//---------------------------------------------------------
//---------------joystick_button_config--------------------
//---------------------------------------------------------

void joystick_button_config()
{
gpio_config(GPIO_A,0,SPEED_NO,FLOATING); // ResetArm
gpio_config(GPIO_A,4,SPEED_NO,FLOATING); // +X
gpio_config(GPIO_A,5,SPEED_NO,FLOATING); // -X
gpio_config(GPIO_A,6,SPEED_NO,FLOATING); // +Y
gpio_config(GPIO_A,7,SPEED_NO,FLOATING); // -Y
gpio_config(GPIO_C,4,SPEED_NO,FLOATING); // +Z
gpio_config(GPIO_C,5,SPEED_NO,FLOATING); // -Z
}

//---------------------------------------------------------
//---------------------led_stm32_init----------------------
//---------------------------------------------------------

void led_stm32_init()
{
gpio_config(GPIO_C,8,SPEED_50,GENERAL_PUSHPULL); //Blue LED
gpio_config(GPIO_C,9,SPEED_50,GENERAL_PUSHPULL); //Green LED
}

//---------------------------------------------------------
//-----------------------joystick--------------------------
//---------------------------------------------------------

void joystick(int usartx)
{
	//Attente de l'appui du bouton
	while( ( (gpio_idr(GPIO_A,0)) + (gpio_idr(GPIO_A,4)) + (gpio_idr(GPIO_A,5)) + (gpio_idr(GPIO_A,7)) + (gpio_idr(GPIO_C,4)) + (gpio_idr(GPIO_C,5)) + (gpio_idr(GPIO_A,6)) ) == 0);
				//Instructions a effectuer suivant le bouton presse
					 if(gpio_idr(GPIO_A,4)==1)
							{
								gpio_bsrr(GPIO_C,8,SET);
									if(posX>20.1){posX=20.1;automatisme(usartx,20.1,posY,posZ);}
									else if(posX<-1.9){posX=-1.9;automatisme(usartx,-1.9,posY,posZ);}
									else{automatisme(usartx,posX+1,posY,posZ);}
							}
					 else if(gpio_idr(GPIO_A,5)==1)
							{
								gpio_bsrr(GPIO_C,8,SET);
									if(posX>20.1){posX=20.1;automatisme(usartx,20.1,posY,posZ);}
									else if(posX<-1.9){posX=-1.9;automatisme(usartx,-1.9,posY,posZ);}
									else{automatisme(usartx,posX-1,posY,posZ);}
							}
					 else if(gpio_idr(GPIO_A,6)==1)
							{
								gpio_bsrr(GPIO_C,9,SET);
									if(posY>35){posY=35;automatisme(usartx,posX,35,posZ);}
									else if(posY<-35){posY=-35;automatisme(usartx,posX,-35,posZ);}
									else{automatisme(usartx,posX,posY+1,posZ);}
							}
					 else if(gpio_idr(GPIO_A,7)==1)
							{
								gpio_bsrr(GPIO_C,9,SET);
									if(posY>35){posY=35;automatisme(usartx,posX,35,posZ);}
									else if(posY<-35){posY=-35;automatisme(usartx,posX,-35,posZ);}
									else{automatisme(usartx,posX,posY-1,posZ);}
							}
					 else if(gpio_idr(GPIO_C,4)==1)
							{
								gpio_bsrr(GPIO_C,8,SET);
									if(posZ>39){posZ=39;automatisme(usartx,posX,posY,39);}
									else if(posZ<4){posZ=4;automatisme(usartx,posX,posY,4);}
									else{automatisme(usartx,posX,posY,posZ+1);}
							}
					 else if(gpio_idr(GPIO_C,5)==1)
							{
								gpio_bsrr(GPIO_C,8,SET);
									if(posZ>39){posZ=39;automatisme(usartx,posX,posY,39);}
									else if(posZ<4){posZ=4;automatisme(usartx,posX,posY,4);}
									else{automatisme(usartx,posX,posY,posZ-1);}
							}
			else if(gpio_idr(GPIO_A,0)==1)
							{
								gpio_bsrr(GPIO_C,8,RESET);
								gpio_bsrr(GPIO_C,9,RESET);
								resetarm(usartx);
							}
			else{gpio_bsrr(GPIO_C,8,SET);gpio_bsrr(GPIO_C,9,SET);}
	//Attente du relâchement du bouton
	while( ( (gpio_idr(GPIO_A,0))+ (gpio_idr(GPIO_A,4)) + (gpio_idr(GPIO_A,5)) + (gpio_idr(GPIO_A,7)) + (gpio_idr(GPIO_C,4)) + (gpio_idr(GPIO_C,5)) + (gpio_idr(GPIO_A,6)) ) != 0);

}

//---------------------------------------------------------
//---------------------joystickDemo------------------------
//---------------------------------------------------------

void joystickDemo(int usartx)
{
	//Attente de l'appui du bouton
	while( ( (gpio_idr(GPIO_A,0)) + (gpio_idr(GPIO_A,4)) + (gpio_idr(GPIO_A,5)) + (gpio_idr(GPIO_A,7)) + (gpio_idr(GPIO_C,4)) + (gpio_idr(GPIO_C,5)) + (gpio_idr(GPIO_A,6)) ) == 0);
				//Instructions a effectuer suivant le bouton presse
					      if(gpio_idr(GPIO_A,4)==1){gpio_bsrr(GPIO_C,8,SET);automatisme(USART_1,15,29.42,9.18);} // 10 45
					 else if(gpio_idr(GPIO_A,5)==1){gpio_bsrr(GPIO_C,8,SET);automatisme(USART_1,15,28,14.2);} // 20 45
					 else if(gpio_idr(GPIO_A,6)==1){gpio_bsrr(GPIO_C,9,SET);automatisme(USART_1,14.97,25.87,18.9);} // 30 45
					 else if(gpio_idr(GPIO_A,7)==1){gpio_bsrr(GPIO_C,9,SET);automatisme(USART_1,14.97,19.20,26.8);} // 50 45
					 else if(gpio_idr(GPIO_C,4)==1){gpio_bsrr(GPIO_C,8,SET);automatisme(USART_1,17.7,-8.97,28.6);} // 110 60
					 else if(gpio_idr(GPIO_C,5)==1){gpio_bsrr(GPIO_C,8,SET);automatisme(USART_1,17.7,-16.7,24);} // 130 60
					 else if(gpio_idr(GPIO_A,0)==1){gpio_bsrr(GPIO_C,8,RESET);gpio_bsrr(GPIO_C,9,RESET);resetarm(usartx);}
			     else{gpio_bsrr(GPIO_C,8,SET);gpio_bsrr(GPIO_C,9,SET);}
	//Attente du relâchement du bouton
	while( ( (gpio_idr(GPIO_A,0))+ (gpio_idr(GPIO_A,4)) + (gpio_idr(GPIO_A,5)) + (gpio_idr(GPIO_A,7)) + (gpio_idr(GPIO_C,4)) + (gpio_idr(GPIO_C,5)) + (gpio_idr(GPIO_A,6)) ) != 0);

}

//---------------------------------------------------------
//----------------------moveARM----------------------------
//---------------------------------------------------------

void moveARM(int usartx)
{
	resetarm(usartx); //Remet le bras a la verticale

	joystick_button_config();//Initialisation des ports d'inputs de la manette
	led_stm32_init(); //Initialisation des LEDs de la STM32

	while(1)
	{
		joystick(usartx);//Driver manette\bras
	}
}

//---------------------------------------------------------
//--------------------moveARMDemo--------------------------
//---------------------------------------------------------

void moveARMDemo(int usartx)
{
	resetarm(usartx); //Remet le bras a la verticale

	joystick_button_config();//Initialisation des ports d'inputs de la manette
	led_stm32_init(); //Initialisation des LEDs de la STM32

	while(1)
	{
		joystickDemo(usartx);//Driver manette\bras
	}
}

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------

