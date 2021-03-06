/*------------------------------------------------------------------------------
  	$File:		Delay.c
  	$Module:  	Simple Delay Function
  	$Prefix:  	DELAY
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Aug 22, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_DELAY_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

#include "GLB.h"
#include "MEM.h"

#include "Delay.h"


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
	$Function: Delay.c
	$Description: Inserts a delay time.

	$Inputs: vu32 nCount - specifies the delay time length.
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/

void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

#undef cMEM_USERCLASS_ID_DELAY_c

