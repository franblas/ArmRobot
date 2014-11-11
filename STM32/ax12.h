/*	****** Written by François Blas
 	****** Last Modification: 23/04/13 	
	
	Using the stm32f10x lib needs a configuration. You need to put STM32F10X_LD_VL in 
	Project\Option for Target\C/C++\Define 										
	
	The datasheet is needed to find the best option for your project and to know the global 
	fonctionnement of each peripherial.	*/ 

/**
------------------------------------------------------
------------------------------------------------------
------------ Precisions sur les AX12 -----------------
------------------------------------------------------
------------------------------------------------------
**/

/**
======  Reduire le baudrate des AX12 a 500k ======
Bien verifier que les baudrates des AX12 ont etes reconfigures a 500k !! (Utiliser Arduino pour aller plus vite !)  
Sur Arduino faire : ax12SetRegister(id,4,3); ou encore ax12SetRegister(id,AX_BAUD_RATE,3);
Arduino biblio : #include <ax12.h> #include <BioloidController.h>	
**/
	
/**
======  Modifier l'identifiant des AX12 ======
ID par default = 1
Sur Arduino faire : ax12SetRegister(oldID,3,newID); ou encore ax12SetRegister(oldID,AX_ID,newID);
Arduino biblio : #include <ax12.h> #include <BioloidController.h>	
**/	

#ifndef AX12_H_INCLUDED
#define AX12_H_INCLUDED

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////// Macros //////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/* USARTx */
#define USART_1 1
#define USART_2 2
#define USART_3 3

/* AX12 Registers */ 
//EEPROM AREA
#define AX_MODEL_NUMBER_R2 0 //Read Only
#define AX_VERSION 2 // Read Only
#define AX_ID 3
#define AX_BAUD_RATE 4
#define AX_RETURN_DELAY_TIME 5
#define AX_CW_ANGLE_LIMIT_R2 6
#define AX_CCW_ANGLE_LIMIT_R2 8
#define AX_SYSTEM_DATA2 10
#define AX_LIMIT_TEMPERATURE 11
#define AX_DOWN_LIMIT_VOLTAGE 12
#define AX_UP_LIMIT_VOLTAGE 13
#define AX_MAX_TORQUE_R2 14
#define AX_RETURN_LEVEL 16
#define AX_ALARM_LED 17
#define AX_ALARM_SHUTDOWN 18
#define AX_OPERATING_MODE 19
#define AX_DOWN_CALIBRATION_R2 20 // Read Only
#define AX_UP_CALIBRATION_R2 22 // Read Only
//RAM AREA
#define AX_TORQUE_ENABLE 24
#define AX_LED 25
#define AX_CW_COMPLIANCE_MARGIN 26
#define AX_CCW_COMPLIANCE_MARGIN 27
#define AX_CW_COMPLIANCE_SLOPE 28
#define AX_CCW_COMPLIANCE_SLOPE 29
#define AX_GOAL_POSITION_R2 30
#define AX_GOAL_SPEED_R2 32
#define AX_TORQUE_LIMIT_R2 34
#define AX_PRESENT_POSITION_R2 36 // Read Only
#define AX_PRESENT_SPEED_R2 38 // Read Only
#define AX_PRESENT_LOAD_R2 40 // Read Only
#define AX_PRESENT_VOLTAGE 42 // Read Only
#define AX_PRESENT_TEMPERATURE 43 // Read Only
#define AX_REGISTERED_INSTRUCTION 44
#define AX_PAUSE_TIME 45
#define AX_MOVING 46
#define AX_LOCK 47
#define AX_PUNCH_R2 48

typedef enum Debit Debit;
enum Debit
{
	BAUD_9600,		/* 9600 bauds */
	BAUD_115200,	/* 115200 bauds */
	BAUD_500000	/* 500000 bauds */
};

typedef enum Direction Direction;
enum Direction
{
	HALF_DUPLEX,	/* Canal Half-Duplex */
	FULL_DUPLEX	    /* Canal Full-Duplex */
};

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
/////////////////// Fonctions ////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/* ======= Autres ======= */
void delay(int del);
void ax12_write_register(int usartx,int id,int reg,int value);
void ax12_write_register2(int usartx,int id,int reg,int value);
void ax12_reset(int usartx);

/* ======= USARTx ======= */
/**
>>>>>> USART_1 (Remap) (STM32F100RB)
FULL_DUPLEX mode : TX on PB6 \ RX on PB7 
HALF_DUPLEX mode : TX\RX on PB6 

>>>>>> USART_2 (No Remap) (STM32F100RB)
FULL_DUPLEX mode : TX on PA2 \ RX on PA3
HALF_DUPLEX mode : TX\RX on PA2

>>>>>> USART_3 (Remap) (STM32F100RB)
FULL_DUPLEX mode : TX on PC10 \ RX on PC11
HALF_DUPLEX mode : TX\RX on PC10

>>>>>> ATTENTION !!! Pour le HALF_DUPLEX mettre une resistance (1k) de pull-up (3.3V ou 5V) en sortie de port 
**/
void usart1_init(Debit p_debit, Direction p_dir);
void usart2_init(Debit p_debit, Direction p_dir);
void usart3_init(Debit p_debit, Direction p_dir);
void enable_usart(int usartx);
void disable_usart(int usartx);
void send_byte(int usartx,unsigned char byte);
unsigned char receive_byte(int usartx);

/* ======= AX12 ======= */
void ax12_init(int usartx);

//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------

/**
------------ Position AX12 ------------
-> usartx : Choix de l'USART
-> id : ID de l'AX12
-> pos : position en mesure AX12 (160 a 871)
160 (butée droite)
204 (horizontale droite)
511 (verticale)  
818 (horizontale gauche)
871 (butée gauche)
---------------------------------------
**/
void ax12_position(int usartx,int id, int pos);

/**
------------ Vitesse AX12 -------------
-> usartx : Choix de l'USART
-> id : ID de l'AX12
-> speed : vitesse en mesure AX12 (1(---) a 1023(+++))
---------------------------------------
**/
void ax12_movingspeed(int usartx,int id,int speed);

/**
------------ Couple AX12 --------------
-> usartx : Choix de l'USART
-> id : ID de l'AX12
-> torque : couple serrage en mesure AX12 (1(---) a 1023(+++))
---------------------------------------
**/
void ax12_torquelimit(int usartx,int id,int torque);

#endif // AX12_H_INCLUDED

