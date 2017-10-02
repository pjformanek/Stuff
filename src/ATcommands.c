/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : ATcommands.c
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Oct 16, 2008
* Description        : Set up file for the Telit device
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "Includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static u8 state= 0 ;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : DO_ATcommands
* Description    : Sends the AT commands necessary to receive voice calls
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DO_ATcommands( void )
{
     Send_AT_CMD_USART2 ( mAT_CMD_SOFTWARE_RESET() );
     Delay(0xFFFFF);
     
     Send_AT_CMD_USART2 ( mAT_CMD() );
     Delay(0xFFFFF);
        
     Send_AT_CMD_USART2 ( mAT_CMD_VOICE() );
     Delay(0xFFFFF);
    
     Send_AT_CMD_USART2 ( mAT_CMD_AUTO_ANSWER_1_RINGS() );
     Delay(0xFFFFF);
     
//     Send_AT_CMD_USART2 ( mAT_CMD_DIALTEST() );
//     Delay(0XFFFFF);
     
     
}

/*******************************************************************************
* Function Name  : Send_AT_CMD_USART2
* Description    : Sends AT commands to the telit device using USART2
* Input          : u8* command, pointer to a AT command string 
* Output         : None
* Return         : None
*******************************************************************************/
void Send_AT_CMD_USART2( u8* command )
{
  //<cr> default value is 13 decimal or 0x0D or "\r\n"
  u8 i = 0;
  while ( command[i] )
  {
    UART2_WAIT_AND_SEND( command[i] );
    i++;   
    //USART_SendData(USART2, );                                       // this was the original code in this function juan clean up 
    //while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){ }
     
  } 
}



// THIS FUNCTIONS MAY NOT BE NEEDED AT ALL ===============================================================juan clean up


/*******************************************************************************
* Function Name  : your function
* Description    : your function's description
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Send_AT_CMD_USART3( u8* command )
{
  //<cr> default value is 13 decimal or 0x0D or "\r\n"
  u8 i = 0;
  while ( command[i] )
  {
    UART3_WAIT_AND_SEND( command[i] );
    i++;    
  } 
}


/*******************************************************************************
* Function Name  : your function
* Description    : your function's description
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void AT_App_Main( u8 TelitChar )
{
  UART3_WAIT_AND_SEND( TelitChar );
  switch( state )
  {
    case 0:
      if( TelitChar == 'N' )
        state = 1;
      break;
      
    case 1:
      if( TelitChar == 'O' )
      {
        GlobalPasswordState = 0;  
        state = 0;
      }
      else
      {
        state = 0;
      }
      break;
      
    default:
      state = 0;
      break;    
  }  
}