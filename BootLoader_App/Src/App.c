/*
 * App.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Azza Saeed
 */
#include "App.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "USART_interface.h"
#include "STK_interface.h"
#include "DIO_interface.h"
#include "FPEC_Interface.h"
#include "Parse_Interface.h"

volatile u8 Receive_Buffer[100];
volatile u8 Counter = 0;

volatile First_Time = 1;

volatile u8  Time_Out   = 0;
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08001000;

	addr_to_call = *(Function_t*)(0x08001004);
	addr_to_call();
}

void App_Init(void)
{
	RCC_voidInitSysClock(); /* HSI */
	RCC_voidEnableClock(RCC_APB2,14); /* USART1 */
	RCC_voidEnableClock(RCC_APB2,2);  /* PortA  */
	RCC_voidEnableClock(RCC_AHB,4);   /* FPEC   */


	MGPIO_VidSetPinDirection(GPIOA,9,0b1010);   /* TX AFPP */
	MGPIO_VidSetPinDirection(GPIOA,10,0b0100);  /* RC Input Floating */

	MUSART1_voidInit();

	MSTK_voidInit();
}
void App_Main(void)
{
	u8 Status;
	MSTK_voidSetIntervalSingle(9000000,func);
    while( Time_Out == 0 )
    {
    	Status = MUSART1_u8Receive( &(Receive_Buffer[Counter]));
    	if( Status == 1 )
    	{
    		MSTK_voidStopInterval();

    		if( Receive_Buffer[Counter] == '\n' )
    		{
    			if ( First_Time == 1 )
    			{
    				FPEC_voidEraseSection();
    				First_Time=0;
    			}
    			Parse_voidRecord(Receive_Buffer);
    			MUSART1_voidTransmit("ok");
    			Counter=0;
    		}else{
    			Counter++;
    		}
			MSTK_voidSetIntervalSingle(9000000,func);
    	}else{
    		/* Do Nothing */
    	}
    }
}
