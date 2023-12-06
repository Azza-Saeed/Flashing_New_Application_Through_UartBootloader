/*
 * FPEC_Program.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Azza Saeed
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "FPEC_Interface.h"
#include "FPEC_Private.h"
#include "FPEC_Config.h"

void FPEC_voidFlashWrite(u32 Address, u16* Copy_Data, u8 Length)
{
	u8 i;
	volatile u16 Returned_Data;

	while( GET_BIT(FPEC->SR,0) == 1 );
	 /* Lock Operation */
	if( GET_BIT(FPEC->CR,7 ) == 1 )
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}
	/* Write Operation */
	for(i=0;i<Length;i++)
	{
		/* Enable programming */
		SET_BIT(FPEC->CR,0);

		Returned_Data=Copy_Data[i];
		*((volatile u16*)Address)=Copy_Data[i];
		Address+=2;

		/* Stop Operation */
		SET_BIT(FPEC->SR,5);
		CLR_BIT(FPEC->CR,0);

	}
}

void FPEC_voidFlashErasePage(u8 PageNumber)
{
	while( GET_BIT(FPEC->SR,0) == 1 );

	/* lOCK OPERATION */
	if( GET_BIT( FPEC->CR,7) == 1 )
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}

	/* Enable erase operation */
	SET_BIT(FPEC->CR,1);

	/* SET ADDRESS */
	FPEC->AR= (u32)(PageNumber * 1024)+0x08000000;

	/* Start Erase */
	SET_BIT(FPEC->CR,6);

	while( GET_BIT( FPEC->SR,0) == 1 );

	/* Stop operation */
	SET_BIT(FPEC->SR,5);
	CLR_BIT(FPEC->CR,1);
}

void FPEC_voidEraseSection(void)
{
	u8 i;

	for( i=START_App;i<END_APP;i++ )
	{
		FPEC_voidFlashErasePage(i);
	}
}

