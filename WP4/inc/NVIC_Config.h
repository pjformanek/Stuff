/*------------------------------------------------------------------------------
  	$File:		NVIC_Config.h	
  	$Module:  	Header file for NVIC_Config.c
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

#ifndef __NVIC_H__
#define __NVIC_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */


#define cNVIC_USART2_Int      0x0001
#define cNVIC_USART3_Int      0x0002
#define cNVIC_BUTTON_Int      0x0004
#define cNVIC_GD0_Int         0x0008
#define cNVIC_TIM1_Int        0x0010
#define cNVIC_TIM2_Int        0x0020
#define cNVIC_DTMF_Int        0x0040
#define cNVIC_TELIT_Int       0x0080
#define cNVIC_RTC_Alarm_Int   0x0100
#define cNVIC_USART1_Int      0x0101
#define cNVIC_DOS_Int         0x0110

#define cNVIC_ENABLE_ALL_Int  0xFFFF

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */
void NVIC_Configuration( u16 wIRQ_Channels, FunctionalState NewState );

void NVIC_DMA1_Ch4_Configuration( FunctionalState NewState );
void NVIC_DMA1_Ch6_Configuration( FunctionalState NewState );
void NVIC_DMA1_Ch7_Configuration( FunctionalState NewState );



#endif // __NVIC_H__

