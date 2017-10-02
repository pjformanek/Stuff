/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : L2_GSM.c
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : June 10, 2009
* Description        : Layer 2 Telit interactions
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "Includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
sc8 * pbL2_GSM_RspLookUpTable[] = {
                                    cAT_RSP_ERROR, cAT_RSP_OK, 
                                    cAT_RSP_NO_CARRIER                                       
                                 };

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : L2_GSM_RspLookUpTable
* Description    : Takes a string input and outputs it to the serial port usart3
* Input          : u8 * pbUSART_RX_Buffer - pointer to message string containing
*                                           ASCII At command
* Output         : None
* Return         : u16 i position of the look up table where the at command is
*******************************************************************************/
u16 L2_GSM_RspLookUpTable( u8 * pbUSART_RX_Buffer ) 
{
  const int wAvailableRspCommands = sizeof pbL2_GSM_RspLookUpTable / sizeof *pbL2_GSM_RspLookUpTable;
    
  for(int i=0; i!= wAvailableRspCommands; i++)
  {
    if( strcmp( pbUSART_RX_Buffer, pbL2_GSM_RspLookUpTable[i]) == 0 )
    {
      return i;
    }
  }
  return 0;
}



/*******************************************************************************
* Function Name  : L2_GSM_InitSettings
* Description    : This function populates some of the setting for the telit
*                  device and also makes sure that the telit device is up and 
*                  running 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 L2_GSM_InitSettings( void )
{
  //( cAT_CMD_SOFTWARE_RESET );
  printf( "%s\n", cAT_CMD_SOFTWARE_RESET );
  
  
  //mL2_GSM_SEND_AT_CMD_USART2( cAT_CMD );
  printf( "%s\n", cAT_CMD_SOFTWARE_RESET );
  
  //mL2_GSM_SEND_AT_CMD_USART2( cAT_CMD );
  printf( "%s\n", cAT_CMD_SOFTWARE_RESET );
  
  return 1;
}

// ups tracking number   1z03y710dk58069486
// 18007425877 


/*******************************************************************************
* Function Name  : L2_GSM_InitSettings
* Description    : This function populates some of the setting for the telit
*                  device and also makes sure that the telit device is up and 
*                  running 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 L2_GSM_SendATcmd( u8 * pbAtCmd , u16 wTimeOutsms )
{
  printf( "%s\n", pbAtCmd );
  
  //mL2_GSM_SEND_AT_CMD_USART2( pbAtCmd );
  
  bUSART_debugTriggerUsart2 = 1;
  
  if( L2_GSM_WaitForCommand( wTimeOutsms ) == 1 ) // if response came in fine 
  {
    
  }
  else if( L2_GSM_WaitForCommand( wTimeOutsms ) == cL2_GSM_TIM1_TIMEOUT ) // function timed out 
  {
    
  }
  
  return 1;
}



/*******************************************************************************
* Function Name  : L2_GSM_InitSettings
* Description    : This function populates some of the setting for the telit
*                  device and also makes sure that the telit device is up and 
*                  running 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 L2_GSM_WaitForCommand( u16 wTimeOutsms ) 
{
  u8 bTimeOutFlag = 0;
    
  if( wTimeOutsms > cL2_GSM_NO_TIMEOUT )
  {
    TIM1_Configuration(  wTimeOutsms );
    TIM_Cmd(TIM1, ENABLE); 

    while( bUSART2_RX_IntFlag == 0 )
    {
       if( TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET )
       {
           TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
             
           bTimeOutFlag = 1;
           TIM_Cmd(TIM1, DISABLE);
           break;        
       }     
    }
    
    if( bTimeOutFlag == 1 )
    {
      return cL2_GSM_TIM1_TIMEOUT;
      //time out was generated resend or keep going not up to this funtion 
    }
    else
    {
      return bUSART2_RX_IntFlag; 
    }
  }
  
  
  else if( wTimeOutsms == cL2_GSM_NO_TIMEOUT )
  {
    
  }
  
  else
  {
    //error invalid entry
  }
  return 1;
}