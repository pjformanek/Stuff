/*------------------------------------------------------------------------------
  	$File:		NVIC_Config.c
  	$Module:  	COnfiguration settings for NVIC
  	$Prefix:  	NVIC
  	$Language:	ANSI C

  	$Description:

  	$Notes:

  	$Author:	Jramirez, Dec 23, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_NVIC_CONFIG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "MEM.h"

#include "platform_config.h"
#include "NVIC_Config.h"
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
NVIC_InitTypeDef NVIC_InitStructure;

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
	$Function: NVIC_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: u16 wIRQ_Channel -  mask for channels that need to be enable
                 FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_Configuration( u16 wIRQ_Channels, FunctionalState NewState )
{
  //NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  _VECT_TAB_RAM
  /* Set the Vector Table base location at 0x20000000 */
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#elif   _VECT_TAB_BOOT
  /* Set the Vector Table base location at 0x08002000 in order to use the IAP bootloader */
  NVIC_SetVectorTable(NVIC_VectTab_BOOT, 0x0);
#else  /* _VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* 1 bits for Preemption Priority and 2 bits for Sub Priority */
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

#ifdef cRTC_INTERNAL_ENABLE
  if( cNVIC_RTC_Alarm_Int & wIRQ_Channels )
  {
    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Init(&NVIC_InitStructure);
  }
#endif




#ifdef cDTMF_ENABLE
  if( cNVIC_DTMF_Int & wIRQ_Channels )
  {
    /* Enable the DTMF Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Init(&NVIC_InitStructure);
  }
#endif

#ifdef cPA_ENABLE
  if( cNVIC_DTMF_Int & wIRQ_Channels )
  {
    /* Enable the PA Test Button Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Init(&NVIC_InitStructure);
  }
#endif





#ifdef cCC1101_ENABLE
  if( cNVIC_GD0_Int & wIRQ_Channels )
  {
    /* Enable the GD0 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Init(&NVIC_InitStructure);
  }
#endif










#ifdef cNVIC_DOS_ENABLE
  if( cNVIC_DOS_Int & wIRQ_Channels )
  {
    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Init(&NVIC_InitStructure);
  }
#endif





//  /* Enable the TIM7 Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQChannel;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
}

































/*------------------------------------------------------------------------------
	$Function: NVIC_DMA1_Ch4_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_DMA1_Ch4_Configuration( FunctionalState NewState )
{
  /* Enable the DMA1 channel 4 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}
/*------------------------------------------------------------------------------
	$Function: NVIC_DMA1_Ch6_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_DMA1_Ch6_Configuration( FunctionalState NewState )
{
  /* Enable the DMA1 channel 6 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}

#undef cMEM_USERCLASS_ID_NVIC_CONFIG_c
