/**
  ******************************************************************************
  * @file    STM32F429_DSPDEMO/Inc/fft.h 
  * @author  MCD Application Team
  * @brief   Header for fft_processing.c module
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
#ifndef __FFT_H
#define __FFT_H

/* Includes ------------------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/
#define MATH_FUNCTION           USE_Q15             // can be USE_F32 or USE_Q15 or USE_Q31
#define SAMPLING_LENGTH         256                 // Sampling Data buffer ALLOCATION, V, I, Ipulse
#define DTMF_MIN                697                 // Hz
#define DTMF_MAX                1633                // Hz
    
#define FFT_LENGTH_MAX          SAMPLING_LENGTH     // FFT Buffers ALLOCATION: 1024, 512, 256, 128, 64
#define FFT_LENGTH              SAMPLING_LENGTH     // Used length to calculate the FFT 
#define FFT_MIN_FREQ            (600)      // Hz, Lower frequencies shall be ignored 
#define FFT_MAX_FREQ            (1730)      // Hz, Lower frequencies shall be ignored 
#define FFT_MIN_INDEX           (((FFT_MIN_FREQ * FFT_LENGTH * 2) / FFT_SAMPLING_FREQ + 1) / 2) // Hz, Lower frequencies shall be ignored 
#define FFT_MAX_INDEX           (((FFT_MAX_FREQ * FFT_LENGTH * 2) / FFT_SAMPLING_FREQ + 1) / 2) // Hz, Lower frequencies shall be ignored 
#define FFT_MAX_INDEX_DEVIATION (FFT_LENGTH / 128)  // Index deviation of 2 biggest Frequency indexes
#define FFT_SAMPLING_FREQ       TIM3_FREQ_HZ        // Hz 3840

#define FFT_INVERSE_FLAG        ((uint8_t)0)        // default fft
#define FFT_Normal_OUTPUT_FLAG  ((uint8_t)1)        // default fft

#define Index(Freq)             (uint32_t)(Freq * fftUsedLength / FFT_SAMPLING_FREQ) // Position in the fft buffer
#define Freq(Index)             (uint32_t)(Index * FFT_SAMPLING_FREQ / fftUsedLength) // Freq from Position in the buffer

#define USE_F32         3
#define USE_Q15         4
#define USE_Q31         5

/* Private variables ---------------------------------------------------------*/

#if MATH_FUNCTION == USE_Q15
  extern q15_t           fftOutputBuf[];
  extern q15_t           maxValue;
#endif    
extern    uint32_t       fftIndex;
extern    uint16_t       fftUsedLength;
   
/* Macro definition ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void        FFT_Processing_F32 (float32_t * pSrc, uint32_t fftSize);
void        FFT_Processing_Q15 (q15_t * pSrc, uint32_t fftSize);
void        FFT_Processing_Q31 (q31_t * pSrc, uint32_t fftSize);

#endif /* __FFT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
