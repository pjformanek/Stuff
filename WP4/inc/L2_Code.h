                                                                                    /*------------------------------------------------------------------------------
  	$File:		L2_Code.h	
  	$Module:  	Telit Layer Script
  	$Prefix:  	L2
  	$Language:	ANSI C
  	$Description:
		
  	$Notes:
  
  	$Author:	Juan Ramirez, 2009-July-16
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __L2_CODE_H__
#define __L2_CODE_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */


#define cL2_GSM_MAX_SMS_STRING        140
#define cL2_GSM_MAX_GPRS_STRING       1024

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

extern const char * psL2_CODE_ScrtData[];
extern u8 * psL2_CODE_ImportantLayer2Data[];
extern u8  psL2_CODE_SendPicHttp[];


extern u8 bL2_GSM_SmsInputString[cL2_GSM_MAX_SMS_STRING];
extern u8 bL2_GSM_GprsInputString[cL2_GSM_MAX_GPRS_STRING];
extern u8 bL2_GSM_HttpContentLength[5];

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

#endif // __L2_CODE_H__

