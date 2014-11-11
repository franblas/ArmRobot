/*	****** Written by François Blas
 	****** Last Modification: 23/04/13 	
	
	Using the stm32f10x lib needs a configuration. You need to put STM32F10X_LD_VL in 
	Project\Option for Target\C/C++\Define 										
	
	The datasheet is needed to find the best option for your project and to know the global 
	fonctionnement of each peripherial.	*/ 

#include <stm32f10x_lib.h>
#include "ax12.h"

//---------------------------------------------------------
//----------------------enable_usart-----------------------
//---------------------------------------------------------

//Activate USARTx
void enable_usart(int usartx)
{
	switch(usartx)
	{
		case USART_1:
		USART1->CR1 |= (1<<13);
		break;
		
		case USART_2:
		USART2->CR1 |= (1<<13);
		break;
		
		case USART_3:
		USART3->CR1 |= (1<<13);
		break;
	}
}

//---------------------------------------------------------
//----------------------disable_usart----------------------
//---------------------------------------------------------

//Desactivate USARTx
void disable_usart(int usartx)
{
	switch(usartx)
	{
		case USART_1:
		USART1->CR1 &= ~(1<<13);
		break;
		
		case USART_2:
		USART2->CR1 &= ~(1<<13);
		break;
		
		case USART_3:
		USART3->CR1 &= ~(1<<13);
		break;
	}			
}

//---------------------------------------------------------
//-----------------------usart1_init-----------------------
//---------------------------------------------------------

/* Configure USART1 */
void usart1_init(Debit p_debit, Direction p_dir)
{
	/* AFIO Clock Enable */
	RCC->APB2ENR |= 0x00000001;
	/* USART1 Clock Enable */
	RCC->APB2ENR |= 0x00004000;	
	/* PORTB Clock Enable */
	RCC->APB2ENR |= 0x00000008;
	
	/* Remappage vers PB6 et PB7 */
	AFIO->MAPR |= 0x0004;
	
		
	/* Sélection de la direction des pins */
		if(p_dir==HALF_DUPLEX)
		{	
				/* HALF DUPLEX */
				/* PB6 en Alternate output open-drain  */
				GPIOB->CRL &= 0xF0FFFFFF;
				GPIOB->CRL |= 0xFD000000;
		}
		
		else
		{
			/* FULL DUPLEX */
			/* PB6 en Alternate output push-pull et PB7 floating input */
			GPIOB->CRL &= 0x00FFFFFF;
			GPIOB->CRL |= 0x49000000;	
		}
	
	/*Usart1 disable*/
	USART1->CR1 &= ~(1<<13);	
	
	/* Usart1 Enable, Transmitter Enable, Receiver Enable */
	USART1->CR1 |= 0x0000000C;	
	
	/* DMA Enable Transmitter, DMA Enable Receiver */
	USART1->CR3 |= 0x000000C0;
		
	/* Sélection Half/Full duplex */
	if (p_dir == HALF_DUPLEX) {USART1->CR3 |= 0x00000008;}
	
	/* Sélection baudrate */
	switch (p_debit)
	{
		case BAUD_9600:
			USART1->BRR=0x341;
			break;
		case BAUD_115200:
 			USART1->BRR=0x45; 
			break;
		case BAUD_500000:
			USART1->BRR=0x0010;
			break;
	}
	/* Autorisation des interruptions au niveau du processeur */
	NVIC->ISER[1] |= (1<<5);

}

//---------------------------------------------------------
//---------------------usart2_init-------------------------
//---------------------------------------------------------

/* Configure USART2 */
void usart2_init(Debit p_debit, Direction p_dir)
{
	/* AFIO Clock Enable */
	RCC->APB2ENR |= 0x00000001;
	/* USART2 Clock Enable */
	RCC->APB1ENR |= (1<<17);
	/* PORTA Clock Enable */
	RCC->APB2ENR |= 0x00000004;
	
	/* Sélection de la direction des pins */
		if(p_dir==HALF_DUPLEX)
		{
		/* HALF DUPLEX */
		/* PA2 en Alternate output open-drain  */
		GPIOA->CRL &= 0xFFFFF0FF;
		GPIOA->CRL |= 0x00000D00;
		}
		
		else
		{
		/* FULL DUPLEX */
		/* PA2 en Alternate output push-pull et PA3 floating input */
		GPIOA->CRL &= 0xFFFF00FF;
		GPIOA->CRL |= 0x00004900;
		}
	
	/*Usart2 disable*/
	USART2->CR1 &= ~(1<<13);	
	
	/* Usart2 Enable, Transmitter Enable, Receiver Enable */
	USART2->CR1 |= 0x0000000C;	
	
	/* DMA Enable Transmitter, DMA Enable Receiver */
	USART2->CR3 |= 0x000000C0;
		
	/* Sélection Half/Full duplex */
	if (p_dir == HALF_DUPLEX) {USART2->CR3 |= 0x00000008;}
	
	/* Sélection baudrate */
	switch (p_debit)
	{
		case BAUD_9600:
			USART2->BRR=0x341;
			break;
		case BAUD_115200:
 			USART2->BRR=0x45; 
			break;
		case BAUD_500000:
			USART2->BRR=0x0010;
			break;
	}
	/* Autorisation des interruptions au niveau du processeur */
	NVIC->ISER[1] |= (1<<6);

}

//---------------------------------------------------------
//----------------------usart3_init------------------------
//---------------------------------------------------------

/* Configure USART3 */
void usart3_init(Debit p_debit, Direction p_dir)
{
	/* AFIO Clock Enable */
	RCC->APB2ENR |= 0x00000001;
	/* USART3 Clock Enable */
	RCC->APB1ENR |= (1<<18);
	/* PORTC Clock Enable */
	RCC->APB2ENR |= (1<<4);
	
	/* Remappage vers PC10 et PC11 */
	AFIO->MAPR &=~(1<<5);
	AFIO->MAPR |=(1<<4);
		
	/* Sélection de la direction des pins */
		if(p_dir==HALF_DUPLEX)
		{
				/* HALF DUPLEX */
				/* PC10 en Alternate output open-drain  */
				GPIOC->CRH &= 0xFFFFF0FF;
				GPIOC->CRH |= 0x00000D00;
		}
		
		else
		{
				/* FULL DUPLEX */
				/* PC10 en Alternate output push-pull et PC11 floating input */
				GPIOC->CRH &= 0xFFFF00FF;
				GPIOC->CRH |= 0x00004900;
		}
	
	/*Usart3 disable*/
	USART3->CR1 &= ~(1<<13);	
	
	/* Usart3 Enable, Transmitter Enable, Receiver Enable */
	USART3->CR1 |= 0x0000000C;	
	
	/* DMA Enable Transmitter, DMA Enable Receiver */
	USART3->CR3 |= 0x000000C0;
		
	/* Sélection Half/Full duplex */
	if (p_dir == HALF_DUPLEX) {USART3->CR3 |= 0x00000008;}
	
	/* Sélection baudrate */
	switch (p_debit)
	{
		case BAUD_9600:
			USART3->BRR=0x341;
			break;
		case BAUD_115200:
 			USART3->BRR=0x45; 
			break;
		case BAUD_500000:
			USART3->BRR=0x0010;
			break;
	}
	/* Autorisation des interruptions au niveau du processeur */
	NVIC->ISER[1] |= (1<<7);
	
}

//---------------------------------------------------------
//----------------------send_byte--------------------------
//---------------------------------------------------------

//Send data (1 byte) with USART
void send_byte(int usartx,unsigned char byte)
{
	if (usartx == USART_1)
	{
		while ((USART1->SR & (1<<7)) != (1<<7));  // Wait for the TX gets ready to send a byte
		USART1->DR = byte;
	}
	else if (usartx == USART_2)
	{
		while ((USART2->SR & (1<<7)) != (1<<7));// Wait for the TX gets ready to send a byte
		USART2->DR = byte;
	}
	else if (usartx == USART_3)
	{
		while ((USART3->SR & (1<<7)) != (1<<7));  // Wait for the TX gets ready to send a byte
		USART3->DR = byte;
	}
	else {}	
}

//---------------------------------------------------------
//----------------------ax12_init--------------------------
//---------------------------------------------------------

//Initialize communication for AX12
void ax12_init(int usartx)
{
	switch(usartx)
	{
		case USART_1:
			usart1_init(BAUD_500000,HALF_DUPLEX);
		  enable_usart(USART_1);
		break;

		case USART_2:
			usart2_init(BAUD_500000,HALF_DUPLEX);
		  enable_usart(USART_2);
		break;

    case USART_3:
			usart3_init(BAUD_500000,HALF_DUPLEX);
		  enable_usart(USART_3);
    break;			
	}
}

//---------------------------------------------------------
//--------------------ax12_position------------------------
//---------------------------------------------------------

//Set the position of one AX12 
void ax12_position(int usartx, int id, int pos)
{
	int checksum1 = ~((id + 5 + 3 + 30 + (pos&0xFF) + ((pos&0xFF00)>>8)) % 256);

			 if(pos<160){pos=161;}//Range of position forbidden 
	else if(pos>871){pos=871;}
	else{pos=pos;}

		send_byte(usartx,0xff);//Initialize communication
		send_byte(usartx,0xff);
		send_byte(usartx,id); //ID of the AX12
		send_byte(usartx,0x05); //Length
		send_byte(usartx,0x03); //Write in the RAM of the AX12
		send_byte(usartx,0x1e); //Address AX12 in the RAM
		send_byte(usartx,(pos & 0x00FF));//Send the position
		send_byte(usartx,((pos & 0xFF00)>>8));
		send_byte(usartx,checksum1);//Verify 

	/* Have to send instructions 2 times */

		send_byte(usartx,0xff);
		send_byte(usartx,0xff);
		send_byte(usartx,id); 
		send_byte(usartx,0x05); 
		send_byte(usartx,0x03); 
		send_byte(usartx,0x1e); 
		send_byte(usartx,(pos & 0x00FF));
		send_byte(usartx,((pos & 0xFF00)>>8));
		send_byte(usartx,checksum1);
}

//---------------------------------------------------------
//------------------ax12_movingspeed-----------------------
//---------------------------------------------------------

//Set the speed of one ax12
void ax12_movingspeed(int usartx,int id,int speed)
{
		int checksum = ~((id + 5 + 3 + 32 + (speed&0xFF) + ((speed&0xFF00)>>8)) % 256);
	
		if(speed<1 || speed>1023){speed=1023;}//Values of speed forbidden
	
		send_byte(usartx,0xff);//Initialize communication
		send_byte(usartx,0xff);
		send_byte(usartx,id); //ID of the AX12
		send_byte(usartx,0x05); //Length 
		send_byte(usartx,0x03); //Write in the RAM of the AX12
		send_byte(usartx,0x20); //Address AX12 in the RAM
		send_byte(usartx,(speed & 0x00FF));//Send the speed
		send_byte(usartx,((speed & 0xFF00)>>8));
		send_byte(usartx,checksum);//Verify 

	/* Have to send instructions 2 times */

		send_byte(usartx,0xff);
		send_byte(usartx,0xff);
		send_byte(usartx,id); //ID
		send_byte(usartx,0x05); //Length
		send_byte(usartx,0x03); //Write
		send_byte(usartx,0x20); //Addr AX12
		send_byte(usartx,(speed & 0x00FF));
		send_byte(usartx,((speed & 0xFF00)>>8));
		send_byte(usartx,checksum);
}

//---------------------------------------------------------
//------------------------delay----------------------------
//---------------------------------------------------------

//wait
void delay(int del)
{
	int i=0;
	for(i=0;i<del;i++){}
}

//---------------------------------------------------------
//-----------------ax12_torquelimit------------------------
//---------------------------------------------------------

//Set the torque of one ax12
void ax12_torquelimit(int usartx,int id,int torque)
{
		int checksum2 = ~((id + 5 + 3 + 34 + (torque&0xFF) + ((torque&0xFF00)>>8)) % 256);
	
		if(torque<1 || torque>1023){torque=1023;}//values of torque forbidden
	
		send_byte(usartx,0xff);//Initialize communication
		send_byte(usartx,0xff);
		send_byte(usartx,id); //ID of the AX12
		send_byte(usartx,0x05); //Length 
		send_byte(usartx,0x03); //Write in the RAM of the AX12
		send_byte(usartx,0x22); //Address AX12 in the RAM
		send_byte(usartx,(torque & 0x00FF));//Send the torque
		send_byte(usartx,((torque & 0xFF00)>>8));
		send_byte(usartx,checksum2);//Verify 

	/* Have to send instructions 2 times */

		send_byte(usartx,0xff);
		send_byte(usartx,0xff);
		send_byte(usartx,id); //ID
		send_byte(usartx,0x05); //Length
		send_byte(usartx,0x03); //Write
		send_byte(usartx,0x22); //Addr AX12
		send_byte(usartx,(torque & 0x00FF));
		send_byte(usartx,((torque & 0xFF00)>>8));
		send_byte(usartx,checksum2);
}

//---------------------------------------------------------
//-------------------receive_byte--------------------------
//---------------------------------------------------------

//Reveive data from USARTx
unsigned char receive_byte(int usartx)
{
	if (usartx == USART_1)
	{
		while ((USART1->SR & (1<<5))!= (1<<5)); // Wait for a data  
   	return (USART1->DR & 0x1FF);
	}
	else if (usartx == USART_2)
	{
		while ((USART2->SR & (1<<5))!= (1<<5)); // Wait for a data
		return (USART2->DR & 0x1FF);
	}
	else if (usartx == USART_3)
	{
		while ((USART3->SR & (1<<5)) != (1<<5));  // Wait for a data
		return (USART3->DR & 0x1FF);
	}
	else
	{
	return 0;
	}
}

//---------------------------------------------------------
//------------------ax12_write_register--------------------
//---------------------------------------------------------

void ax12_write_register2(int usartx,int id,int reg,int value)
{
		int checksum3 = ~((id + 5 + 3 + reg + (value&0xFF) + ((value&0xFF00)>>8)) % 256);
	
		send_byte(usartx,0xff);//Initialize communication
		send_byte(usartx,0xff);
		send_byte(usartx,id); //ID of the AX12
		send_byte(usartx,0x05); //Length 
		send_byte(usartx,0x03); //Write in the RAM of the AX12
		send_byte(usartx,reg); //Address AX12 in the RAM
		send_byte(usartx,(value & 0x00FF));//Send the torque
		send_byte(usartx,((value & 0xFF00)>>8));
		send_byte(usartx,checksum3);//Verify 

	/* Have to send instructions 2 times */

		send_byte(usartx,0xff);
		send_byte(usartx,0xff);
		send_byte(usartx,id); //ID
		send_byte(usartx,0x05); //Length
		send_byte(usartx,0x03); //Write
		send_byte(usartx,0x22); //Addr AX12
		send_byte(usartx,(value & 0x00FF));
		send_byte(usartx,((value & 0xFF00)>>8));
		send_byte(usartx,checksum3);
}

//---------------------------------------------------------
//-------------------ax12_write_register-------------------
//---------------------------------------------------------

void ax12_write_register(int usartx,int id,int reg,int value)
{
		int checksum4 = ~((id + 4 + 3 + reg + (value&0xFF)) % 256);
	
		send_byte(usartx,0xff);//Initialize communication
		send_byte(usartx,0xff);
		send_byte(usartx,id); //ID of the AX12
		send_byte(usartx,0x04); //Length 
		send_byte(usartx,0x03); //Write in the RAM of the AX12
		send_byte(usartx,reg); //Address AX12 in the RAM
		send_byte(usartx,(value & 0x00FF));//Send the torque
		send_byte(usartx,checksum4);//Verify 

	/* Have to send instructions 2 times */

		send_byte(usartx,0xff);
		send_byte(usartx,0xff);
		send_byte(usartx,id); //ID
		send_byte(usartx,0x04); //Length
		send_byte(usartx,0x03); //Write
		send_byte(usartx,0x22); //Addr AX12
		send_byte(usartx,(value & 0x00FF));
		send_byte(usartx,checksum4);
}

//---------------------------------------------------------
//--------------------ax12_reset---------------------------
//---------------------------------------------------------

void ax12_reset(int usartx)
{
		send_byte(usartx,0xff);//Initialize communication
		send_byte(usartx,0xff);
		send_byte(usartx,0x00); //ID to reset the AX12
		send_byte(usartx,0x02); //Length 
		send_byte(usartx,0x06); //Instruction = reset
		send_byte(usartx,0xf7);//Verify 
	
	/* Have to send instructions 2 times */
	
		send_byte(usartx,0xff);
		send_byte(usartx,0xff);
		send_byte(usartx,0x00); //ID to reset the AX12
		send_byte(usartx,0x02); //Length 
		send_byte(usartx,0x06); //Instruction = reset
		send_byte(usartx,0xf7);//Verify 
}

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
