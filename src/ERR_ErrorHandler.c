/*------------------------------------------------------------------------------
  	$File:		ERR_Module.c	
  	$Module:  	Error Module
  	$Prefix:  	ERR
  	$Language:	ANSI C
  	$Description:
				   
		This unit provides all interfaces for error handling including logging
		and data retrieval.

  	$Author:	KGANS, originated 2009-June-8
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S.FOSTER Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_ERR_Module_c

/*----------------------------------------------------------------------------
			----- I N C L U D E   F I L E S -----
  ----------------------------------------------------------------------------*/
#include "GLB.h"
#include "MEM.h"

/*----------------------------------------------------------------------------
			----- M A C R O   D E F I N I T I O N S -----
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			----- L O C A L   T Y P E S	-----
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			----- L O C A L   F U N C T I O N   P R O T O T Y P E S	-----
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			----- L O C A L   V A R I A B L E S	-----
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			----- G L O B A L   V A R I A B L E S -----
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			----- L O C A L   F U N C T I O N S	-----
  ----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
			----- G L O B A L   F U N C T I O N S -----
  ----------------------------------------------------------------------------*/

void ERR_Module_ReportError( u16 wErrId,
							 u8 * pbData, 
							 u16 wNumBytes,
							 const char * psFile,
							 const char * psFunction,
							 u16 wLineNumber )
{
	u16 wi;

	/* dump something out the serial port for live debugging
	*/
	printf("\r\nERR_Id:%d in File:",wErrId);
	printf(psFile);
	printf("; Function:");
	printf(psFunction);
	printf("  Line:%d",wLineNumber);

	printf("\r\ndata: 0x%X",pbData[0]);
	if( wNumBytes > 1 )
	{
		for( wi = 1; wi < wNumBytes; wi++ )
		{
			printf(" 0x%X",pbData[wi]);
		}
	}

	////// JUAN, what we should really be doing above is, we should "print" the
	/////        serial data to a buffer or queue amd then decide if
	////		we want to send it via HTTP session, send it to the serial
	////		port, both, or none.
	////		...we could also write the data to a file in EEPROM and
	////			send that file as a report later, via FTP, HTTP, serial
	////			file dump, etc.
	////		...we can also do a simple coded logging as we currently do in WMS
}



#undef cMEM_USERCLASS_ID_ERR_Module_c