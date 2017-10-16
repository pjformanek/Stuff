/*------------------------------------------------------------------------------
  	$File:		RCC_Config.c
  	$Module:  	Configurations for RCC controller
  	$Prefix:  	RCC
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Dec 23, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_RCC_CONFIG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "MEM.h"

#include "RCC_Config.h"

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
ErrorStatus HSEStartUpStatus;

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
	$Function: RCC_Configuration
	$Description: Configures the different system clocks.

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void RCC_Configuration(void)
{
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  RCC_LSICmd( DISABLE );

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK */
    RCC_PCLK1Config(RCC_HCLK_Div1);

#ifdef cRCC_PLL_ENABLE
    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);



    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
#endif
  }


      /* Select HSE as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);	

    /* Wait till HSE is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x04)
    {}
    /* Enable AFIO clock */
    /* This is here in order for the remapping of pins especially for usart3
       This is also needed to enable the external Interrupts
    */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);


}



/*------------------------------------------------------------------------------
	$Function: SYSCLKConfig_STOP
	$Description: Configures system clock after wake-up from STOP: enable HSE, PLL
                      and select PLL as system clock source.

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void SYSCLKConfig_STOP(void)
{
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {

    /* Select HSE as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);	


#ifdef cRCC_PLL_ENABLE
    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
#endif
  }
}



#undef cMEM_USERCLASS_ID_RCC_CONFIG_c
