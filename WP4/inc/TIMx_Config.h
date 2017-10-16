/*------------------------------------------------------------------------------
  	$File:		TIMx_Config.h	
  	$Module:  	Header file for TIMx_Config.c
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

#ifndef __TIM_H__
#define __TIM_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define mTIM2_ENABLE_100us()      TIM2_Configuration( 100 ); TIM_Cmd( TIM2, ENABLE );
#define mTIM2_DISABLE_100us()     TIM_Cmd( TIM2, ENABLE );
/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */


/*  #if 4 == sizeof(tTIM_VAR)
		we need to be explicit in identifying that the tick
		is 100us and 32-bits
*/
#define cTIMx_APP_tick_MAX		(0xFFFFFFFF)
#define cTIMx_APP_TicksPer100us	(1)

/* ABITG   ... to discuss
*/
#define mTIM1_1s()       2000
#define mTIM1_500ms()    1000
#define mTIM1_100ms()    200


#define mTIMx_SYS_TICK_1s()      0x0F3000 // exactly 1 second tick at 8MHz


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
extern  vu16 wTIM_Ticks_Tim1;
extern  volatile tTIM_VAR rTIM_Ticks_Tim2;;
extern  vu16 wTIM_SysTickCounter;

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */
void TIM7_Configuration( void );
void TIM1_Configuration( u16 wTimeOutms );
void TIM8_Configuration( void );
void TIM2_Configuration( u16 wTimeOutus );
void TIM3_Configuration( u16 wTimeOutus );
void TIM4_Configuration( u16 wTimeOutus );
void TIM5_Configuration( u16 wTimeOutus );
void TIM6_Configuration( u16 wTimeOutus );
void SysTick_Configuration( u32 lwTimeOut  );

tTIM_VAR TIM2_ReturnCounterValue( void );
void TIM2_UpdateCounterValue( tTIM_VAR lwNewCounterValue );



void TIM1_Callback( void );
void TIM1_Func( u16 wTimeOutms, void (*pfCallBack)(void) );
void TIM1_TestFunc2( void );

void TIM1_SetTimer( u16 wTimeOutms );

#endif // __TIM_H__

