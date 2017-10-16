/*------------------------------------------------------------------------------
$File:		GLB.h	
$Module:  	Global header
$Prefix:  	GLB
$Language:	ANSI C
$Description:
        
$Notes:

$Author:	Jramirez, Nov 05, 2010
                PFormanek, Oct 10, 2017
--------------------------------------------------------------------------
$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
--------------------------------------------------------------------------
$End
  ----------------------------------------------------------------------------*/

#ifndef __GLB_H__
#define __GLB_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <intrinsics.h>

#include "stm32f10x_lib.h"
#include "stm32f10x_type.h"
#include "BLD.h"
#include "HW_Def.h"
//#include "DEBUG.h"
#include "Delay.h"

#ifdef _DEBUG
/* $WARNING: UART-1 may interact with the CC1010 Evaluation Board when
	the multi-pin header is connected ... H/W resets may result */
#define cBLD_DEBUG		 	1
#else
#define cBLD_DEBUG		 	0
#endif

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define mGLB_ENTER_SLEEP() (*(vu32 *) SCB_SysCtrl |= SysCtrl_SLEEPDEEP_Set)
#define mGLB_Array_NUM_ENTRIES(x) ( (sizeof(x)) / (sizeof(x[0])) )

#define mGLB_SystemReset()        NVIC_GenerateSystemReset()
#define mGLB_CoreReset()          NVIC_GenerateCoreReset()

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */
/* 
================================  Products Select  ============================= 
This selects the type of product this way we can enable different modules to run 
in said product 
*/



#define cGLB_PRINT_DEBUG

#define HI                ecGPIO_BitAction_SET
#define LOW               ecGPIO_BitAction_CLEAR
#define ON                HI
#define OFF               LOW
#define cSET              1
#define cCLEAR            0


/*
============   Defines to select the type of board we are using    =============
this also enables the right ports in platform_config.h
*/
//#define cHW_DEV_BOARD
#define cHW_XPLAT_BOARD

/*
=================    Defines the Hardware Modules Frameworks   =================
*/
#define cGLB_RF_FRAMEWORK
#define cGLB_GSM_FRAMEWORK
#define cGLB_STORE_FRAMEWORK
#define cGLB_TIME_FRAMEWORK
#define cGLB_TIMER_FRAMEWORK
#define cGLB_ENCODE_FRAMEWORK


/*
============== Product Builder  DEFINE ONLY ONE AT THE TIME ====================
*/


/*
  Enables the RF and light flashing toolset
*/
//#define c40cpm
//#define cGLB_DUAL_TX
//#define cGLB_Reservice_Delay

#define cGLB_PRODUCT_XWALK

/*
  Enables the FOB toolset
*/
//#define cGLB_PRODUCT_FOB

/*
  Enables the Modem toolset
*/
//#define cGLB_PRODUCT_SZ_CTRL

/*
  Enables the 24Hr flasher
*/
//#define cGLB_PRODUCT_24HR

/*
  Enables the Remote firmware load and its modules
  Note: this is for all remotes see its settings for specifics
*/
//#define cGLB_PRODUCT_REMOTE_TX

/*
  Enables communication with old SZ controller through RS-232 toolset
*/
 #define cGLB_PRODUCT_OLDSZ_READER

// #define cGLB_EVERYTHING_ON

/* -------------  Hardware Builder  -------------
  The following configurations let the rest of the firmware layer
  know what kind of hardware this device has which also enables those modules
  no app could use a module that is not defined here
*/



////////////////////////////////////////////////////////


/*
  Defines what modules to load in an SZ device
*/
#ifdef cGLB_PRODUCT_SZ_CTRL
#define cGLB_GSM_ENABLE
//#define cWD_ENABLE
// error module 
//#define cERR_ENABLE
//#define cGLB_LED_ENABLE
#endif // ********** END OF cGLB_PRODUCT_SZ_CTRL **********

/*
  Defines what modules to load in an XWALK device
*/
#ifdef cGLB_PRODUCT_XWALK
//#define cGLB_INIT_SET_UP  // this is done to enable all modules to init EEprom registers to a desired value
#define cGLB_LED_ENABLE
#define cGLB_RF_ENABLE
//#define cGLB_GSM_ENABLE
//#define cGLB_BT_ENABLE
//#define cGLB_DELAY_CUSTOM // makes an RF-ON wait 10 sec
#define cGLB_ON_OFF_REPEATER_CUSTOM //makes an on or off received rf signal get transmitted back
//#define cWD_ENABLE
// #define cIWDG_ENABLE
// Allow unit to go to sleep
#define cAllow_Sleep
// error module 
// #define cERR_ENABLE
//speed sensor
//#define cGLB_SPEED_ENABLE
// Device ID default Value
#define cGLB_XWALK_DEV_ID               0xFFFF
#endif // END OF cGLB_PRODUCT_XWALK

/*
  This is a special load that enables ALL The possible modules 
*/
#ifdef cGLB_EVERYTHING_ON
#define cGLB_RF_ENABLE
#define cGLB_GSM_ENABLE
#define cGLB_BT_ENABLE
#define cWD_ENABLE
//speed sensor
//#define cGLB_SPEED_ENABLE
#endif // END OF cGLB_EVERYTHING_ON

#ifdef cGLB_PRODUCT_FOB
#ifndef cGLB_PRODUCT_XWALK
#define cGLB_RF_ENABLE
//#define cGLB_ON_OFF_REPEATER_CUSTOM //makes an on or off received rf signal get transmitted back
#ifndef _DEBUG
#define cWD_ENABLE
#endif
// Allow unit to go to sleep
#define cAllow_Sleep
// Device ID default Value
#define cGLB_XWALK_DEV_ID       cGLB_XWALK_UNIVERSAL_DEV_ID
#endif
#endif // ******** END OF cGBL_PRODUCT_FOB

/*
   
*/
#ifdef cGLB_PRODUCT_REMOTE_TX
#define cGLB_RF_ENABLE
#endif // END OF cGLB_REMOTE_ENABLE


#ifdef cGLB_PRODUCT_24HR
#define cGLB_LED_ENABLE
#define cWD_ENABLE
#define cAllow_Sleep
#endif



////////////////////////////////////////////////////////



/*
*/
#ifdef cGLB_XWALK_DEV_ID

#define mGLB_XWALK_DEV_ID_MSB(x)          mMSB_FROM_WORD(x)
#define mGLB_XWALK_DEV_ID_LSB(x)          mMSB_FROM_WORD(x)

#define cGLB_XWALK_DEV_ID_EEPROM_ADDR_MSB 0xD9
#define cGLB_XWALK_DEV_ID_EEPROM_ADDR_LSB 0xDA


#define mGLB_XWALK_GET_DEV_ID()     mWORD_FROM_BYTES( (EE_I2C_ByteRead( cGLB_XWALK_DEV_ID_EEPROM_ADDR_MSB )), \
                                                    (EE_I2C_ByteRead( cGLB_XWALK_DEV_ID_EEPROM_ADDR_LSB )) ) 
  

#define mGBL_XWALK_SET_DEV_ID(bMSB,bLSB)     EE_I2C_ByteWrite( bMSB,cGLB_XWALK_DEV_ID_EEPROM_ADDR_MSB ); \
                                    EE_I2C_ByteWrite( bLSB,cGLB_XWALK_DEV_ID_EEPROM_ADDR_LSB );
  

// there are some device IDs that are saved for special uses

#define cGLB_XWALK_DEFAULT_DEV_ID             0xFFFF

// if this device ID allows for any controller to control any xwalk device
// wihtout having to train the device

#define cGLB_XWALK_UNIVERSAL_DEV_ID           0xFFFE

#endif // ********** END OF cGLB_XWALK_DEV_ID **********

/*
  Extra settings if the RF Module is enable
*/
#ifdef cGLB_RF_ENABLE 

// if the remote load is enable we know that 
// we do not want syncing of any kind
#ifndef cGLB_PRODUCT_REMOTE_TX

// allows for the RF_State module to be loaded
// this module is only used in crosswalk applications
// or any other prodcut that needs to sync with another device
#define cRF_Sync_Enable 


/*
  IF NOT commented out = transmitting in sigle freq ONLY
  IF commented out = transmitting in FHSS
*/
#define cRF_nFCC_Enable // comment this if you wanna send unit to FCC test

#endif // END OF cGLB_REMOTE_ENABLE 


// selects the desired output power for the RF chip
#define cRF_Output_Gain                             (cRF_PA_OUTPOWER_13dBm)   


#endif // END OF cGLB_RF_ENABLE






/*
  Extra settings if the GSM module is enabled
*/
#ifdef cGLB_GSM_ENABLE

// this define will prevent the modem for being configures but it will still be turned on
#define cGLB_NO_CONFIGS_FOR_GSM      1

#endif

/*
  Mode settings if the ERR module is set 
*/
#ifdef cERR_ENABLE

// this is set if we want to override older errors if the error database is full
#define cERR_Override_Errors


#endif

//#define cLED_I2C_ENABLE
//#define cDTMF_ENABLE
//#define cSYS_TIM_ENABLE
//#define cDEBUG_MODE
//#define cBUTTON_ENABLE
//#define cRCC_PLL_ENABLE
//#define cIWDG_ENABLE



#define cCOMPANY_NAME    "JSF Technologies"


//#ifdef cGLB_PRODUCT_SZ_CTRL

//#define cPRODUCT_NAME    "SZ"

//#define cHW_VER          "2.03"

//#define cSW_VER          "1.11"

//#endif // ********** END OF cGLB_PRODUCT_SZ_CTRL**********



#ifdef cGLB_PRODUCT_XWALK
#ifdef cGLB_PRODUCT_SZ_CTRL
#define cPRODUCT_NAME    "SZ"
#else 
#define cPRODUCT_NAME    "Active Beacon"
#endif
#define cHW_VER          "1.02"

#define cSW_VER          "1.24"

#endif // ********** END OF cGLB_PRODUCT_XWALK**********

#ifdef cGLB_PRODUCT_24HR
#define cPRODUCT_NAME     "24Hr"
#define cHW_VER           "2.03"
#define cSW_VER           "1.22"
#endif // ********* END of cGLB_PRODUCT_24HR **********

#ifdef cGLB_PRODUCT_FOB
#ifndef cGLB_PRODUCT_XWALK
#define cPRODUCT_NAME     "FOB"
#define cHW_VER           "1.00"
#define cSW_VER           "1.00"
#endif
#endif // ******** END of cGLB_PRODUCT_FOB **********

#define cGLB_SUPERVISOR   "SP"
#define cGLB_SLAVE        "SL"

#define cGLB_60secSysTim 0x3C
#define cGLB_30secSysTim 0x1E




#define pcGLB_aBufPtr_INVALID (tGLB_aBufPtr)(NULL)
#define pbGLB_NULL (tGLB_aBufPtr)(NULL)




/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */
/*--------------------------------------------------------------------
 	$Type: Primary Storage Types
	$Description: primary types
	$End
 */
typedef u8 tBOOL;
typedef u32 tTIM_VAR;

/*--------------------------------------------------------------------
 	$Type: tpvDATA_PTR
	$Description: Far data void pointer
	$End
 */
//typedef tGLB_FAR_DATA void * tpvGLB_DATA_PTR;
typedef void * tpvGLB_DATA_PTR;



/*------------------------------------------------------------------------------
 	$Type: tGLB_BitFlags16
	$Description: bit-fields to replace bdata bit and sbit declarations
	$End
 */
typedef struct
{
	unsigned short int	bit_0	:	1;
	unsigned short int	bit_1	:	1;
	unsigned short int	bit_2	:	1;
	unsigned short int	bit_3	:	1;
	unsigned short int	bit_4	:	1;
	unsigned short int	bit_5	:	1;
	unsigned short int	bit_6	:	1;
	unsigned short int	bit_7	:	1;
	unsigned short int	bit_8	:	1;
	unsigned short int	bit_9	:	1;
	unsigned short int	bit_10 : 1;
	unsigned short int	bit_11 : 1;
	unsigned short int	bit_12 : 1;
	unsigned short int	bit_13 : 1;
	unsigned short int	bit_14 : 1;
	unsigned short int	bit_15 : 1;

} tGLB_BitFlags16;

/*------------------------------------------------------------------------------
 	$Type: tGLB_BitFlags16_union
	$Description: single statement access to clear all bit-fields
	$End
 */
typedef union
{
	unsigned short int uiAll;
	tGLB_BitFlags16	bits;

} tGLB_BitFlags16_union;


/*------------------------------------------------------------------------------
 	$Type: tGLB_TimeStamp_Struct
	$Description: This struct contains all the fields needed to create and use
                      a timestamp/timeout function 
	$End
 */
typedef struct
{
  u8 bFlag;
  u32 lwTimeStamp;
  u32 lwTimeOut;
  
} tGLB_TimeStamp_Struct;

/*------------------------------------------------------------------------------
 	$Type: tMEM_WordByte_union
	$Description: Union to allow u8 or u16 access to same memory location
	$End
 */
typedef union
{
	u16	wVar;
	u8	pbVar[2];

} tMEM_WordByte_union;

/*--------------------------------------------------------------------
 	$Type: tGLB_aBufPtr
	$Description: defined to overcome a circular compile problems
	$End
 */
typedef u8 * tGLB_aBufPtr;

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

#endif // __GLB_H__

