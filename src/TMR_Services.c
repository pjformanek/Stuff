/*------------------------------------------------------------------------------
  	$File:		TMR_Services.c	
  	$Module:  	System Timer(s)
  	$Prefix:  	TMR
  	$Language:	ANSI C

  	$Description: This unit provides the following support for Tasks:
					<> manual Tmr

	ABITG  .... BasicTmr   ... for Syscor, a Tmr structure was used  ... advantages
				multiple arguments can be passed with a single ptr
				for WP4 this may be useful in the future as we find more and more uses
				for TMR  ... this code should be updated .... less than 2 hours
				required to make this change

	ABITG
	*****************	
	AT TIME OF CODING ...
	*****************	
		rMEM_TMR_Services_ticks is being used to track System Tmr ticks
		... this may not be required, as we should be able to simply read
			the 16 or 32-bit counter of the associated Tmr ... if we do
			this we can free up a lot of machine cycles that will otherwise
			be burned in supporting an interrupt
			.... as the granularity of the tick becomes finer, the cost of
					servicing the Tmr interrupt becomes greater (and the
					chances of creating	a problem priority / nesting issue
					increases; or the chance of missing a tick increases)

			... perhaps the best scheme is to start off development
			using rMEM_TMR_Services_ticks, then use the scope and LED
			traces to emprically measure the real-time being used to service
			the interrupt.


	$CAUTION: The functions declared in this file are not re-entrant and
				so should never be called at interrupt level or in a pre-emptive
				multi-tasking system.

  	$Author:	KGANS, originated 2010-May-8
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2010 J.S.FOSTER Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_TMR_SERVICES_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "BLD.h"
#include "ERR.h"
#include "TIMx_Config.h"
#include "TMR_Services.h"
#include "MEM.h"

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
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
	$Function: TMR_Services_Ticks_QryCurrent
	$Description: Returns the current value of the system timer variable
					...this is effectively a time-stamp, given in ticks
					...ticksShift is added to the time-stamp to shift
						it forward in time
	$Inputs: rShiftTicks
	$Outputs: tTMR_Services_ticks; system timer time-stamp (ticks)
	$Assumptions: rShiftTicks is much less than cTMR_System_tick_A_MAX
	$WARNINGS:
	$End
*/
tTMR_Services_ticks TMR_Services_QryCurrent( tTMR_Services_ticks rShiftTicks )
{
	tTMR_Services_ticks rTicks_Temp;

	rTicks_Temp = TIM2_ReturnCounterValue();

	/* first check and see if timer will wrap once shift added
	*/
	if( rTicks_Temp <= (cTIMx_APP_tick_MAX - rShiftTicks) )
	{
		/* timer will not wrap with shift added
		*/
		rTicks_Temp += rShiftTicks;
	} else {
		/* timer will wrap
		*/
		rTicks_Temp = cTIMx_APP_tick_MAX - rTicks_Temp;
		rTicks_Temp = rShiftTicks - rTicks_Temp;
	}

	return( rTicks_Temp );
}

/*------------------------------------------------------------------------------
	$Function: TMR_Services_Ticks_QryElapsed
	$Description: Returns the number of system timer ticks that have passed
					since the time-stamp (arg data) was issued
	$Inputs: none
	$Outputs: no return data; global data incremented
	$Assumption: This function is called within the maximum time that can be
					represented by the system timer ; else result is erroneous
	$WARNINGS:
	$End
*/
tTMR_Services_ticks Local_TMR_Services_Ticks_QryElapsed( tTMR_Services_ticks rTicks_TimeStamp  )
{
	tTMR_Services_ticks rTicks_Temp;

	/* sample the timer first ... otherwise error can occur if timer wraps
		during execution of this function
	*/
	rTicks_Temp = TIM2_ReturnCounterValue();

	/* first check and see if timer has wrapped
	*/
	if( rTicks_Temp < rTicks_TimeStamp )
	{
		/* timer has wrapped ... subtract time-stamp from max-time and then
			 add the current value of the system timer
		*/
		return( ((cTIMx_APP_tick_MAX) - rTicks_TimeStamp) + rTicks_Temp );
		/* note: order of operations in statement above does not actually matter */
	} else {
		/* timer has not wrapped ... subtract the time-stamp value from the
			 system timer value
		*/
		return( rTicks_Temp - rTicks_TimeStamp );
	}
}

/*------------------------------------------------------------------------------
	$Function: TMR_Services_Ticks_IsElapsed
	$Description: Returns TRUE if arg ticks have passed since the arg
					"time-stamp" ticks was sampled. Note that the TRUE
					result is actually the elapsed ticks so that
					it can be used for Tmrs that require this for a shift
					on restart
	$Inputs: tTMR_Services_ticks ticks	
			 tTMR_Services_ticks ticks_TimeStamp
	$Outputs: tTMR_Services_ticks ticks	 (non-zero, TRUE if elapsed)
	$ASSUMPTIONS:
	$WARNINGS:
	$End
*/
tTMR_Services_ticks TMR_Services_IsElapsed( tTMR_Services_ticks ticks_TimeStamp, tTMR_Services_ticks ticks )
{
	tTMR_Services_ticks rTmrElapsedTicks;

	rTmrElapsedTicks = Local_TMR_Services_Ticks_QryElapsed( ticks_TimeStamp );

	/* set to "FALSE" so caller will not use the result
	*/
	if( rTmrElapsedTicks < ticks ) {
		rTmrElapsedTicks = 0;
	}

	return( rTmrElapsedTicks );
}

/*------------------------------------------------------------------------------
	$Function: TMR_Services_Ticks_ReqDelay
	$Description: Delays return from function for the number of ticks in
					call-arg
	$Inputs: tTMR_Services_ticks ticks
	$Outputs:
	$ASSUMPTIONS:
	$WARNINGS:
	$End
*/
void TMR_Services_ReqDelay( tTMR_Services_ticks rTicks )
{
	tTMR_Services_ticks	rTicks_TimeStamp;

	rTicks_TimeStamp = TMR_Services_QryCurrent( 0 );
	while( !(TMR_Services_IsElapsed( rTicks_TimeStamp, rTicks )) );
}

/*------------------------------------------------------------------------------
	$Function: TMR_Services_Init
	$Description: Sets TMR_Services memory structures to default state.

ABITG: 32 or 16 bit  TIM7 is 16-bit counter  ... use 16-bit counter
					for short duration (1us to 1 minute)
						and 32 bit for long durations (1s to multiple days)

					Promote the 16-bit counter to 32 bits so that TMR services
					functions can be the same.



					The 32-bit Tmr variable supported for manual Tmrs need not
					be initialized as all "time stamps" issued are actually
					just a return values of the current 32-bit value (which
					is incremented on every tick).
	$Inputs: none
	$Outputs: return: ERRor code
	$WARNINGS:
	$End
*/
u16 TMR_Services_Init( void )
{
	// ABITG   TMR_System_Init(); ?????
	return( 0 );
}

#undef cMEM_USERCLASS_ID_TMR_SERVICES_c