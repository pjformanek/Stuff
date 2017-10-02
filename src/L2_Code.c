/*------------------------------------------------------------------------------
  	$File:		L2_Code.c
  	$Module:  	Diagnostic and Error Handling
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

#define cMEM_USERCLASS_ID_L2_CODE_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "L2_Code.h" 
#include "Utilities.h"

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N   P R O T O T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */


u8 bL2_GSM_SmsInputString[cL2_GSM_MAX_SMS_STRING] = { "123" };
u8 bL2_GSM_GprsInputString[cL2_GSM_MAX_GPRS_STRING] = {0};
u8 bL2_GSM_HttpContentLength[5] = { 0 };


/* ---- L A Y E R 2  S C R I P T ---*/

const char  psL2_CODE_InitScrt[] =
{
  "sendln AT^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 50 " 
  
  "sendln ATE0^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 100 "  
  
  "sendln AT^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 100 "   
    
  "sendln AT^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 150 " 
    
  "sendln AT+FLO=0^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 120 "  
};

const char psL2_CODE_SelInt[] =
{
  "sendln AT#SELINT=2^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 120 " 
};

const char psL2_CODE_SmsSetUp[] = 
{
  "sendln AT+CMGF=1^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 150 "  
    
  "sendln AT#E2SMSRI=100^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 150 "    
};

const char psL2_CODE_NetworkTest[] =
{
  "sendln AT+COPS?^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  //"retry 2 "  
  "timeout 150 "
    
  "sendln AT+CMGF=1^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  //"retry 1 "  
  "timeout 150 "    
};


const char psL2_CODE_HttpSession[] = 
{
  "sendln AT#USERID=EASY GPRS^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 150 " 
    
  "sendln AT#PASSW=EASY GPRS^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 150 " 
     
  "sendln AT+CGDCONT=1,IP,gprs02.motient.net,0.0.0.0,0,0^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 150 "    
     

  "sendln AT#SKTSET=0,80,www.jsfglobal.com^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 200 "   
};

const char psL2_CODE_TurnOnGprs[] =
{
  "sendln AT#GPRS=1^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 40000 "
};

const char psL2_CODE_TurnOffGprs[] =
{
  "sendln AT#GPRS=0^"   
  "waitln OK ERROR "          
  "respln OK DUMMY "
  "timeout 5000 "
};


const char psL2_CODE_HttpGet[] = 
{ 
  "sendln POST /services/capture.php HTTP/1.1\r\nHost: www.jsfglobal.com\r\nContent-Type:application/x-www-form-urlencoded\r\nContent-Length:*cContentLen\r\nConnection: Close\r\n\r\n*cPicHttp^"  
  "waitln + ^ ^^ "
  "respln OK DUMMY DUMMY "
  "timeout 40000 "            
};

const char psL2_CODE_CheckAllSms[] =
{
  "sendln AT+CMGL=ALL^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 40000 " 
};

const char psL2_CODE_DeleteAllSms[] =
{
  "sendln AT+CMGD=1,4^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 40000 " 
};

const char psL2_CODE_SendSms[] =
{
  "sendln AT+CMGS=*cSmsNum,145^"   
  "waitln > ERROR "
  "respln SEND DUMMY "
  "timeout 10000 " 
};  

const char psL2_CODE_ReadSms[] =
{    
  "sendln AT+CPMS?^"   
  "waitln CPMS ERROR "
  "respln SMSNUM DUMMY "
  "timeout 10000 " 
  
  "sendln AT+CMGL=ALL^"   
  "waitln CMGL ERROR "
  "respln READSMS DUMMY "
  "timeout 40000 "  
}; 

const char psL2_CODE_SendPic[] =
{
  "sendln *cPicHttp^"   
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 25000 " 
};

const char psL2_CODE_SktOpen[] =
{
  "sendln AT#SKTOP^"   
  "waitln CONNECT ERROR "
  "respln OK DUMMY "
  "timeout 40000 "         
};

const char psL2_CODE_HttpChatPost[] =
{   
  //"sendln [GET /management/relay_post.php?command=[AT=OK] HTTP/1.1\nHost: www.jsfglobal.com\n\n\r^"  
  //"sendln POST /services/capture.php HTTP/1.1\r\nHost: www.jsfglobal.com\r\nContent-Type:application/x-www-form-urlencoded\r\nContent-Length:18\r\nConnection: Close\r\n\r\nd=215&n=1&i=1&p=[[^"  
  "sendln POST /services/echo.php HTTP/1.1\r\nHost: www.jsfglobal.com\r\nContent-Type:application/x-www-form-urlencoded\r\nContent-Length:37\r\nKeep-Alive: 300\r\nConnection: keep-alive\r\n\r\nd=215&n=1&i=1&p=[[^"  
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 2500 "      
};

const char psL2_CODE_Twitter[] =
{
    
  "sendln POST /statuses/update.xml HTTP/1.1\r\nHost: www.twitter.com\r\nAuthorization: Basic cmFwc29kaWE0OToxOTIyNDc0Mw==\r\nContent-Type:application/x-www-form-urlencoded\r\nContent-Length:13\r\nConnection: Close\r\n\r\nstatus=\"test\"^"  
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 2500 "  
};


const char psL2_CODE_HttpChatGet[] =
{
  "sendln [GET /management/relay_post.php?check=true HTTP/1.1 \n Host: www.jsfglobal.com\n\n\r^"  
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 2500 "   
  
};

const char psL2_CODE_Skt_Timeout[] =
{
  "sendln AT#SKTTO=0^"
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 2500 " 
};

const char test[] =
{
  "sendln d=215&n=1&i=2&p=[[^"
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 2500 "  
};
const char psL2_CODE_HttpClearPicBuffer[] = 
{
  "sendln [GET /services/echo.php?cmd=clear_buffer HTTP/1.1\nHost: www.jsfglobal.com\n\n\r^"  
  "waitln OK ERROR "
  "respln OK DUMMY "
  "timeout 2500 "    
};




/* --- I M P O R T A N T  L A Y E R 2  D A T A ---*/

u8  psL2_CODE_SmsPhoneNum[] = { "+12012380826" };//{ "+12505891019" };
u8  psL2_CODE_HttpRead[] = { "[GET /management/relay_post.php?check=true HTTP/1.1 \n Host: www.jsfglobal.com\n\n\r" };
u8  psL2_CODE_HttpWrite[] = { "[GET /management/relay_post.php?command=HereIsjOE HTTP/1.1'\n'Host: www.jsfglobal.com\n\n\r" };
//u8  psL2_CODE_SendPicHttp[] = { "[POST /services/capture.php HTTP/1.1 \n Host: www.jsfglobal.com\n\n\r" };
u8  psL2_CODE_SendPicHttp[] = { "[POST /services/capture.php HTTP/1.1 \n Host: www.jsfglobal.com \n\n\rContent-Type:application/x-www-form-urlencoded\r\nContent-Length:21\r\nConnection:Close\r\n\r\n" };
u8  psL2_CODE_SendPicData[] = { "d=215&n=1&i=1&p=1234A" };
u8  psL2_CODE_SmsReceiverNum[] = { "12012380826" };
u8  psL2_CODE_HttpHost[] = { "www.jsfglobal.com" }; 

u8 psL2_CODE_PayLoadHttp[] = { "d=215&n=%n&i=%i&p=" };

/*------------------------------------------------------------------------------
				----- G L O B A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

const char * psL2_CODE_ScrtData[] = 
{ 
  psL2_CODE_InitScrt,    // 0
  psL2_CODE_SelInt,      // 1
  psL2_CODE_SmsSetUp,    // 2
  psL2_CODE_NetworkTest, // 3
  psL2_CODE_HttpSession, // 4
  psL2_CODE_TurnOnGprs,  // 5
  psL2_CODE_TurnOffGprs, // 6
  psL2_CODE_SktOpen,     // 7
  psL2_CODE_CheckAllSms, // 8
  psL2_CODE_DeleteAllSms,// 9
  psL2_CODE_SendSms,     // 10
  psL2_CODE_ReadSms,     // 11
  psL2_CODE_SendPic,     // 12
  psL2_CODE_HttpChatGet, // 13
  psL2_CODE_HttpChatPost, // 14 
  psL2_CODE_Twitter,      // 15
  psL2_CODE_HttpChatGet,  // 16
  psL2_CODE_Skt_Timeout,   // 17
    test, // 18  
  psL2_CODE_HttpClearPicBuffer // 19  
};


u8 * psL2_CODE_ImportantLayer2Data[] =
{
  psL2_CODE_SmsPhoneNum,
  bL2_GSM_GprsInputString,//psL2_CODE_SendPicHttp,
  bL2_GSM_HttpContentLength,
  psL2_CODE_HttpRead,
  psL2_CODE_HttpWrite,
  psL2_CODE_SmsReceiverNum,  
  psL2_CODE_PayLoadHttp  
};


/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
	$Function: 
	$Description: 

	$Inputs: none
	$Outputs: none
	$Assumptions: 
	$WARNINGS:
	$End
*/


/*------------------------------------------------------------------------------
				----- G L O B A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

#undef cMEM_USERCLASS_ID_L2_CODE_c
