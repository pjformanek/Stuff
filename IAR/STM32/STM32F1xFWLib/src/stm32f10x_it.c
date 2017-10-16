/*******************************************************************************
* File Name          : stm32f10x_it.c
* Author             :
* Version            :
* Date               :
* Description        : Main Interrupt Service Routines.
*                      This file provides template for all exceptions handler
*                      and peripherals interrupt service routine.
********************************************************************************

*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "Includes.h"

#include "GSM_Telit_Config.h"
#include "XPLAT.h"
#include "SYS.h"
#include "LED.h"
#include "Bluetooth.h"
#include "StorageManager.h"
#include "USART_Config.h"
#include "TimerManager.h"
#include "RF_State.h"
#include <intrinsics.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/





#if 0 // 2010-05-27, removed to get rid of warning
static u16 count = 0x0001;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Function Name  : EXTI4_IRQHandler
* Description    : This function handles External interrupt Line 4 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
  if( EXTI_GetITStatus( cEXTI_LINE_SX_DIO0_PIN ) != RESET )
  {
    EXTI_ClearFlag( cEXTI_LINE_SX_DIO0_PIN );
    
    //printf("D0\n"); // debug only
    //bSX_D0Flag = 1;
    
    
    //mUSART_DEBUG_WAIT_AND_SEND('D');
    
    mGPIO_LED_SMT(HI);
    SX_SetDio0Flag( TRUE );
  }  
}


/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 9 to 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
  
//  if(EXTI_GetITStatus( cEXTI_LINE_SX_DIO5_PIN ) != RESET)
//  {
//    EXTI_ClearFlag( cEXTI_LINE_SX_DIO5_PIN );
//    // printf("D5\n"); // debug only 
//    //mUSART_DEBUG_WAIT_AND_SEND(0x35);
//    bSX_D5Flag = 1;
//  }
  
  if(EXTI_GetITStatus( cEXTI_LINE_PED_PIN ) != RESET)
  {
    EXTI_ClearFlag( cEXTI_LINE_PED_PIN );
    SYS_Set_PED_Status( TRUE );
    lwPedDelayTimeStamp = TIMER_GetTimeStamp( 0 );
    #ifdef cGLB_PRODUCT_FOB //*PF
        RF_Pre_Send_A_Packet();
    #endif
    //mUSART_DEBUG_WAIT_AND_SEND('Z');
  }
  else{
    EXTI_ClearFlag( cEXTI_LINE_PED_PIN );
  }
}






/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
  //printf("RING PWU\n");
  if(EXTI_GetITStatus(cEXTI_LINE_RING) != RESET)
  {
    //USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
    //ResetValues();
    if( GlobalPasswordState == 1 )
    {
      GlobalPasswordState = 0;
    }
    //Debug_Message("Enter Password\n\r");
     //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  /* Clear the Key Button EXTI line pending bit */
    EXTI_ClearITPendingBit(cEXTI_LINE_RING);
  }
  
  if(EXTI_GetITStatus( cEXTI_LINE_AUX_PB_PIN ) != RESET)
  {
    //printf( "\nLOCKING UP NOW\n" );
    EXTI_ClearFlag( cEXTI_LINE_AUX_PB_PIN );
    SYS_Set_AUX_PED_Status( TRUE );
    //while(1){}
  }
  
  /* Check if the Wake-Up flag is set */
  if(PWR_GetFlagStatus(PWR_FLAG_WU) != RESET)
  {
    /* Clear Wake Up flag */
    PWR_ClearFlag(PWR_FLAG_WU);
  }
  
  if(EXTI_GetITStatus( cEXTI_LINE_SPEED_PIN ) != RESET)
  {
    EXTI_ClearFlag( cEXTI_LINE_SPEED_PIN );
    SYS_Set_SPEED_Status( TRUE );     
  }
}




/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_UP_IRQHandler( void )
{
  LED_MUTCD_Pattern();
  //kwefk = 10;
}




/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
  LED_JSF_Strobe_Pattern();
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : This function handles TIM7 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{}



  /*******************************************************************************
* Function Name  : TIM8_UP_IRQHandler
* Description    : This function handles TIM8 overflow and update interrupt
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{}

/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFaultException(void)
{
//  u32 bbaabb = 0;
//  bbaabb = NVIC_GetFaultHandlerSources(SystemHandler_HardFault);
//  printf("Fault Handler Sources: %x\n", bbaabb);
//  bbaabb = NVIC_GetFaultAddress(SystemHandler_BusFault);
//  printf("Fault Address_Bus: %x\n", bbaabb);
//  bbaabb = NVIC_GetFaultAddress(SystemHandler_MemoryManage);
//  printf("Fault Address_Mem: %x\n", bbaabb);
 unsigned int stacked_r0; 
 unsigned int stacked_r1; 
 unsigned int stacked_r2; 
 unsigned int stacked_r3; 
 unsigned int stacked_r12; 
 unsigned int stacked_lr; 
 unsigned int stacked_pc; 
 unsigned int stacked_psr; 
 u32* hardfault_args = (u32*) 0x20000400; 

 asm( "TST LR, #4 \n" 
 "ITE EQ \n" 
 "MRSEQ R0, MSP \n" 
 "MRSNE R0, PSP \n"); 

 stacked_r0 = ((unsigned long) hardfault_args[0]); 
 stacked_r1 = ((unsigned long) hardfault_args[1]); 
 stacked_r2 = ((unsigned long) hardfault_args[2]); 
 stacked_r3 = ((unsigned long) hardfault_args[3]); 

 stacked_r12 = ((unsigned long) hardfault_args[4]); 
 stacked_lr = ((unsigned long) hardfault_args[5]); 
 stacked_pc = ((unsigned long) hardfault_args[6]); 
 stacked_psr = ((unsigned long) hardfault_args[7]); 

 printf ("[Hard fault handler]\n"); 
 printf ("R0 = %x\n", stacked_r0); 
 printf ("R1 = %x\n", stacked_r1); 
 printf ("R2 = %x\n", stacked_r2); 
 printf ("R3 = %x\n", stacked_r3); 
 printf ("R12 = %x\n", stacked_r12); 
 printf ("LR = %x\n", stacked_lr); 
 printf ("PC = %x\n", stacked_pc); 
 printf ("PSR = %x\n", stacked_psr); 
 printf ("BFAR = %x\n", (*((volatile unsigned long *)(0xE000ED38)))); 
 printf ("CFSR = %x\n", (*((volatile unsigned long *)(0xE000ED28)))); 
 printf ("HFSR = %x\n", (*((volatile unsigned long *)(0xE000ED2C)))); 
 printf ("DFSR = %x\n", (*((volatile unsigned long *)(0xE000ED30)))); 
 printf ("AFSR = %x\n", (*((volatile unsigned long *)(0xE000ED3C)))); 
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}
// hard fault handler in C,
// with stack frame location as input parameter
void hard_fault_handler_c(unsigned int * hardfault_args)
{
unsigned int stacked_r0;
unsigned int stacked_r1;
unsigned int stacked_r2;
unsigned int stacked_r3;
unsigned int stacked_r12;
unsigned int stacked_lr;
unsigned int stacked_pc;
unsigned int stacked_psr;
unsigned int rBFAR;
unsigned int rCFSR;
unsigned int rHFSR;
unsigned int rDFSR;
unsigned int rAFSR;

stacked_r0 = ((unsigned long) hardfault_args[0]);
stacked_r1 = ((unsigned long) hardfault_args[1]);
stacked_r2 = ((unsigned long) hardfault_args[2]);
stacked_r3 = ((unsigned long) hardfault_args[3]);

stacked_r12 = ((unsigned long) hardfault_args[4]);
stacked_lr = ((unsigned long) hardfault_args[5]);
stacked_pc = ((unsigned long) hardfault_args[6]);
stacked_psr = ((unsigned long) hardfault_args[7]);

rBFAR = (*((volatile unsigned long *)(0xE000ED38)));
rCFSR = (*((volatile unsigned long *)(0xE000ED28)));
rHFSR = (*((volatile unsigned long *)(0xE000ED2C)));
rDFSR = (*((volatile unsigned long *)(0xE000ED30)));
rAFSR = (*((volatile unsigned long *)(0xE000ED3C)));

printf ("[Hard fault handler]\n");
printf ("R0 = %x\n", stacked_r0);
printf ("R1 = %x\n", stacked_r1);
printf ("R2 = %x\n", stacked_r2);
printf ("R3 = %x\n", stacked_r3);
printf ("R12 = %x\n", stacked_r12);
printf ("LR = %x\n", stacked_lr);
printf ("PC = %x\n", stacked_pc);
printf ("PSR = %x\n", stacked_psr);
printf ("BFAR = %x\n", rBFAR);
printf ("CFSR = %x\n", rCFSR);
printf ("HFSR = %x\n", rHFSR);
printf ("DFSR = %x\n", rDFSR);
printf ("AFSR = %x\n", rAFSR);

while(1);

}
/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickHandler(void)
{
  //printf("SYS\n");
  //Debug_Message(" SYS tick \n\r");

  /* Toggle GPIO_LED pin 6 */
    //GPIO_WriteBit(GPIOC, GPIO_Pin_6, (teGIO_BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6))));

  wTIM_SysTickCounter++;


  //Debug_Message("sys\r\n");

  /* Clear SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Clear);
}

/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : PVD_IRQHandler
* Description    : This function handles PVD interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PVD_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TAMPER_IRQHandler
* Description    : This function handles Tamper interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TAMPER_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{

  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {

    
    //LED_I2C_PerformHalfPeriodFlash_2( LED_I2C_GetPattern() );
    /* Clear EXTI line17 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line17);

    /* Check if the Wake-Up flag is set */
    if(PWR_GetFlagStatus(PWR_FLAG_WU) != RESET)
    {
      /* Clear Wake Up flag */
      PWR_ClearFlag(PWR_FLAG_WU);
    }

    TimeDisplay = 1;

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Clear RTC Alarm interrupt pending bit */
    RTC_ClearITPendingBit(RTC_IT_SEC);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }

  if (RTC_GetITStatus(RTC_IT_OW) != RESET)
  {
    printf("\nRTC_OVERFLOW\n");
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Clear RTC Alarm interrupt pending bit */
    RTC_ClearITPendingBit(RTC_IT_OW);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }
  
  
}


/*******************************************************************************
* Function Name  : FLASH_IRQHandler
* Description    : This function handles Flash interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : RCC_IRQHandler
* Description    : This function handles RCC interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
  //printf("SQW\n");
  if(EXTI_GetITStatus( cEXTI_LINE_RTC_INT_SQW_PIN ) != RESET)
  {
    //mRTC_I2C_CLEAR_INT_FLAGS()
    //mRTC_I2C_DISPLAY();
    RTC_I2C_SetInterruptFlag(HI);
    EXTI_ClearFlag( cEXTI_LINE_RTC_INT_SQW_PIN );
  }
  
  // bluetooth interrupt
  printf("BT\n");

  if(EXTI_GetITStatus( cEXTI_LINE_BT_INT_PIN ) != RESET)
  {
    printf("CD\n");
   
    EXTI_ClearFlag( cEXTI_LINE_BT_INT_PIN );
  }
  cBT_Connection_Flag = 1;
  // USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
  // printf("Baby Monkey On A Pig\n");
  //   USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
}

/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus( cEXTI_LINE_RING ) != RESET)
  {
    printf("\nRI\n");
    bGSM_Telit_RingFlag = 1;
    GSM_Telit_SetBusy( cGSM_TELIT_BUSY );
    EXTI_ClearFlag( cEXTI_LINE_RING );
  }
}

/*******************************************************************************
* Function Name  : EXTI2_IRQHandler
* Description    : This function handles External interrupt Line 2 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI2_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : EXTI3_IRQHandler
* Description    : This function handles External interrupt Line 3 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI3_IRQHandler(void)
{}



/*******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel2_IRQHandler
* Description    : This function handles DMA1 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel3_IRQHandler
* Description    : This function handles DMA1 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel3_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel4_IRQHandler
* Description    : This function handles DMA1 Channel 4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
//  /* Check if the Transfer Complete flag is set */  
//  if(DMA_GetITStatus(DMA1_IT_TC4))
//  {  
//    /* Clear the Transfer Complete bit */
//    //DMA_ClearITPendingBit(DMA1_IT_GL4); 
//    DMA_ClearITPendingBit(DMA1_IT_GL4);     
//    DMA_ClearFlag(DMA1_IT_GL4);    
//    
//
//    
//#if 1   // got an error saying that the function is not defined so I commented it out
//
//    if ( LSY201_Transfer_IsDone() )
//    {
//      //wake micro
//    }
//  }
}
//#endif
/*******************************************************************************
* Function Name  : DMA1_Channel5_IRQHandler
* Description    : This function handles DMA1 Channel 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel6_IRQHandler
* Description    : This function handles DMA1 Channel 6 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel6_IRQHandler(void)
{
//  /* Test on DMA1 Channel6 Half Transfer interrupt */
//  if(DMA_GetITStatus(DMA1_IT_HT6))
//  {
//    DMA_USART1_TX();
//    /* Clear DMA1 Channel6 Global interrupt pending bits */
//    DMA_ClearFlag(DMA1_IT_GL6); 
//    DMA_ClearITPendingBit(DMA1_IT_GL6);    
//  }
}
/*******************************************************************************
* Function Name  : DMA1_Channel7_IRQHandler
* Description    : This function handles DMA1 Channel 7 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel7_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles ADC1 and ADC2 global interrupts requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : CAN_RX1_IRQHandler
* Description    : This function handles CAN RX1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : CAN_SCE_IRQHandler
* Description    : This function handles CAN SCE interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{}



/*******************************************************************************
* Function Name  : TIM1_BRK_IRQHandler
* Description    : This function handles TIM1 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{}



/*******************************************************************************
* Function Name  : TIM1_TRG_COM_IRQHandler
* Description    : This function handles TIM1 Trigger and commutation interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM1_CC_IRQHandler
* Description    : This function handles TIM1 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{}



/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)
{
  LED_RRFB_Pattern();
  //kwefk = 8;
//  static u16 ic_readvalue1 = 0, ic_readvalue2 = 0;
//  static u16 capture_number = 0;
//  static u32 CAPTURE = 0;
//  static u32 TIM_FREQ = 0;
//  if(TIM_GetITStatus(TIM3, TIM_IT_CC1) == SET)
//  {
//    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
//    if(capture_number == 0){
//      ic_readvalue1 = TIM_GetCapture1(TIM3);
//      capture_number = 1;
//    }
//    else if(capture_number == 1){
//      ic_readvalue2 = TIM_GetCapture1(TIM3);
//      if(ic_readvalue2 > ic_readvalue1){
//        CAPTURE = (ic_readvalue2 - ic_readvalue1)-1;
//      }
//      else if(ic_readvalue2 < ic_readvalue1){
//        CAPTURE = ((0xFFFF - ic_readvalue1) + ic_readvalue2) - 1;
//      }
//      else{
//        CAPTURE = 0;
//      }
//      TIM_FREQ = (u32)72000000 / CAPTURE;
//      capture_number = 0;
//      global_ExternalFlashDuration = TIM_FREQ;
//    }
//  }
}

/*******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : This function handles TIM4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)
{
  LED_JSF_Strobe_WigWag_Pattern();
  //kwefk = 7;
}

/*******************************************************************************
* Function Name  : I2C1_EV_IRQHandler
* Description    : This function handles I2C1 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : I2C1_ER_IRQHandler
* Description    : This function handles I2C1 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : I2C2_EV_IRQHandler
* Description    : This function handles I2C2 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : I2C2_ER_IRQHandler
* Description    : This function handles I2C2 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : SPI1_IRQHandler
* Description    : This function handles SPI1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_IRQHandler(void)
{
  //printf("spi1\n");
  if( SPI_I2S_GetITStatus( SPI1, SPI_I2S_IT_RXNE ) != RESET )
  {
#if 0
    bSPI1_RX_BufferA[wSPI1Count++] = SPI_I2S_ReceiveData( SPI1 );
    bSPI1_RX_IntFlag = 1;
#endif
  }
}

/*******************************************************************************
* Function Name  : SPI2_IRQHandler
* Description    : This function handles SPI2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI2_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
  //printf("usart1\n");
  //static u8 buffToggle = 0;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit( USART1, USART_IT_RXNE );
    bUSART1_RX_IntFlag = 1;
//    if(!setTimer1)
//    {
//      setTimer1++;
//      buffToggle1 ^= 1;
//      wUsart1Count = 0;
//      wUsart1Count2 = 0;
//    }
    if(buffToggle1)
    {
      if(wUsart1Count<=255){
        bUSART1_RX_Buffer[wUsart1Count++] = USART_ReceiveData( USART1 );
      }
    }
    else
    {
      if(wUsart1Count2<=255){
        bUSART1_RX_Buffer2[wUsart1Count2++] = USART_ReceiveData( USART1 );
      }
    }
  }
  else{
    USART_ReceiveData( USART1 );
  }
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{

////  //printf("USART2\n");
//  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//  {
//
//     USART_Config_Usart2IdleIt( ENABLE );
//     //bUSART2_RX_Buffer[bCount++] = USART_ReceiveData( USART2 );
//     USART_ClearITPendingBit( USART2, USART_IT_RXNE );
//  }
 
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    if( bUSART2_RX_IntFlag & cXPLAT_USART_GSM_FLAG )
    {
      bUSART2_RX_IntFlag = 1;
      //bUSART2_RX_Buffer[0] = USART_ReceiveData( USART2 );
      
      
    }
    else if( bUSART2_RX_IntFlag & cXPLAT_USART_XPLAT_FLAG )
    {
      GSM_Telit_Load_Buffers( USART_ReceiveData( USART2 ) );
    }
    else
    {
      USART_ReceiveData( USART2 );
    }
    USART_ClearITPendingBit( USART2, USART_IT_RXNE );
  }
//
//  if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
//  {
//#if 0
////    bUSART2_RX_IntFlag = 1;
////
////    wUsart2Count = bCount;
////    bCount = 0;
////
////    USART_Config_Usart2IdleIt( DISABLE );
//#endif 
//    USART_ClearITPendingBit( USART2, USART_IT_IDLE );
//  }
  
  
//  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
//  {
 
//    USART_ClearITPendingBit( USART2, USART_IT_TXE );
//  }
  
//  static u8 buffToggle2 = 0;
  ////comment from here
//  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//  {
//    lwUSART2TimeStamp = TIMER_GetTimeStamp( 0 );
//    if(!setTimer2)
//    {
//      setTimer2++;
//      buffToggle2 ^= 1;
//      wUsart2Count = 0;
//      wUsart2Count2 = 0;
//    }
//    if(buffToggle2)
//    {
//      bUSART2_RX_Buffer[wUsart2Count++] = USART_ReceiveData( USART2 );
//    }
//    else
//    {
//      bUSART2_RX_Buffer2[wUsart2Count2++] = USART_ReceiveData( USART2 );
//    }
//    USART_ClearITPendingBit( USART2, USART_IT_RXNE );
//    bUSART2_RX_IntFlag = 1;
//  }
}

/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{
#if 0
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
     USART_Config_Usart3IdleIt( ENABLE );

     bUSART3_RX_Buffer[wUsart3Count++] = USART_ReceiveData( USART3 );

     USART_ClearITPendingBit( USART3, USART_IT_RXNE );
  }



  if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
  {
    bUSART3_RX_IntFlag = 1;

    wUsart3Count = 0;

    USART_Config_Usart3IdleIt( DISABLE );

    USART_ClearITPendingBit( USART3, USART_IT_IDLE );
  }
#else
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
    if( bUSART3_RX_IntFlag & cXPLAT_USART_GSM_FLAG )
    {
      bUSART3_RX_IntFlag = 1;
      USART_ClearITPendingBit( USART3, USART_IT_RXNE );
    }
    else if( bUSART3_RX_IntFlag & cXPLAT_USART_XPLAT_FLAG )
    {
      bUSART3_RX_Buffer[0] = USART_ReceiveData( USART3 );
      USART_ClearITPendingBit( USART3, USART_IT_RXNE );
      //XPLAT_PacketParser( (u8*)bUSART3_RX_Buffer , 1, cUSART_USART_DEBUG_ENABLE );
      //mUSART_DEBUG_WAIT_AND_SEND('G');
    }
    else
    {
      USART_ReceiveData( USART3 );
      USART_ClearITPendingBit( USART3, USART_IT_RXNE );
    }
    
    

  }
  
  
  if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
  {
    USART_Config_Usart3IdleIt( DISABLE );
    USART_ClearITPendingBit( USART3, USART_IT_IDLE );
  }
//  printf(">%c", USART_ReceiveData( USART3 ));


#endif

}



/*******************************************************************************
* Function Name  : RTCAlarm_IRQHandler
* Description    : This function handles RTC Alarm interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_ALR) != RESET)
  {    
    //mGPIO_LED_SMT_TOGGLE();
    //LED_I2C_PerformHalfPeriodFlash_2( LED_I2C_GetPattern() );
    
   
    /* Clear EXTI line17 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line17);

    /* Check if the Wake-Up flag is set */
    if(PWR_GetFlagStatus(PWR_FLAG_WU) != RESET)
    {
      /* Clear Wake Up flag */
      PWR_ClearFlag(PWR_FLAG_WU);
    }

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();   
    /* Clear RTC Alarm interrupt pending bit */
    RTC_ClearITPendingBit(RTC_IT_ALR);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    
    
    
#ifdef cGLB_RF_ENABLE 
    // here I can make the call that switches frequencies
    //RF_Set_Sync();
#endif
  }
}

/*******************************************************************************
* Function Name  : USBWakeUp_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM8_BRK_IRQHandler
* Description    : This function handles TIM8 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{}



/*******************************************************************************
* Function Name  : TIM8_TRG_COM_IRQHandler
* Description    : This function handles TIM8 Trigger and commutation interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM8_CC_IRQHandler
* Description    : This function handles TIM8 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{
//  static u16 ic_readvalue1 = 0, ic_readvalue2 = 0;
//  static u16 capture_number = 0;
//  static u32 CAPTURE = 0;
//  static u32 TIM_FREQ = 0;
//  if(TIM_GetITStatus(TIM3, TIM_IT_CC1) == SET)
//  {
//    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
//    if(capture_number == 0){
//      ic_readvalue1 = TIM_GetCapture1(TIM3);
//      capture_number = 1;
//    }
//    else if(capture_number == 1){
//      ic_readvalue2 = TIM_GetCapture1(TIM3);
//      if(ic_readvalue2 > ic_readvalue1){
//        CAPTURE = (ic_readvalue2 - ic_readvalue1)-1;
//      }
//      else if(ic_readvalue2 < ic_readvalue1){
//        CAPTURE = ((0xFFFF - ic_readvalue1) + ic_readvalue2) - 1;
//      }
//      else{
//        CAPTURE = 0;
//      }
//      TIM_FREQ = (u32)72000000 / CAPTURE;
//      capture_number = 0;
//      global_ExternalFlashDuration = TIM_FREQ;
//    }
//  }
}

/*******************************************************************************
* Function Name  : ADC3_IRQHandler
* Description    : This function handles ADC3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC3_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : FSMC_IRQHandler
* Description    : This function handles FSMC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM5_IRQHandler
* Description    : This function handles TIM5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM5_IRQHandler(void)
{
  LED_MUTCD_WigWag_Pattern();
  //kwefk = 6;
}

/*******************************************************************************
* Function Name  : SPI3_IRQHandler
* Description    : This function handles SPI3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI3_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : UART4_IRQHandler
* Description    : This function handles UART4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART4_IRQHandler(void)
{
  static u8 buffToggle = 0;

  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {
    lwUART4TimeStamp = TIMER_GetTimeStamp( 0 );
    if(!setTimer4)
    {
      setTimer4++;
      buffToggle ^= 1;
      wUart4Count = 0;
      wUart4Count2 = 0;
    }
    if(buffToggle)
    {
      bUART4_RX_Buffer[wUart4Count++] = USART_ReceiveData( UART4 );
    }
    else
    {
      bUART4_RX_Buffer2[wUart4Count2++] = USART_ReceiveData( UART4 );
    }
    USART_ClearITPendingBit( UART4, USART_IT_RXNE );
    bUART4_RX_IntFlag = 1;
  }
}

/*******************************************************************************
* Function Name  : UART5_IRQHandler
* Description    : This function handles UART5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART5_IRQHandler(void)
{
  volatile static u8 byte_received = 0;
//  if(USART_GetITStatus(UART5, USART_IT_ORE) != RESET){
//    USART_ClearITPendingBit( UART5, USART_IT_ORE );
//    //printf("\n\nORE\n\n");
//  }
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
  {
    u8 crashFix = USART_ReceiveData( UART5 );
    #ifdef cGLB_PRODUCT_OLDSZ_READER   
    //printf ("%c",USART_ReceiveData( UART5 ));
    switch(byte_received){
    case 0:
      if(crashFix == 0x52)
        byte_received = 1;
      break;
    case 1:
      if(crashFix == 0x32 || crashFix == 0x31)
        byte_received = 2;
      else
        byte_received = 0;
      break;
    case 2:
      if(crashFix == 0x41)
        byte_received = 3;
      else if(crashFix == 0x49)
        byte_received = 4;
      else
        byte_received = 0;
      break;
    case 3:
      if(crashFix == 0x2C){
        SYS_Set_OLDSZ_Status(0x80);
      }
      byte_received = 0;
      break;
    case 4:
      if(crashFix == 0x2C){
        SYS_Set_OLDSZ_Status(0x40);
      }
      byte_received = 0;
      break;
    default:
      byte_received = 0;
      break;
    }
    #endif
    USART_ClearITPendingBit( UART5, USART_IT_RXNE );
  }
  else{
    USART_ReceiveData( UART5 );
  }
//  if(USART_GetITStatus(UART5, USART_IT_FE) != RESET){
//    USART_ClearITPendingBit( UART5, USART_IT_FE );
//  }
}

/*******************************************************************************
* Function Name  : TIM6_IRQHandler
* Description    : This function handles TIM6 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM6_IRQHandler(void)
{
  LED_RRFB_WWS();
}



/*******************************************************************************
* Function Name  : DMA2_Channel1_IRQHandler
* Description    : This function handles DMA2 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA2_Channel2_IRQHandler
* Description    : This function handles DMA2 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA2_Channel3_IRQHandler
* Description    : This function handles DMA2 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA2_Channel4_5_IRQHandler
* Description    : This function handles DMA2 Channel 4 and DMA2 Channel 5
*                  interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel4_5_IRQHandler(void)
{}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
