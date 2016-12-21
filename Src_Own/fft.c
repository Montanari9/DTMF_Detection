/* ----------------------------------------------------------------------
* Copyright (C) 2010-2012 ARM Limited. All rights reserved.
*
* $Date:         17. January 2013
* $Revision:     V1.4.0
*
* Project:       CMSIS DSP Library
* Title:	     arm_fft_bin_example_f32.c
*
* Description:   Example code demonstrating calculation of Max energy bin of
*                frequency domain of input signal.
*
* Target Processor: Cortex-M4/Cortex-M3
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
 * -------------------------------------------------------------------- */

/**
 * @ingroup groupExamples
 */

/**
 * @defgroup FrequencyBin Frequency Bin Example
 *
 * \par Description
 * \par
 * Demonstrates the calculation of the maximum energy bin in the frequency
 * domain of the input signal with the use of Complex FFT, Complex
 * Magnitude, and Maximum functions.
 *
 * \par Algorithm:
 * \par
 * The input test signal contains a 10 kHz signal with uniformly distributed white noise.
 * Calculating the FFT of the input signal will give us the maximum energy of the
 * bin corresponding to the input frequency of 10 kHz.
 *
 * \par Block Diagram:
 * \image html FFTBin.gif "Block Diagram"
 * \par
 * The figure below shows the time domain signal of 10 kHz signal with
 * uniformly distributed white noise, and the next figure shows the input
 * in the frequency domain. The bin with maximum energy corresponds to 10 kHz signal.
 * \par
 * \image html FFTBinInput.gif "Input signal in Time domain"
 * \image html FFTBinOutput.gif "Input signal in Frequency domain"
 *
 * \par Variables Description:
 * \par
 * \li \c fftInput points to the input data
 * \li \c fftOutputBuf points to the output data
 * \li \c fftSize length of FFT
 * \li \c ifftFlag flag for the selection of CFFT/CIFFT
 * \li \c doBitReverse Flag for selection of normal order or bit reversed order
 * \li \c fftIndex calculated index value at which maximum energy of bin ocuurs
 *
 * \par CMSIS DSP Software Library Functions Used:
 * \par
 * - arm_cfft_f32()
 * - arm_cmplx_mag_f32()
 * - arm_max_f32()
 *
 * <b> Refer  </b>
 * \link arm_fft_bin_example_f32.c \endlink
 *
 */

#include "main2.h"
#include "arm_const_structs.h"

/* -------------------------------------------------------------------
* External Input and Output buffer Declarations for FFT Bin Example
* ------------------------------------------------------------------- */
#if MATH_FUNCTION == USE_F32
  float32_t         fftOutputBuf[FFT_LENGTH_MAX];
  static float32_t  fftInputDraft[FFT_LENGTH_MAX*2];
  float32_t         maxValue;
#endif   
   
#if MATH_FUNCTION == USE_Q15
  q15_t             fftOutputBuf[FFT_LENGTH_MAX];
  static q15_t      fftInputDraft[FFT_LENGTH_MAX*2];
  q15_t             maxValue;
#endif    
   
#if MATH_FUNCTION == USE_Q31
  q31_t             fftOutputBuf[FFT_LENGTH_MAX];
  static q31_t      fftInputDraft[FFT_LENGTH_MAX*2];
  q31_t             maxValue;
#endif    

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */

uint32_t          ifftFlag = 0;                   // ARM definition
uint32_t          doBitReverse = 1;               // ARM definition
uint32_t          fftIndex = 0;
uint16_t          fftUsedLength = FFT_LENGTH;   // can be 1024, 512, 256, 128, 64
//uint16_t          fftPhase = 0;
//_Bool             InputBufferFull;
//uint16_t          MainFrequency;

/* ----------------------------------------------------------------------
* Max magnitude FFT Bin test
* ------------------------------------------------------------------- */

#if MATH_FUNCTION == USE_F32
void FFT_Processing_F32 (float32_t * pSrc, uint32_t fftSize)
{
  const arm_cfft_instance_f32 * psR;
  uint32_t      i;
  
  /* Prepare the Input Draft as a complex data */
  for (i = 0; i < fftSize * 2; )      // 2x the fftSize
  {
    fftInputDraft[i++] = *pSrc++;     // fullfill the real data
    fftInputDraft[i++] = 0;           // fullfill the imaginary data
  }
  
  /* Select cfft instance according to the length*/
  if (fftSize == 1024)      psR = &arm_cfft_sR_f32_len1024;
  else if (fftSize == 512)  psR = &arm_cfft_sR_f32_len512;
  else if (fftSize == 256)  psR = &arm_cfft_sR_f32_len256;
  else if (fftSize == 128)  psR = &arm_cfft_sR_f32_len128;
  else                      psR = &arm_cfft_sR_f32_len64;  

  /* Process the data through the CFFT/CIFFT module */
  arm_cfft_f32(psR, fftInputDraft, ifftFlag, doBitReverse);

  /* Process the data through the Complex Magnitude Module for
  calculating the magnitude at each bin */
  arm_cmplx_mag_f32(fftInputDraft, fftOutputBuf, fftSize);

  /* Calculates maxValue and returns corresponding BIN value */
  fftIndex = fftSize;
  arm_max_f32(fftOutputBuf, fftSize/2, &maxValue, &fftIndex);
}
#endif

#if MATH_FUNCTION == USE_Q15
void FFT_Processing_Q15 (q15_t * pSrc, uint32_t fftSize)  // results maxValue, fftIndex
{
  const arm_cfft_instance_q15 * psR;
  uint32_t      i;

  /* Prepare the Input Draft as a complex data */
  for (i = 0; i < fftSize * 2; )      // 2x the fftSize
  {
    fftInputDraft[i++] = *pSrc++ * 16;    // fullfill the real data, 12 to 16bit
    fftInputDraft[i++] = 0;               // fullfill the imaginary data
  }
  
  /* Select cfft instance according to the length*/
  if (fftSize == 1024)      psR = &arm_cfft_sR_q15_len1024;
  else if (fftSize == 512)  psR = &arm_cfft_sR_q15_len512;
  else if (fftSize == 256)  psR = &arm_cfft_sR_q15_len256;
  else if (fftSize == 128)  psR = &arm_cfft_sR_q15_len128;
  else                      psR = &arm_cfft_sR_q15_len64;  

  /* Process the data through the CFFT/CIFFT module */
  arm_cfft_q15(psR, fftInputDraft, ifftFlag, doBitReverse);

  /* Process the data through the Complex Magnitude Module for calculating the magnitude at each bin */
  arm_cmplx_mag_q15(fftInputDraft, fftOutputBuf, fftSize);
  
  /* Calculates maxValue and returns corresponding BIN value */
  fftIndex = fftSize;                                // only as fill-in purpose
  arm_max_q15(fftOutputBuf, fftSize/2, &maxValue, &fftIndex);
}
#endif

#if MATH_FUNCTION == USE_Q31
void FFT_Processing_Q31 (q31_t * pSrc, uint32_t fftSize)
{
  const arm_cfft_instance_q31 * psR;
  uint32_t      i;

  /* Prepare the Input Draft as a complex data */
  for (i = 0; i < fftSize * 2; )      // 2x the fftSize
  {
    fftInputDraft[i++] = *pSrc++;     // fullfill the real data
    fftInputDraft[i++] = 0;           // fullfill the imaginary data
  }
  
  /* Select cfft instance according to the length*/
  if (fftSize == 1024)      psR = &arm_cfft_sR_q31_len1024;
  else if (fftSize == 512)  psR = &arm_cfft_sR_q31_len512;
  else if (fftSize == 256)  psR = &arm_cfft_sR_q31_len256;
  else if (fftSize == 128)  psR = &arm_cfft_sR_q31_len128;
  else                      psR = &arm_cfft_sR_q31_len64;  

  /* Process the data through the CFFT/CIFFT module */
  arm_cfft_q31(psR, fftInputDraft, ifftFlag, doBitReverse);

  /* Process the data through the Complex Magnitude Module for
  calculating the magnitude at each bin */
  arm_cmplx_mag_q31(fftInputDraft, fftOutputBuf, fftSize);

  /* Calculates maxValue and returns corresponding BIN value */
  fftIndex = fftSize;
  arm_max_q31(fftOutputBuf, fftSize/2, &maxValue, &fftIndex);
}
#endif

 /** \endlink */
