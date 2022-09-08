/*
 * bitOperations.h
 *
 * Created: 22/7/2020 23:15:38
 *  Author: Jims
 */ 


#ifndef BITOPERATIONS_H_
#define BITOPERATIONS_H_

#define _CONCAT(A,B) A##B
#define PORT(x) _CONCAT(PORT,x)
#define PIN(x) _CONCAT(PIN,x)
#define DDR(x) _CONCAT(DDR,x)

#define SET_BIT(byte,bit) (byte |= (1<<bit))
#define CLEAR_BIT(byte,bit) (byte &= ~(1<<bit))
#define GET_BIT(byte,bit) ( (byte&(1<<bit)) !=0 )
#define TOGGLE_BIT(byte,bit) ( (byte ^= (1<<bit)) )



#endif /* bitOperations_H_ */