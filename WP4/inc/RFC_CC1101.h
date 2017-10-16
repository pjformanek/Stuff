/*------------------------------------------------------------------------------
  	$File:		RFC_CC1101.h
  	$Module:	Register and Data definitions TI Chipcon CC1101 chip
  	$Prefix:  	RFC
  	$Language:	ANSI C
  
  	$Description:
			This file contains definitions related to the configuration of the 
			TI Chipcon CC1101 900 MHz ISM band transceiver.
  	$Notes:
  	$Author:	KGANS, 2009-March-23
  	--------------------------------------------------------------------------
  	$Copyright (c) 2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef cRFC_CC1101_H
#define cRFC_CC1101_H

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

#define cpbHW_CC1101_INIT_DATA_NUM_ENTRIES			pcbHW_Code_CC1101_RegData_InitData_NUM_ENTRIES[0]
#define cHW_CC1101_PATABLE_Profile_DEFAULT_INDEX 	(1)

/* ...about the frequency multiplier
		... if we want to use the "CHANNEL" facility of the CC1101 we have to define
			smaller frequency steps (26MHz crystal limits the width of a channel to about
			405 kHz and we want 500 kHz steps  ... therefore, we define 102 channels
			instead of 51 and then only use the even channels
*/
#define	cRFC_CC1101_FREQ_MULTIPLIER					(2)

/* 	------------------------------
		--- Register Access Ranges ---
		------------------------------ 
*/
#define cHW_CC1101_RegType_BLOCKED			(0)
#define cHW_CC1101_RegType_CONFIG			(1)
#define cHW_CC1101_RegType_STATUS			(2)
#define cHW_CC1101_RegType_DATA				(3)
#define cHW_CC1101_RegType_RESERVED			(4)

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*--------------------------------------------------------------------
 	$Type: tpHW_CC1101_perFreqCalData
	$Description:
		Creates the structure for populating arrays of calibration
		data. It is intended that this data will be part of any manual 
		frequency calibration process implemented.
	$End
 */
typedef struct tpHW_CC1101_perFreqCalData_tag 
{
	u8	bFSCAL1;

} tpHW_CC1101_perFreqCalData;

/*--------------------------------------------------------------------
 	$Type: tpHW_CC1101_allFreqCalData
	$Description:
		Creates the structure for transceiver calibration data that
		does not change with frequency
		data. It is intended that this data will be part of any manual 
		frequency calibration process implemented.
	$End
 */
typedef struct tpHW_CC1101_allFreqCalData_tag 
{
	u8	bFSCAL3;
	u8	bFSCAL2;
	u8	bRCCTRL1;
	u8	bRCCTRL0;

} tpHW_CC1101_allFreqCalData;

/*--------------------------------------------------------------------
 	$Type: tRFC_Data_CC1101_RegData
	$Description:
		Creates the structure for populating arrays of configuration 
		parameters.
	$End
 */
#if 0
typedef struct tRFC_Data_CC1101_RegData_tag 
{
	u8	bRegAddrs;
	u8	bRegData;

} tRFC_Data_CC1101_RegData;
#endif

/*--------------------------------------------------------------------
 	$Type: tRFC_CC1101_RegData
	$Description:
		Creates the structure for populating arrays of configuration 
		parameters.
	$End
 */
#if 0
typedef struct tRFC_CC1101_RegData_tag 
{
	u8	bRegAddrs;
	u8	bRegData;

} tRFC_CC1101_RegData;
#endif

/*--------------------------------------------------------------------
 	$Type: tpHW_CC1101_PATABLE_Profile
	$Description:
		Creates the structure for populating array of CC1101
		power amplifier ramping data (PATABLE).
	$End
*/
typedef struct tpHW_CC1101_PATABLE_Profile_tag 
{
	u8	pbData[cHW_CC1101_PATABLE_NUM_BYTES];

} tpHW_CC1101_PATABLE_Profile;

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
extern const tpHW_CC1101_RegData ppcHW_CC1101_code_RegData_init[];
extern const tHW_CC1101_PATABLE_Profile ppcHW_CC1101_code_PATABLE_Profile[];

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

#endif /* cRFC_CC1101_H */