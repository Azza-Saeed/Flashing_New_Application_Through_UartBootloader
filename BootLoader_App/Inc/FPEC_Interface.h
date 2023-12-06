/*
 * FPEC_Interface.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Azza Saeed
 */

#ifndef FPEC_INTERFACE_H_
#define FPEC_INTERFACE_H_

#define START_App 4
#define END_APP 64

void FPEC_voidEraseSection(void);

void FPEC_voidFlashErasePage(u8 PageNumber);

void FPEC_voidFlashWrite(u32 Address, u16* Copy_Data, u8 Length);

#endif /* FPEC_INTERFACE_H_ */
