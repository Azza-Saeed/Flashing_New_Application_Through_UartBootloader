/********************************************************
 * BIT_MATH.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Azza Saeed
*******************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR,BIT)          VAR |=  (1 << (BIT))
#define CLR_BIT(VAR,BIT)          VAR &= ~(1 << (BIT)) 
#define GET_BIT(VAR,BIT)          ((VAR >> BIT) & 1  )
#define TOG_BIT(VAR,BIT)          VAR ^=  (1 << (BIT))


#endif 
