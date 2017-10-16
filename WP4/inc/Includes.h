/*------------------------------------------------------------------------------
  	$File:		Includes.h	
  	$Module:  	Header file which all other header files
  	$Prefix:  	INC
  	$Language:	ANSI C
  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Dec 23, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __INC_H__
#define __INC_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <intrinsics.h>
#include "GLB.h"
#include "GPIO_Config.h"
#include "USART_Config.h"
#include "RCC_Config.h"
#include "Delay.h"
#include "SPI_Config.h"
#include "NVIC_Config.h"
#include "platform_config.h"
#include "Boot.h"
#include "TIMx_Config.h"
#include "EXTINT_Config.h"
#include "USART_Debug.h"
#include "App_Main.h"
#include "RF_Prot.h"
#include "ATcommands.h"
#include "DTMF.h"
#include "DAT_Access.h"
#include "SCAN_Data.h"
#include "App_State.h"
#include "RNG.h"
#include "RTC_Config.h"
#include "DEBUG.h"
#include "L2_GSM_Process.h"
#include "L2_Code.h"
#include "CAM_AppState.h"
#include "CAM.h"
#include "DOS.h"
#include "LED.h"
#include "RTC_I2C_Config.h"
#include "EE_I2C_Config.h"
#include "SX_Config.h"
#include "I2C_Config.h"	

#include "Utilities.h"

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

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

#endif // __INC_H__
