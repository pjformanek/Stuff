/*------------------------------------------------------------------------------
  	$File:		TMR_Ticks.h	
  	$Module:  	System Timer(s)
  	$Prefix:  	TMR
  	$Language:	ANSI C

  	$Description: This unit defines the literal definitions	(macros) to be used 
  					by applications requiring TMR services.

  	$Author:	KGANS, originated 2010-May-8
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2010 J.S.FOSTER Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __TMR_TICKS_H__
#define __TMR_TICKS_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/* interrupt rate for TMR / counter must be set to 10kHz for the following values 
	to be correct
*/
#define cTMR_Ticks_Per100us						(cTIMx_APP_TicksPer100us)
#define cTMR_Ticks_Per1ms						((10)*(cTMR_Ticks_Per100us))
#define cTMR_Ticks_Per1s						((10000)*(cTMR_Ticks_Per100us))

/* create other definitions using these macros
*/
#define mTMR_Ticks_PerSeconds(seconds_Token)	((seconds_Token)*(cTMR_Ticks_Per1s))
#define mTMR_Ticks_PerMilliseconds(ms_Token)   	((ms_Token)*(cTMR_Ticks_Per1ms))
#define mTMR_Ticks_Per100us(_100us_Token)		((_100us_Token)*(cTMR_Ticks_Per100us))

/* definitions for millisecond multiples
*/
#define cTMR_Ticks_Per10ms						(mTMR_Ticks_PerMilliseconds(10))
#define cTMR_Ticks_Per20ms						(mTMR_Ticks_PerMilliseconds(20))

/* definitions for second multiples
*/
#define cTMR_Ticks_Per2s						(mTMR_Ticks_PerSeconds(2))

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

#endif // __TMR_TICKS_H__
