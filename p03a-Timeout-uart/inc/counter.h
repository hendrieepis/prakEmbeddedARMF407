/*
 * counter.h
 *
 *  Created on: Sep 27, 2017
 *      Author: hendri
 */

#ifndef COUNTER_H_
#define COUNTER_H_
#include <stdint.h>
//counter.h dan counter.c
uint8_t CounterGetValue(void);
void counterShow(void);
void CounterUpdate(void);
void CounterZero(void);
#endif /* COUNTER_H_ */
