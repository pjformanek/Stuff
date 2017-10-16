/*------------------------------------------------------------------------------
  	$File:		DEBUG.h	
  	$Module:  	DEBUG
  	$Prefix:  	DEBUG
  	$Language:	ANSI C
  	$Description:
		
  	$Notes:

  	$Author:	KGANS, 2009-June-12
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __DEBUG_H__
#define __DEBUG_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

#if cBLD_DEBUG == 0
#define cDEBUG_RFC_Utilities	(0)

#elif cBLD_DEBUG == 1
#define cDEBUG_RFC_Utilities	(0)
#else
#endif

#ifdef cHW_DEV_BOARD
#define mDEBUG_USARTxConfiguration()            USART_Usart1Config();
#define mDEBUG_USARTx_GPIO_Configuration()      GPIO_USART1Configuration();
#else
#define mDEBUG_USARTxConfiguration()            USART_Usart1Config();
#define mDEBUG_USARTx_GPIO_Configuration()      GPIO_USART1Configuration();
#endif

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

#define cDEBUG_AT_START_CHAR      '('
#define cDEBUG_AT_END_CHAR        ')'


#define cDEBUG_AT_START_STRING      "("
#define cDEBUG_AT_END_STRING        ")"


#define cDEBUG_AT_CC1101_MEM        "CC"
#define cDEBUG_AT_GSM_MEM           "GSM"
#define cDEBUG_AT_RAM_MEM           "RAM"
#define cDEBUG_AT_ROM_MEM           "ROM"
#define cDEBUG_AT_APP_MEM           "APP"
#define cDEBUG_AT_EE_MEM            "EE"
#define cDEBUG_AT_DOS_MEM           "DOS"
#define cDEBUG_AT_RTC_MEM           "RTC"

#define cDEBUG_AT_READ_FLAG         3
#define cDEBUG_AT_WRITE_FLAG        2
#define cDEBUG_AT_ASSIGN_FLAG       1


#define cDEBUG_AT_WRITE_CMD         '+'
#define cDEBUG_AT_READ_CMD          '#'
#define cDEBUG_AT_ASSIGN_CMD        '='
#define cDEBUG_AT_COMMA             ','
#define cDEBUG_AT_END_CMD           ';'

#define cDEBUG_CC_INDEX             0
#define cDEBUG_GSM_INDEX            1
#define cDEBUG_RAM_INDEX            2
#define cDEBUG_ROM_INDEX            3
#define cDEBUG_APP_INDEX            4
#define cDEBUG_EE_INDEX             5
#define cDEBUG_DOS_INDEX            6
#define cDEBUG_RTC_INDEX            7

#define cDEBUG_CC_FREQ              "FREQ"
#define cDEBUG_CC_PA                "PA"
#define cDEBUG_CC_HFREQ             "HFREQ"

#define cDEBUG_APP_DEBUG            "DEBUG"
#define cDEBUG_APP_CAM              "CAM"
#define CDEBUG_APP_PHONE            "PHONE"


#define cDEBUG_GSM_DUMMY            "DUMMY"
#define cDEBUG_GSM_SCRIPT           "SCRIPT"
#define cDEBUG_GSM_L2DATA           "L2DATA"

#define cDEBUG_DOS_DEBUG            "DEBUG"

#define cDEBUG_RTC_TIM              "TIM"

#define cDEBUG_USE_LAST_CMD_OUTPUT  "^$"

#define cDEBUG_MAX_MEM_LENGTH       20
#define cDEBUG_MAX_RETURN_LENGTH    32


#define cERR_ERROR_CODE      0xFF

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
    u8 * bDebugBuffer;
    u8 * bCommand;
    u8   bTmpDataIndex;
    u8   bAtFlag;

}tsDEBUG_CC1101CmdEntryTable;

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
    u8 * bDebugBuffer;
    u8 * bCommand;
    u8   bTmpDataIndex;
    u8   bAtFlag;

}tsDEBUG_GsmCmdEntryTable;

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
    u8 * bDebugBuffer;
    u8 * bCommand;
    u8   bTmpDataIndex;
    u8   bAtFlag;

}tsDEBUG_RamCmdEntryTable;

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
    u8 * bDebugBuffer;
    u8 * bCommand;
    u8   bTmpDataIndex;
    u8   bAtFlag;

}tsDEBUG_RomCmdEntryTable;

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
    u8 * bDebugBuffer;
    u8 * bCommand;
    u8   bTmpDataIndex;
    u8   bAtFlag;

}tsDEBUG_AppCmdEntryTable;

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
    u8 * bDebugBuffer;
    u8 * bCommand;
    u8   bTmpDataIndex;
    u8   bAtFlag;

}tsDEBUG_EeCmdEntryTable;



/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
    u8 * bDebugBuffer;
    u8 * bCommand;
    u8   bTmpDataIndex;
    u8   bAtFlag;

}tsDEBUG_DosCmdEntryTable;

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
    u8 * bDebugBuffer;
    u8 * bCommand;
    u8   bTmpDataIndex;
    u8   bAtFlag;
}tsDEBUG_RtcCmdEntryTable;

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
  u8  bFailFlag;
  u8  bByteVar;
  u8  bByteArrayVar[cDEBUG_MAX_RETURN_LENGTH];
  u16 wWordVar;
  u32 lwLongWordVar;

}tsDEBUG_ReturnVariables;


typedef u8(*tfDEBUG_CC1101Func)( tsDEBUG_CC1101CmdEntryTable * );
typedef u8(*tfDEBUG_GsmFunc)( tsDEBUG_GsmCmdEntryTable * );
typedef u8(*tfDEBUG_RamFunc)( tsDEBUG_RamCmdEntryTable * );
typedef u8(*tfDEBUG_RomFunc)( tsDEBUG_RomCmdEntryTable * );
typedef u8(*tfDEBUG_AppFunc)( tsDEBUG_AppCmdEntryTable * );
typedef u8(*tfDEBUG_EeFunc)( tsDEBUG_EeCmdEntryTable * );
typedef u8(*tfDEBUG_DosFunc)( tsDEBUG_DosCmdEntryTable * );
typedef u8(*tfDEBUG_RtcFunc)( tsDEBUG_RtcCmdEntryTable * );


/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */


/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
extern u8 bDEBUG_TempMemSpace[cDEBUG_MAX_MEM_LENGTH];
extern u8 bDEBUG_TempCmdSpace[cDEBUG_MAX_MEM_LENGTH];

extern u8 bDEBUG_DebugOnOffFlag;

extern u8 bDEBUG_WriteFlag;
extern u8 bDEBUG_ReadFlag;
extern u8 bDEBUG_AssignFlag;

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

u8 DEBUG_LiveDebugAppState( u8 * pbUSART_RX_Buffer );
u8 DEBUG_StripCmd( u8 * pbBuffer, u8 * pbTempBuffer , u8 bStartByte, u8 bEndCharacter );
u16 DEBUG_LookUpTableIndexFinder( u8 * pbBuffer, sc8 * pbLookUpTable[], sc16 wAvailableCommands );



u8 DEBUG_CcFreqCmd( tsDEBUG_CC1101CmdEntryTable * ptsCC1101CmdEntryTable );
u8 DEBUG_CcPaCmd( tsDEBUG_CC1101CmdEntryTable * ptsCC1101CmdEntryTable );
u8 DEBUG_CcHfreqCmd( tsDEBUG_CC1101CmdEntryTable * ptsCC1101CmdEntryTable );

u8 DEBUG_GsmDummy1( tsDEBUG_GsmCmdEntryTable * ptsDEBUG_GsmCmdEntryTable );
u8 DEBUG_GsmScript( tsDEBUG_GsmCmdEntryTable * ptsDEBUG_GsmCmdEntryTable );
u8 DEBUG_GsmL2Data( tsDEBUG_GsmCmdEntryTable * ptsDEBUG_GsmCmdEntryTable );


u8 DEBUG_AppDebug( tsDEBUG_AppCmdEntryTable * ptsDEBUG_AppCmdEntryTable );
u8 DEBUG_AppCam( tsDEBUG_AppCmdEntryTable * ptsDEBUG_AppCmdEntryTable );

u8 DEBUG_DosDebug( tsDEBUG_DosCmdEntryTable * ptsDEBUG_DosCmdEntryTable );

u8 DEBUG_RtcDebug( tsDEBUG_RtcCmdEntryTable * ptsDEBUG_RtcCmdEntryTable );



void DEBUG_Init( void );

#endif // __DEBUG_H__

