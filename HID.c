/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2019 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    HID.c
 * Purpose: USB Device - Human Interface Device example
 *----------------------------------------------------------------------------*/

#include "main.h"
#include "rl_usb.h"                     // Keil.MDK-Pro::USB:CORE

#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"              // ::Board Support:Buttons
#include "Board_GLCD.h"                 // ::Board Support:Graphic LCD
#include "GLCD_Config.h"                // Keil.STM32F746G-Discovery::Board Support:Graphic LCD
#include "string.h"

// Main stack size must be multiple of 8 Bytes
#define APP_MAIN_STK_SZ (1024U)
uint64_t app_main_stk[APP_MAIN_STK_SZ / 8];
const osThreadAttr_t app_main_attr = {
  .stack_mem  = &app_main_stk[0],
  .stack_size = sizeof(app_main_stk)
};

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

extern ADC_HandleTypeDef hadc3;

/*------------------------------------------------------------------------------
 *        Application
 *----------------------------------------------------------------------------*/
__NO_RETURN void app_main (void *arg) {
  uint8_t but, but_last;

  (void)arg;

  LED_Initialize();                     /* LED Initialization                 */
  Buttons_Initialize();                 /* Buttons Initialization             */

  GLCD_Initialize         ();
  GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
  GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
  GLCD_ClearScreen        ();
  GLCD_SetFont            (&GLCD_Font_16x24);
  GLCD_DrawString         (0U, 0U*24U, "    USB Device      ");
  GLCD_DrawString         (0U, 1U*24U, "    HID Class       ");
  GLCD_DrawString         (0U, 2U*24U, "    HID Example     ");
  GLCD_DrawString         (0U, 4U*24U, "USBFS: HID0         ");
  GLCD_DrawString         (0U, 5U*24U, "USBHS: HID1         ");
  GLCD_DrawString         (0U, 8U*24U, "  Keil Tools by ARM ");
  GLCD_DrawString         (0U, 9U*24U, "    www.keil.com    ");

  USBD_Initialize(0U);                  /* USB Device 0 Initialization        */
  USBD_Connect   (0U);                  /* USB Device 0 Connect               */

  USBD_Initialize(1U);                  /* USB Device 1 Initialization        */
  USBD_Connect   (1U);                  /* USB Device 1 Connect               */

  uint32_t dk_state = 0;
	
	HAL_ADC_Init(&hadc3);
	
  for (;;) {                            /* Loop forever                       */
		uint32_t dk_state_new = 0;
		
		if (HAL_GPIO_ReadPin(DK1_GPIO_Port, DK1_Pin) == GPIO_PIN_RESET) {
			dk_state_new |= 0x01;
		} else {
			dk_state_new |= 0;
		}
		if (HAL_GPIO_ReadPin(DK2_GPIO_Port, DK2_Pin) == GPIO_PIN_RESET) {
			dk_state_new |= 0x02;
		} else {
			dk_state_new |= 0;
		}
		if (HAL_GPIO_ReadPin(DK3_GPIO_Port, DK3_Pin) == GPIO_PIN_RESET) {
			dk_state_new |= 0x04;
		} else {
			dk_state_new |= 0;
		}
		if (HAL_GPIO_ReadPin(DK4_GPIO_Port, DK4_Pin) == GPIO_PIN_RESET) {
			dk_state_new |= 0x08;
		} else {
			dk_state_new |= 0;
		}
		
		HAL_ADC_Start(&hadc3);
		HAL_ADC_PollForConversion(&hadc3, 1000);
		uint32_t pot_val = HAL_ADC_GetValue(&hadc3);
		pot_val = pot_val >> 8;
		pot_val = pot_val << 4;
		
		dk_state = pot_val + dk_state_new;
			
		if (USBD_Configured(0)) { USBD_HID_GetReportTrigger(0U, 0U, &dk_state, 1U); }
		
    osDelay(100U);                      /* 100 ms delay for sampling buttons  */
  }
}
