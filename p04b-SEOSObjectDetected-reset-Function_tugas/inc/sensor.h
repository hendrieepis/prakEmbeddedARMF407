/*
 * sensor.h
 *
 *  Created on: Sep 27, 2017
 *      Author: hendri
 */

#ifndef SENSOR_H_
#define SENSOR_H_
#include "stdint.h"
uint8_t sensorDetected(void);
uint8_t sensorDetectedTimeout(void);
uint8_t resetDetected(void);


#endif /* SENSOR_H_ */
