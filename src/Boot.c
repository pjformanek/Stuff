/*------------------------------------------------------------------------------
  	$File:		Boot.c
  	$Module:  	Boot configuration for all peripherals
  	$Prefix:  	BOOT
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Jrmairez, Dec 22, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_BOOT_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
*/

#include "stm32f10x_lib.h"

#include "GLB.h"
#include "MEM.h"

#include "platform_config.h"
#include "GPIO_Config.h"
#include "RCC_Config.h"
#include "DEBUG.h"
#include "EXTINT_Config.h"
#include "NVIC_Config.h"
#include "Delay.h"
#include "RTC_COnfig.h"


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

/*------------------------------------------------------------------------------
				----- G L O B A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- G L O B A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */


/*------------------------------------------------------------------------------
	$Function: GPIO_Init_Configuration
	$Description: Inits all GPIO to GPIO_Mode_IN_FLOATING
                      on exit it will disable all RCC clocks


	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
//void GPIO_Init_Configuration( void )
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  
//  /*******************************************************************************************/
//   /* Configure all unused GPIO port pins in Analog Input mode (floating input
//     trigger OFF), this will reduce the power consumption and increase the device
//     immunity against EMI/EMC ************************************************/
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
//                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
//                         RCC_APB2Periph_GPIOE, ENABLE);
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//  GPIO_Init(GPIOD, &GPIO_InitStructure);
//  GPIO_Init(GPIOE, &GPIO_InitStructure);
//  
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
//                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
//                         RCC_APB2Periph_GPIOE, DISABLE); 
//  
//  /*******************************************************************************************/
//
//}

/*------------------------------------------------------------------------------
	$Function: Main_BootConfiguration
	$Description: Inits all the GPIO and the RCC and sys tick

	$Inputs: none
	$Outputs: none
	$Assumptions: THIS MUST BE THE FIRST FUNCTION CALL IN MAIN
	$WARNINGS: 
	$End
*/
void Main_BootConfiguration( void )
{
  __disable_interrupt();

  GPIO_Init_Configuration();
  
  /* System Clocks Configuration **********************************************/
  RCC_Configuration();




#ifdef cSYS_TIM_ENABLE
  /* Set up for System TIck */
  SysTick_Configuration( mTIMx_SYS_TICK_1s() );
#endif

}







#undef cMEM_USERCLASS_ID_BOOT_c