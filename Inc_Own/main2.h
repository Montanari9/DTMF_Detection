/*******************************************************************************
  MAIN2.H file
*******************************************************************************/

#ifndef __MAIN2_H
#define __MAIN2_H

#include "stm32f0xx.h" 

#include "main.h"
#include "user_defs.h"
#include <arm_math.h>
#include <math.h>

/*******************************************************************************
  DEFINITIONS BY COMPILING DIRECTIVES ACCORDING TO THE APPLICATION NEEDS 
  Depending on the definition value, compiling and functional results are different
*******************************************************************************/

/*******************************************************************************
  APPLICATION DEFINITIONS
*******************************************************************************/

/*******************************************************************************
  DEFINITIONS CONSYSTENCY CHECK
*******************************************************************************/

/************** CONFLICTIVE DEFINITIONS *******************/

/*******************************************************************************
  STRUCTS DEFINITIONS
*******************************************************************************/

/*******************************************************************************
  INCLUDE FILES
*******************************************************************************/

#include "interrupt.h"
#include "fft.h"

/*******************************************************************************
  EXTERNAL GLOBAL CONSTANTS
*******************************************************************************/

#define ADC_CHANNELS_QTTY   2     // ADC_Buffer purposes

// ADC Input Port Definition
typedef enum
{ ADC_INDEX_DTMF      =    0,     // ADC_CHANNEL_0       ADC_DTMF_IN
  ADC_INDEX_AUX       =    1      // ADC_CHANNEL_1       ADC_AUX_IN
} Adc_Buff_Index;                 // ADC_Buffer Index

#define ADC_DTMF           ADC_Buffer[ADC_INDEX_DTMF]
#define ADC_Aux            ADC_Buffer[ADC_INDEX_AUX]

typedef struct fft_data
{
  uint16_t          Index;
  q15_t             Value;
} FFT_data_TypeDef;

typedef struct fft_result
{
  uint16_t          Index;
  q15_t             Value;
  uint16_t          Frequency;
} FFT_result_TypeDef;

/*******************************************************************************
  EXTERNAL GLOBAL VARS
*******************************************************************************/
// ADC Buffer capture
extern    uint16_t                  ADC_Buffer[];
extern    uint16_t  volatile        Enable_Main_Loop;
extern    q15_t                     DTMF_Buffer[SAMPLING_LENGTH]; 
extern    uint32_t                  DTMF_Buffer_Index;             
extern    _Bool                     DTMF_Buffer_Full;                
extern    _Bool                     DTMF_Buffer_Released;           

/*******************************************************************************
  PROTOTYPES DEFINITIONS
*******************************************************************************/
void        DMA_Disable_HalfTransfer_IT(DMA_HandleTypeDef *hdma);
void        System_Vars_Initialization (void);
void        Get_DTMF_From_FFT (void);
void        Clear_DTMF_Buffer (void);           
void        DTMF_Receiver (void);

#endif  // __MAIN_H
