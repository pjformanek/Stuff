/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : App_Main.c
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Dec 22, 2008
* Description        : your description
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "Includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//static u8 state = 0;
#ifdef mDTMF_ENABLE
static u8 PassState = 0;
#endif

APP_PassWordTypeDef AppPassWord;
uc8 bitMask8[] = {
   0x80,  // binary 10000000
   0x40,  // binary 01000000
   0x20,  // binary 00100000
   0x10,  // binary 00010000
   0x08,  // binary 00001000
   0x04,  // binary 00000100
   0x02,  // binary 00000010
   0x01   // binary 00000001
};


/* Global Variables ----------------------------------------------------------*/
#ifdef mDTMF_ENABLE
static u8 GlobalPasswordState;
#endif
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : your function
* Description    : your function's description
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void App_Main( void )
{
 
  
}


#ifdef mDTMF_ENABLE
/*******************************************************************************
* Function Name  : your function
* Description    : your function's description
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 PasswordCheck( u8 DTMFval )
{
  switch( PassState )
  {
    case 0:     
       Debug_Message("First password digit\r\n" );
       AppPassWord.PassByteH = DTMFval;
       PassState = 1;     
    break;
                      
    case 1:     
      Debug_Message("Second password digit\r\n" );
      AppPassWord.PassByteM = DTMFval;
      PassState = 2;
    break;
    
    case 2:       
      Debug_Message("Third password digit\r\n ");           
      AppPassWord.PassByteL = DTMFval;
      
      if( AppPassWord.PassByteH == mAPP_PASS_BYTE_H  && AppPassWord.PassByteM ==  mAPP_PASS_BYTE_M &&
          AppPassWord.PassByteL == mAPP_PASS_BYTE_L )
      {
        PassState = 0;        
        Debug_Message("Password is correct!!!\r\n ");
               
        return 1; 
      }
      else
      {
        PassState = 0;
        
        Debug_Message("Wrong password try again\r\n");  
        
        return 0; 
      }
    break;
    
    default:    
      PassState = 0;
      Debug_Message("Error has occurred\r\n");
    break;  
  }  
  return 0;
}


/*******************************************************************************
* Function Name  : your function
* Description    : your function's description
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ResetValues( void )
{
  //GLB_HangUpCall = 0;
  state = 0;
  PassState = 0; 
}

#endif
