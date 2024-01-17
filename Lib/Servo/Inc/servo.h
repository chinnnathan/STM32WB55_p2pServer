/*
 * servo.h
 *
 *  Created on: Jan 16, 2024
 *      Author: nchinn
 */

#ifndef APPLICATION_USER_STM32_WPAN_APP_SERVO_H_
#define APPLICATION_USER_STM32_WPAN_APP_SERVO_H_

#include <stdint.h>


void run_counterclockwise(uint16_t delay, uint16_t breakval);
void run_clockwise(uint16_t delay, uint16_t breakval);



#endif /* APPLICATION_USER_STM32_WPAN_APP_SERVO_H_ */
