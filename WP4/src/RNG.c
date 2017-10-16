/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : yourcfile.c
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Dec 29, 2008
* Description        : Random Number Generator
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
* Function Name  : your function
* Description    : your function's description
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u16 RNG( u16 wRandomInput )
{
  int t;
  
  u32 dDevID;
  
  dDevID =  DBGMCU_GetDEVID();
  
  srand( ( rand()%rand() ) + wRandomInput + dDevID);
  t = rand();
  #ifdef mDEBUG_MODE
  UART3_WAIT_AND_SEND(t>>4);
  UART3_WAIT_AND_SEND(t);
  #endif
  
  return t;
}


/*******************************************************************************
* Function Name  : RandomAB_ID_Generator
* Description    : generates a random 16 bit number and validates the new generated id
* Input          : u16 wRandomInput - extra ramdon seed,to add extra randomness 
* Output         : None
* Return         : u16 RandomID - the id generated
*******************************************************************************/
u16 RandomAB_ID_Generator( u16 wRandomInput ) 
{
  u16 RandomID;
  //u32 dDevID = DBGMCU_GetDEVID();
  u8 ValidRandomDataFlag = 0;         // MAY NEED TO INSERT TIMEOUT JUST IN CASE IT GETS STUCK FOREVER HERE WDGT COULD BE GOOOD
  do
  {
    RandomID = RNG( rand() );
    ValidRandomDataFlag = ValidateNewRandomData( RandomID );
  }
  while( ValidRandomDataFlag != 1 );
  return RandomID; 
}
