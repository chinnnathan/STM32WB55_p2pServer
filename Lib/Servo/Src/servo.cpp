/*
 * servo.cpp
 *
 *  Created on: Jan 16, 2024
 *      Author: nchinn
 */

#include "main.h"
#include "stm32wbxx_hal.h"
#include "stm32wb55xx.h"
#include "servo.h"

uint32_t value_adc = 1;

void step(uint8_t id, uint16_t delay)
{
	switch(id)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOC, SN_34E_Pin, 	        GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, SN_1A_Pin, 	        GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, SN_2A_Pin,      	    GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, SN_12E_Pin, 	        GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOC, SN_12E_Pin, 	        GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, SN_3A_Pin, 	        GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, SN_4A_Pin|SN_34E_Pin, 	GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOC, SN_34E_Pin, 	        GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, SN_2A_Pin, 	        GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, SN_1A_Pin, 	        GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, SN_12E_Pin, 	        GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOC, SN_4A_Pin|SN_12E_Pin,  GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, SN_3A_Pin|SN_34E_Pin, 	GPIO_PIN_SET);
		break;
	}
	// osDelay(delay);
}

void run_clockwise(uint16_t delay, uint16_t breakval)
{
	uint8_t sentinel = 0;
	while(sentinel < 1)
	{
		// HAL_ADC_Start(&hadc1);

		step(0, delay);
		step(1, delay);
		step(2, delay);
		step(3, delay);

		if (value_adc > breakval)
		{
			sentinel++;
		}
	}
    HAL_GPIO_WritePin(GPIOC, SN_12E_Pin|SN_34E_Pin, GPIO_PIN_RESET);
	// HAL_ADC_Stop(&hadc1);
}

void run_counterclockwise(uint16_t delay, uint16_t breakval)
{
	uint8_t sentinel = 0;
	while(sentinel < 1)
	{
		// HAL_ADC_Start(&hadc1);

		step(3, delay);
		step(2, delay);
		step(1, delay);
		step(0, delay);

		if (value_adc > breakval)
		{
			sentinel++;
		}
	}
	HAL_GPIO_WritePin(GPIOC, SN_12E_Pin|SN_34E_Pin, GPIO_PIN_RESET);
	// HAL_ADC_Stop(&hadc1);
}
