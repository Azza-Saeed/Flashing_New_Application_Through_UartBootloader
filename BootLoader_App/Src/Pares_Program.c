/*
 * Pares_Program.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Azza Saeed
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "Parse_Interface.h"
#include "FPEC_Interface.h"

u16 Data[100];
u32 Address=0x08000000;

void Parse_voidRecord(u16 *Copy_Record)
{
	switch(Copy_Record[8])
	{
	case '0':
		Parse_voidData(Data);
		break;
	case '4':
		Parse_voidUpperAddress(Data);
		break;
	}
}
void Parse_voidData(u16 *Copy_Data)
{
	u8 CountLow,CountHigh,CC,i;
	u8 Digit0,Digit1,Digit2,Digit3;
	u8 counter=0;

	/* Character Count */
	CountLow= Convert_u8ToHex(Copy_Data[1]);
	CountHigh= Convert_u8ToHex(Copy_Data[2]);
	CC= (CountHigh<<4) | CountLow;
   /* Address */
	Digit0 = Convert_u8ToHex(Copy_Data[3]);
	Digit1 = Convert_u8ToHex(Copy_Data[4]);
	Digit2 = Convert_u8ToHex(Copy_Data[5]);
	Digit3 = Convert_u8ToHex(Copy_Data[6]);

	/* Clear low part of address */
	Address = Address | 0xffff0000;
	Address = Address | (Digit3) | (Digit2<<4) | (Digit1<<8) | (Digit0<<12);

	/* Write Data */
	for(i=0;i<CC/2;i++)
	{
		/* Write 16 bit at time */
		Digit0 = Convert_u8ToHex(Copy_Data[4*i+9]);
		Digit1 = Convert_u8ToHex(Copy_Data[4*i+10]);
		Digit2 = Convert_u8ToHex(Copy_Data[4*i+11]);
		Digit3 = Convert_u8ToHex(Copy_Data[4*i+12]);

		Data[counter] = (Digit3 << 8) | (Digit2 << 12) | (Digit1) | (Digit0<<4);
		counter++;
	}
	FPEC_voidFlashWrite(Address, Data, CC/2);

}
void Parse_voidUpperAddress(u16 *Copy_Data)
{
	u8 Digit0,Digit1,Digit2,Digit3;

	/* Address**/
	Digit0 = Convert_u8ToHex(Copy_Data[3]);
	Digit1 = Convert_u8ToHex(Copy_Data[4]);
	Digit2 = Convert_u8ToHex(Copy_Data[5]);
	Digit3 = Convert_u8ToHex(Copy_Data[6]);
	/* Clear Low Part of Address */
	Address = Address & (u32)0x0000FFFF;
	Address = Address | (u32)((u32)(Digit3 << 28) | (u32)(Digit2 << 24) | (u32)(Digit1 << 20) | (u32)(Digit0 << 16));
}
u8 Convert_u8ToHex(u8 data)
{
	u8 Result;
	if( (data>=48) && (data<=57)) /* from 0 to 9 */
	{
		Result=data-48;
	}else{
		Result=data-55; /* from A to F */
	}
	return Result;
}
