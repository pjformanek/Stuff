/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : DTMF.c
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Dec 23, 2008
* Description        : your description
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "Includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : DTMF_Decoder
* Description    : Decodes the 4 binary input from the DTMf decoder chip and 
*                  stores the result in an ASCII u8 
* Input          : None
* Output         : u8 i - byte result in ASCII
* Return         : None
*******************************************************************************/
u8 DTMF_Decoder( void )
{
  u8 i = 0;
  
  i = GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_15);                   //D3
  i = GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_14) + (i << 1);        //D2
  i = GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_13) + (i << 1);        //D1
  i = GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_12) + (i << 1);        //D0
  i = i + 0x30;
  
  
  //UART3_WAIT_AND_SEND(i); //spm
  
  return i;
  
}

//the way shawn would do this
      /*
      i =  GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_12);               //D0
      i = (GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_13) + (i << 1));  //D1
      i = (GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_14) + (i << 2));  //D2
      i = (GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_15) + (i << 3));  //D3
      i = i + 0x30;  //covert i to an ascii value
      */