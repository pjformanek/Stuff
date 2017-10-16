/*------------------------------------------------------------------------------
  	$File:		MEM.h
  	$Module:  	Memory Configuration Directives, Definitions
  	$Prefix:  	MEM
  	$Language:	ANSI C
  	$Description:

		ROM Memory Mapping.
		  ... each .C unit must #define a cMEM_USER_CLASS_ID
		  ... the _ID is used to control access to global variables
		      and more importantly, to allow the ROM in the unit
			  to be allocated to the proper memory space using the
			  userclass pragma
				///// TBD how this works with IAR

		RAM Memory Mapping. Memory used for data buffers must be
		statically declared. This removes it from the free pool of
		memory available to the IAR linker. Because of this,
		at certain points in the code, some of the static
		buffer memory must be made available through a MALLOC
		scheme.

  	$Notes:
  	$Author:	KGANS, 2009-May-26
  	--------------------------------------------------------------------------
  	$Copyright (c) 2005-2010 J.S. Foster Corporation  	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __MEM_H__
#define __MEM_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M E M O R Y   M A P P I N G -----
  ------------------------------------------------------------------------------
 */

// ---------------------------------------------------------------------
//		----- R A M ---------------
// ---------------------------------------------------------------------


// ---------------------------------------------------------------------
//		----- R O M ---------------
// ---------------------------------------------------------------------

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
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*	----------------------------------------------------------------------------
	-----  C O R E  /  S Y S T E M  --------------------------------------------
	----------------------------------------------------------------------------
*/

// -------------------------------------------------------------------------------
// WARNING: If using the Keil compiler, do not use these bit fields for
//			assignment (e.g. do not code bFlagStatus = bbMEM_appFlags_DebugEnable)
//			This has been known to corrupt other bits.
//
//			If you need to sample the flag status you must do so using a logical
//			bit check (e.g. if( bbMEM_appFlags_DebugEnable ) bFlagStatus = 1)
// -------------------------------------------------------------------------------

#define bbMEM_appFlags_RFC_SEMA_isActiveTx			pMEM_appFlags1.bits.bit_0
#define bbMEM_appFlags_RFC_SEMA_isServiced			pMEM_appFlags1.bits.bit_1
#define bbMEM_appFlags_free_A2									pMEM_appFlags1.bits.bit_2
#define bbMEM_appFlags_free_A3									pMEM_appFlags1.bits.bit_3
#define bbMEM_appFlags_free_A4									pMEM_appFlags1.bits.bit_4
#define bbMEM_appFlags_free_A5									pMEM_appFlags1.bits.bit_5
#define bbMEM_appFlags_free_A6									pMEM_appFlags1.bits.bit_6
#define bbMEM_appFlags_free_A7									pMEM_appFlags1.bits.bit_7
#define bbMEM_appFlags_free_A8									pMEM_appFlags1.bits.bit_8
#define bbMEM_appFlags_free_A9									pMEM_appFlags1.bits.bit_9
#define bbMEM_appFlags_free_A10									pMEM_appFlags1.bits.bit_10
#define bbMEM_appFlags_free_A11									pMEM_appFlags1.bits.bit_11
#define bbMEM_appFlags_free_A12									pMEM_appFlags1.bits.bit_12
#define bbMEM_appFlags_free_A13									pMEM_appFlags1.bits.bit_13
#define bbMEM_appFlags_free_A14									pMEM_appFlags1.bits.bit_14
#define bbMEM_appFlags_free_A15									pMEM_appFlags1.bits.bit_15

// -------------------------------------------------------------------------------
// WARNING: If using the Keil compiler, do not use these bit fields for
//			assignment (e.g. do not code bFlagStatus = bbMEM_appFlags_DebugEnable)
//			This has been known to corrupt other bits.
//
//			If you need to sample the flag status you must do so using a logical
//			bit check (e.g. if( bbMEM_appFlags_DebugEnable ) bFlagStatus = 1)
// -------------------------------------------------------------------------------
 #define bbMEM_appFlags_L2_GSM_INIT							pMEM_appFlags2.bits.bit_0
 #define bbMEM_appFlags_L2_GSM_DATA							pMEM_appFlags2.bits.bit_1
 #define bbMEM_appFlags_L2_GSM_SMS_RX 					pMEM_appFlags2.bits.bit_2
 #define bbMEM_appFlags_GSM_SMS_POLLING					pMEM_appFlags2.bits.bit_3
 #define bbMEM_appFlags_L2_GPRS_FTP							pMEM_appFlags2.bits.bit_4
 #define bbMEM_appFlags_L1_DIRECT_RX_FLOW_OFF		pMEM_appFlags2.bits.bit_5
 #define bbMEM_appFlags_I2C_EE_BLOCK_HI					pMEM_appFlags2.bits.bit_6
 #define bbMEM_appFlags_RtcDeviceRefreshState		pMEM_appFlags2.bits.bit_7
 #define bbMEM_appFlags_EventPushButton_OLD_JUNK			pMEM_appFlags2.bits.bit_8
 #define bbMEM_appFlags_APP_RUN									pMEM_appFlags2.bits.bit_9
 #define bbMEM_appFlags_CODE_TBL_SELECT					pMEM_appFlags2.bits.bit_10
 #define bbMEM_appFlags_L2_DEBUG_MUTE						pMEM_appFlags2.bits.bit_11
 #define bbMEM_appFlags_L2_GPRS_HTTP						pMEM_appFlags2.bits.bit_12
 #define bbMEM_appFlags_DAT_WRITE								pMEM_appFlags2.bits.bit_13
 #define bbMEM_appFlags_HW_FLOW_TX_DELAY	  		pMEM_appFlags2.bits.bit_14
 #define bbMEM_appFlags_HW_FLOW_SWING_ACTIVE		pMEM_appFlags2.bits.bit_15

// -------------------------------------------------------------------------------
// WARNING: If using the Keil compiler, do not use these bit fields for
//			assignment (e.g. do not code bFlagStatus = bbMEM_appFlags_DebugEnable)
//			This has been known to corrupt other bits.
//
//			If you need to sample the flag status you must do so using a logical
//			bit check (e.g. if( bbMEM_appFlags_DebugEnable ) bFlagStatus = 1)
// -------------------------------------------------------------------------------
 #define bbMEM_appFlags_HW_RTS_image						pMEM_appFlags3.bits.bit_0
 #define bbMEM_appFlags_HW_DTR_image						pMEM_appFlags3.bits.bit_1
 #define bbMEM_appFlags_L1_WMS_TEXT_FLTR				pMEM_appFlags3.bits.bit_2
 #define bbMEM_appFlags_L1_SMS_FLOW_OFF					pMEM_appFlags3.bits.bit_3
 #define bbMEM_appFlags_TX_CARRIER_TEST					pMEM_appFlags3.bits.bit_4
 #define bbMEM_appFlags_Free5										pMEM_appFlags3.bits.bit_5
 #define bbMEM_appFlags_Free6										pMEM_appFlags3.bits.bit_6
 #define bbMEM_appFlags_Free7										pMEM_appFlags3.bits.bit_7
 #define bbMEM_appFlags_Free8										pMEM_appFlags3.bits.bit_8
 #define bbMEM_appFlags_Free9										pMEM_appFlags3.bits.bit_9
 #define bbMEM_appFlags_Free10									pMEM_appFlags3.bits.bit_10
 #define bbMEM_appFlags_Free11									pMEM_appFlags3.bits.bit_11
 #define bbMEM_appFlags_Free12									pMEM_appFlags3.bits.bit_12
 #define bbMEM_appFlags_Free13									pMEM_appFlags3.bits.bit_13
 #define bbMEM_appFlags_Free14									pMEM_appFlags3.bits.bit_14
 #define bbMEM_appFlags_Free15									pMEM_appFlags3.bits.bit_15

/*=======================================*/
	#ifdef cMEM_USERCLASS_ID_MEM_BOOT_c
/*=======================================*/
	#define __MEM_BOOT_c	/* for CW background parser only */

	/*----------------
	Local Declarations
 	------------------*/

	/*-----------------
	Global Declarations
 	-------------------*/
	tGLB_BitFlags16_union						pMEM_appFlags1;

	#else
	/*---------------
	Access to Globals
	-----------------*/
	extern tGLB_BitFlags16_union				pMEM_appFlags1;
	extern tGLB_BitFlags16_union				pMEM_appFlags2;
	extern tGLB_BitFlags16_union				pMEM_appFlags3;

	#endif /* cMEM_USERCLASS_ID_MEM_BOOT_c */

/*============================================*/
	#ifdef cMEM_USERCLASS_ID_RFC_UTILITIES_c
/*============================================*/
	#define __RFC_UTILITIES_c	/* for CW background parser only */

 	#include "HW_CC1101.h"

	/*----------------
	Local Declarations
 	------------------*/
	static tpHW_CC1101_allFreqCalData	pRFC_CC1101_allFreqCalData;
	static tpHW_CC1101_perFreqCalData	pRFC_CC1101_perFreqCalData[(cRFC_CC1101_FREQ_MULTIPLIER)*(cBLD_RFC_PROT_NUM_FREQS)];

	/*-----------------
	Global Declarations
 	-------------------*/

	#else
	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_RFC_UTILITIES_c */



/*========================================*/
	#ifdef cMEM_USERCLASS_ID_HW_CC1101_c
/*========================================*/
	#define __HW_CC1101_c	/* for CW background parser only */
	/*----------------
	Local Declarations
 	------------------*/
	static u8 						bMEM_HW_CC1101_chipStatusByte;

	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_HW_CC1101_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_SD_OPEN_LOG_CONFIG_c
/*========================================*/
	#define __HW_CC1101_c	/* for CW background parser only */
	/*----------------
	Local Declarations
 	------------------*/
	static u8 						bMEM_HW_CC1101_chipStatusByte;

	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_HW_CC1101_c */




/*========================================*/
	#ifdef cMEM_USERCLASS_ID_STORAGE_MANAGER_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_STORAGE_MANAGER_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_TIME_MANAGER_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_TIME_MANAGER_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_ENCODE_MANAGER_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_ENCODE_MANAGER_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_SD_OPEN_LOG_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_RTC_I2C_CONFIG_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_SYS_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_SYS_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_TIMER_MANAGER_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_TIMER_MANAGER_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_L2_GSM_PROCESS_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_L2_GSM_PROCESS_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_L2_CODE_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_L2_CODE_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_SW_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_SW_CONFIG_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_CAM_APPSTATE_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_CAM_APPSTATE_c */



/*========================================*/
        #ifdef cMEM_USERCLASS_ID_UTIL_UTILITIES_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_UTIL_UTILITIES_c */

/*========================================*/
        #ifdef cMEM_USERCLASS_ID_I2C_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_I2C_CONFIG_c */




/*========================================*/
	#ifdef cMEM_USERCLASS_ID_DOS_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_DOS_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_CC_CC1101_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_CC_CC1101_CONFIG_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_DEBUG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_DEBUG_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_EE_I2C_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_EE_I2C_CONFIG_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_LED_I2C_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_LED_I2C_CONFIG_c */



/*========================================*/
	#ifdef cMEM_USERCLASS_ID_RTC_I2C_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_RTC_I2C_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_DELAY_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_DELAY_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_BOOT_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_BOOT_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_EXTINT_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_EXTINT_CONFIG_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_GPIO_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/

	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_GPIO_CONFIG_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_MAIN_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_MAIN_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_NVIC_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_NVIC_CONFIG_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_RCC_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_RCC_CONFIG_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_RTC_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_RTC_CONFIG_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_SPI_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_SPI_CONFIG_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_TIMX_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_TIMX_CONFIG_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_USART_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_USART_CONFIG_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_ERR_c
/*========================================*/
	#define __ERR_c	/* for CW background parser only */

	/*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_ERR_c */


/*========================================*/
	#ifdef cMEM_USERCLASS_ID_GSM_TELIT_CONFIG_c
/*========================================*/
	#define __GSM_c	/* for CW background parser only */

	/*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_GSM_TELIT_CONFIG_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_USART_DEBUG_c            // Juan Clean up might need to get rid of this
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

        #endif /* cMEM_USERCLASS_ID_USART_DEBUG_c */

/*========================================*/
	#ifdef cMEM_USERCLASS_ID_SX_CONFIG_c
/*========================================*/

        /*----------------
	Local Declarations
 	------------------*/


	/*-----------------
	Global Declarations
 	-------------------*/


	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_SX_CONFIG_c */

/*============================================*/
	#ifdef cMEM_USERCLASS_ID_TMR_SYSTEM_c
/*============================================*/
	#define __TMR_SYSTEM_c	/* for CW background parser only */

	/*----------------
	Local Declarations
 	------------------*/

	/*-----------------
	Global Declarations
 	-------------------*/

	#else
	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_TMR_SYSTEM_c */

/*============================================*/
	#ifdef cMEM_USERCLASS_ID_TMR_SERVICES_c
/*============================================*/
	#define __TMR_SERVICES_c	/* for CW background parser only */
	
	/*----------------
	Local Declarations
 	------------------*/

	/*-----------------
	Global Declarations
 	-------------------*/
	#else
	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_TMR_SERVICES_c */

/*============================================*/
	#ifdef cMEM_USERCLASS_ID_XPLAT_c
/*============================================*/
	
	
	/*----------------
	Local Declarations
 	------------------*/

	/*-----------------
	Global Declarations
 	-------------------*/
	#else
	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_XPLAT_c */


/*============================================*/
	#ifdef cMEM_USERCLASS_ID_XPLAT_PROT_c
/*============================================*/
	
	
	/*----------------
	Local Declarations
 	------------------*/

	/*-----------------
	Global Declarations
 	-------------------*/
	#else
	/*---------------
	Access to Globals
	-----------------*/

	#endif /* cMEM_USERCLASS_ID_XPLAT_PROT_c */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

#endif // __MEM_H__

