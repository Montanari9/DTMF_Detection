/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
#define SYS_TIM_Hz 6000000
#define SYSTICK_TIMEBASE_us 1000
#define SYSTICK_CAL (SYSTICK_TIMEBASE_us*SYS_TIM_Hz/1000000)
#define BR1 115200
#define BR2 230400
#define BR4 460800
#define TIM_CLK_48MHz 48000000
#define TIM_CLK TIM_CLK_48MHz
#define TIM3_CK_CNT_Hz 48000000
#define TIM3_PSC ((TIM_CLK/TIM3_CK_CNT_Hz)-1)
#define TIM3_TIMEBASE_us (1000000/TIM3_FREQ_HZ)
#define TIM3_ARR ((TIM3_CK_CNT_Hz/TIM3_FREQ_HZ)-1)
#define TIM3_FREQ_HZ 3840
#define TIMD_CK_CNT_Hz 24000000
#define TIMD_PSC ((TIM_CLK/TIMD_CK_CNT_Hz)-1)
#define TIMD_F1_Hz 697
#define TIMD_F1_ARR ((TIMD_CK_CNT_Hz/TIMD_F1_Hz)-1)
#define TIMD_F2_Hz 770
#define TIMD_F3_Hz 852
#define TIMD_F4_Hz 941
#define TIMD_F5_Hz 1209
#define TIMD_F6_Hz 1336
#define TIMD_F7_Hz 1477
#define TIMD_F8_Hz 1633
#define TIMD_F5_ARR ((TIMD_CK_CNT_Hz/TIMD_F5_Hz)-1)

#define ADC_DTMF_IN_Pin GPIO_PIN_0
#define ADC_DTMF_IN_GPIO_Port GPIOA
#define ADC_AUX_IN_Pin GPIO_PIN_1
#define ADC_AUX_IN_GPIO_Port GPIOA
#define FREQ_LO_Pin GPIO_PIN_4
#define FREQ_LO_GPIO_Port GPIOA
#define OUT0_Pin GPIO_PIN_5
#define OUT0_GPIO_Port GPIOA
#define FREQ_HI_Pin GPIO_PIN_6
#define FREQ_HI_GPIO_Port GPIOA
#define OUT1_Pin GPIO_PIN_7
#define OUT1_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
