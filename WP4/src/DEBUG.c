/*------------------------------------------------------------------------------
  	$File:		DEBUG.c
  	$Module:  	Debugging engine
  	$Prefix:  	DEBUG
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Dec 12, 2009
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_DEBUG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "stm32f10x_lib.h"
#include "GLB.h"
#include "Includes.h"
#include "DEBUG.h"
#include "Utilities.h"
#include "MEM.h"

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
tfDEBUG_CC1101Func  tfCcFunc[] = { &DEBUG_CcFreqCmd, &DEBUG_CcPaCmd, &DEBUG_CcHfreqCmd
                                 };

tfDEBUG_GsmFunc     tfGsmFunc[] = { &DEBUG_GsmDummy1, &DEBUG_GsmScript, &DEBUG_GsmL2Data
                                  };

tfDEBUG_RomFunc     tfRomFunc[] = {0};

tfDEBUG_RamFunc     tfRamFunc[] = {0};

tfDEBUG_AppFunc     tfAppFunc[] = { &DEBUG_AppDebug, &DEBUG_AppCam
                                  };

tfDEBUG_EeFunc      tfEeFunc[] = {0};

tfDEBUG_DosFunc      tfDosFunc[] = { &DEBUG_DosDebug };

tfDEBUG_RtcFunc      tfRtcFunc[] = { &DEBUG_RtcDebug };

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N   P R O T O T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

static u8 bDebugInitDoneFlag = 0;

u8 bDEBUG_TempMemSpace[cDEBUG_MAX_MEM_LENGTH] = {0};
u8 bDEBUG_TempCmdSpace[cDEBUG_MAX_MEM_LENGTH] = {0};
u8 bDEBUG_AtFlag = 0x00;

u8 bDEBUG_DebugOnOffFlag = 0;

tsDEBUG_CC1101CmdEntryTable tsCC1101CmdEntryTable;
tsDEBUG_GsmCmdEntryTable    tsGsmCmdEntryTable;
tsDEBUG_RamCmdEntryTable    tsRamCmdEntryTable;
tsDEBUG_RomCmdEntryTable    tsRomCmdEntryTable;
tsDEBUG_AppCmdEntryTable    tsAppCmdEntryTable;
tsDEBUG_EeCmdEntryTable     tsEeCmdEntryTable;
tsDEBUG_DosCmdEntryTable    tsDosCmdEntryTable;
tsDEBUG_RtcCmdEntryTable    tsRtcCmdEntryTable;

tsDEBUG_ReturnVariables     tsReturnVariables;


sc8 * pbDeviceMemSpaceLookUpTable[] = { cDEBUG_AT_CC1101_MEM , cDEBUG_AT_GSM_MEM,
                                        cDEBUG_AT_RAM_MEM, cDEBUG_AT_ROM_MEM,
                                        cDEBUG_AT_APP_MEM, cDEBUG_AT_EE_MEM,
                                        cDEBUG_AT_DOS_MEM, cDEBUG_AT_RTC_MEM
                                      };

sc8 * pbCC1101RegisterLookUpTable[] = { cDEBUG_CC_FREQ, cDEBUG_CC_PA, cDEBUG_CC_HFREQ
                                      };

sc8 * pbGsmRegisterLookUpTable[] = { cDEBUG_GSM_DUMMY, cDEBUG_GSM_SCRIPT, cDEBUG_GSM_L2DATA
                                   };

sc8 * pbRamRegisterLookUpTable[] = { 0
                                   };

sc8 * pbRomRegisterLookUpTable[] = { 0
                                   };

sc8 * pbAppRegisterLookUpTable[] = { cDEBUG_APP_DEBUG, cDEBUG_APP_CAM
                                   };

sc8 * pbEeRegisterLookUpTable[] = { 0
                                  };


sc8 * pbDosRegisterLookUpTable[] = { cDEBUG_DOS_DEBUG
                                  };

sc8 * pbRtcRegisterLookUpTable[] = { cDEBUG_RTC_TIM
                                  };

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
	$Function: DEBUG_LiveDebugAppState
	$Description: Main State machine for debugging engine. It checks out the
                      semantics of the debug message and directs the commands to the
                      proper function.

	$Inputs: u8 * pbUSART_RX_Buffer - Contains a string with the debug message
	$Outputs: TBD , returns 0 if not sucessfull
	$Assumptions:
	$WARNINGS:
	$End
*/
void DEBUG_Init( void )
{
  mDEBUG_USARTx_GPIO_Configuration();
  mDEBUG_USARTxConfiguration();

  bDebugInitDoneFlag = 1;
}



/*------------------------------------------------------------------------------
	$Function: DEBUG_LiveDebugAppState
	$Description: Main State machine for debugging engine. It checks out the
                      semantics of the debug message and directs the commands to the
                      proper function.

	$Inputs: u8 * pbUSART_RX_Buffer - Contains a string with the debug message
	$Outputs: TBD , returns 0 if not sucessfull
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_LiveDebugAppState( u8 * pbUSART_RX_Buffer )
{
    u8 bTmpCmdIndex = 0x00, bTmpDataIndex = 0x00;
    u16 bTmpCmdLookUpTableIndex = 0x00;

    u8 bCurrentAtCmd[50] = { 0 }, bCurrentCmdDataIndex = 0x01;
    u16 wMsgCounter = 0, i = 0;

    /*tsReturnVariables.bByteVar = 0;
    memset( tsReturnVariables.bByteArrayVar, 0, cDEBUG_MAX_RETURN_LENGTH );
    tsReturnVariables.wWordVar = 0;
    tsReturnVariables.lwLongWordVar = 0;*/



    //bCurrentCmdDataIndex = DEBUG_StripCmd( pbUSART_RX_Buffer, bCurrentAtCmd, 0x01, cDEBUG_AT_PERIOD );
    wMsgCounter = NumOfCmds( pbUSART_RX_Buffer, cDEBUG_AT_END_CMD );
    printf( "NUm of cmd = %d\n", wMsgCounter );
    //wMsgCounter = atoi( (char*)bCurrentAtCmd );

    while( i++ != wMsgCounter )
    {

      bCurrentCmdDataIndex = DEBUG_StripCmd( pbUSART_RX_Buffer, bCurrentAtCmd, bCurrentCmdDataIndex, cDEBUG_AT_END_CMD );

      printf("\n\nCurrent cmd = %s \n\n", bCurrentAtCmd );
      if( bCurrentAtCmd == cDEBUG_AT_END_STRING)
      {
        return 0;
      }

      if( ( strstr( (char*)bCurrentAtCmd, "AT" ) ) )
      {
        memset( bDEBUG_TempCmdSpace, 0 , cDEBUG_MAX_MEM_LENGTH );
        memset( bDEBUG_TempMemSpace, 0 , cDEBUG_MAX_MEM_LENGTH );

        if( ( strstr((char*)bCurrentAtCmd, "=" ) ) )
        {
          bDEBUG_AtFlag = cDEBUG_AT_ASSIGN_FLAG;
        }
        if( ( strstr((char*)bCurrentAtCmd, "+" ) ) )
        {
          bDEBUG_AtFlag = cDEBUG_AT_WRITE_FLAG;
        }
        if( ( strstr((char*)bCurrentAtCmd, "#" ) ) )
        {
          bDEBUG_AtFlag = cDEBUG_AT_READ_FLAG;
        }



        if( bDEBUG_AtFlag != cDEBUG_AT_ASSIGN_FLAG )
        {
          bTmpCmdIndex = DEBUG_StripCmd( bCurrentAtCmd, bDEBUG_TempMemSpace, 0x03, cDEBUG_AT_COMMA );

          bTmpDataIndex = DEBUG_StripCmd( bCurrentAtCmd, bDEBUG_TempCmdSpace, bTmpCmdIndex, cDEBUG_AT_COMMA );
          printf( "memspace = %s\n",bDEBUG_TempMemSpace );

          switch( DEBUG_LookUpTableIndexFinder( bDEBUG_TempMemSpace, pbDeviceMemSpaceLookUpTable, ( sizeof(pbDeviceMemSpaceLookUpTable)/sizeof(*pbDeviceMemSpaceLookUpTable) ) ) )
          {
          case cDEBUG_CC_INDEX:

            bTmpCmdLookUpTableIndex = DEBUG_LookUpTableIndexFinder( bDEBUG_TempCmdSpace, pbCC1101RegisterLookUpTable, ( sizeof(pbCC1101RegisterLookUpTable)/sizeof(*pbCC1101RegisterLookUpTable) ) );

            if( bTmpCmdLookUpTableIndex != cERR_ERROR_CODE )
            {
              tsCC1101CmdEntryTable.bCommand = bDEBUG_TempCmdSpace;
              tsCC1101CmdEntryTable.bDebugBuffer = bCurrentAtCmd;
              tsCC1101CmdEntryTable.bTmpDataIndex = bTmpDataIndex;
              tsCC1101CmdEntryTable.bAtFlag = bDEBUG_AtFlag;
              tfCcFunc[bTmpCmdLookUpTableIndex]( &tsCC1101CmdEntryTable );

            }
            else
              printf("No Valid Index found CC LUT\n");

            break;

          case cDEBUG_GSM_INDEX:

            bTmpCmdLookUpTableIndex = DEBUG_LookUpTableIndexFinder( bDEBUG_TempCmdSpace, pbGsmRegisterLookUpTable, ( sizeof(pbGsmRegisterLookUpTable)/sizeof(*pbGsmRegisterLookUpTable) ) );

            if( bTmpCmdLookUpTableIndex != cERR_ERROR_CODE )
            {
              tsGsmCmdEntryTable.bCommand = bDEBUG_TempCmdSpace;
              tsGsmCmdEntryTable.bDebugBuffer = bCurrentAtCmd;
              tsGsmCmdEntryTable.bTmpDataIndex = bTmpDataIndex;
              tsGsmCmdEntryTable.bAtFlag = bDEBUG_AtFlag;

              tfGsmFunc[bTmpCmdLookUpTableIndex]( &tsGsmCmdEntryTable );
            }
            else
              printf("No Valid Index found GSM LUT\n");

            break;

          case cDEBUG_RAM_INDEX:

            bTmpCmdLookUpTableIndex = DEBUG_LookUpTableIndexFinder( bDEBUG_TempCmdSpace, pbRamRegisterLookUpTable, ( sizeof(pbRamRegisterLookUpTable)/sizeof(*pbRamRegisterLookUpTable) ) );
            if( bTmpCmdLookUpTableIndex != cERR_ERROR_CODE )
            {
              tsRamCmdEntryTable.bCommand = bDEBUG_TempCmdSpace;
              tsRamCmdEntryTable.bDebugBuffer = bCurrentAtCmd;
              tsRamCmdEntryTable.bTmpDataIndex = bTmpDataIndex;
              tsRamCmdEntryTable.bAtFlag = bDEBUG_AtFlag;

              tfRamFunc[bTmpCmdLookUpTableIndex]( &tsRamCmdEntryTable );
            }
            else
              printf("No Valid Index found Ram LUT\n");
            break;

          case cDEBUG_ROM_INDEX:

            bTmpCmdLookUpTableIndex = DEBUG_LookUpTableIndexFinder( bDEBUG_TempCmdSpace, pbRomRegisterLookUpTable, ( sizeof(pbRomRegisterLookUpTable)/sizeof(*pbRomRegisterLookUpTable) ) );
            if( bTmpCmdLookUpTableIndex != cERR_ERROR_CODE )
            {
              tsRomCmdEntryTable.bCommand = bDEBUG_TempCmdSpace;
              tsRomCmdEntryTable.bDebugBuffer = bCurrentAtCmd;
              tsRomCmdEntryTable.bTmpDataIndex = bTmpDataIndex;
              tsRomCmdEntryTable.bAtFlag = bDEBUG_AtFlag;
              tfRomFunc[bTmpCmdLookUpTableIndex]( &tsRomCmdEntryTable );
            }

            else
              printf("No Valid Index found Rom LUT\n");
            break;

          case cDEBUG_APP_INDEX:

            bTmpCmdLookUpTableIndex = DEBUG_LookUpTableIndexFinder( bDEBUG_TempCmdSpace, pbAppRegisterLookUpTable, ( sizeof(pbAppRegisterLookUpTable)/sizeof(*pbAppRegisterLookUpTable) ) );

            if( bTmpCmdLookUpTableIndex != cERR_ERROR_CODE )
            {
              tsAppCmdEntryTable.bCommand = bDEBUG_TempCmdSpace;
              tsAppCmdEntryTable.bDebugBuffer = bCurrentAtCmd;
              tsAppCmdEntryTable.bTmpDataIndex = bTmpDataIndex;
              tsAppCmdEntryTable.bAtFlag = bDEBUG_AtFlag;
              tfAppFunc[bTmpCmdLookUpTableIndex]( &tsAppCmdEntryTable );
            }
            else
              printf("No Valid Index found App LUT\n");
            break;

          case cDEBUG_EE_INDEX:

            bTmpCmdLookUpTableIndex = DEBUG_LookUpTableIndexFinder( bDEBUG_TempCmdSpace, pbEeRegisterLookUpTable, ( sizeof(pbEeRegisterLookUpTable)/sizeof(*pbEeRegisterLookUpTable) ) );
            if( bTmpCmdLookUpTableIndex != cERR_ERROR_CODE )
            {
              tsEeCmdEntryTable.bCommand = bDEBUG_TempCmdSpace;
              tsEeCmdEntryTable.bDebugBuffer = bCurrentAtCmd;
              tsEeCmdEntryTable.bTmpDataIndex = bTmpDataIndex;
              tsEeCmdEntryTable.bAtFlag = bDEBUG_AtFlag;
              tfEeFunc[bTmpCmdLookUpTableIndex]( &tsEeCmdEntryTable );
            }

            else
              printf("No Valid Index found EE LUT\n");
            break;

          case cDEBUG_DOS_INDEX:

            bTmpCmdLookUpTableIndex = DEBUG_LookUpTableIndexFinder( bDEBUG_TempCmdSpace, pbDosRegisterLookUpTable, ( sizeof(pbDosRegisterLookUpTable)/sizeof(*pbDosRegisterLookUpTable) ) );

            if( bTmpCmdLookUpTableIndex != cERR_ERROR_CODE )
            {
              tsDosCmdEntryTable.bCommand = bDEBUG_TempCmdSpace;
              tsDosCmdEntryTable.bDebugBuffer = bCurrentAtCmd;
              tsDosCmdEntryTable.bTmpDataIndex = bTmpDataIndex;
              tsDosCmdEntryTable.bAtFlag = bDEBUG_AtFlag;
              tfDosFunc[bTmpCmdLookUpTableIndex]( &tsDosCmdEntryTable );
            }
            else
              printf("No Valid Index found Dos LUT\n");
            break;

          case cDEBUG_RTC_INDEX:

            bTmpCmdLookUpTableIndex = DEBUG_LookUpTableIndexFinder( bDEBUG_TempCmdSpace, pbRtcRegisterLookUpTable, ( sizeof(pbDosRegisterLookUpTable)/sizeof(*pbRtcRegisterLookUpTable) ) );

            if( bTmpCmdLookUpTableIndex != cERR_ERROR_CODE )
            {
              tsRtcCmdEntryTable.bCommand = bDEBUG_TempCmdSpace;
              tsRtcCmdEntryTable.bDebugBuffer = bCurrentAtCmd;
              tsRtcCmdEntryTable.bTmpDataIndex = bTmpDataIndex;
              tsRtcCmdEntryTable.bAtFlag = bDEBUG_AtFlag;
              tfRtcFunc[bTmpCmdLookUpTableIndex]( &tsRtcCmdEntryTable );
            }
            else
              printf("No Valid Index found Dos LUT\n");
            break;


          default:
            printf("Not a valid memory space\n");
            return cERR_ERROR_CODE;

          }
        }
        else
        {
        }


      }
      else
      {
        printf("ERROR\n");
        return cERR_ERROR_CODE;
      }

    }
    return 1;
}




/*------------------------------------------------------------------------------
	$Function: DEBUG_StripCmd
	$Description: Strips partial string from the main message

	$Inputs: u8 * pbBuffer - Contains the full message
                 u8 * pbTempBuffer - Variable where the stripped string will be stored
                 u8 bStartByte - Place where to begin parsing
                 u8 bEndCharacter - where to stop parsing
	$Outputs: Next position on array
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_StripCmd( u8 * pbBuffer, u8 * pbTempBuffer , u8 bStartByte, u8 bEndCharacter )
{
     u8 i = bStartByte, j = 0;

     if( bEndCharacter == cDEBUG_AT_COMMA )
     {
        while( pbBuffer[i] != bEndCharacter && pbBuffer[i] != cDEBUG_AT_END_CMD )
        {

           pbTempBuffer[j] = pbBuffer[i];
           i++;
           j++;
        }
     }
     else
     {
        while( pbBuffer[i] != bEndCharacter )
        {
            pbTempBuffer[j] = pbBuffer[i];
            i++;
            j++;
        }
        if( pbBuffer[i] == cDEBUG_AT_END_CMD )
        {
          pbTempBuffer[j] = pbBuffer[i];
        }

     }


     return i+1;
}





/*------------------------------------------------------------------------------
	$Function: DEBUG_LookUpTableIndexFinder
	$Description: Function to find the index of certain value in a look up table

	$Inputs: u8 * pbBuffer - buffer where value is stored
                 sc8 * pbLookUpTable[] - pointer to the LUT to be searched
                 sc16 wAvailableCommands - variable that determines the number of
                                           values in the table
	$Outputs: u16 i - index of the value
	$Assumptions:
	$WARNINGS:
	$End
*/
u16 DEBUG_LookUpTableIndexFinder( u8 * pbBuffer, sc8 * pbLookUpTable[], sc16 wAvailableCommands )
{
  //sc16 wAvailableCommands = sizeof( ( sc8 * )pbLookUpTable );//( sizeof( **pbLookUpTable )/sizeof( *pbLookUpTable ) );/// sizeof pbLookUpTable;

  //printf("Avaliavle Cmd's: %d\n", wAvailableCommands );
  u16 i = 0;

  //printf(" command: %s\n", pbBuffer );
  for( i=0; i< wAvailableCommands; i++)
  {
    //printf(" List Cmd's %s\n", pbLookUpTable[i] );
    if( ( strcmp( (char*)pbBuffer, (char*)pbLookUpTable[i] ) ) == 0 )
    {
      return i;
    }
  }

  return cERR_ERROR_CODE;
}


/*------------------------------------------------------------------------------
	$Function: DEBUG_CcFreqCmd
	$Description: Function to deal with the CC,FREQ debug command

	$Inputs: tsDEBUG_CC1101CmdEntryTable * ptsCC1101CmdEntryTable - Struct for the
                                                                        CC memory space
	$Outputs: TBD
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_CcFreqCmd( tsDEBUG_CC1101CmdEntryTable * ptsCC1101CmdEntryTable )
{
    u8   bTmpDataBuffer[32] = {0} ;

    //printf("%s\n", ptsCC1101CmdEntryTable->bCommand );

    DEBUG_StripCmd( ptsCC1101CmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsCC1101CmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );

    printf("Setting up new frequency at %sMHz\n",bTmpDataBuffer );
    printf("DONE\n");
    return 0;
}




/*------------------------------------------------------------------------------
	$Function: DEBUG_CcPaCmd
	$Description: Function to deal with the CC,PA debug command

	$Inputs: tsDEBUG_CC1101CmdEntryTable * ptsCC1101CmdEntryTable - Struct for the
                                                                        CC memory space
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_CcPaCmd( tsDEBUG_CC1101CmdEntryTable * ptsCC1101CmdEntryTable )
{
    u8   bTmpDataBuffer[32] = {0} ;


    //printf("%s\n", ptsCC1101CmdEntryTable->bCommand );
    //DEBUG_StripCmd( u8 * pbBuffer, u8 * pbTempBuffer , u8 bStartByte, u8 bEndCharacter );
    DEBUG_StripCmd( ptsCC1101CmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsCC1101CmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );

    printf("Setting up new PA at %sdBm\n",bTmpDataBuffer );
    printf("DONE\n");
    return 0;
}


/*------------------------------------------------------------------------------
	$Function: DEBUG_CcHfreqCmd
	$Description: Function to deal with the CC,HFREQ debug command

	$Inputs: sDEBUG_CC1101CmdEntryTable * ptsCC1101CmdEntryTable - Struct for the
                                                                       CC memory space
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_CcHfreqCmd( tsDEBUG_CC1101CmdEntryTable * ptsCC1101CmdEntryTable )
{
  u8 bTmpNumFreq[10] = {0};
  u8   bTmpDataBuffer[32] = {0} ;
  u8 * bTmpFreq[] = { 0 };
  u16 wTmpNumFreq = 0, i = 0;


  ptsCC1101CmdEntryTable->bTmpDataIndex = DEBUG_StripCmd( ptsCC1101CmdEntryTable->bDebugBuffer, bTmpNumFreq , ptsCC1101CmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );

  wTmpNumFreq = atoi( (char*)bTmpNumFreq );

  printf("Setting %s hopping frequencies at ", bTmpNumFreq );

  for( i=0;i<wTmpNumFreq;i++ )
  {
    //printf("Data Index %d\n", ptsCC1101CmdEntryTable->bTmpDataIndex );
    ptsCC1101CmdEntryTable->bTmpDataIndex = DEBUG_StripCmd( ptsCC1101CmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsCC1101CmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );

    bTmpFreq[i] = bTmpDataBuffer;

    printf("%s  ", bTmpFreq[i]);
    memset( bTmpDataBuffer, 0 , 32 );

  }
  printf("\n");
  printf("DONE\n");

  return 0;
}


/*------------------------------------------------------------------------------
	$Function: Dummy Function for the GSM memory space (AT+GSM,DUMMY,0;)
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_GsmDummy1( tsDEBUG_GsmCmdEntryTable * ptsDEBUG_GsmCmdEntryTable )
{
    u8   bTmpDataBuffer[32] = {0} ;

    //printf("%s\n", ptsDEBUG_GsmCmdEntryTable->bCommand );

    //DEBUG_StripCmd( u8 * pbBuffer, u8 * pbTempBuffer , u8 bStartByte, u8 bEndCharacter );
    DEBUG_StripCmd( ptsDEBUG_GsmCmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsDEBUG_GsmCmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );


    printf("Setting up Dummy = %s\n",bTmpDataBuffer );

    printf("DONE\n");

    return 0;
}


/*------------------------------------------------------------------------------
	$Function: DEBUG_GsmScript
	$Description: Function to run Telit Scripts or specific commands  //AT+GSM,SCRIPT,0.   or   AT+GSM,SCRIPT,AT~20.

	$Inputs: tsDEBUG_GsmCmdEntryTable * ptsDEBUG_GsmCmdEntryTable - pointer to the main GSM structure

	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_GsmScript( tsDEBUG_GsmCmdEntryTable * ptsDEBUG_GsmCmdEntryTable )
{
  u8   bTmpDataBuffer[32] = {0}, bTmpCustomData[32] = {0};
  u8   bTmpTimeout[10] = {0}, temp = 0;
  u16  wTmpScriptIndex = 0;


  temp = DEBUG_StripCmd( ptsDEBUG_GsmCmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsDEBUG_GsmCmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );

  printf("\nCmd = %s\n", bTmpDataBuffer);

  if( strstr((char*)bTmpDataBuffer, "AT" ) == NULL )
  {
    wTmpScriptIndex = atoi( (char*)bTmpDataBuffer );
    printf("Running script at index = %d\n\n",wTmpScriptIndex );

    if( strstr((char*)ptsDEBUG_GsmCmdEntryTable->bDebugBuffer, ",AT" ) != NULL )
    {
      DEBUG_StripCmd( ptsDEBUG_GsmCmdEntryTable->bDebugBuffer, bTmpCustomData , temp, cDEBUG_AT_COMMA  );
      printf("%s\n", bTmpCustomData );
    }

    L2_GSM_ScriptEngine(  psL2_CODE_ScrtData[wTmpScriptIndex] );
  }
  else
  {
    memset(bTmpDataBuffer, 0, 32);
    temp = DEBUG_StripCmd( ptsDEBUG_GsmCmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsDEBUG_GsmCmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );

    DEBUG_StripCmd( ptsDEBUG_GsmCmdEntryTable->bDebugBuffer, bTmpTimeout , temp,  cDEBUG_AT_COMMA );

    printf("timeout = %s\n DATA = %s\n", bTmpTimeout, bTmpDataBuffer);

    USART_EnableUsartX_Printf = cUSART_USART_GSM_ENABLE;
    printf( "%s\r", bTmpDataBuffer );
    USART_EnableUsartX_Printf = cUSART_USART_DEBUG_ENABLE;


    TIM1_Configuration( atoi( (char*)bTmpTimeout ) );
    TIM_Cmd(TIM1, ENABLE);


    while( bUSART2_RX_IntFlag != 1 )
    {
      if( TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET )
      {
        TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);

        printf("TIMEOUT!!\n\n");
        TIM_Cmd(TIM1, DISABLE);
        break;
      }
    }
    //bUSART2_RX_IntFlag = 0;
    //printf( "\n>%s<\n", bUSART2_RX_Buffer );
    //memset(bUSART2_RX_Buffer, 0, 50);
  }
  printf("DONE\n");
  return 0;
}


/*------------------------------------------------------------------------------
	$Function: DEBUG_GsmL2Data
	$Description:

	$Inputs:  tsDEBUG_GsmCmdEntryTable * ptsDEBUG_GsmCmdEntryTable - pointer to the main GSM structure

	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_GsmL2Data( tsDEBUG_GsmCmdEntryTable * ptsDEBUG_GsmCmdEntryTable )
{

  u8  bTmpDataBuffer[32] = {0}, temp = 0;

  temp = DEBUG_StripCmd( ptsDEBUG_GsmCmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsDEBUG_GsmCmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );

  printf("\nCmd = %s!!\n", bTmpDataBuffer);

  if( strstr((char*)bTmpDataBuffer, "SMS" ) != NULL )
  {
    memset( bL2_GSM_SmsInputString, 0, cL2_GSM_MAX_SMS_STRING );
    printf("SMS buffer  &d=0&i=2\n");
    DEBUG_StripCmd( ptsDEBUG_GsmCmdEntryTable->bDebugBuffer, bL2_GSM_SmsInputString , temp, cDEBUG_AT_COMMA  );
  }
  else if( strstr((char*)bTmpDataBuffer, "GPRS" ) != NULL )
  {
  }
  else
  {
    printf("ERROR\n");
    return cERR_ERROR_CODE;
  }

  printf("OK\n");
  return 1;
}






/*------------------------------------------------------------------------------
	$Function: DEBUG_AppDebug
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_AppDebug( tsDEBUG_AppCmdEntryTable * ptsDEBUG_AppCmdEntryTable )
{
  u8   bTmpDataBuffer[32] = {0} ;

  DEBUG_StripCmd( ptsDEBUG_AppCmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsDEBUG_AppCmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );


  if( ( strcmp( (char const*)bTmpDataBuffer, "ON" ) ) == 0 )
  {
     printf("DEBUGGING ON\n");
     bDEBUG_DebugOnOffFlag = 1;
  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "OFF" ) ) == 0 )
  {
    printf("DEBUGGING OFF\n");
    bDEBUG_DebugOnOffFlag = 0;
  }
  else
  {
    printf( "ERROR\n" );

  }

  printf("OK\n");

  return 0;
}


/*------------------------------------------------------------------------------
	$Function: DEBUG_AppCam
	$Description: Function that deals with the Commands for the C328R Camera
                      module

	$Inputs: tsDEBUG_AppCmdEntryTable * ptsDEBUG_AppCmdEntryTable - pointer to the main app structure

	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_AppCam( tsDEBUG_AppCmdEntryTable * ptsDEBUG_AppCmdEntryTable )
{
  u8   bTmpDataBuffer[32] = {0} , bTmpPosition = 0, bTmpLengthBuffer[3] = { 0 };
  u32 lwLength = 0;
  u8 bTmpPacketNum[5] = { 0 };
  char * rep = 0;

  bTmpPosition = DEBUG_StripCmd( ptsDEBUG_AppCmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsDEBUG_AppCmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );

  if( ( strcmp( (char const*)bTmpDataBuffer, "SYNC" ) ) == 0 )
  {
     printf("Sending Sync\n");

     tsReturnVariables.bByteVar = Sync( 2000 );

     printf("OK\n");
     return tsReturnVariables.bByteVar;

  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "ACK" ) ) == 0 )
  {
    printf("Sending Ack\n");
    DEBUG_StripCmd( ptsDEBUG_AppCmdEntryTable->bDebugBuffer, bTmpLengthBuffer , bTmpPosition, cDEBUG_AT_COMMA  );
    if( ( strstr( (char*)bTmpLengthBuffer, cDEBUG_USE_LAST_CMD_OUTPUT ) ) )
    {
      lwLength = tsReturnVariables.lwLongWordVar;
      printf("Using Package length = %d\n", tsReturnVariables.lwLongWordVar );
    }
    else
    {
      lwLength = atoi( (char*)bTmpLengthBuffer );
    }
    tsReturnVariables.bByteVar = AckMsg( lwLength );
    printf("OK\n");
    return tsReturnVariables.bByteVar;
  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "INIT" ) ) == 0 )
  {
    printf( "Sending Initial\n" );
    tsReturnVariables.bByteVar = Initial();
    printf("OK\n");
    return tsReturnVariables.bByteVar;

  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "PACK" ) ) == 0 )
  {
    printf( "Sending PACK\n" );
    tsReturnVariables.bByteVar = SetPackageSize();
    printf("OK\n");
    return tsReturnVariables.bByteVar;

  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "SNAP" ) ) == 0 )
  {
    printf( "Sending Snapshot\n" );
    tsReturnVariables.bByteVar = SnapShot();
    printf("OK\n");
    return tsReturnVariables.bByteVar;

  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "GET" ) ) == 0 )
  {
    printf( "Sending Get\n" );
    tsReturnVariables.lwLongWordVar = GetPicture();
    printf("PACK_GET = %d\n", tsReturnVariables.lwLongWordVar );


    itoa( (tsReturnVariables.lwLongWordVar+1) , (char*)bTmpPacketNum, 10);
    printf("pack get = %s\n", bTmpPacketNum );



    rep = replace_str( "%n", (char*)bTmpPacketNum, (char*)psL2_CODE_ImportantLayer2Data[6]  );
    strcpy( (char*)psL2_CODE_ImportantLayer2Data[6] , rep );

    printf("pack get = %s\n", psL2_CODE_ImportantLayer2Data[6]  );

    printf("OK\n");
    return tsReturnVariables.lwLongWordVar;
  }
  else
  {
    printf("ERROR\n");
    printf("OK\n");
    return cERR_ERROR_CODE;
  }

}



/*------------------------------------------------------------------------------
	$Function: DEBUG_DosDebug
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_DosDebug( tsDEBUG_DosCmdEntryTable * ptsDEBUG_DosCmdEntryTable )
{
  u8   bTmpDataBuffer[10] = {0} , bTmpPosition = 0, bTmpBuffer[10] = { 0 };



  bTmpPosition = DEBUG_StripCmd( ptsDEBUG_DosCmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsDEBUG_DosCmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );

  if( ( strcmp( (char const*)bTmpDataBuffer, "SYNC" ) ) == 0 )
  {
    printf( "Number of bytes %d\n", DOS_Sync( 2 ) );
  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "MNT" ) ) == 0 )
  {
    printf( "Number of bytes %d\n", DOS_Mnt() );
  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "MKDIR" ) ) == 0 )
  {
    memset( bTmpDataBuffer, 0, sizeof( bTmpDataBuffer ) );

    DEBUG_StripCmd( ptsDEBUG_DosCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );

    printf( "Number of bytes %d\n", DOS_MkDir( bTmpDataBuffer ) );
  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "WR" ) ) == 0 )
  {
    memset( bTmpDataBuffer, 0, sizeof( bTmpDataBuffer ) );

    bTmpPosition = DEBUG_StripCmd( ptsDEBUG_DosCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );

    DOS_OpenFile( DOS_CMD_OPEN_WRITE, bTmpDataBuffer  );


    memset( bTmpDataBuffer, 0, sizeof( bTmpDataBuffer ) );

    DEBUG_StripCmd( ptsDEBUG_DosCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );

    DOS_Write( bTmpDataBuffer, 1 );
  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "RD" ) ) == 0 )
  {
    memset( bTmpDataBuffer, 0, sizeof( bTmpDataBuffer ) );

    bTmpPosition = DEBUG_StripCmd( ptsDEBUG_DosCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );


    memset( bTmpBuffer, 0, sizeof( bTmpBuffer ) );

    DEBUG_StripCmd( ptsDEBUG_DosCmdEntryTable->bDebugBuffer, bTmpBuffer , bTmpPosition, cDEBUG_AT_COMMA  );

    printf("number of bytes = %d\n tmp = %s\n", atoi( (char*)bTmpBuffer ), bTmpBuffer );

    DOS_Read( bTmpDataBuffer, atoi( (char*)bTmpBuffer ) );
  }
  else if( ( strcmp( (char const*)bTmpDataBuffer, "RM" ) ) == 0 )
  {
    memset( bTmpDataBuffer, 0, sizeof( bTmpDataBuffer ) );

    DEBUG_StripCmd( ptsDEBUG_DosCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );

    DOS_Remove( bTmpDataBuffer );
  }



  return 1;
}



/*------------------------------------------------------------------------------
	$Function: DEBUG_RtcDebug
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 DEBUG_RtcDebug( tsDEBUG_RtcCmdEntryTable * ptsDEBUG_RtcCmdEntryTable )
{
  u8   bTmpDataBuffer[10] = {0} , bTmpPosition = 0;

  u8   bTemp = 0;

  RTC_I2C_Init();


  bTmpPosition = DEBUG_StripCmd( ptsDEBUG_RtcCmdEntryTable->bDebugBuffer, bTmpDataBuffer , ptsDEBUG_RtcCmdEntryTable->bTmpDataIndex, cDEBUG_AT_COMMA  );
  bTemp = atoi( (const char*)bTmpDataBuffer );
  printf("year = %d\n", bTemp );
  RTC_I2C_ByteWrite( bTemp, cRTC_I2C_YEAR_REG );
  bTemp = 0;
  memset(bTmpDataBuffer, 0, 10);

  bTmpPosition = DEBUG_StripCmd( ptsDEBUG_RtcCmdEntryTable->bDebugBuffer, bTmpDataBuffer ,bTmpPosition, cDEBUG_AT_COMMA  );
  bTemp = atoi( (const char*)bTmpDataBuffer );
  printf("month = %d\n", bTemp );
  RTC_I2C_ByteWrite( bTemp, cRTC_I2C_MONTH_CENT_REG );
  bTemp = 0;
  memset(bTmpDataBuffer, 0, 10);

  bTmpPosition = DEBUG_StripCmd( ptsDEBUG_RtcCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );
  bTemp = atoi( (const char*)bTmpDataBuffer );
  printf("date = %d\n", bTemp );
  RTC_I2C_ByteWrite( bTemp+6, cRTC_I2C_DATE_REG );
  bTemp = 0;
  memset(bTmpDataBuffer, 0, 10);

  bTmpPosition = DEBUG_StripCmd( ptsDEBUG_RtcCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );
  bTemp = atoi( (const char*)bTmpDataBuffer );
  printf("day = %d\n", bTemp );
  RTC_I2C_ByteWrite( bTemp, cRTC_I2C_DAY_REG );
  bTemp = 0;
  memset(bTmpDataBuffer, 0, 10);

  bTmpPosition = DEBUG_StripCmd( ptsDEBUG_RtcCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );
  bTemp = atoi( (const char*)bTmpDataBuffer );
  printf("hour = %d\n", bTemp );
  RTC_I2C_ByteWrite( bTemp+6, cRTC_I2C_HOUR_REG );
  bTemp = 0;
  memset(bTmpDataBuffer, 0, 10);

  bTmpPosition = DEBUG_StripCmd( ptsDEBUG_RtcCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );
  bTemp = atoi( (const char*)bTmpDataBuffer );
  printf("min = %d\n", bTemp );
  RTC_I2C_ByteWrite( bTemp, cRTC_I2C_MINUTE_REG );
  bTemp = 0;
  memset(bTmpDataBuffer, 0, 10);

  bTmpPosition = DEBUG_StripCmd( ptsDEBUG_RtcCmdEntryTable->bDebugBuffer, bTmpDataBuffer , bTmpPosition, cDEBUG_AT_COMMA  );
  bTemp = atoi( (const char*)bTmpDataBuffer );
  printf("sec = %d\n", bTemp );
  RTC_I2C_ByteWrite( bTemp+6, cRTC_I2C_SECOND_REG );
  bTemp = 0;
  memset(bTmpDataBuffer, 0, 10);






  return 1;
}

#undef cMEM_USERCLASS_ID_DEBUG_c