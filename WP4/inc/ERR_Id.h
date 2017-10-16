/*--------------------------------------------------------------------------
	$Filename:	ERR_Id.h
	$Module: 	Error Module
	$Prefix:	ERR

	$Description:
		This file contains error Ids. 

		-----------------
		Application Notes:
		-----------------
			Any person can create a new Error definition. Please use the
			defined enumerators and macros.

				...	each module has an enumerated type (add new types to 
														end of list)
				...	each module defines its own errors enumerated error ids
				...	each error that is added must have a report string defined.
					These strings may or may not ever be used at run time
					but they clarify the intent of the error and, if they are 
					needed in the future, having them already coded will
					save time.

  	$Author:	KGANS, originated 2009-June-8
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S.FOSTER Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef ERR_ID_H
#define ERR_ID_H


/*----------------------------------------------------------------------------
			----- I N C L U D E   F I L E S -----
  ----------------------------------------------------------------------------*/
//#include "BLD_TEST.h"

/*----------------------------------------------------------------------------
			-----   M A C R O   D E F I N T I O N S   -----
  ----------------------------------------------------------------------------*/

#define mERR_Id_CreateErrorId(cToken_module,cToken_error) \
	((cToken_module)<<(8))|(cToken_error)

/*----------------------------------------------------------------------------
			-----   E N U M E R A T E D   T Y P E S   -----
  ----------------------------------------------------------------------------*/

/* register modules here ... */
typedef enum
{
	eERR_Id_ModuleIndex_NULL = 0,
	eERR_Id_ModuleIndex_RFC = 1
} tERR_Id_ModuleIndex;

/* define new RFC error codes here ... */
typedef enum
{
	eERR_Id_SubIndex_RFC_DeviceInitFailure = 0,
	eERR_Id_SubIndex_RFC_DeviceRegWriteFailure = 1,
	eERR_Id_SubIndex_RFC_NUM_SUB_INDEXES

} tERR_Id_SubIndex_RFC;

/*----------------------------------------------------------------------------
			-----   E R R O R   I D   D E F I N T I O N S   -----
  ----------------------------------------------------------------------------*/

/* 	-----------
	--- RFC ---
	----------- */

#define cERR_Id_RFC_DeviceInitFailure (mERR_Id_CreateErrorId(eERR_Id_ModuleIndex_RFC,eERR_Id_SubIndex_RFC_DeviceInitFailure))
#define cERR_Id_RFC_DeviceInitFailure_string "CC1101 power up init failed"

#define cERR_Id_RFC_DeviceRegWriteFailure (mERR_Id_CreateErrorId(eERR_Id_ModuleIndex_RFC,eERR_Id_SubIndex_RFC_DeviceRegWriteFailure))
#define cERR_Id_RFC_DeviceRegWriteFailure_string "CC1101 config register data write failed"

#endif // 

