/*------------------------------------------------------------------------------
  	$File:		TMR_Services.h	
  	$Module:  	System Timer(s)
  	$Prefix:  	TMR

  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	KGANS, 2009-August-28
  	--------------------------------------------------------------------------
  	$Copyright (c) 2009 Syscor Controls & Automation Inc.  All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __TMR_SERVICES_H__
#define __TMR_SERVICES_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "TIMx_Config.h"
#include "TMR_Ticks.h"

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */
typedef tTIM_VAR tTMR_Services_ticks;

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */
extern tTMR_Services_ticks TMR_Services_QryCurrent( tTMR_Services_ticks rShiftTicks );
//extern tTMR_Services_ticks Local_TMR_Services_QryElapsed( tTMR_Services_ticks rTicks_TimeStamp  );
extern tTMR_Services_ticks TMR_Services_IsElapsed( tTMR_Services_ticks ticks_TimeStamp, tTMR_Services_ticks ticks );
extern void TMR_Services_ReqDelay( tTMR_Services_ticks rTicks );
extern u16 TMR_Services_Init( void );

#endif // __TMR_SERVICES_H__
