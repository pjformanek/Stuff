/*------------------------------------------------------------------------------
  	$File:		L2_GSM_Process.c
  	$Module:  	Scripting Engine
  	$Prefix:  	L2_GSM
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Juan Ramirez, 2009-March-19
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_L2_GSM_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "L2_GSM_Process.h"
#include "L2_Code.h"
#include "USART_Debug.h"
#include "TIMx_Config.h"
#include "DEBUG.h"
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
tsL2_GSM_Process_ScriptData tsScriptData;
tsL2_GSM_Process_SmsData tsSmsData;

u8 bL2_GSM_UartGprsSearchForCharFlag;





/* ---- F U N C T I O N  P O I N T E R S ----*/
tfL2_GSM_RspFunc tfRspFunc[] =
{
  &L2_GSM_OkRsp, &L2_GSM_ErrorRsp,
  &L2_GSM_DummyRsp, &L2_GSM_SendSmsRsp,
  &L2_GSM_SmsNumRsp, &L2_GSM_ReadSmsRsp
};

/*-------------------------------------------*/

/* ---- L O O K   U P  T A B L E S ---- */
sc8 * psL2_GSM_ScriptEngineRspLookUpTable[] =
{
    cL2_GSM_RESP_OK, cL2_GSM_RESP_ERROR,
    cL2_GSM_RESP_DUMMY, cL2_GSM_RESP_SENDSMS,
    cL2_GSM_RESP_SMSNUM, cL2_GSM_RESP_READSMS,
    cL2_GSM_RESP_CONNECT  //cL2_GSM_RESP_NO_CARRIER,

};


sc8 * psL2_GSM_ScriptEngineCmdLookUpTable[] =
{
    cL2_GSM_SENDLN, cL2_GSM_WAITLN,
    cL2_GSM_RESPLN, /*cL2_GSM_RETRY,*/ cL2_GSM_TIMEOUT, cL2_GSM_OPTION
};

sc8 * psL2_GSM_ScriptEngineCustomCmdLookUpTable[] =
{
  cL2_GSM_CUSTOM_CMD_SMS_NUM,
  cL2_GSM_CUSTOM_CMD_HTTP_PIC,
  cL2_GSM_CUSTOM_CMD_HTTP_CONTENT_LENGTH
};
/* -------------------------------------*/



u8 bErrorFlag = 0;

/*------------------------------------------------------------------------------
				----- G L O B A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */


/*------------------------------------------------------------------------------
				----- G L O B A L   F U N C T I O N S -----
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
u8 L2_GSM_ScriptEngine( const char bScriptData[] )
{
    u8 bState = 0, i = 0, j = 0 , k = 0, bTmpFlag = 0, bTimeOutFlag = 0, bFlag = 0;
    u16 wLookUptableIndex = 0, wTmpLookUptableIndex = 0, tmp = 0;
    u16 wCounter = 0, wRetryData = 1;
    u8 bRetryFlag = 0;
    char * pTemp;
    char pbTempData[cL2_GSM_MAX_BUFFER_GPRS];

    tsScriptData.wRetry = 1;




    DEBUG_Strtok(bScriptData, (char*)pbTempData, ' ');
    while( ( strcmp( (char const*)pbTempData, NULL ) != 0 ) )
    {
      //printf("\n{%s}\n",  pbTempData );
      switch( bState )
      {
      case 0:

        wLookUptableIndex = DEBUG_LookUpTableIndexFinder( (u8*)pbTempData, psL2_GSM_ScriptEngineCmdLookUpTable, ( sizeof psL2_GSM_ScriptEngineCmdLookUpTable / sizeof *psL2_GSM_ScriptEngineCmdLookUpTable ) );

        if( wLookUptableIndex == cERR_ERROR_CODE )
        {
          bTmpFlag = 1;
          wLookUptableIndex = wTmpLookUptableIndex;
        }
        else
        {
          bTmpFlag = 0;
          wTmpLookUptableIndex = wLookUptableIndex;
        }


        switch( wLookUptableIndex )
        {
        case cL2_GSM_SENDLN_INDEX:

          if( bTmpFlag == 0)
          {
            printf("temp!!!\n");
            DEBUG_Strtok(NULL, (char*)tsScriptData.psSendLnData[i], '^');
            strcpy( pbTempData, (const char*)tsScriptData.psSendLnData[i] );
          }

          printf("sending LN:  ");


          printf("%s\n", tsScriptData.psSendLnData[i] );

          i++;

          break;

        case cL2_GSM_WAITLN_INDEX:

          if( bTmpFlag == 0)
          {
            DEBUG_Strtok(NULL, (char*)tsScriptData.psWaitLnData[j], ' ');
            strcpy( pbTempData, (const char*)tsScriptData.psWaitLnData[j] );
          }
          else
          {
            strcpy( (char*)tsScriptData.psWaitLnData[j], pbTempData );
          }

          printf("wait lines:  ");


          printf("%s\n", tsScriptData.psWaitLnData[j] );
          j++;

          break;

        case cL2_GSM_RESPLN_INDEX:

          if( bTmpFlag == 0)
          {
            DEBUG_Strtok(NULL, (char*)tsScriptData.psRespLnData[k], ' ');
            strcpy( pbTempData, (char*)tsScriptData.psRespLnData[k] );
          }
          else
          {
            strcpy( (char*)tsScriptData.psRespLnData[k], pbTempData );
          }
          printf("Resp:  ");


          printf("%s\n", tsScriptData.psRespLnData[k] );
          k++;

          break;

          /*case cL2_GSM_RETRY_INDEX:

          printf("Retry  :");
          DEBUG_Strtok(NULL, (char*)pbTempData, ' ');
          tsScriptData.wRetry = atoi( pbTempData );
          if( bRetryFlag == 0 )
          {
          wRetryData = tsScriptData.wRetry+1;
        }
          printf("%d\n", tsScriptData.wRetry );

          break;*/

        case cL2_GSM_TIMEOUT_INDEX:

          printf("Timeout  :");
          DEBUG_Strtok(NULL, (char*)pbTempData, ' ');
          tsScriptData.wTimeout = atoi( pbTempData );
          printf("%d\n", tsScriptData.wTimeout );
          bState = 1;

          break;

        default:
          printf("Script cmd not found\n");
          break;
        }
        break;

      case 1:

        printf( "sending data:  %s\n", tsScriptData.psSendLnData[i-1] );

        pTemp = strstr((char*)tsScriptData.psSendLnData[i-1], "*" );
        //printf( "pTEMP =  %s\n ", pTemp  );
        //if( strstr((char*)tsScriptData.psSendLnData[i-1], "*" ) == NULL )
        if( !pTemp )
        {

          printf( "~>%s\n", tsScriptData.psSendLnData[i-1] );

          cL2_GSM_ENABLE_USARTx_PRINTF = 1;
          printf("%s\r", tsScriptData.psSendLnData[i-1]);
          cL2_GSM_ENABLE_USARTx_PRINTF = 0;
        }
        else
        {
          //printf("new cmd = %s\n", L2_GSM_CustomCmd( tsScriptData.psSendLnData[i-1], (u8*)pTemp ) );

          pTemp = L2_GSM_CustomCmd( tsScriptData.psSendLnData[i-1], (u8*)pTemp );

          printf( "~>%s\n", tsScriptData.psSendLnData[i-1] );

          cL2_GSM_ENABLE_USARTx_PRINTF = 1;
          printf( "%s\r", pTemp);
          cL2_GSM_ENABLE_USARTx_PRINTF = 0;
        }


        TIM1_Configuration( tsScriptData.wTimeout );
        TIM_Cmd(TIM1, ENABLE);


        while( cL2_USARTx_RX_INT_FLAG != 1 )
        {
          if( wCounter == 10 )
          {
            printf("<~");
          }
          wCounter++;
          if( TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET )
          {
            TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);

            bTimeOutFlag = 1;
            TIM_Cmd(TIM1, DISABLE);
            break;
          }
        }


        if( !bTimeOutFlag )
        {

          tmp = j;
          j = 0;
          while( j != tmp )
          {
            printf("(%s)\n", strstr((char*)cL2_USARTx_BUFFER, (char*)tsScriptData.psWaitLnData[j] ) );
            if( strstr((char*)cL2_USARTx_BUFFER, (char*)tsScriptData.psWaitLnData[j] ) == NULL )
            {
              j++;
            }
            else
            {
              printf( "\n>%s<\n J = %d\n", cL2_USARTx_BUFFER, j );
              cL2_USARTx_RX_INT_FLAG = 0;
              //memset(cL2_USARTx_BUFFER, 0, cUSART_MAX_BUFFER_LENGTH);
              bFlag = 1;
              break;
            }
          }

          if( bFlag )
          {

            bFlag = 0;
            tmp = DEBUG_LookUpTableIndexFinder( tsScriptData.psRespLnData[j], psL2_GSM_ScriptEngineRspLookUpTable, ( sizeof psL2_GSM_ScriptEngineRspLookUpTable / sizeof *psL2_GSM_ScriptEngineRspLookUpTable ) );
            printf(" TMP = %d\n rsp[j] = %s\n", tmp, tsScriptData.psRespLnData[j]);
            if( tmp != cERR_ERROR_CODE )
            {
              tfRspFunc[tmp]();
            }
            else
            {
              printf("Error LUT\n");
            }
            cL2_USARTx_RX_INT_FLAG = 0;
            memset(cL2_USARTx_BUFFER, 0, cUSART_MAX_BUFFER_LENGTH);
          }
          else
          {
            //printf("bFlag NOT set\n");
            printf( "\n>%s<\n J = %d\n", cL2_USARTx_BUFFER, j );
            //cL2_USARTx_RX_INT_FLAG = 0;
            memset(cL2_USARTx_BUFFER, 0, cUSART_MAX_BUFFER_LENGTH);
            tfRspFunc[2]();
          }

        }
        else
        {
          printf("Timeout occurred\n");
          tfRspFunc[2]();

        }
        bState = 0;

        //printf( "\n[%s]\n", cL2_USARTx_BUFFER );
        //cL2_USARTx_RX_INT_FLAG = 0;
        //memset(cL2_USARTx_BUFFER, 0, 50);

        //memset(cL2_USARTx_BUFFER, 0, cUSART_MAX_BUFFER_LENGTH);

        i = 0;
        j = 0;
        k = 0;
        memset(tsScriptData.psSendLnData, 0, 10);
        memset(tsScriptData.psWaitLnData, 0, 10);
        memset(tsScriptData.psRespLnData, 0, 10);
        printf("finnished!!\n");
        //bUSART_Usart2CountBufferFlag = 0;
        break;

      default:
        printf("Not a valid command\n");
        break;
      }







      if( bState == 0 )
      {
        DEBUG_Strtok(NULL, (char*)pbTempData, ' ');
      }
      if( bErrorFlag == 1)
      {
        bErrorFlag = 0;
        DEBUG_Strtok(bScriptData, (char*)pbTempData, ' ');
      }


    }

     return 1;
}










/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 L2_GSM_OkRsp( void )
{
    printf("\nyay\n");
    return 0;
}

/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 L2_GSM_ErrorRsp( void )
{
    //bErrorFlag = 1;
    printf("\nbooo\n");
    return 0;
}


u8 L2_GSM_DummyRsp( void )
{
  printf("\nDUMMY\n");
  return 0;
}

/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 L2_GSM_SendSmsRsp( void )
{
  char t = 0x1A;
  cL2_GSM_ENABLE_USARTx_PRINTF = 1;
  printf("%s", bL2_GSM_SmsInputString );
  printf("%c", t);
  cL2_GSM_ENABLE_USARTx_PRINTF = 0;

  memset( bL2_GSM_SmsInputString, 0, cL2_GSM_MAX_SMS_STRING );

  return 0;
}

/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 L2_GSM_SmsNumRsp( void )
{
  u8  pbTemp[50] = {0}, bTempPosition = 0;

  printf("Counting Number of SMS in Mem  %s\n\n", cL2_USARTx_BUFFER);
  bTempPosition = DEBUG_StripCmd( cL2_USARTx_BUFFER, pbTemp , 0x00,  cDEBUG_AT_COMMA );
  DEBUG_StripCmd( cL2_USARTx_BUFFER, pbTemp , bTempPosition,  cDEBUG_AT_COMMA );
  tsSmsData.bNumOfSms = atoi( (char const *)pbTemp );

  printf("SMS num = %d\n", tsSmsData.bNumOfSms );
  return 0;
}



/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 L2_GSM_ReadSmsRsp( void )
{
  u8 i = 0;
  tsSmsData.bSmsNumOfDebugMsgs = 0;
  char * pTmp = {0};


  memset( tsSmsData.bSmsDataBuffer, 0, cL2_GSM_MAX_BUFFER_SMS_DATA );



  if( strstr((char*)cL2_USARTx_BUFFER, (char*)psL2_CODE_ImportantLayer2Data[4] ) )
  {


    pTmp = strstr((char*)cL2_USARTx_BUFFER, cDEBUG_AT_START_STRING );
    strcat( (char*)tsSmsData.bSmsDataBuffer, pTmp );
    printf("\ncombined string = %s\n",  tsSmsData.bSmsDataBuffer );
  }
  else
  {
    printf("\nNot a valid Phone number\n");
  }


  if( tsSmsData.bNumOfSms > 1 )
  {
    while( !( strstr((char*)cL2_USARTx_BUFFER, "OK" ) ) )//|| cL2_USARTx_RX_INT_FLAG == 1 )
    {
      if( cL2_USARTx_RX_INT_FLAG == 1 )
      {
        cL2_USARTx_RX_INT_FLAG = 0;

        if( strstr((char*)cL2_USARTx_BUFFER, (char*)psL2_CODE_ImportantLayer2Data[4] ) )
        {


          pTmp = strstr((char*)cL2_USARTx_BUFFER, cDEBUG_AT_START_STRING );
          strcat( (char*)tsSmsData.bSmsDataBuffer, pTmp );
          printf("\ncombined string = %s\n",  tsSmsData.bSmsDataBuffer );
        }
        else
        {
          printf("\nNot a valid Phone number\n");
        }
      }
    }

    if( strstr((char*)cL2_USARTx_BUFFER, (char*)psL2_CODE_ImportantLayer2Data[4] ) )
    {


      pTmp = strstr((char*)cL2_USARTx_BUFFER, cDEBUG_AT_START_STRING );
      strcat( (char*)tsSmsData.bSmsDataBuffer, pTmp );
      printf("\ncombined string = %s\n",  tsSmsData.bSmsDataBuffer );
    }
    else
    {
      printf("\nNot a valid Phone number\n");
    }
  }

  tsSmsData.bSmsDataFlag = 1;

  while( i < tsSmsData.bNumOfSms )
  {
    i++;
  }

  return 0;
}





/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 * L2_GSM_CustomCmd( u8 * pbOriginalSrc, u8 * pbCustomCmd )
{
  //u16 wTmp = 0;

  //u8 bTmpBuffer[30] = {0};
  char * rep = 0;

  u16 wCount = 0;//cL2_GSM_SIZEOF_CUSTOM_CMD_LUT_ARRAY;
  u16 temp = 0;

  //printf("original str = (%s)\n cmd = | %s |\n", pbOriginalSrc, pbCustomCmd );

  temp = NumOfCmds( pbOriginalSrc, '*' );

  printf("temp = %d\n", temp);

  while( temp-- )
  {
    while( wCount < cL2_GSM_SIZEOF_CUSTOM_CMD_LUT_ARRAY )
    {
      if( ( strstr( (char*)pbOriginalSrc, (char const*)psL2_GSM_ScriptEngineCustomCmdLookUpTable[wCount] ) ) != NULL )
      {
        //printf(" >>>>%s<<<<\n", psL2_GSM_ScriptEngineCustomCmdLookUpTable[wCount] );
        rep = replace_str( (char*)psL2_GSM_ScriptEngineCustomCmdLookUpTable[wCount] , (char*)psL2_CODE_ImportantLayer2Data[wCount], (char*)pbOriginalSrc );
        //printf("rep ===== \n%s\n", rep);
        strcpy( (char*)pbOriginalSrc, rep );

        //printf("\n((((\n%s\n)))))\n", pbOriginalSrc);
        break;
      }
      else
      {
        printf("HOLY CRAP\n\n");
        wCount++;
      }
    }
    printf("TEST!!!!!!\n");
    wCount = 0;
  }





//  wTmp = DEBUG_LookUpTableIndexFinder( /*bTmpBuffer*/pbCustomCmd, psL2_GSM_ScriptEngineCustomCmdLookUpTable, ( sizeof(psL2_GSM_ScriptEngineCustomCmdLookUpTable)/sizeof(*psL2_GSM_ScriptEngineCustomCmdLookUpTable) ) );

//  if( wTmp != cERR_ERROR_CODE )
//  {
//    printf("wTmp = %d\n bTmpbuffer = %s\n dataL2 = %s\n ", wTmp, bTmpBuffer, psL2_CODE_ImportantLayer2Data[wTmp]);
//
//    rep = str_replace((char*)/*bTmpBuffer*/pbCustomCmd, (char const*)psL2_CODE_ImportantLayer2Data[wTmp], (char*)pbOriginalSrc);
//  }
//  else
//  {
//    DEBUG_StripCmd( pbCustomCmd, bTmpBuffer , 0x00, cDEBUG_AT_COMMA );
//  }
//
//  wTmp = DEBUG_LookUpTableIndexFinder( bTmpBuffer, psL2_GSM_ScriptEngineCustomCmdLookUpTable, ( sizeof(psL2_GSM_ScriptEngineCustomCmdLookUpTable)/sizeof(*psL2_GSM_ScriptEngineCustomCmdLookUpTable) ) );
//
//  if( wTmp != cERR_ERROR_CODE )
//  {
//    printf("wTmp = %d\n bTmpbuffer = %s\n dataL2 = %s\n ", wTmp, bTmpBuffer, psL2_CODE_ImportantLayer2Data[wTmp]);
//
//    rep = str_replace((char*)bTmpBuffer, (char const*)psL2_CODE_ImportantLayer2Data[wTmp], (char*)pbOriginalSrc);
//  }
//  else
//  {
//    return NULL;
//  }



  printf("\n>(%s)<\n", rep);




  return (u8*)rep;
}


















/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 CheckExecuteSMS( void )
{
  if( tsSmsData.bSmsDataFlag )
  {
    tsSmsData.bSmsDataFlag = 0;  // only do this after all messages have been executed ?? Maybe succesfully or not ??
    printf( "#%d SMS to be read/executed \n", tsSmsData.bNumOfSms );
    DEBUG_LiveDebugAppState( tsSmsData.bSmsDataBuffer );
  }
  return 1;

}



#undef cMEM_USERCLASS_ID_L2_GSM_c