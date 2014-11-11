/*	****** Written by François Blas
 	****** Last Modification: 25/05/13 	
	
	Using the stm32f10x lib needs a configuration. You need to put STM32F10X_LD_VL in 
	Project\Option for Target\C/C++\Define 										
	
	The datasheet is needed to find the best option for your project and to know the global 
	fonctionnement of each peripherial.	*/ 
	
#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////// Macros //////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/* GPIOx */
#define GPIO_A 1
#define GPIO_B 2
#define GPIO_C 3

/* OUTPUT */
#define GENERAL_PUSHPULL 4
#define ALTERNATE_PUSHPULL 5
#define SPEED_50 6
#define SPEED_10 7
#define SPEED_2 8
#define ALTERNATE_OPENDRAIN 9
#define GENERAL_OPENDRAIN 10

/* INPUT */
#define ANALOGUE 11
#define FLOATING 12
#define PULLUPDOWN 13
#define SPEED_NO 14

/* AUTRES */
#define SET 15
#define RESET 16

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
/////////////////// Fonctions ////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/**
Configurations preliminaires
**/
void gpio_clock(int gpiox);
void gpioa_crl(int gpiox, int num, int speed, int mode);
void gpioa_crh(int gpiox, int num, int speed, int mode);
void gpiob_crl(int gpiox, int num, int speed, int mode);
void gpiob_crh(int gpiox, int num, int speed, int mode);
void gpioc_crl(int gpiox, int num, int speed, int mode);
void gpioc_crh(int gpiox, int num, int speed, int mode);

/**
------------------------------------------------
---------- Configuration finale GPIOx ----------
------------------------------------------------
-> gpiox : nom du port (GPIO_A, GPIO_B, GPIO_C)
-> numport : numero du port (0 a 15)
-> speed : freq du port (SPEED_2 (2MHz), SPEED_10 (10MHz), SPEED_50 (50MHz))
-> mode : mode du port 
	 (Output : GENERAL_PUSHPULL, GENERAL_OPENDRAIN, ALTERNATE_PUSHPULL, ALTERNATE_OPENDRAIN)
	 (Input : ANALOGUE, FLOATING, PULLUPDOWN) 
-------------------------------------------------
**/
void gpio_config(int gpiox, int numport, int speed, int mode);

/**
-------------------------------------------------
------------- Set/Reset data GPIOx --------------
-------------------------------------------------
-> gpiox : nom du port (GPIO_A, GPIO_B, GPIO_C)
-> num : numero du port (0 a 15)
-> action : set ou reset data (SET, RESET)
-------------------------------------------------
**/
void gpio_bsrr(int gpiox, int num, int action);

/**
-------------------------------------------------
----------- Read input data GPIOx ---------------
-------------------------------------------------
Renvoi 0 si pas de data, 1 sinon
-> gpiox : nom du port (GPIO_A, GPIO_B, GPIO_C)
-> num : numero du port (0 a 15)
-------------------------------------------------
**/
int gpio_idr(int gpiox, int num);

#endif // GPIO_H_INCLUDED

