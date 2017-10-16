/*------------------------------------------------------------------------------
  	$File:		RTC_Config.h	
  	$Module:  	Header file for RTC_Config.c
  	$Prefix:  	RTC
  	$Language:	ANSI C
  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Feb 02, 2009
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __RTC_H__
#define __RTC_H__

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
#define cRTC_tick_MAX    (0xFFFFFFFF)
#define cRTC_Tick_Interval_1h (cRTC_Tick_Interval_1m*60)
#define cRTC_Tick_Interval_1m (cRTC_Tick_Interval_1s*60)
#define cRTC_Tick_Interval_1s (cRTC_Tick_Interval_100ms*10)  // this is for a 1000 ms tick
#define cRTC_Tick_Interval_100ms 1  // this is for a 100 ms tick
#define cRTC_1_SEC_TICK  32767

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
extern vu32 TimeDisplay;


/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */
void RTC_Configuration( u32 ulPrescalerRtc );
u32 Time_Regulate(void);
void Time_Adjust(void);
void Time_Show(void);
void Time_Display(u32 TimeVar);
void RTC_Init( void );

void RTC_Set_Alarm( u32 ulTime_To_Wait );


u32 RTC_HasTimeStampElapsed( u32 lwTimeStamp, u32 lwTimeout );
u32 RTC_ReturnCounter( u32 lwTimeStampShift );
#endif // __RTC_H__