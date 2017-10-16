/*------------------------------------------------------------------------------
$File:		RTC_Config.c
$Module:  	Configuration for the internal( external ) RTC
$Prefix:  	RTC
$Language:	ANSI C

$Description:
        
$Notes:

$Author:	Jramirez, Feb 02, 2009
                PFormanek, 2017-Oct-12
--------------------------------------------------------------------------
$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
--------------------------------------------------------------------------
$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_RTC_CONFIG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "MEM.h"
#include "NVIC_Config.h"
#include "EXTINT_Config.h"
#include "RTC_Config.h"
#include "platform_config.h"



/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N   P R O T O T Y P E S -----
  ------------------------------------------------------------------------------
 */
u32 Local_RTC_NumbersOfTicksElapsedSince( u32 lwTimeStamp );

/*------------------------------------------------------------------------------
				----- L O C A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
vu32 TimeDisplay = 0;


/*------------------------------------------------------------------------------
				----- G L O B A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */


/*------------------------------------------------------------------------------
	$Function: NVIC_RTC_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_RTC_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the RTC Alarm Interrupt */
#ifndef LED_MODE
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
#endif
  
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);

}

/*------------------------------------------------------------------------------
	$Function: EXTINT_RtcAlarmConfiguration
	$Description: Configures EXTI line17 to RTC Alarm event for wakeup from
                      low power modes
	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void EXTINT_RtcAlarmConfiguration( void )
{
  EXTI_InitTypeDef EXTI_InitStructure;
  
  /* Configure EXTI Line17(RTC Alarm) to generate an interrupt on rising edge */
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);   
}


/*------------------------------------------------------------------------------
	$Function: Local_RTC_NumbersOfTicksElapsedSince
	$Description: returns 1 if timestamp has elapsed

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u32 Local_RTC_NumbersOfTicksElapsedSince( u32 lwTimeStamp )
{
  u32 temp = RTC_GetCounter();

  /* sample the timer first ... otherwise error can occur if timer wraps
  during execution of this function
  */
  temp = RTC_GetCounter();

  /* first check and see if timer has wrapped
  */
  if( temp < lwTimeStamp )
  {
    /* timer has wrapped ... subtract time-stamp from max-time and then
    add the current value of the system timer
    */
    return( ((cRTC_tick_MAX) - lwTimeStamp) + temp );
    /* note: order of operations in statement above does not actually matter */
  } else {
    /* timer has not wrapped ... subtract the time-stamp value from the
    system timer value
    */
    return( temp - lwTimeStamp );
  }
}



/*------------------------------------------------------------------------------
				----- G L O B A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
$Function: RTC_Init
$Description: Inits the RTC timer module

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void RTC_Init( void )
{
  EXTINT_RtcAlarmConfiguration();
  NVIC_RTC_Configuration( ENABLE );
  RTC_Configuration( 1 );
}

/*------------------------------------------------------------------------------
	$Function: RTC_Configuration
	$Description: Configures the RTC.

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void RTC_Configuration( u32 ulPrescalerRtc )
{
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);


  /* RTC clock source configuration ------------------------------------------*/
  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

#if 1
  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);
   /* Wait till LSE is ready */
//  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
//  {
//  }

  for( int H = 0; H < 200; H++){
    if ( RCC_GetFlagStatus(RCC_FLAG_LSERDY) == SET ){
      printf("\n%d / 200\n",H);//, #: %d",H,RCC_GetFlagStatus(RCC_FLAG_LSERDY));
      break;
    }
    printf("\n%d / 200",H);//,RCC_GetFlagStatus(RCC_FLAG_LSERDY));
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    Delay(500*cDELAY_Timeout_1ms);
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    Delay(500*cDELAY_Timeout_1ms);
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE 
  }
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#else
  RCC_LSICmd( ENABLE );
  
  /* Wait till LSE is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#endif
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);
  /* RTC configuration -------------------------------------------------------*/
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();


  /* Set the RTC time base to 1s */
  //RTC_SetPrescaler( ulPrescalerRtc );   /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
#ifdef LED_MODE
  RTC_SetPrescaler( 2031 );
#else
  RTC_SetPrescaler( 3276 );
#endif
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  //printf("\n z\n");
  /* Enable the RTC Alarm interrupt */
  RTC_ITConfig(RTC_IT_ALR, ENABLE);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  //printf("\n k\n");
  /* Enable the RTC Alarm interrupt */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Alarm interrupt */
  RTC_ITConfig(RTC_IT_OW, ENABLE);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

}


/*------------------------------------------------------------------------------
	$Function: Time_Adjust
	$Description: Adjusts time.

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void Time_Adjust(void)
{
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  /* Change the current time */
  RTC_SetCounter(0x00015180);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Return the value to store in RTC counter register */
//  return((Tmp_HH*3600 + Tmp_MM*60 + Tmp_SS));
}


/*------------------------------------------------------------------------------
	$Function: Time_Display
	$Description: Displays the current time.

	$Inputs: u32 TimeVar - TimeVar: RTC counter value.
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void Time_Display(u32 TimeVar)
{
  u32 THH = 0, TMM = 0, TSS = 0;

  /* Compute  hours */
  THH = TimeVar / 3600;
  /* Compute minutes */
  TMM = (TimeVar % 3600) / 60;
  /* Compute seconds */
  TSS = (TimeVar % 3600) % 60;

  printf("Time: %0.2d:%0.2d:%0.2d\n", THH, TMM, TSS);
}


/*------------------------------------------------------------------------------
	$Function: Time_Show
	$Description: Shows the current time (HH:MM:SS) on the Hyperterminal.

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void Time_Show(void)
{
  printf("Time Show\n");

  /* Infinite loop */
  while (1)
  {
    /* If 1s has paased */
    if (TimeDisplay == 1)
    {
      /* Display current time */
      Time_Display(RTC_GetCounter());
      TimeDisplay = 0;
    }
  }
}


/*------------------------------------------------------------------------------
	$Function: RTC_ReturnCounter
	$Description: return the current count of the counter

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/

u32 RTC_ReturnCounter( u32 lwTimeStampShift )
{
  u32 temp = RTC_GetCounter();


  temp = RTC_GetCounter();

  /* first check and see if timer will wrap once shift added
  */
  if( temp <= (cRTC_tick_MAX - lwTimeStampShift) )
  {
    /* timer will not wrap with shift added
    */
    temp += lwTimeStampShift;
  }
  else
  {
    /* timer will wrap
    */
    temp = cRTC_tick_MAX - temp;
    temp = lwTimeStampShift - temp;
  }

  return( temp );
}




/*------------------------------------------------------------------------------
	$Function: RTC_HasTimeStamElapsed
	$Description: returns 1 if timestamp has elapsed

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u32 RTC_HasTimeStampElapsed( u32 lwTimeStamp, u32 lwTimeout )
{
  u32 lwElapsedTicks = 0;
  u32 lwTempRtcCounter = RTC_GetCounter();


  lwElapsedTicks = Local_RTC_NumbersOfTicksElapsedSince( lwTimeStamp );

  /* set to "FALSE" so caller will not use the result
  */
  if( lwElapsedTicks < lwTimeout ) {
    lwElapsedTicks = 0;
  }

  return( lwElapsedTicks );
}



/*------------------------------------------------------------------------------
        $Function: RTC_Set_Alarm
        $Description: Sets the alarm on the internal RTC 
        
        $Inputs: u32 ulTime_To_Wait - time ticks to wait until alarm comes in as interrupt
        $Outputs: none
        $Assumptions:
        $WARNINGS:
        $End
*/
void RTC_Set_Alarm( u32 ulTime_To_Wait )
{
  /* Alarm in 3 second */
    RTC_SetAlarm(RTC_GetCounter()+ ulTime_To_Wait);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}



#undef cMEM_USERCLASS_ID_RTC_CONFIG_c