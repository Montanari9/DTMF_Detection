/*******************************************************************************
  INTERRUPT.C file
  
  Interrupt routines
*******************************************************************************/

#include "main2.h"

/*******************************************************************************
  INTERRUPT VARIABLES
*******************************************************************************/

/*******************************************************************************
  INTERRUPT ROUTINES
*******************************************************************************/
void ADC_ConvCpltCallback (void) 
//void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef* hadc)

// Sampling Frequency TIM3_FREQ_HZ (3840 Hz);
// After automatic ADC sequence conversion / DMA1 CH1 transfer to ADC Buffer   
{
  Capture_DTMF_Samples();                                                       // Fill in the DTMF_Buffer
}

void Capture_DTMF_Samples (void)
{
  if (DTMF_Buffer_Released)
  {                                               // Buffer released to be filled in
    DTMF_Buffer[DTMF_Buffer_Index] = ADC_DTMF - 2048;    // Put ADC sample in the DTMF_Buffer 
    if (++DTMF_Buffer_Index >= SAMPLING_LENGTH)
    {                                             // End of capture
      DTMF_Buffer_Released = FALSE;               // Block buffer to be filled
      DTMF_Buffer_Full = TRUE;                    // DTMF_Buffer indicates completed
    }
  }
}



