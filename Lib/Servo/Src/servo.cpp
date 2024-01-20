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
#include "dbg_trace.h"

// constexpr uint32_t sum_val = 800; // 5 V
uint32_t sum_val = 2100; // 10V

uint32_t step(uint8_t id, uint16_t delay)
{
    HAL_ADC_Start(&hadc1);

	switch(id)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOA, SN_1A_Pin|SN_2A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, SN_3A_Pin|SN_4A_Pin, GPIO_PIN_RESET);
		break;
	case 1:
        HAL_GPIO_WriteMultipleStatePin(GPIOA, SN_1A_Pin, SN_2A_Pin);
        HAL_GPIO_WriteMultipleStatePin(GPIOC, SN_4A_Pin, SN_3A_Pin);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, SN_1A_Pin|SN_2A_Pin,   GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, SN_3A_Pin|SN_4A_Pin,   GPIO_PIN_SET);
		// HAL_GPIO_WritePin(GPIOC, SN_12E_Pin, 	        GPIO_PIN_SET);
		// HAL_GPIO_WritePin(GPIOC, SN_34E_Pin, 	        GPIO_PIN_SET);
		break;
	case 3:
        HAL_GPIO_WriteMultipleStatePin(GPIOA, SN_2A_Pin, SN_1A_Pin);
        HAL_GPIO_WriteMultipleStatePin(GPIOC, SN_3A_Pin, SN_4A_Pin);
		break;
	}
    HAL_Delay(delay);
	// osDelay(delay);
    return value_adc;
}


struct Stepper
{
    private:
    uint16_t cur = 0;
    uint16_t numTicks = 0;


    public:
    bool     openCW = false;
    bool     openCCW = false;

    uint32_t clockwise(uint16_t delay, uint16_t count = 4)
    {
        HAL_GPIO_WritePin(GPIOC, SN_12E_Pin|SN_34E_Pin, GPIO_PIN_SET);
        uint32_t retVal = 0;
        do
        {
            if (cur++ > 3)
                cur = 0;
            retVal += step(cur, delay);
        } while(count--);
        HAL_GPIO_WritePin(GPIOC, SN_12E_Pin|SN_34E_Pin, GPIO_PIN_RESET);
        return retVal;
    }

    uint32_t counterclockwise(uint16_t delay, uint16_t count = 4)
    {
        HAL_GPIO_WritePin(GPIOC, SN_12E_Pin|SN_34E_Pin, GPIO_PIN_SET);
        uint32_t retVal = 0;
        do
        {
            if (cur == 0)
                cur = 4;
            retVal += step(--cur, delay);
        } while(count--);
        HAL_GPIO_WritePin(GPIOC, SN_12E_Pin|SN_34E_Pin, GPIO_PIN_RESET);
        return retVal;
    }

    void run_counterclockwise(uint16_t delay)
    {
        if (!openCCW)
            counterclockwise(delay, numTicks);
        openCCW = true;
        openCW = false;
    }

    void run_clockwise(uint16_t delay)
    {
        if (!openCW)
            clockwise(delay, numTicks);
        openCW = true;
        openCCW = false;
    }

    uint16_t ticks() const { return numTicks; }
    void ticks(uint16_t t) { numTicks = t; }
};

namespace {
    uint16_t ccCount;
    uint16_t cCount;
    Stepper stepper;
}

// uint32_t value_adc = 1;



uint32_t step_clockwise(uint16_t delay)
{
    uint32_t retVal =  step(0, delay);
    retVal += step(1, delay);
    retVal += step(2, delay);
    retVal += step(3, delay);
    return retVal;
}

uint32_t step_counterclockwise(uint16_t delay)
{
    uint32_t retVal =  step(3, delay);
    retVal += step(2, delay);
    retVal += step(1, delay);
    retVal += step(0, delay);
    return retVal;
}

void init_servo()
{
    // Stepper Motors take more power to stay still than to move
    // because E-mag is a fickle mistress that we don't need to understand.
    // We'll just say left hand rule, etc, and move on.
    // So, if I set the magnetic signal to position 1, but it is locked out, what happens?
    // Its a magnet, so it tries to get to position 1. This means theres little baby pulses.
    // If I find that there are these pulses, that means I know where edge 1 and edge 2 are.
    // So, I move, then let set for a moment. If the pulse is detectable, then I know I've hit the edge.
    // The current should be stable.

    HAL_ADC_Start(&hadc1);
    HAL_GPIO_WritePin(GPIOA, SN_1A_Pin|SN_2A_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WriteMultipleStatePin(GPIOC, SN_3A_Pin|SN_4A_Pin, SN_12E_Pin|SN_34E_Pin);
    uint32_t sum = 0, numSteps = 25, stepC = 0;
    while(stepC++ < numSteps)
    {
        HAL_ADC_Start(&hadc1);
        HAL_Delay(5);
        sum += value_adc;
    }
    HAL_Delay(5);
    HAL_ADC_Stop(&hadc1);
    // this value is the average
    printf("Average idle value: %lu\n", sum / numSteps);

    sum = stepper.clockwise(1, 4 * numSteps);
    printf("Stepping CW Value: %lu\n", sum / numSteps);
    sum_val = (sum / numSteps) * 2;
  
    sum = stepper.counterclockwise(1, 4 * numSteps);
    
    stepper.counterclockwise(1, 150);

    printf("Stepping CCW Value: %lu\n", sum / numSteps);
    HAL_ADC_Stop(&hadc1);

    do
    {
        HAL_Delay(1000);

        stepC = 0;
        do
        {
            sum = stepper.clockwise(1, 8);
            stepC += 8;
            HAL_Delay(200);
        } while (sum < sum_val);
        stepper.ticks(stepC);

        sum = stepper.counterclockwise(1, stepC);
        sum_val += 100;
        stepper.openCCW = true;
    }while (stepper.ticks() < 100);
 
    
    printf("Stepping CCW Value: %lu : %lu\n", stepC, sum);
	HAL_ADC_Stop(&hadc1);
}

void run_clockwise(uint16_t delay, uint16_t breakval)
{
	stepper.run_clockwise(delay);
}

void run_counterclockwise(uint16_t delay, uint16_t breakval)
{
	stepper.run_counterclockwise(delay);
}
