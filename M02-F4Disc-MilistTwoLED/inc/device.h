/*
 * device.h
 *
 *  Created on: Oct 1, 2018
 *      Author: hendri
 */

#ifndef DEVICE_H_
#define DEVICE_H_
//  start device.h
//define General IO on Development Board
#define bar3_Pin GPIO_PIN_2
#define bar3_GPIO_Port GPIOE
#define bar5_Pin GPIO_PIN_4
#define bar5_GPIO_Port GPIOE
#define bar4_Pin GPIO_PIN_5
#define bar4_GPIO_Port GPIOE
#define bar7_Pin GPIO_PIN_6
#define bar7_GPIO_Port GPIOE
#define bar6_Pin GPIO_PIN_13
#define bar6_GPIO_Port GPIOC
#define bar9_Pin GPIO_PIN_14
#define bar9_GPIO_Port GPIOC
#define bar8_Pin GPIO_PIN_15
#define bar8_GPIO_Port GPIOC
#define pbUp_Pin GPIO_PIN_4
#define pbUp_GPIO_Port GPIOC
#define pbRight_Pin GPIO_PIN_5
#define pbRight_GPIO_Port GPIOC
#define pbDown_Pin GPIO_PIN_0
#define pbDown_GPIO_Port GPIOB
#define pbLeft_Pin GPIO_PIN_1
#define pbLeft_GPIO_Port GPIOB
#define pbOk_Pin GPIO_PIN_10
#define pbOk_GPIO_Port GPIOE
#define pbCancel_Pin GPIO_PIN_15
#define pbCancel_GPIO_Port GPIOE
#define dipSW3_Pin GPIO_PIN_11
#define dipSW3_GPIO_Port GPIOB
#define dipSW4_Pin GPIO_PIN_12
#define dipSW4_GPIO_Port GPIOB
#define dipSW2_Pin GPIO_PIN_10
#define dipSW2_GPIO_Port GPIOD
#define dipSW1_Pin GPIO_PIN_11
#define dipSW1_GPIO_Port GPIOD
#define buzzer_Pin GPIO_PIN_11
#define buzzer_GPIO_Port GPIOC
#define bar0_Pin GPIO_PIN_7
#define bar0_GPIO_Port GPIOD
#define bar2_Pin GPIO_PIN_4
#define bar2_GPIO_Port GPIOB
#define bar1_Pin GPIO_PIN_5
#define bar1_GPIO_Port GPIOB
//define General IO on STM32F4Discovery BOard
#define led0_Pin GPIO_PIN_12
#define led0_GPIO_Port GPIOD
#define led1_Pin GPIO_PIN_13
#define led1_GPIO_Port GPIOD
#define led2_Pin GPIO_PIN_14
#define led2_GPIO_Port GPIOD
#define led3_Pin GPIO_PIN_15
#define led3_GPIO_Port GPIOD
#define userButton_Pin GPIO_PIN_0
#define userButton_GPIO_Port GPIOA


#endif /* DEVICE_H_ */
