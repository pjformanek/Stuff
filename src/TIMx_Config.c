/*------------------------------------------------------------------------------
  	$File:		TIMx_Config.c
  	$Module:  	Timer configuration settings
  	$Prefix:  	TIM
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Dec 23, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_TIMX_CONFIG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "MEM.h"
#include "NVIC_Config.h"

#include "TIMx_Config.h"

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

/*------------------------------------------------------------------------------
				----- L O C A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

static void (*TheCallBack)(void) = NULL;

/*------------------------------------------------------------------------------
				----- G L O B A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
vu16 vwTIM_Ticks_Tim1;
volatile tTIM_VAR rTIM_Ticks_Tim2;
vu16 wTIM_SysTickCounter = 0;

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */



/*------------------------------------------------------------------------------
	$Function: NVIC_TIM2_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_TIM1_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}



/*------------------------------------------------------------------------------
	$Function: NVIC_TIM2_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_TIM2_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}

/*------------------------------------------------------------------------------
	$Function: NVIC_TIM2_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_TIM3_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}
/*------------------------------------------------------------------------------
	$Function: NVIC_TIM4_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_TIM4_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}
/*------------------------------------------------------------------------------
	$Function: NVIC_TIM5_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_TIM5_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}
void NVIC_TIM6_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}
/*------------------------------------------------------------------------------
				----- G L O B A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */


void TIM1_SetTimer( u16 wTimeOutms )
{
  
  
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = wTimeOutms;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
}

/*------------------------------------------------------------------------------
	$Function: TIM1_Configuration
	$Description: Configurations for Timer1 in this case Timer1 has been
                      configured to a 1ms pulse according to a 16Mhz xtal check

	$Inputs: u16 TimeOutms - a decimal value of the timeout in ms
                                 This function is configured to run under 8 Mghz only
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TIM1_Configuration( u16 wTimeOutms )
{
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE );

  //wTimeOutms = ( wTimeOutms * 10 );
  // Set timer period 0.001 sec
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = wTimeOutms;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  // Clear update interrupt bit
  TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
  // Enable update interrupt
  TIM_ITConfig(TIM1, TIM_FLAG_Update, ENABLE);

  NVIC_TIM1_Configuration( ENABLE );
}

/*------------------------------------------------------------------------------
	$Function: TIM2_ReturnCounterValue
	$Description: Returns the current value of the TIM2 Tick counter

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
tTIM_VAR TIM2_ReturnCounterValue( void )
{
  return rTIM_Ticks_Tim2;
}



/*------------------------------------------------------------------------------
	$Function: TIM2_UpdateCounterValue
	$Description: updates the timer 2 variable

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TIM2_UpdateCounterValue( tTIM_VAR rNewCounterValue )
{
  rTIM_Ticks_Tim2 = rNewCounterValue;
}


/*------------------------------------------------------------------------------
	$Function: TIM2_Configuration
	$Description: Configurations for Timer2

	$Inputs: u16 TimeOutus - a decimal value of the timeout in us
                                 This function is configured to run under 8 Mghz only
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TIM2_Configuration( u16 wTimeOutus )
{
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );

  //wTimeOutus = ( wTimeOutus * 8 );
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = wTimeOutus;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  // Clear update interrupt bit
  TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
  // Enable update interrupt
  TIM_ITConfig(TIM2, TIM_FLAG_Update, ENABLE);

  NVIC_TIM2_Configuration( ENABLE );
}

/*------------------------------------------------------------------------------
	$Function: TIM2_Configuration
	$Description: Configurations for Timer2

	$Inputs: u16 TimeOutus - a decimal value of the timeout in us
                                 This function is configured to run under 8 Mghz only
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TIM4_Configuration( u16 wTimeOutus )
{
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );

  //wTimeOutus = ( wTimeOutus * 8 );
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = wTimeOutus;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  // Clear update interrupt bit
  TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);
  // Enable update interrupt
  TIM_ITConfig(TIM4, TIM_FLAG_Update, ENABLE);

  NVIC_TIM4_Configuration( ENABLE );
}
void TIM5_Configuration( u16 wTimeOutus )
{
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM5, ENABLE );

  //wTimeOutus = ( wTimeOutus * 8 );
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = wTimeOutus;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  // Clear update interrupt bit
  TIM_ClearITPendingBit(TIM5, TIM_FLAG_Update);
  // Enable update interrupt
  TIM_ITConfig(TIM5, TIM_FLAG_Update, ENABLE);

  NVIC_TIM5_Configuration( ENABLE );
}
void TIM6_Configuration( u16 wTimeOutus )
{
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM6, ENABLE );

  //wTimeOutus = ( wTimeOutus * 8 );
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = wTimeOutus;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  // Clear update interrupt bit
  TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);
  // Enable update interrupt
  TIM_ITConfig(TIM6, TIM_FLAG_Update, ENABLE);

  NVIC_TIM6_Configuration( ENABLE );
}
/*------------------------------------------------------------------------------
	$Function: SysTick_Configuration
	$Description: Configurations for the system tick

	$Inputs: u32 lwTimeOut -  word controlling the lenght of the systick
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void SysTick_Configuration( u32 lwTimeOut )
{
  /* SysTick end of count event each 1ms with input clock equal to 8MHz (HCLK/8, default) */
  SysTick_SetReload(0x0F3000);  // used to eb 100000

  /* Enable SysTick interrupt */
  SysTick_ITConfig(ENABLE);

  /* Enable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Enable);
}

/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TIM2_Callback( void )
{
  TheCallBack();
}

/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TIM1_Callback( void )
{
  TheCallBack();
}

void TIM1_Func( u16 wTimeOutms, void (*pfCallBack)(void) )
{
  TIM1_Configuration( wTimeOutms );
  TheCallBack = pfCallBack;
  TIM_Cmd( TIM1, ENABLE );
}

void TIM1_TestFunc2( void )
{
  printf("Call back TIM1!!\n");
}
void TIM3_Configuration( u16 wTimeOutus )
{
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );

  //wTimeOutus = ( wTimeOutus * 8 );
  TIM_TimeBaseStructure.TIM_Prescaler = 8000;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = wTimeOutus;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  // Clear update interrupt bit
  TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
  // Enable update interrupt
  TIM_ITConfig(TIM3, TIM_FLAG_Update, ENABLE);

  NVIC_TIM3_Configuration( ENABLE );
}
#undef cMEM_USERCLASS_ID_TIMX_CONFIG_c