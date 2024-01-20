/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal.h"
#include "app_conf.h"
#include "app_entry.h"
#include "app_common.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32wbxx_nucleo.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_LPUART1_UART_Init(void);
void MX_USART1_UART_Init(void);

/* USER CODE BEGIN EFP */
extern ADC_HandleTypeDef hadc1;
extern uint32_t value_adc;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SN_3A_Pin GPIO_PIN_0
#define SN_3A_GPIO_Port GPIOC
#define SN_4A_Pin GPIO_PIN_1
#define SN_4A_GPIO_Port GPIOC
#define SN_34E_Pin GPIO_PIN_2
#define SN_34E_GPIO_Port GPIOC
#define SN_12E_Pin GPIO_PIN_3
#define SN_12E_GPIO_Port GPIOC
#define SN_1A_Pin GPIO_PIN_0
#define SN_1A_GPIO_Port GPIOA
#define SN_2A_Pin GPIO_PIN_1
#define SN_2A_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
