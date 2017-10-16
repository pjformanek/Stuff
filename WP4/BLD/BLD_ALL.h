/*--------------------------------------------------------------------------
$Filename: BLD.h
$Prefix: BLD

$Description:
        This file contains macro definitions that configure the build of the
        WP4 project.This file should be reviewed before building each 
        F/W release to ensure that all desired build options (including
        version definitions) are properly set.

$CAUTION:	This file only applies to 'c' source files. Files that are
                are outside this scope (e.g. .asm files) must be 
                controlled through some separate mechanism.

$Author:	KGANS, JRAMIREZ, originated 2009-Mar-6
--------------------------------------------------------------------------
$Copyright (c) 2004-2009 J.S.FOSTER Corporation 	All Rights Reserved
--------------------------------------------------------------------------
$End
----------------------------------------------------------------------------*/

#ifndef BLD_H
#define BLD_H

/*----------------------------------------------------------------------------
			----- I N C L U D E   F I L E S -----
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			----- M A C R O   D E F I N I T I O N S -----
  ----------------------------------------------------------------------------*/


#define cBLD_PreReleaseSourceReview 				(0)	/* set this flag to identify all 
															questionable source statements */




#if 0 /* WP4  ... for quick reference ... any of this that is required
			for WP4 should be cut and pasted  ... the rest should be deleted
			ASAP */



/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
//#include "BLD_Test.h"

/* -------------------
	HARDWARE REVISION
   ------------------- */

	#define cBLD_HW_Revision				(cBLD_HW_Revision_RV2A)

	// revision definitions
	//
	#define HW_Revision_EB					1	// evaluation board hardware
	#define HW_Revision_EB_STAN				2	// small board created by Stan 
												// Polyakov, similar to evaluation board 
												// hardware
	#define HW_Revision_RV1A				3	// first cut protoypes of CWSD hardware
												// built by hand by Stan Polyakov

	#define HW_Revision_RV1A_UNLOADED		4	// first cut protoypes of CWSD hardware
												// built by hand by Stan Polyakov with
												// only minimal components required for
												// RF operation populated
	#define cBLD_HW_Revision_RV2A			5	// first manufacturing release of CWSD 
												// hardware based largely on HW_Revision_RV1A
												// - Note: first boards (2004/Sept) built by Prosemble
	#define BLD_HW_Revision_RmtTx_RV1A		6	// prototype boards for universal RmtTx

/* --------------------
    PRODUCT VARIATIONS
   -------------------- */
// Activate these product variants through .UV2 or other makefile
// Note: PROT_DeviceId.h activated through makefile as well
//			but will default to NULL if no makefile definition
//
#ifdef _AB_SNIFFER
#define cBLD_AB_NETWORK_SNIFFER			(1) /* synch with Ts0 device but do not transmit */
#else
#define cBLD_AB_NETWORK_SNIFFER			(0) /* synch with Ts0 device but do not transmit */
#endif

// -----------------------------------------------
//  --- MULTI MINUTE DURATION FROM PED BUTTON ---
// -----------------------------------------------
#define cBLD_MULTI_MINUTE_BEACON_AB		(0) /* normal product */
#define cBLD_MULTI_MINUTE_BEACON_CC		(1) /* Cattle Crossing AB one-of */
#define cBLD_MULTI_MINUTE_BEACON_HWY1	(2) /* highway warning AB variant #1 one-of */
//
#ifdef _MMB_HYW1
#define cBLD_MULTI_MINUTE_BEACON 			(cBLD_MULTI_MINUTE_BEACON_HWY1)
#else
#ifdef _MMB_CC
#define cBLD_MULTI_MINUTE_BEACON 			(cBLD_MULTI_MINUTE_BEACON_CC)
#else
#define cBLD_MULTI_MINUTE_BEACON 			(cBLD_MULTI_MINUTE_BEACON_AB)
#endif
#endif

// ---------------------
//  --- FLORIDA DOT ---
// ---------------------
#define cBLD_AB_N0_STROBE_NOT_FLORIDA	(0) /* normal product */
#define cBLD_AB_N0_STROBE_FLORIDA		(1) /* AB for Florida DOT */
#ifdef _MUTCD
#define cBLD_AB_N0_STROBE		   		(cBLD_AB_N0_STROBE_FLORIDA)
#else
#define cBLD_AB_N0_STROBE		   		(cBLD_AB_N0_STROBE_NOT_FLORIDA)
#endif

// Set the timer duration for WMS Remote Active flashing (timeout if no refresh 
//   burst from controller) ... 1 hour + 255 hours = 256 hours
#define cBLD_PROT_LedRemoteDurationSeconds_INIT	(cPROT_FlashDurationSeconds_1HR)
#ifdef _TO4
#define cBLD_PROT_LedRemoteDurationHours_INIT	(3)
#endif
#ifdef _TO24
#define cBLD_PROT_LedRemoteDurationHours_INIT	(23)
#endif
#ifdef _TO256
#define cBLD_PROT_LedRemoteDurationHours_INIT	(255)
#endif

/* -------------------
    SOFTWARE RELEASES
   ------------------- */

 // assume CWSD_2_V2 or CWSD_2_V2_Tester or BLD_CWSD2_V2_SP
 #define cGLOBAL_SwVersion_Major		5
 #define cGLOBAL_SwVersion_Minor		0
 #define cGLOBAL_SwVersion_Trial		'c' /* not used in source code ... reminder
													to F/W developer ... when making preliminary
													releases (release candidates) it may be helpful
													to name them _a, _b ... etc. so that subtle
													changes / tweaks in source code can be tracked */
/* ----------------
    MEMORY OPTIONS
   ---------------- */
//#define cBLD_RFC_crc8_BASE_ADDRS		(0xE0)
//#define cBLD_RFC_rxBuf_BASE_ADDRS		(0xE2)

/* --------------
    Boot Options
   -------------- */
#define BLD_HW_SFR_INIT				1	// see main.c initialization
#define BLD_HW_FastOutputEnable			1	// see main.c and HW_Init.c

// -----------------
// ----- W M S -----
// -----------------
//

// added in FEAT0010, modified in FEAT0011
#define mBLD_WMS_OptionSwitch()			SCAN_currentData_bFlashDuration
#define mBLD_WMS_UnTrainingSwitch()		SCAN_currentData_bNetAddrs
#define cbBLD_WMS_OptionSwitch_TRAINING		(0x0F)
#define cbBLD_WMS_UnTrainingSwitch_ON		(15)
#define cBLD_WMS_TRAINING_SECONDS		(120)

// ----------------
// ----- A W -----
// ----------------
//

// added in FEAT0C00
#define cbBLD_WMS_OptionSwitch_AW			(0x0D)
#define cBLD_AWB_FAILSAFE_DELAY_NUM_SECONDS	(10)

/* each hop allows an additional 5 ms for APP to complete main() 
	background activities BUT also,	slows down the synchronization
	process ...  at time of SW release, this value was not being used
	as sync forecast had been implemented ... prior to 
	forecasting, 3 seemed to be the "sweet" number for fast sync
	but this may have been dependent on the frequency CONFIG used
	by the AWC at the time of testing
*/
#define cBLD_AWB_NumFreqHopsAtSscTransition	(3) 
#define cBLD_AWB_UseSSCTestState			(0)



// ---------------------------------------------------
// ----- T E S T I N G   and   D E B U G G I N G -----
// ---------------------------------------------------
//

// - define '_DEBUGGING' flag in the uVision2 .UV2 project file (project options, C51 Tab)
//
#ifdef _DEBUGGING
#define DEBUGGING_ENABLED 				1	// Using the evaluation board in debug mode
#define BLD_ForceTs0Transition			0	// option to force device to be Ts 0 device

#else // !_DEBUGGING
#define DEBUGGING_ENABLED 				0	// Using the evaluation board in debug mode
#define BLD_ForceTs0Transition			0	// option to force device to be Ts 0 device

#endif // _DEBUGGING

#define cBLD_RLED_TimeslotDiagnostics	1
#define BLD_PROT_TestMaxIntensity		0 // invoke pattern of "always on" at max duty cycle ...for CWSD_2 only

// -----
// $CAUTION: When defining the following option as '0', ensure that target HW for 
// RV1A_UNLOADED PCBs does not have SW4 port tied to Gnd as the port may be defined 
// as output logic high (would likely burn out the related output transistors)
//
#define BLD_PROT_RxTxNetworkTest_HWSW		1 	// allow HW switch to disable test

/* -------------------------------------------------------------
    ----- P R O T O C O L   A N D   P U S H   B U T T O N -----
   -------------------------------------------------------------*/

/* ---------------
	PROT REVISION
   --------------- */
#define BLD_PROT_Revision					BLD_PROT_Revision_V2B
#define BLD_PROT_Revision_V1				0 // Mike Osborne reference implementation
#define BLD_PROT_Revision_V2A				1 // based partly on Mike Osborne 
#define BLD_PROT_Revision_V2B				2 // protocol altered, incompatible with previous revisions

/* -----------------
	BUTTON REVISION
   ----------------- */
#define BLD_PROT_ButtonMethod				BLD_PROT_ButtonMethod_V2
#define BLD_PROT_ButtonMethod_V1			0
#define BLD_PROT_ButtonMethod_V2			1

// added post FEAT0010
// these are part of the increasing resilience against spontaneous 
// flashing added in AB WI3.02
#define cBLD_WMS_OptionSwitch_REMOTE		(0x0E)
#define cBLD_PROT_BUTTON_BLOCKING_A			0
#define cBLD_PROT_BUTTON_BLOCKING_B			0
#define cBLD_PROT_BUTTON_BLOCKING_C			1
#define cBLD_PROT_BUTTON_BLOCKING_D			1
#define cBLD_PROT_BUTTON_BLOCKING_E			1
#define cBLD_PROT_BUTTON_BLOCKING_F			0
#define cBLD_PROT_BUTTON_BLOCKING_G			1

// added for the Rls of RmtTx_WI200
#define cBLD_SHORT_STIM_SUPPORT				0

// added in FEAT0015
// Define the RF Protocol Tx messages that will be used in the product
//
#define cBLD_RFC_PROT_TxMsgId_ClassShortStim_RMTBUTTON			(0)
#define cBLD_RFC_PROT_TxMsgId_ClassShortStim_RMTACTIVE			(0)
#define cBLD_RFC_PROT_TxMsgId_ClassShortStim_RMTIDLE			(0)
#define cBLD_RFC_PROT_TxMsgId_ClassBasic_LIFE					(1)
#define cBLD_RFC_PROT_TxMsgId_ClassBasic_MSG1					(1)
#define cBLD_RFC_PROT_TxMsgId_ClassBasic_MSG2					(1)
#define cBLD_RFC_PROT_TxMsgId_ClassBasic_WMS_RMTACTIVE_MODEA	(0)	
#define cBLD_RFC_PROT_TxMsgId_ClassBasic_WMS_RMTIDLE_MODEA		(0)	
#define cBLD_RFC_PROT_TxMsgId_ClassBasic_WMS_RMTTRAINING_MODEA	(0)	
#define cBLD_RFC_PROT_TxMsgId_ClassVariable1_TBD				(0)

/* ---------------------
 	--- workarounds ---
   ---------------------*/

#define cBLD_PROT_RT_InhibitScan						1

// to address CC1010 silicon bug
#define cBLD_RFC_FREQLOCK_WORKAROUND					1

// protection against spontaneous flashing
#define cBLD_PROT_ShortStimRmtTxMsgIntegrity_SECONDS	3
#define cBLD_PROT_ShortStimRmtTxMsgIntegrity_COUNT		3 /* require 3 msgs in 3 seconds */
#define cBLD_PROT_WmsRmtTxMsgIntegrity_SECONDS			5
#define cBLD_PROT_WmsRmtTxMsgIntegrity_COUNT			0 /* DISABLED */

/* -------------------------------------------------------------------------
	----- R A D I O   F R E Q U E N C Y   C O M M U N I C A T I O N -----
   -------------------------------------------------------------------------- */

/* options: 50 or 51 */
#define cBLD_RFC_NUM_FREQS					51

/* Only for ABs - Remote transmitters do not need this */
#define cBLD_RFC_TimeslotProcessing			1

/* Only for ABs - Remote transmitters do not need this */
#define cBLD_RFC_BuildRx					1

/* Only for Remote transmitters - ABs do not need this */
#define cBLD_RFC_BuildTxBurst				0

/* Set the target CC1010 RF Power at the end of power amplifier ramping 
	Note: WMS Controllers should not define this but rather handle
				PA Power through downloadable NVMEM parameters */
#define cBLD_RFC_PA_POW_Target				(eRFC_WMS_PA_POW_4dBm)

/* -------------
	RF REVISION
   ------------- */

#define BLD_RFC								(BLD_RFC_V3)
#define BLD_RFC_SCH							(BLD_RFC_V3)
#define BLD_RFC_TMR0						(BLD_RFC_V3)

#define BLD_RFC_V1 							1	// V1:mainly using Mike Osborne's 
												// reference implementation with subtle tweaks
#define BLD_RFC_V2 							2	// V2:based on reference implementation 
												// with functions broken into chunks
#define BLD_RFC_V3							3	// same as V1 but using scheduler to
												// move actuation outside of TMR0 ISR
												// so that TMR1 (LED flashing) is not so 
												// inhibited by TMR0 ISR
#define BLD_RFC_FREQLOCK_WORKAROUND			1	// to address CC1010 silicon bug

#define FREQ_HOPPING_DISABLED 		 		0	// define as 1 to transmit on a single 
												// frequency only
#if FREQ_HOPPING_DISABLED == 1
#define BLD_RFCOMM_NUM_FREQS 				2
#define BLD_RFCOMM_902_5MHZ_TestFreq 		0	// lowest
#define BLD_RFCOMM_915_MHZ_TestFreq			1	// middle
#define BLD_RFCOMM_927_5MHZ_TestFreq		0	// highest
#else
#define BLD_RFCOMM_NUM_FREQS				51	// options: 50 or 51
#endif

// define additional action to ensure that lock is solid before enabling 
// full Rx or Tx
//
#define cBLD_RFC_FREQLOCK_POSTLOCKMODE_NONE	0
#define cBLD_RFC_FREQLOCK_POSTLOCKMODE_WAIT	1	// found to cause spurious (spurs) Tx out of band
#define cBLD_RFC_FREQLOCK_POSTLOCKMODE_TEST	2	// found to cause spurious (spurs) Tx out of band
#define cBLD_RFC_FREQLOCK_POSTLOCKMODE		BLD_RFC_FREQLOCK_POSTLOCKMODE_NONE

#define cBLD_RFC_FREQLOCK_CallibrateDelay	0	// add an additional lock delay time in effort
												// to remove a spurious frequency error (934 MHz)
												// ...does not seem to have any effect

// -------------------------
// ----- MODEM CONTROL -----
// -------------------------
//
#define cBLD_RFC_MODEM						cBLD_RFC_MODEM_V2
#define cBLD_RFC_MODEM_V1					1	// implementation as per Mike Osborne's 
												// reference design
#define cBLD_RFC_MODEM_V2					2	// modifications to allow free running of
												// averaging filter and selection of preamble 
												// based on sensitivity and settling time
#define cRFC_MODEM1_UsePeakDetector 		1	// peak detector; requires careful choice 
												// of the peak level offset (PLO) value
												// stored in MODEM2
// For experimenation only...
// according to Chipcon, can let averaging filter run
// free when using a balanced signal (manchester encoded)
#define cBLD_RFC_LOCK_AVG_FILTER			0

// ---------------------------------
// ----- TRANSCEIVER OPERATION -----
// ---------------------------------
//
#define cBLD_RFC_IsrRfDisable_RxError				0
#define cBLD_RFC_IsrPowerDownRfPostTx 				1
#define cBLD_RFC_TxPowerEnableRamping 				1

// --------------------------
// ----- IMPORTANT NOTE -----
// --------------------------
//
//	Many combinations of flags that follow were tested (2004-APR-14) 
//	None were observed to make any significant change in amount of out-of-band 
//	Tx power. Therefore it is believed that options can be set based on the 
//	most desirable real-time budget and power management
//
#if 0
#define BLD_RFCOMM_TxPowerDisableRamping 			0
#define BLD_RFCOMM_TxPowerDisableRamping_TxOff		1	// 1:slam PA_POW to 0 once packet Tx'd
#define BLD_RFCOMM_RFPowerDownAfterTx				1	// 1:power down the RF section once packet Tx'd
#endif

// -----------------------------------------------
// ----- R F   F R E Q U E N C Y   T E S T S -----
// -----------------------------------------------
//
#define BLD_RFCOMM_DisableRx 				0	// To stop RFMAIN RX_PD from getting cleared (inhibit Rx power up)
#define BLD_RFCOMM_DisableTx 				0	// To stop RFMAIN TX_PD from getting cleared (inhibit Tx power up)
#define	BLD_RFCOMM_AlwaysOnRx				0 	// only disable Rx and enable Tx for the minimum amount of time
#define cBLD_RFC_ReqTxTestMode				0

// ----------------------------------------------------------------------------------------------
//  	S S C   -   S Y N C H R O N I Z A T I O N   S T A T E   M A C H I N E   O P T I O N S
// ----------------------------------------------------------------------------------------------
//

/* ------------------
   --- SSC METHOD ---
   ------------------ */
#define BLD_SSC_Method 						BLD_SSC_Method_V1A
#define BLD_SSC_Method_V1					0
#define BLD_SSC_Method_V1A					1
#define BLD_SSC_Method_V2A					2

#define BLD_SSC_ResetOnProtocolTimeslotError 1	// $CAUTION: Devices within our own network can cause
												// these errors in cases of extreme jitter so reset
												// can actually create a less stable solution $End
#define cBLD_SSC_ResetOnNetworkError		0	// added for AB WI3.03

// ----------------------------------------------
// ----- S C H E D U L E R   O P T I O N S ------
// ----------------------------------------------
//
												// processing), the SSC processing cycles
#define BLD_SCH_EventQueueCheckInMain		1	// if not defined, may get linker recursion warning

// ----------------------------------------------
// ----- S C A N N I N G    O P T I O N S -------
// ----------------------------------------------
//
#define BLD_SCAN_InhibitScanning			0
#define BLD_ADC_RunContinuous				0	// remain scanning forever in SCAN_Data_Init()
#define cBLD_SCAN_ScanningInSearchMode 		1
#define cBLD_scanThrottleInit_AB			11 // attempted workaround for Bug 127 that wasn't a solution
#define cBLD_scanThrottleInit_AWB			0 // attempted workaround for Bug 127 that wasn't a solution

// change quickly to target within number of samples of FIR rather than
// using slow ramping
//
#define BLD_LED_Intensity_FastUpdate		0

// secondary update process that is run in conjunction with original
// LED_IntensityUpdate()
//
#define BLD_LED_Intensity_Adaptive			1

// charging and voltage sampling
//
#define BLD_SCAN_ChargingTest				0
#define BLD_SCAN_TempSensor 				0	// not supported in HW; supporting SW is incomplete
#define BLD_SCAN_SupportResetSwitch			1
#define cBLD_SCAN_SupportShutDown			(0)	// whether or not to shutdown unit
												// if battery voltage sample indicates
												// low battery
// --------------------------------
// 		--- W A T C H D O G ---
// --------------------------------

//#define cBLD_WDT_Watchdog					1

// -------------------------------------------
// ----- R E A L - T I M E   I S S U E S -----
// -------------------------------------------

#define cBLD_ISR_DECLARE_VOLATILE			(1)
#define cBLD_ISR_DATA_DECLARATIONS_SCH		(1)
#define cBLD_ISR_DATA_DECLARATIONS_TMR1		(1)
#define cBLD_ISR_DATA_DECLARATIONS_MAIN		(1)
#define cBLD_ISR_DATA_DECLARATIONS_RFC_RX	(1)
#define cBLD_ISR_DATA_DECLARATIONS_LED		(1)
#define cBLD_MAIN_TMR1_EXECUTE_IN_ISR		(1)

#define BLD_ACTIVE_IDLE_Ratio				(BLD_ACTIVE_IDLE_Ratio_30Percent)

#define BLD_ACTIVE_IDLE_Ratio_25Percent		(1)
#define BLD_ACTIVE_IDLE_Ratio_30Percent		(2)
#define BLD_ACTIVE_IDLE_Ratio_64Percent 	(3)

#define BLD_SCAN_SlowDataUpdate				0

#define BLD_TMR0_SyncTimerForTs0					0

// -----------------------------------------------
// 		--- L E D   D I A G N O S T I C S ---
// -----------------------------------------------
//
// In general the LEDs are used for diagnostics in the following way:
//
//		RED			: Used to measure TMR0 and timeslot event activity
//		YELLOW		: Used to mimic the light heads and to show sync state
//		GREEN		: Used to measure various events, reassign to different tests
//		BLUE		: Used as a lifesign

 #define BLD_TestLed_Red					1
 #define BLD_TestLed_Yellow					1

// -------
// RED LED
// -------

#define BLD_TMR0_RTEvent_Testpoint			0	// for SCH RT engine events, RED LED: ON=begin OFF=done
#define BLD_RFCOMM_ReCalibrateWarning		0	// Use RED LED to indicate that an Rx frequency would not lock

// -----------
// YELLOW LED
// -----------

// Use main light heads and Yellow LED to report SSC state changes, etc.
//
#define BLD_LED_EnableDiagFlashes			1
// ...report the number of seen devices based on the number of flashes
//
#define BLD_LED_DiagReportSeenDevices		0
// ...report the timeslot used by this device based on the number of flashes
//
#define BLD_LED_DiagReportTimeslot			1
// ...flash following reset, before interrupts are enabled
// 
#define BLD_FlashLedsOnReset				0
// ...flash if defined number of frequencies does not match frequency table
// 
#define BLD_FlashLedsOnFreqBldError			1

extern code char scCopyright[];
extern code char scSwVersion[2];

#endif /* WWP4 */

#endif // BLD_H

