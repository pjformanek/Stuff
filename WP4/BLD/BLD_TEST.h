/*--------------------------------------------------------------------------
$Filename: BLD_TEST.h
$Prefix: BLD

$Description:
        This file contains macro definitions that configure the build for 
        specific testing, including special non-mission tests such as H/W 
        tests.

$Author:	KGANS, originated 2009-Mar-23
--------------------------------------------------------------------------
$Copyright (c) 2004-2009 J.S.FOSTER Corporation 	All Rights Reserved
--------------------------------------------------------------------------
$End
  ----------------------------------------------------------------------------*/

#ifndef cBLD_TEST_H
#define cBLD_TEST_H

/*----------------------------------------------------------------------------
			----- I N C L U D E   F I L E S -----
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			----- M A C R O   D E F I N I T I O N S -----
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			----- I N C L U D E   F I L E S -----
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			-----   A P P L I C A T I O N   O P T I O N S   -----
  ----------------------------------------------------------------------------*/
#define cBLD_TEST_HW_CC1101				(1)
#define cBLD_TEST_WP4_RmtTx				(1)
#define cBLD_CC1101_SPI_BurstTest			(1)

/*----------------------------------------------------------------------------
			-----   D E B U G   P R I N T   O P T I O N S   -----
  ----------------------------------------------------------------------------*/


//////////////////////////
//////////////  macro does not work   ... instead, add the file name in
//////////////  specific error reporting   ... establish error handling
/////////////		immediately
////////////	report data format (to PMI) ... string  ^z  u16-ERRID  data
////////////////////////////
#if 0
#define	mERR_ReportError(cERR_ID_token,pbData_token)\
	ERR_ReportError( char * psFile, u16 wErrId, u8 * pbData ) {}

	ERR_ReportError( __BASE_FILE__, cERR_ID_token, pbData_token );
#endif

//#define	mPRINT(string_token,...)
#define	mPRINT(my_string_token)\
	do {\
	printf("\r\n");\
	printf(__BASE_FILE__);\
	printf(my_string_token,...);\
	printf("\r\n");\
	} while(0)

#if cBLD_DEBUG_PRINT == cBLD_DEBUG_PRINT_release
		#define cBLD_DEBUG_PRINT_option_RFC_FSCAL	0
#elif cBLD_DEBUG_PRINT == cBLD_DEBUG_PRINT_debug
		#define cBLD_DEBUG_PRINT_option_RFC_FSCAL       1
#else
#error
#endif

#endif // cBLD_TEST_H

