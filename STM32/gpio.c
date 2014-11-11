/*	****** Written by François Blas
 	****** Last Modification: 25/05/13

	Using the stm32f10x lib needs a configuration. You need to put STM32F10X_LD_VL in
	Project\Option for Target\C/C++\Define

	The datasheet is needed to find the best option for your project and to know the global
	fonctionnement of each peripherial.	*/

#include <stm32f10x_lib.h>
#include "gpio.h"

//---------------------------------------------------------
//----------------------gpio_clock-------------------------
//---------------------------------------------------------

void gpio_clock(int gpiox)
{
	switch(gpiox)
	{
		case GPIO_A:
		RCC->APB2ENR |= 0x00000004;
		break;

		case GPIO_B:
		RCC->APB2ENR |= 0x00000008;
		break;

		case GPIO_C:
		RCC->APB2ENR |= 0x00000010;
		break;
	}
}

//---------------------------------------------------------
//----------------------gpioa_crl--------------------------
//---------------------------------------------------------

void gpioa_crl(int gpiox, int num, int speed, int mode)
{

					switch(mode)
					{
						case ANALOGUE:
						GPIOA->CRL &= ~(1<<((num*4)+2));
						GPIOA->CRL &= ~(1<<((num*4)+3));
						break;

						case FLOATING:
						GPIOA->CRL &= ~(1<<((num*4)+2));
						GPIOA->CRL |= (1<<((num*4)+2));
						GPIOA->CRL &= ~(1<<((num*4)+3));
						break;

						case PULLUPDOWN:
						GPIOA->CRL &= ~(1<<((num*4)+2));
						GPIOA->CRL &= ~(1<<((num*4)+3));
						GPIOA->CRL |= (1<<((num*4)+3));
						break;

							case GENERAL_PUSHPULL:
							GPIOA->CRL &= ~(1<<((num*4)+2));
							GPIOA->CRL &= ~(1<<((num*4)+3));
							break;

							case GENERAL_OPENDRAIN:
							GPIOA->CRL &= ~(1<<((num*4)+2));
							GPIOA->CRL |= (1<<((num*4)+2));
							GPIOA->CRL &= ~(1<<((num*4)+3));
							break;

							case ALTERNATE_PUSHPULL:
							GPIOA->CRL &= ~(1<<((num*4)+2));
							GPIOA->CRL &= ~(1<<((num*4)+3));
							GPIOA->CRL |= (1<<((num*4)+3));
							break;

							case ALTERNATE_OPENDRAIN:
							GPIOA->CRL &= ~(1<<((num*4)+2));
							GPIOA->CRL &= ~(1<<((num*4)+3));
							GPIOA->CRL |= (1<<((num*4)+2));
							GPIOA->CRL |= (1<<((num*4)+3));
							break;
						}

						switch(speed)
						{
							case SPEED_10:
							GPIOA->CRL &= ~(1<<(num*4));
							GPIOA->CRL &= ~(1<<((num*4)+1));
							GPIOA->CRL |= (1<<(num*4));
							break;

							case SPEED_2:
							GPIOA->CRL &= ~(1<<(num*4));
							GPIOA->CRL &= ~(1<<((num*4)+1));
							GPIOA->CRL |= (1<<((num*4)+1));
							break;

							case SPEED_50:
							GPIOA->CRL &= ~(1<<(num*4));
							GPIOA->CRL &= ~(1<<((num*4)+1));
							GPIOA->CRL |= (1<<(num*4));
							GPIOA->CRL |= (1<<((num*4)+1));
							break;

							case SPEED_NO:
							GPIOA->CRL &= ~(1<<(num*4));
							GPIOA->CRL &= ~(1<<((num*4)+1));
							break;
							}

}

//---------------------------------------------------------
//----------------------gpioa_crh--------------------------
//---------------------------------------------------------

void gpioa_crh(int gpiox, int num, int speed, int mode)
{
		num = num - 8;

			switch(mode)
					{
						case ANALOGUE:
						GPIOA->CRH &= ~(1<<((num*4)+2));
						GPIOA->CRH &= ~(1<<((num*4)+3));
						break;

						case FLOATING:
						GPIOA->CRH &= ~(1<<((num*4)+2));
						GPIOA->CRH |= (1<<((num*4)+2));
						GPIOA->CRH &= ~(1<<((num*4)+3));
						break;

						case PULLUPDOWN:
						GPIOA->CRH &= ~(1<<((num*4)+2));
						GPIOA->CRH &= ~(1<<((num*4)+3));
						GPIOA->CRH |= (1<<((num*4)+3));
						break;

							case GENERAL_PUSHPULL:
							GPIOA->CRH &= ~(1<<((num*4)+2));
							GPIOA->CRH &= ~(1<<((num*4)+3));
							break;

							case GENERAL_OPENDRAIN:
							GPIOA->CRH &= ~(1<<((num*4)+2));
							GPIOA->CRH |= (1<<((num*4)+2));
							GPIOA->CRH &= ~(1<<((num*4)+3));
							break;

							case ALTERNATE_PUSHPULL:
							GPIOA->CRH &= ~(1<<((num*4)+2));
							GPIOA->CRH &= ~(1<<((num*4)+3));
							GPIOA->CRH |= (1<<((num*4)+3));
							break;

							case ALTERNATE_OPENDRAIN:
							GPIOA->CRH &= ~(1<<((num*4)+2));
							GPIOA->CRH &= ~(1<<((num*4)+3));
							GPIOA->CRH |= (1<<((num*4)+2));
							GPIOA->CRH |= (1<<((num*4)+3));
							break;
						}

						switch(speed)
						{
							case SPEED_10:
							GPIOA->CRH &= ~(1<<(num*4));
							GPIOA->CRH &= ~(1<<((num*4)+1));
							GPIOA->CRH |= (1<<(num*4));
							break;

							case SPEED_2:
							GPIOA->CRH &= ~(1<<(num*4));
							GPIOA->CRH &= ~(1<<((num*4)+1));
							GPIOA->CRH |= (1<<((num*4)+1));
							break;

							case SPEED_50:
							GPIOA->CRH &= ~(1<<(num*4));
							GPIOA->CRH &= ~(1<<((num*4)+1));
							GPIOA->CRH |= (1<<(num*4));
							GPIOA->CRH |= (1<<((num*4)+1));
							break;

							case SPEED_NO:
							GPIOA->CRH &= ~(1<<(num*4));
							GPIOA->CRH &= ~(1<<((num*4)+1));
							break;
							}
}

//---------------------------------------------------------
//----------------------gpiob_crl--------------------------
//---------------------------------------------------------

void gpiob_crl(int gpiox, int num, int speed, int mode)
{
				switch(mode)
					{
						case ANALOGUE:
						GPIOB->CRL &= ~(1<<((num*4)+2));
						GPIOB->CRL &= ~(1<<((num*4)+3));
						break;

						case FLOATING:
						GPIOB->CRL &= ~(1<<((num*4)+2));
						GPIOB->CRL |= (1<<((num*4)+2));
						GPIOB->CRL &= ~(1<<((num*4)+3));
						break;

						case PULLUPDOWN:
						GPIOB->CRL &= ~(1<<((num*4)+2));
						GPIOB->CRL &= ~(1<<((num*4)+3));
						GPIOB->CRL |= (1<<((num*4)+3));
						break;

							case GENERAL_PUSHPULL:
							GPIOB->CRL &= ~(1<<((num*4)+2));
							GPIOB->CRL &= ~(1<<((num*4)+3));
							break;

							case GENERAL_OPENDRAIN:
							GPIOB->CRL &= ~(1<<((num*4)+2));
							GPIOB->CRL |= (1<<((num*4)+2));
							GPIOB->CRL &= ~(1<<((num*4)+3));
							break;

							case ALTERNATE_PUSHPULL:
							GPIOB->CRL &= ~(1<<((num*4)+2));
							GPIOB->CRL &= ~(1<<((num*4)+3));
							GPIOB->CRL |= (1<<((num*4)+3));
							break;

							case ALTERNATE_OPENDRAIN:
							GPIOB->CRL &= ~(1<<((num*4)+2));
							GPIOB->CRL &= ~(1<<((num*4)+3));
							GPIOB->CRL |= (1<<((num*4)+2));
							GPIOB->CRL |= (1<<((num*4)+3));
							break;
						}

						switch(speed)
						{
							case SPEED_10:
							GPIOB->CRL &= ~(1<<(num*4));
							GPIOB->CRL &= ~(1<<((num*4)+1));
							GPIOB->CRL |= (1<<(num*4));
							break;

							case SPEED_2:
							GPIOB->CRL &= ~(1<<(num*4));
							GPIOB->CRL &= ~(1<<((num*4)+1));
							GPIOB->CRL |= (1<<((num*4)+1));
							break;

							case SPEED_50:
							GPIOB->CRL &= ~(1<<(num*4));
							GPIOB->CRL &= ~(1<<((num*4)+1));
							GPIOB->CRL |= (1<<(num*4));
							GPIOB->CRL |= (1<<((num*4)+1));
							break;

							case SPEED_NO:
							GPIOB->CRL &= ~(1<<(num*4));
							GPIOB->CRL &= ~(1<<((num*4)+1));
							break;
							}
}

//---------------------------------------------------------
//----------------------gpiob_crh--------------------------
//---------------------------------------------------------

void gpiob_crh(int gpiox, int num, int speed, int mode)
{
		num = num - 8;

							switch(mode)
					{
						case ANALOGUE:
						GPIOB->CRH &= ~(1<<((num*4)+2));
						GPIOB->CRH &= ~(1<<((num*4)+3));
						break;

						case FLOATING:
						GPIOB->CRH &= ~(1<<((num*4)+2));
						GPIOB->CRH |= (1<<((num*4)+2));
						GPIOB->CRH &= ~(1<<((num*4)+3));
						break;

						case PULLUPDOWN:
						GPIOB->CRH &= ~(1<<((num*4)+2));
						GPIOB->CRH &= ~(1<<((num*4)+3));
						GPIOB->CRH |= (1<<((num*4)+3));
						break;

							case GENERAL_PUSHPULL:
							GPIOB->CRH &= ~(1<<((num*4)+2));
							GPIOB->CRH &= ~(1<<((num*4)+3));
							break;

							case GENERAL_OPENDRAIN:
							GPIOB->CRH &= ~(1<<((num*4)+2));
							GPIOB->CRH |= (1<<((num*4)+2));
							GPIOB->CRH &= ~(1<<((num*4)+3));
							break;

							case ALTERNATE_PUSHPULL:
							GPIOB->CRH &= ~(1<<((num*4)+2));
							GPIOB->CRH &= ~(1<<((num*4)+3));
							GPIOB->CRH |= (1<<((num*4)+3));
							break;

							case ALTERNATE_OPENDRAIN:
							GPIOB->CRH &= ~(1<<((num*4)+2));
							GPIOB->CRH &= ~(1<<((num*4)+3));
							GPIOB->CRH |= (1<<((num*4)+2));
							GPIOB->CRH |= (1<<((num*4)+3));
							break;
						}

						switch(speed)
						{
							case SPEED_10:
							GPIOB->CRH &= ~(1<<(num*4));
							GPIOB->CRH &= ~(1<<((num*4)+1));
							GPIOB->CRH |= (1<<(num*4));
							break;

							case SPEED_2:
							GPIOB->CRH &= ~(1<<(num*4));
							GPIOB->CRH &= ~(1<<((num*4)+1));
							GPIOB->CRH |= (1<<((num*4)+1));
							break;

							case SPEED_50:
							GPIOB->CRH &= ~(1<<(num*4));
							GPIOB->CRH &= ~(1<<((num*4)+1));
							GPIOB->CRH |= (1<<(num*4));
							GPIOB->CRH |= (1<<((num*4)+1));
							break;

							case SPEED_NO:
							GPIOB->CRH &= ~(1<<(num*4));
							GPIOB->CRH &= ~(1<<((num*4)+1));
							break;
							}
}

//---------------------------------------------------------
//----------------------gpioc_crl--------------------------
//---------------------------------------------------------

void gpioc_crl(int gpiox, int num, int speed, int mode)
{
			switch(mode)
					{
						case ANALOGUE:
						GPIOC->CRL &= ~(1<<((num*4)+2));
						GPIOC->CRL &= ~(1<<((num*4)+3));
						break;

						case FLOATING:
						GPIOC->CRL &= ~(1<<((num*4)+2));
						GPIOC->CRL |= (1<<((num*4)+2));
						GPIOC->CRL &= ~(1<<((num*4)+3));
						break;

						case PULLUPDOWN:
						GPIOC->CRL &= ~(1<<((num*4)+2));
						GPIOC->CRL &= ~(1<<((num*4)+3));
						GPIOC->CRL |= (1<<((num*4)+3));
						break;

							case GENERAL_PUSHPULL:
							GPIOC->CRL &= ~(1<<((num*4)+2));
							GPIOC->CRL &= ~(1<<((num*4)+3));
							break;

							case GENERAL_OPENDRAIN:
							GPIOC->CRL &= ~(1<<((num*4)+2));
							GPIOC->CRL |= (1<<((num*4)+2));
							GPIOC->CRL &= ~(1<<((num*4)+3));
							break;

							case ALTERNATE_PUSHPULL:
							GPIOC->CRL &= ~(1<<((num*4)+2));
							GPIOC->CRL &= ~(1<<((num*4)+3));
							GPIOC->CRL |= (1<<((num*4)+3));
							break;

							case ALTERNATE_OPENDRAIN:
							GPIOC->CRL &= ~(1<<((num*4)+2));
							GPIOC->CRL &= ~(1<<((num*4)+3));
							GPIOC->CRL |= (1<<((num*4)+2));
							GPIOC->CRL |= (1<<((num*4)+3));
							break;
						}

						switch(speed)
						{
							case SPEED_10:
							GPIOC->CRL &= ~(1<<(num*4));
							GPIOC->CRL &= ~(1<<((num*4)+1));
							GPIOC->CRL |= (1<<(num*4));
							break;

							case SPEED_2:
							GPIOC->CRL &= ~(1<<(num*4));
							GPIOC->CRL &= ~(1<<((num*4)+1));
							GPIOC->CRL |= (1<<((num*4)+1));
							break;

							case SPEED_50:
							GPIOC->CRL &= ~(1<<(num*4));
							GPIOC->CRL &= ~(1<<((num*4)+1));
							GPIOC->CRL |= (1<<(num*4));
							GPIOC->CRL |= (1<<((num*4)+1));
							break;

							case SPEED_NO:
							GPIOC->CRL &= ~(1<<(num*4));
							GPIOC->CRL &= ~(1<<((num*4)+1));
							break;
							}
}

//---------------------------------------------------------
//----------------------gpioc_crh--------------------------
//---------------------------------------------------------

void gpioc_crh(int gpiox, int num, int speed, int mode)
{
		num = num - 8;

					switch(mode)
					{
						case ANALOGUE:
						GPIOC->CRH &= ~(1<<((num*4)+2));
						GPIOC->CRH &= ~(1<<((num*4)+3));
						break;

						case FLOATING:
						GPIOC->CRH &= ~(1<<((num*4)+2));
						GPIOC->CRH |= (1<<((num*4)+2));
						GPIOC->CRH &= ~(1<<((num*4)+3));
						break;

						case PULLUPDOWN:
						GPIOC->CRH &= ~(1<<((num*4)+2));
						GPIOC->CRH &= ~(1<<((num*4)+3));
						GPIOC->CRH |= (1<<((num*4)+3));
						break;

							case GENERAL_PUSHPULL:
							GPIOC->CRH &= ~(1<<((num*4)+2));
							GPIOC->CRH &= ~(1<<((num*4)+3));
							break;

							case GENERAL_OPENDRAIN:
							GPIOC->CRH &= ~(1<<((num*4)+2));
							GPIOC->CRH |= (1<<((num*4)+2));
							GPIOC->CRH &= ~(1<<((num*4)+3));
							break;

							case ALTERNATE_PUSHPULL:
							GPIOC->CRH &= ~(1<<((num*4)+2));
							GPIOC->CRH &= ~(1<<((num*4)+3));
							GPIOC->CRH |= (1<<((num*4)+3));
							break;

							case ALTERNATE_OPENDRAIN:
							GPIOC->CRH &= ~(1<<((num*4)+2));
							GPIOC->CRH &= ~(1<<((num*4)+3));
							GPIOC->CRH |= (1<<((num*4)+2));
							GPIOC->CRH |= (1<<((num*4)+3));
							break;
						}

						switch(speed)
						{
							case SPEED_10:
							GPIOC->CRH &= ~(1<<(num*4));
							GPIOC->CRH &= ~(1<<((num*4)+1));
							GPIOC->CRH |= (1<<(num*4));
							break;

							case SPEED_2:
							GPIOC->CRH &= ~(1<<(num*4));
							GPIOC->CRH &= ~(1<<((num*4)+1));
							GPIOC->CRH |= (1<<((num*4)+1));
							break;

							case SPEED_50:
							GPIOC->CRH &= ~(1<<(num*4));
							GPIOC->CRH &= ~(1<<((num*4)+1));
							GPIOC->CRH |= (1<<(num*4));
							GPIOC->CRH |= (1<<((num*4)+1));
							break;

							case SPEED_NO:
							GPIOC->CRH &= ~(1<<(num*4));
							GPIOC->CRH &= ~(1<<((num*4)+1));
							break;
							}
}

//---------------------------------------------------------
//----------------------gpio_config------------------------
//---------------------------------------------------------

void gpio_config(int gpiox, int numport, int speed, int mode)
{
	switch(gpiox)
	{
		case GPIO_A:
			gpio_clock(GPIO_A);
			if(numport<8 && numport>=0){gpioa_crl(GPIO_A,numport,speed,mode);}
			else if(numport<16 && numport>7){gpioa_crh(GPIO_A,numport,speed,mode);}
			else{}
		break;

		case GPIO_B:
			gpio_clock(GPIO_B);
			if(numport<8 && numport>=0){gpiob_crl(GPIO_B,numport,speed,mode);}
			else if(numport<16 && numport>7){gpiob_crh(GPIO_B,numport,speed,mode);}
			else{}
		break;

		case GPIO_C:
			gpio_clock(GPIO_C);
			if(numport<8 && numport>=0){gpioc_crl(GPIO_C,numport,speed,mode);}
			else if(numport<16 && numport>7){gpioc_crh(GPIO_C,numport,speed,mode);}
			else{}
		break;
	}
}

//---------------------------------------------------------
//----------------------gpio_bsrr--------------------------
//---------------------------------------------------------

void gpio_bsrr(int gpiox, int num, int action)
{
	switch(gpiox)
	{
		case GPIO_A:
			if(action==SET)
				{GPIOA->BSRR &= ~(1<<num);
				 GPIOA->BSRR |= (1<<num);}
			else if(action==RESET)
				{GPIOA->BSRR &= ~(1<<(num+16));
				 GPIOA->BSRR |= (1<<(num+16));}
			else{}
		break;

		case GPIO_B:
			if(action==SET)
				{GPIOB->BSRR &= ~(1<<num);
				 GPIOB->BSRR |= (1<<num);}
			else if(action==RESET)
				{GPIOB->BSRR &= ~(1<<(num+16));
				 GPIOB->BSRR |= (1<<(num+16));}
			else{}
		break;

		case GPIO_C:
			if(action==SET)
				{GPIOC->BSRR &= ~(1<<num);
				 GPIOC->BSRR |= (1<<num);}
			else if(action==RESET)
				{GPIOC->BSRR &= ~(1<<(num+16));
				 GPIOC->BSRR |= (1<<(num+16));}
			else{}
		break;
	}
}

//---------------------------------------------------------
//----------------------gpio_idr---------------------------
//---------------------------------------------------------

int gpio_idr(int gpiox, int num)
{
	if(num<0 || num>15){num=0;}

	if(gpiox==GPIO_A)
	{
		if((GPIOA->IDR & (1<<num)) == 0 ){return 0;}
		else{return 1;}
	}

	else if(gpiox==GPIO_B)
	{
		if((GPIOB->IDR & (1<<num)) == 0 ){return 0;}
		else{return 1;}
	}

	else if(gpiox==GPIO_C)
	{
		if((GPIOC->IDR & (1<<num)) == 0 ){return 0;}
		else{return 1;}
	}

	else{return 42;}
}

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------

