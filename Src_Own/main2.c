/*******************************************************************************
  MAIN2.C file

  Initiation routines
*******************************************************************************/

#include "main2.h"

/*------------------------------------------------------------------------------
CHANGES CONTROL

- Initial release
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

/*******************************************************************************
  GLOBAL CONSTANTS
*******************************************************************************/

/*******************************************************************************
  GLOBAL VARS
*******************************************************************************/
// ADC Buffer capture
uint16_t              ADC_Buffer[ADC_CHANNELS_QTTY];              // [sizeof(Adc_Buff_Index)];
uint16_t  volatile    Enable_Main_Loop 						= 0;					  // Main loop scan 
FFT_result_TypeDef    FFT_Result[4];                              // Learning Resuts from FFT calculation
q15_t                 DTMF_Buffer[SAMPLING_LENGTH];               // Sampling DTMF
uint32_t              DTMF_Buffer_Index = 0;                      // points to first position
_Bool                 DTMF_Buffer_Full = FALSE;                   // DTMF_Buffer indicates incompleted
_Bool                 DTMF_Buffer_Released = FALSE;               // Block buffer to be filled

/*******************************************************************************
  MAIN2 ROUTINES
*******************************************************************************/

void DMA_Disable_HalfTransfer_IT(DMA_HandleTypeDef *hdma)
{
  /* Disable the Half transfer complete interrupt */
  __HAL_DMA_DISABLE_IT(hdma, DMA_IT_HT);  
  /* Disable the transfer error interrupt */
  __HAL_DMA_DISABLE_IT(hdma, DMA_IT_TE);
}

void System_Vars_Initialization (void)	// OK
{
  Clear_DTMF_Buffer();                  // Clear DTMF_Buffer
  DTMF_Buffer_Released = TRUE;          // Release buffer to be filled
}

void DTMF_Receiver (void)
{
  if (DTMF_Buffer_Full)
  {                                       // DTMF_Buffer just completed
    Get_DTMF_From_FFT();                  // Capture frequencies, available at FFT_Result
    Clear_DTMF_Buffer();                  // Clear DTMF_Buffer and DTMF_Buffer_Full flag
    DTMF_Buffer_Released = TRUE;          // Release buffer to be filled
  }
}

void Get_DTMF_From_FFT (void)     // Get DTMF Frequencies
{
  FFT_data_TypeDef        FFT_Data[5];          //temp fft data vars

  // Fullfill the FFT Data buffer to verify the best Amplitude from Buffer sector
  //fftUsedLength = FFT_LENGTH;                                                 // FFT buffer size to calculate FFT
  FFT_Processing_Q15((q15_t *)&DTMF_Buffer[0], FFT_LENGTH);                     // Process FFT, results fftOutputBuf[], maxValue, fftIndex
#if 1  
  // Find 3 biggest Values among the fftOutputBuf
  FFT_Data[0].Index = 0;                                                        // clear FFT_Data.Index
  FFT_Data[0].Value = 0;                                                        // clear FFT_Data.Value
  FFT_Data[1].Index = 0;                                 
  FFT_Data[1].Value = 0;                                                        
  FFT_Data[2].Index = 0;                                 
  FFT_Data[2].Value = 0;
  FFT_Data[3].Index = 0;                                 
  FFT_Data[3].Value = 0;
  for (fftIndex = FFT_MIN_INDEX; fftIndex <= FFT_MAX_INDEX; fftIndex++)         // excluding FFT_MIN_INDEX first indexes
  {                                                                             // do FFT_LENGTH/2 times
    FFT_Data[4].Index = fftIndex;
    FFT_Data[4].Value = fftOutputBuf[fftIndex];
    if (FFT_Data[4].Value > FFT_Data[0].Value)
    {                                                                           // Found biggest value
      FFT_Data[3] = FFT_Data[2];                                                // Save previous as 3rd bigger
      FFT_Data[2] = FFT_Data[1];                                                // Save previous as 3rd bigger
      FFT_Data[1] = FFT_Data[0];                                                // Save previous as 2nd bigger
      FFT_Data[0] = FFT_Data[4];                                                // Update biggest value
    }
    else if (FFT_Data[4].Value > FFT_Data[1].Value)
    {                                                                           // Found 2nd bigger value
      FFT_Data[3] = FFT_Data[2];                                                // Save previous as 3rd bigger
      FFT_Data[2] = FFT_Data[1];                                                // Save previous as 3rd bigger
      FFT_Data[1] = FFT_Data[4];                                                // Update 2nd bigger value
    }
    else if (FFT_Data[4].Value > FFT_Data[2].Value)
    {                                                                           // Found 3rd bigger value
      FFT_Data[3] = FFT_Data[2];                                                // Save previous as 3rd bigger
      FFT_Data[2] = FFT_Data[4];                                                // Update 3rd bigger value
    }
    else if (FFT_Data[4].Value > FFT_Data[3].Value)
    {                                                                           // Found 4th bigger value
      FFT_Data[3] = FFT_Data[4];                                                // Update 3rd bigger value
    }
  }
  FFT_Result[0].Index = FFT_Data[0].Index;                                      // Update FFT_Result for Global use
  FFT_Result[0].Value = FFT_Data[0].Value;                                      // Update FFT_Result for Global use
  FFT_Result[1].Index = FFT_Data[1].Index;                                      // Update FFT_Result for Global use
  FFT_Result[1].Value = FFT_Data[1].Value;                                      // Update FFT_Result for Global use
  FFT_Result[2].Index = FFT_Data[2].Index;                                      // Update FFT_Result for Global use
  FFT_Result[2].Value = FFT_Data[2].Value;                                      // Update FFT_Result for Global use
  FFT_Result[3].Index = FFT_Data[3].Index;                                      // Update FFT_Result for Global use
  FFT_Result[3].Value = FFT_Data[3].Value;                                      // Update FFT_Result for Global use
  FFT_Result[0].Frequency = ((uint32_t)FFT_Result[0].Index * FFT_SAMPLING_FREQ + (FFT_LENGTH/2)) / FFT_LENGTH;  // Calc the MainFrequency according to the Processed FFT
  FFT_Result[1].Frequency = ((uint32_t)FFT_Result[1].Index * FFT_SAMPLING_FREQ + (FFT_LENGTH/2)) / FFT_LENGTH;  // Calc the MainFrequency according to the Processed FFT
  FFT_Result[2].Frequency = ((uint32_t)FFT_Result[2].Index * FFT_SAMPLING_FREQ + (FFT_LENGTH/2)) / FFT_LENGTH;  // Calc the MainFrequency according to the Processed FFT
  FFT_Result[3].Frequency = ((uint32_t)FFT_Result[3].Index * FFT_SAMPLING_FREQ + (FFT_LENGTH/2)) / FFT_LENGTH;  // Calc the MainFrequency according to the Processed FFT
#endif
}

void Clear_DTMF_Buffer (void)           // Clear DTMF_Buffer
{
  uint32_t i;
  for (i = 0; i < SAMPLING_LENGTH; i++)
  {
    DTMF_Buffer[i] = 0;                             // Clear DTMF_Buffer samples
  }
  DTMF_Buffer_Index = 0;                            // points to first position
  DTMF_Buffer_Full = FALSE;                         // DTMF_Buffer indicates incompleted
}


