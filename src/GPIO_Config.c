/*------------------------------------------------------------------------------
  	$File:		GPIO_Config.c
  	$Module:  	Configures all GPIO pins for all peripherals
  	$Prefix:  	GPIO
  	$Language:	ANSI C

  	$Description:

  	$Notes:

  	$Author:	Jramirez, Aug 22, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_GPIO_CONFIG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

#include "GLB.h"
#include "MEM.h"
#include "ERR.h"
 #include "platform_config.h"
#include "EXTINT_Config.h"
#include "NVIC_Config.h"

#include "GPIO_Config.h"



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
#define cGPIO_DeInit_Pin_Mode   GPIO_Mode_Out_PP//GPIO_Mode_AIN//GPIO_Mode_IN_FLOATING

/*------------------------------------------------------------------------------
				----- L O C A L   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N   P R O T O T Y P E S -----
  ------------------------------------------------------------------------------
 */
void GPIO_RTC_I2C_INTConfiguration( void );



/*------------------------------------------------------------------------------
				----- L O C A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
GPIO_InitTypeDef GPIO_InitStructure;

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
	$Function: GPIO_Configuration
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_Configuration( void )
{
  

}












/*------------------------------------------------------------------------------
	$Function: GPIO_Init_Configuration
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_Init_Configuration( void )
{
  /*******************************************************************************************/
   /* Configure all unused GPIO port pins in Analog Input mode (floating input
     trigger OFF), this will reduce the power consumption and increase the device
     immunity against EMI/EMC ************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  /*******************************************************************************************/
  GPIO_DC_DCConfiguration();
  GPIO_LED_OEConfiguration();
  GPIO_SX_RES_Configuration( 1 );
  GPIO_Relay_TriggerPins_Configuration();
  GPIO_lockout_Configuration(1);
}

#undef cMEM_USERCLASS_ID_GPIO_CONFIG_c
