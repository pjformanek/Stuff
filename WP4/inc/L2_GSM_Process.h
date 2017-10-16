/*------------------------------------------------------------------------------
  	$File:		L2_GSM_Process.h	
  	$Module:  	Scripting Engine
  	$Prefix:  	L2_GSM
  	$Language:	ANSI C
  	$Description:
		
  	$Notes:

  	$Author:	Juan Ramirez, 2009-July-3
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __L2_GSM_PROCESS_H__
#define __L2_GSM_PROCESS_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */


#define cL2_USARTx_RX_INT_FLAG            bUSART3_RX_IntFlag
#define cL2_USARTx_BUFFER                 bUSART3_RX_Buffer

#define cL2_GSM_SENDLN      "sendln"
#define cL2_GSM_WAITLN      "waitln"
#define cL2_GSM_RESPLN      "respln"
#define cL2_GSM_TIMEOUT     "timeout"
#define cL2_GSM_OPTION      "option"
#define cL2_GSM_RETRY       "retry"

#define cL2_GSM_SENDLN_INDEX      0
#define cL2_GSM_WAITLN_INDEX      1
#define cL2_GSM_RESPLN_INDEX      2
#define cL2_GSM_RETRY_INDEX       3
#define cL2_GSM_TIMEOUT_INDEX     3

#define cL2_GSM_RESP_OK                "OK"
#define cL2_GSM_RESP_ERROR             "ERROR"
#define cL2_GSM_RESP_DUMMY             "DUMMY"
#define cL2_GSM_RESP_CONNECT           "CONNECT"
#define cL2_GSM_RESP_NO_CARRIER        "NO CARRIER"
#define cL2_GSM_RESP_SENDSMS           "SEND"
#define cL2_GSM_RESP_SMSNUM            "SMSNUM"
#define cL2_GSM_RESP_READSMS           "READSMS"


#define cL2_GSM_CUSTOM_CMD_SMS_NUM                    "*cSmsNum"
#define cL2_GSM_CUSTOM_CMD_HTTP_PIC                   "*cPicHttp"
#define cL2_GSM_CUSTOM_CMD_HTTP_CONTENT_LENGTH        "*cContentLen"

#define cL2_GSM_MAX_BUFFER_SMS_DATA   256
#define cL2_GSM_MAX_BUFFER_GPRS       512

#define cL2_GSM_SIZEOF_CUSTOM_CMD_LUT_ARRAY 3


/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

typedef u8 (*tfL2_GSM_RspFunc)( void );


typedef struct
{
    u8  psSendLnData[10][cL2_GSM_MAX_BUFFER_GPRS];
    u8  psWaitLnData[10][40];
    u8  psRespLnData[10][40];
    u16 wRetry;
    u16 wTimeout;

}tsL2_GSM_Process_ScriptData;

typedef struct
{
  u8 bNumOfSms;
  u8 bSmsDataBuffer[cL2_GSM_MAX_BUFFER_SMS_DATA];
  u8 bSmsDataFlag;
  u16 bSmsNumOfDebugMsgs;
}tsL2_GSM_Process_SmsData;


extern u8 bL2_GSM_UartGprsSearchForCharFlag;


/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */


/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */




/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */
u8 L2_GSM_ScriptEngine( const char bScriptData[] );

u8 L2_GSM_OkRsp( void );
u8 L2_GSM_ErrorRsp( void );
u8 L2_GSM_DummyRsp( void );
u8 L2_GSM_SendSmsRsp( void );
u8 L2_GSM_SmsNumRsp( void );
u8 L2_GSM_ReadSmsRsp( void );


u8 * L2_GSM_CustomCmd( u8 * pbOriginalSrc, u8 * pbCustomCmd );


u8 CheckExecuteSMS( void );



#endif // __L2_GSM_PROCESS_H__

