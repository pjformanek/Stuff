/*------------------------------------------------------------------------------
  	$File:		ERR_Module.h	
  	$Module:  	Error Reporting and Logging Interface
  	$Prefix:  	ERR
  	$Language:	ANSI C
  	$Description:
		
  	$Notes:
  
  	$Author:	KGANS, 2009-June-12
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __ERR_MODULE_H__
#define __ERR_MODULE_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "ERR_Id.h"

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/* this code violates the coding standard
		... can we / should e create an exception for this in the coding 
			standard
*/
#define cBF	__BASE_FILE__
#define cPF __PRETTY_FUNCTION__
#define cL	__LINE__



/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

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
extern void ERR_Module_ReportError( u16 wErrId,
									 u8 * pbData, 
									 u16 wNumBytes,
									 const char * psFile,
									 const char * psFunction,
									 u16 wLineNumber );

#endif // __ERR_MODULE_H__

