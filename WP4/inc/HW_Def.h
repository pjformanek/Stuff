/*------------------------------------------------------------------------------
	$File:		HW_Def.h	
	$Module:	Hardware Master Definition file
 	$Prefix:	HW
 	$Language:	ANSI C

 	$Description:
		This file creates definitions used throughout the rest of the 
		Hardware (base) layer.
		
 	$Notes:
  
 	$Author:	KGANS, 2009-March-23
 	--------------------------------------------------------------------------
 	$Copyright (c) 2009 J.S. Foster Corporation  	All Rights Reserved
 	--------------------------------------------------------------------------
 	$End
	----------------------------------------------------------------------------*/

#ifndef cHW_DEF_H
#define cHW_DEF_H

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

#include "BLD.h"
#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"

/* -------------------------
    Known Hardware Versions
   ------------------------- */
#if cBLD_HW_Revision == cBLD_HW_Revision_TandemDevKit1 /* IAR STM-32-SK brd +
																													Chipcon Smart RF04EB 1.9 brd */
	#include "HW_PORTS_TandemDevKit1.h"

	/////////////////////////////////////////////////////////////////////////
	//////////////    temp      must do measurement or cycle count   ////////   
	/////////////////////////////////////////////////////////////////////////
	#define cHW_CLK (cHW_CLK_TEMP_JUNK2)

#elif cBLD_HW_Revision == cBLD_HW_Revision_1_0_0
	/* TBD */
#else
	#error : unknown hardware revision
#endif

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

#if !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL)
 #define USE_STM3210B_EVAL
 //#define USE_STM3210E_EVAL
#endif

///////////////////////////////////////////////////////////
//////////////////////////     CLOCK    CRYSTAL    +   INTERNAL DIVIDER    TBD
////////////////////////////////////////////////////////////////////////////////
#define cHW_CLK_10MHz	 (3)  //// DUMMY
#define cHW_CLK_8MHz	 (4)  //// DUMMY
#define cHW_CLK_TEMP_JUNK1	1
#define cHW_CLK_TEMP_JUNK2	2


/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */
#define tHW_GPIO_Init GPIO_InitTypeDef

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

#endif // cHW_DEF_H

