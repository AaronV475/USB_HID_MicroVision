/**
  ******************************************************************************
  * @file    Templates/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOB
#define LED7_Pin GPIO_PIN_15
#define LED7_GPIO_Port GPIOA
#define LED6_Pin GPIO_PIN_3
#define LED6_GPIO_Port GPIOI
#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOI
#define LED8_Pin GPIO_PIN_8
#define LED8_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_7
#define LED3_GPIO_Port GPIOG
#define DK4_Pin GPIO_PIN_7
#define DK4_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOF
#define DK1_Pin GPIO_PIN_10
#define DK1_GPIO_Port GPIOF
#define DK2_Pin GPIO_PIN_9
#define DK2_GPIO_Port GPIOF
#define DK3_Pin GPIO_PIN_8
#define DK3_GPIO_Port GPIOF
#define LED5_Pin GPIO_PIN_6
#define LED5_GPIO_Port GPIOH

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS2                  // when RTE component CMSIS RTOS2 is used
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern uint64_t app_main_stk[];
extern const osThreadAttr_t app_main_attr;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void app_main (void *arg);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
