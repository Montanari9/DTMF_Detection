/*******************************************************************************
  USER_DEFS.H file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_DEFS_H
#define __USER_DEFS_H

/***************************** PUBLIC DECLARATIONS **************************/

/*******************************************************************************
  GENERAL MACRO DEFINITIONS
*******************************************************************************/

/* Generic Definitions */
#define FALSE           0
#define TRUE            (!(FALSE))
#define OFF             0
#define ON              1

/* Standard Macro Definitions */
#define Dim(x)          (sizeof(x) / sizeof(x[0]))      // Nbr of elements in array x[]
#define ABS(x)          (x) > 0 ? (x) : -(x)            // Absolute value of expression
#define max(a,b)        (a > b)  ? (a) : (b)

/* Memory Access Definitions */
#define LOINT(mem)      (uint16_t)(mem&0xFFFF)          // for long vars
#define HIINT(mem)      (uint16_t)(mem>>16)             // for long vars
#define LOBYTE(mem)     (uint8_t)(mem&0xFF)             // for int vars
#define HIBYTE(mem)     (uint8_t)((mem&0xFF00)>>8)      // for int vars

/* Standard Types Definitions */
typedef enum            {NOT_READY = 0, 
                         READY          }  ReadyStatus;
typedef enum            {N_OK      = 0,      
                         OK             }  OkStatus;
typedef enum            {LOW       = 0,       
                         HIGH      = 1  }  LevelStatus;

/*******************************************************************************
  STRUCTS AND TYPEDEFS
*******************************************************************************/

/* New Type: "hilo":
uint16_t, accessed only as Byte High and Low
ex:  hilo Var;
use: Var.hi; Var.low;
*/                                                        
typedef struct  
{
  uint8_t       hi;
  uint8_t       lo;
} hilo;

/* New Type: "wordbyte":
uint16_t, but also accessed as Byte High and Low 
ex:  wordbyte Var;
use: Var.byte.hi; Var.byte.lo; Var.word;  
*/
typedef union
{
  uint16_t      word;
  hilo          byte;
} wordbyte;
           
/* New Type: "flags":
placed into a char, accessed only as individual bits
ex:  flags Var;
use: Var.bit0; Var.bit4;
*/
typedef struct
{
  uint8_t       bit0:1;
  uint8_t       bit1:1;                
  uint8_t       bit2:1;                 
  uint8_t       bit3:1;            
  uint8_t       bit4:1;
  uint8_t       bit5:1;
  uint8_t       bit6:1;
  uint8_t       bit7:1;
} flags;

typedef struct
{
  uint32_t       bit0:1;
  uint32_t       bit1:1;
  uint32_t       bit2:1;
  uint32_t       bit3:1;
  uint32_t       bit4:1;
  uint32_t       bit5:1;
  uint32_t       bit6:1;
  uint32_t       bit7:1;
  uint32_t       bit8:1;
  uint32_t       bit9:1;
  uint32_t       bit10:1;
  uint32_t       bit11:1;
  uint32_t       bit12:1;
  uint32_t       bit13:1;
  uint32_t       bit14:1;
  uint32_t       bit15:1;
  uint32_t       bit16:1;
  uint32_t       bit17:1;
  uint32_t       bit18:1;
  uint32_t       bit19:1;
  uint32_t       bit20:1;
  uint32_t       bit21:1;
  uint32_t       bit22:1;
  uint32_t       bit23:1;
  uint32_t       bit24:1;
  uint32_t       bit25:1;
  uint32_t       bit26:1;
  uint32_t       bit27:1;
  uint32_t       bit28:1;
  uint32_t       bit29:1;
  uint32_t       bit30:1;
  uint32_t       bit31:1;
} flags32;
  
/* New Type: "uint8_flags_t":
unsigned char, accessed as individual bits as well as whole byte 
ex:  uint8_flags_t Var;
use: Var.bit.bit5; Var.byte; 
*/
typedef union
{
  uint8_t       byte;
  flags         bit;
} uint8_flags_t;

typedef struct
{
  wordbyte      hi;
  wordbyte      lo;
} word_hilo;

typedef union
{
  uint32_t      Long;
  word_hilo     word;
} longword;

#endif /* __USER_DEFS_H */
/******************************** END OF FILE *******************************/
