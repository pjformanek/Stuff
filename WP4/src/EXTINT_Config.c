/*------------------------------------------------------------------------------
  	$File:		EXTINT_Config.c
  	$Module:  	Configures all external interrupts, priorities etc ...
  	$Prefix:  	EXTI
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Dec 23, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_EXTINT_CONFIG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "MEM.h"
#include "Includes.h"


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
EXTI_InitTypeDef EXTI_InitStructure;


/*------------------------------------------------------------------------------
				----- G L O B A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/

/*------------------------------------------------------------------------------
				----- G L O B A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */


/*------------------------------------------------------------------------------
	$Function: EXTINT_Configuration
	$Description: Configures all aspects of external interrupts

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void EXTINT_Configuration( void )
{
  /* Configure EXTI Line17(RTC Alarm) to generate an interrupt on rising edge */
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);




#ifdef cCC1101_ENABLE
  /* Connect RING EXTI Line to RING GPIO Pin */
  GPIO_EXTILineConfig( cGPIO_PORT_SOURCE_GD0_PIN, cGPIO_PIN_SOURCE_GD0_PIN );

  /* Configure Key Button EXTI Line to generate an interrupt on rising edge */
  EXTI_InitStructure.EXTI_Line = cEXTI_LINE_GD0_PIN ;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
#endif


  //////////////////////////////////////////////////////////////////////////////
#ifdef cDTMF_ENABLE
  /* Connect RING EXTI Line to DTMF GPIO Pin */
  GPIO_EXTILineConfig(cGPIO_PORT_SOURCE_DTMF, cGPIO_PIN_SOURCE_DTMF);

  /* Configure Key Button EXTI Line to generate an interrupt on rising edge */
  EXTI_InitStructure.EXTI_Line = cEXTI_LINE_DTMF;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
#endif




}




















#undef cMEM_USERCLASS_ID_EXTINT_CONFIG_c