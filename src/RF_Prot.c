/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : RF_Prot.c
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Dec 23, 2008
* Description        : Contains functions that deal with RF interactions
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "Includes.h"
#include "MEM.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//u8 TxBuffer[8] = { mRF_PROT_GARBAGE_BYTE(), mRF_PROT_START_BYTE(), 0x00, 0x00, 0x00, 0x00, 0x00, mRF_PROT_END_BYTE() };
u8 TxBuffer[128];
u8 GP_Buffer[128];

u8 bGLB_RB_Flag = 0;
u8 bBuffer[128];

u8 bRF_PROT_PED_Flag = 0;
s8 bRF_PROT_IntRxGetFlag = 0;
u8 GLB_SupervisorFlag = 0;
u8 bRF_PROT_TxFlag = 0;

u8 bRF_PROT_RmID_RefreshFlag = 0;


RF_PacketTypeDef RfPacket;
DAT_NetworkSettingsTypeDef DAT_NetworkSettings;
DAT_AB_IDTypeDef DAT_AB_ID_Struct;
static u8 bRrefreshBusrtIdCount = 1;
static u8 bPedBurstIdCount = 0;

u16 wAPP_STATE_RB_NEXT_TIME_OUT = 0;
u8 bAPP_STATE_RB_TIME_OUT_FLAG = 0;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : RF_Main_App
* Description    : Main RF app this function starts setting up the flags to run
* 				   the firmware
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RF_Main_App( void )
{
  u16 wAB_ID;

  #ifdef mDEBUG_MODE
  Debug_Message("Main RF App\r\n");
  #endif

  if( GLB_SupervisorFlag )
  {
    #ifdef mDEBUG_MODE
    Debug_Message("Generating ID\r\n");
    #endif
    wAB_ID = RandomAB_ID_Generator( rand() );
    //bDAT_NumID_Registered = 1;
    #ifdef mDEBUG_MODE
    Debug_Message("ID generated\r\n");
    #endif
    Build_AB_ID_TableValues( wAB_ID, 0, 1 );
    bDAT_NumID_Registered++;
    #ifdef mDEBUG_MODE
    Debug_Message("ID saved in non-volotile mem\r\n");
    #endif
  }
  else
  {
    #ifdef mDEBUG_MODE
    Debug_Message("Joining already formed Network\r\n");
    #endif
  }





}


/*******************************************************************************
* Function Name  : SearchForMasterResponse
* Description    : Sends SFM burst to try to sync with any networks in that
*                  network id.
* Input          : none
* Output         : Sends SFM packet to all units in network
* Return         : None
*******************************************************************************/
void SearchForMasterResponse( u16 wReceiverID )
{
  DAT_NetworkSettings = SCAN_Network_Switches();
  DAT_AB_ID_Struct = ScanID_Values();

  GP_Buffer[0] = mRF_PROT_GARBAGE_BYTE();
  GP_Buffer[1] = mRF_PROT_START_BYTE();
  GP_Buffer[2] = RfPacket.RfStartByte = DAT_NetworkSettings.StartByte;
  GP_Buffer[3] = RfPacket.RfPreambleByte = DAT_NetworkSettings.PreambleByte;
  GP_Buffer[4] = ( DAT_AB_ID_Struct.AB_ID_0&0xFF00 ) >> 8;
  GP_Buffer[5] = ( DAT_AB_ID_Struct.AB_ID_0&0x00FF );
  GP_Buffer[6] = ( mRF_PROT_GLB_RECEIVER_ID()&0xFF00 ) >> 8;
  GP_Buffer[7] = ( mRF_PROT_GLB_RECEIVER_ID()&0x00FF );
  GP_Buffer[8] = RfPacket.RfIndexByteH = mRF_PROT_SFM_INDEX_H_BYTE();
  GP_Buffer[9] = RfPacket.RfIndexByteL = mRF_PROT_SFM_INDEX_L_BYTE();
  GP_Buffer[10] = RfPacket.RfTagByte = mRF_PROT_SFM_RESPONSE_TAG_BYTE();
  GP_Buffer[11] = RfPacket.RfVersionByte = mRF_PROT_SFM_RESPONSE_VERSION_BYTE();
  GP_Buffer[12] = RfPacket.RfLengthByte = 0x03;
  GP_Buffer[13] = ( wReceiverID&0xFF00 ) >> 8;
  GP_Buffer[14] = ( wReceiverID&0x00FF );
  GP_Buffer[15] = bDAT_NumID_Registered;
  GP_Buffer[16] = CheckSumGenerator( GP_Buffer, 14, 2);
  GP_Buffer[17] = mRF_PROT_END_BYTE();

  RFSendPacket( (char * )GP_Buffer, 18 );
  #ifdef mDEBUG_MODE
  Debug_Message( "SFM Response sent!\r\n");
  Convert_ASCII( GP_Buffer, 18 );
  #endif

}

/*******************************************************************************
* Function Name  : SearchForMasterBurst
* Description    : Sends SFM burst to try to sync with any networks in that
*                  network id.
* Input          : none
* Output         : Sends SFM packet to all units in network
* Return         : None
*******************************************************************************/
void SearchForMasterBurst( void )
{

  DAT_NetworkSettings = SCAN_Network_Switches();

  GP_Buffer[0] = mRF_PROT_GARBAGE_BYTE();
  GP_Buffer[1] = mRF_PROT_START_BYTE();
  GP_Buffer[2] = RfPacket.RfStartByte = DAT_NetworkSettings.StartByte;
  GP_Buffer[3] = RfPacket.RfPreambleByte = DAT_NetworkSettings.PreambleByte;
  GP_Buffer[4] = ( mRF_PROT_GLB_SENDER_ID()&0xFF00 ) >> 8;
  GP_Buffer[5] = ( mRF_PROT_GLB_SENDER_ID()&0x00FF );
  GP_Buffer[6] = ( mRF_PROT_GLB_RECEIVER_ID()&0xFF00 ) >> 8;
  GP_Buffer[7] = ( mRF_PROT_GLB_RECEIVER_ID()&0x00FF );
  GP_Buffer[8] = RfPacket.RfIndexByteH = mRF_PROT_SFM_INDEX_H_BYTE();
  GP_Buffer[9] = RfPacket.RfIndexByteL = mRF_PROT_SFM_INDEX_L_BYTE();
  GP_Buffer[10] = RfPacket.RfTagByte = mRF_PROT_SFM_TAG_BYTE();
  GP_Buffer[11] = RfPacket.RfVersionByte = mRF_PROT_SFM_VERSION_BYTE();
  GP_Buffer[12] = RfPacket.RfLengthByte = 0x00;
  GP_Buffer[13] = CheckSumGenerator( GP_Buffer, 11, 2);
  GP_Buffer[14] = mRF_PROT_END_BYTE();



  bRF_PROT_IntRxGetFlag = 0;
  __enable_interrupt();


  RFSendPacket( (char * )GP_Buffer, 15 );
  #ifdef mDEBUG_MODE
  Debug_Message( "SFM sent!\r\n");
  Convert_ASCII( GP_Buffer, 15 );
  #endif
}



/*******************************************************************************
* Function Name  : RF_FillBufferAndSend
* Description    : Fills RF buffer to be sent               MIGHT NOT NEED THIS FUNCTION ANY MORE juan clean up
* Input          : RF_PacketTypeDef * RfPacket
* Output         : None
* Return         : None
*******************************************************************************/
void RF_FillBufferAndSend( u8 * BufferArray, u8 Length )
{
  u8 i = 0;
  for( i = 0; i<=Length; i++ )
  {
    TxBuffer[i] = BufferArray[i];
  }

  RFSendPacket( (char * )TxBuffer, 8 ); // this might be trouble juan
}


/*******************************************************************************
* Function Name  : RF_ParseOutMessage
* Description    : Starts the parsing out the incoming RF packet
* Input          : u8 * pbRxBuffer - pointer to the incoming RF packet
* 				   u8 blength - length of the incoming packet
* Output         : Sends SFM packet to all units in network
* Return         : s8 - -1 if wrong packet lay out
* 					    returns a value from App_State finction
*******************************************************************************/

s8  RF_ParseOutMessage( u8 * pbRxBuffer, u8 blength )
{
  u8 AppState = 0;
  u8 i = 0;



  #ifdef mDEBUG_MODE
  Debug_Message( "RF parser\r\n");
  #endif
  //Convert_ASCII( pbRxBuffer, 15 );
  while( i != 1 )
  {
    switch( AppState )
    {
    case 0:
        if( pbRxBuffer[1] == mRF_PROT_START_BYTE() )
        {
          AppState = 1;
          #ifdef mDEBUG_MODE
          Debug_Message( "Start Byte received\r\n");
          #endif
        }
        else
        {
          #ifdef mDEBUG_MODE
          Debug_Message( "Error Start symbol\r\n");
          #endif
          AppState = 0;
          i = 1;
          return -1;
        }
      break;

    case 1:
        if( pbRxBuffer[2] == DAT_NetworkSettings.StartByte )
        {
          AppState = 2;
          #ifdef mDEBUG_MODE
          Debug_Message( "Start Bits received\r\n");
          #endif
        }
        else
        {
          #ifdef mDEBUG_MODE
          Debug_Message( "Start Bits Error\r\n");
          #endif
          AppState = 0;
          i = 1;
          return -1;
        }
      break;

    case 2:
      if( pbRxBuffer[3] == DAT_NetworkSettings.PreambleByte )
      {
        #ifdef mDEBUG_MODE
        Debug_Message( "Preamble Byte received\r\n");
        #endif

        AppState = 0;
        i = 1;
        return App_State( pbRxBuffer, 12 );
      }
      else
      {
        #ifdef mDEBUG_MODE
        Debug_Message( "Preamble Error\r\n");
        #endif
        AppState = 0;
        i = 1;
        return -1;
      }
      //break;
    }

  }
    return 1;


}


/*******************************************************************************
* Function Name  : CheckSumGenerator
* Description    : Generates a check sum on an incoming or outgoin RF packet
* Input          : u8 * pbBuffer - pointer to the RF packet
* 				   u8 bLength - length of the RF packet( it also determines
* 				   the last byte that should be counted in the checksum
* 				   u8 bStartPosition - the first byte in the packet where the
* 				   funciton starts creating the checksum
* Output         : none
* Return         : u8 bCheckSum - the actual checksum
*******************************************************************************/
u8 CheckSumGenerator( u8 * pbBuffer, u8 bLength, u8 bStartPosition )
{
  u8 j = bStartPosition, bCheckSum = 0, i = 0;

  while( i < bLength )
  {
    bCheckSum = bCheckSum + pbBuffer[j];
    j++;
    i++;
  }
  return bCheckSum;
}


/*******************************************************************************
* Function Name  : RefreshBurst
* Description    : This function reads the ID table and refreshes everyone on the
*                  network
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#if 0
u8 RefreshBurst( void )
{
  u8 i = 0, j = 13 ;
  s8 bRemoveID_Flag = 0;
  DAT_NetworkSettings = SCAN_Network_Switches();
  DAT_AB_ID_Struct = ScanID_Values();



  Debug_Message("*****");
  UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
  Debug_Message("*****");
  GP_Buffer[0] = mRF_PROT_GARBAGE_BYTE();
  GP_Buffer[1] = mRF_PROT_START_BYTE();
  GP_Buffer[2] = RfPacket.RfStartByte = DAT_NetworkSettings.StartByte;
  GP_Buffer[3] = RfPacket.RfPreambleByte = DAT_NetworkSettings.PreambleByte;

  GP_Buffer[4] = ( DAT_AB_ID_Struct.AB_ID_0&0xFF00 ) >> 8;
  GP_Buffer[5] = ( DAT_AB_ID_Struct.AB_ID_0&0x00FF );
  GP_Buffer[6] = ( DAT_AB_ID_Struct.AB_ALL_ID[bRrefreshBusrtIdCount]&0xFF00 ) >> 8;
  GP_Buffer[7] = ( DAT_AB_ID_Struct.AB_ALL_ID[bRrefreshBusrtIdCount]&0x00FF );
  GP_Buffer[8] = RfPacket.RfIndexByteH = mMSB_FROM_WORD( mRF_PROT_RB_INDEX() );
  GP_Buffer[9] = RfPacket.RfIndexByteL = mLSB_FROM_WORD( mRF_PROT_RB_INDEX() );
  GP_Buffer[10] = RfPacket.RfTagByte = mRF_PROT_RB_SENT_TAG();
  GP_Buffer[11] = RfPacket.RfVersionByte = mRF_PROT_RB_SENT_VERSION_BYTE();

  wAPP_STATE_TempID = DAT_AB_ID_Struct.AB_ALL_ID[bRrefreshBusrtIdCount];


  while( i<bDAT_NumID_Registered )
  {
    GP_Buffer[j] = mMSB_FROM_WORD( DAT_AB_ID_Struct.AB_ALL_ID[i] );
    GP_Buffer[j+1] = mLSB_FROM_WORD( DAT_AB_ID_Struct.AB_ALL_ID[i] );
    j = j + 2;
    i++;
    Debug_Message("#");
  }
  GP_Buffer[12] = RfPacket.RfLengthByte = (bDAT_NumID_Registered)*2;


  GP_Buffer[ 13+(bDAT_NumID_Registered*2) ] = bAPP_STATE_TempCheckSum = CheckSumGenerator( GP_Buffer,  11+(bDAT_NumID_Registered*2) , 2);
  GP_Buffer[14+(bDAT_NumID_Registered*2)] = mRF_PROT_END_BYTE();

  RFSendPacket( (char * )GP_Buffer, 15+(bDAT_NumID_Registered*2) );
  #ifdef mDEBUG_MODE
  Debug_Message( "Refresh Burst sent!\r\n");
  Convert_ASCII( GP_Buffer, 15+(bDAT_NumID_Registered*2) );
  #endif
  bGLB_RB_Flag = 1; // make sure this flag has been set up so the next acks coming in are for RB purposes only are the ones that need

  //DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount] = 0x30;


  if( RFReceivePacket( bBuffer,32, 5000 ) )
  {
     if( RF_ParseOutMessage( bBuffer, 64 ) == 2 ) // i was here
     {
       //DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount] = 0x33;
       WriteID_Status( bRrefreshBusrtIdCount, 0x30 );
       Debug_Message("ack for RB\r\n");
       //UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
     }
     else
     {
       WriteID_Status( bRrefreshBusrtIdCount, DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]++ );
      // DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]++; // this will go until it reaches 0x32 which is the maximum number of failures allowed
                                                                    // i need to make sure this value is programable

       if( DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount] == 0x32 ) // if it has failed to contact the unit twice it will remove from network
       {                                                                        // and renew the id table accordingly moving all the necessary id up on the table
         // fucntion to get rid of that unit that is not responding then update all other units with new ID table
         // make sure that the bDAT_NumID_Registered gets decremented by one
         bRemoveID_Flag = RemoveID_Value( bRrefreshBusrtIdCount );
       }
       Debug_Message("no ack for RB\r\n");
       UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
     }
     // if this has Receive timed out then supervisor should no which unit did not respond
   }
   else
   {
     UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
     WriteID_Status( bRrefreshBusrtIdCount, DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]++ );
    // DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]++; // this will go until it reaches 0x32 which is the maximum number of failures allowed
                                                                  // i need to make sure this value is programable

     if( DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount] == 0x32 ) // if it has failed to contact the unit twice it will remove from network
     {                                                                        // and renew the id table accordingly moving all the necessary id up on the table
       // fucntion to get rid of that unit that is not responding then update all other units with new ID table
       // make sure that the bDAT_NumID_Registered gets decremented by one
       bRemoveID_Flag = RemoveID_Value( bRrefreshBusrtIdCount );
     }
     Debug_Message("            no ack for RB\r\n");
     UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
   }
   bRrefreshBusrtIdCount++;
    if( bRrefreshBusrtIdCount == bDAT_NumID_Registered )
    {
      bRrefreshBusrtIdCount = 1;
    }
   wAPP_STATE_RB_NEXT_TIME_OUT = wGLB_SYS_TICK_COUNTER; // take note where the systick is so we know when to send the next RB
   bAPP_STATE_RB_TIME_OUT_FLAG = 1;
  return 1;
}
#endif

#if 1
u8 RefreshBurst( void )
{
  u8 i = 0, j = 13 ;
  DAT_NetworkSettings = SCAN_Network_Switches();
  DAT_AB_ID_Struct = ScanID_Values();
  s8 bRemoveID_Flag = 0;

 /* Debug_Message("*****");
  UART3_WAIT_AND_SEND( DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount] );

  Debug_Message("*****");*/

  GP_Buffer[0] = mRF_PROT_GARBAGE_BYTE();
  GP_Buffer[1] = mRF_PROT_START_BYTE();
  GP_Buffer[2] = RfPacket.RfStartByte = DAT_NetworkSettings.StartByte;
  GP_Buffer[3] = RfPacket.RfPreambleByte = DAT_NetworkSettings.PreambleByte;

  GP_Buffer[4] = ( DAT_AB_ID_Struct.AB_ID_0&0xFF00 ) >> 8;
  GP_Buffer[5] = ( DAT_AB_ID_Struct.AB_ID_0&0x00FF );
  GP_Buffer[6] = ( DAT_AB_ID_Struct.AB_ALL_ID[bRrefreshBusrtIdCount]&0xFF00 ) >> 8;
  GP_Buffer[7] = ( DAT_AB_ID_Struct.AB_ALL_ID[bRrefreshBusrtIdCount]&0x00FF );
  GP_Buffer[8] = RfPacket.RfIndexByteH = mMSB_FROM_WORD( mRF_PROT_RB_INDEX() );
  GP_Buffer[9] = RfPacket.RfIndexByteL = mLSB_FROM_WORD( mRF_PROT_RB_INDEX() );
  GP_Buffer[10] = RfPacket.RfTagByte = mRF_PROT_RB_SENT_TAG();
  GP_Buffer[11] = RfPacket.RfVersionByte = mRF_PROT_RB_SENT_VERSION_BYTE();

  wAPP_STATE_TempID = DAT_AB_ID_Struct.AB_ALL_ID[bRrefreshBusrtIdCount];


  while( i<bDAT_NumID_Registered )
  {
    GP_Buffer[j] = mMSB_FROM_WORD( DAT_AB_ID_Struct.AB_ALL_ID[i] );
    GP_Buffer[j+1] = mLSB_FROM_WORD( DAT_AB_ID_Struct.AB_ALL_ID[i] );
    j = j + 2;
    i++;
    Debug_Message("#");
  }
  GP_Buffer[12] = RfPacket.RfLengthByte = (bDAT_NumID_Registered)*2;


  GP_Buffer[ 13+(bDAT_NumID_Registered*2) ] = bAPP_STATE_TempCheckSum = CheckSumGenerator( GP_Buffer,  11+(bDAT_NumID_Registered*2) , 2);
  GP_Buffer[14+(bDAT_NumID_Registered*2)] = mRF_PROT_END_BYTE();

  RFSendPacket( (char * )GP_Buffer, 15+(bDAT_NumID_Registered*2) );
  #ifdef mDEBUG_MODE
  Debug_Message( "Refresh Burst sent!\r\n");
  Convert_ASCII( GP_Buffer, 15+(bDAT_NumID_Registered*2) );
  #endif
  bGLB_RB_Flag = 1; // make sure this flag has been set up so the next acks coming in are for RB purposes only are the ones that need

  //DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount] = 0x30;


  if( RFReceivePacket( bBuffer,32, 1000 ) )
  {
     if( RF_ParseOutMessage( bBuffer, 64 ) == 2 )
     {
       //DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount] = 0x33;
       WriteID_Status( bRrefreshBusrtIdCount, 0x30 );
       Debug_Message("ack for RB\r\n");
       UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
     }
     else
     {
       //WriteID_Status( bRrefreshBusrtIdCount, ( DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]+1) );
      // DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]++; // this will go until it reaches 0x32 which is the maximum number of failures allowed
                                                                    // i need to make sure this value is programable

       if( DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount] == 0x31 ) // if it has failed to contact the unit twice it will remove from network
       {                                                                        // and renew the id table accordingly moving all the necessary id up on the table
         // fucntion to get rid of that unit that is not responding then update all other units with new ID table
         // make sure that the bDAT_NumID_Registered gets decremented by one
         bRemoveID_Flag =RemoveID_Value( bRrefreshBusrtIdCount );
       }
       else
      {

        //UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
        WriteID_Status( bRrefreshBusrtIdCount, ( DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]+1) );
        // DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]++; // this will go until it reaches 0x32 which is the maximum number of failures allowed
                                                                  // i need to make sure this value is programable
      }
       Debug_Message("no ack for RB\r\n");
       UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
     }
     // if this has Receive timed out then supervisor should no which unit did not respond
   }
   else
   {
     if( DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount] == 0x31 ) // if it has failed to contact the unit twice it will remove from network
     {                                                                        // and renew the id table accordingly moving all the necessary id up on the table
       Debug_Message("Removing ID...\r\n");
       // fucntion to get rid of that unit that is not responding then update all other units with new ID table
       // make sure that the bDAT_NumID_Registered gets decremented by one
       bRemoveID_Flag = RemoveID_Value( bRrefreshBusrtIdCount );
       //bRF_PROT_RmID_RefreshFlag = 1;
     }
     else
     {

      //UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
      WriteID_Status( bRrefreshBusrtIdCount, ( DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]+1) );
      // DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]++; // this will go until it reaches 0x32 which is the maximum number of failures allowed
                                                                  // i need to make sure this value is programable

      bRF_PROT_RmID_RefreshFlag = 0;
     }


     Debug_Message("            no ack for RB\r\n");
     UART3_WAIT_AND_SEND(DAT_AB_ID_Struct.bDAT_AB_ID_STATUS[bRrefreshBusrtIdCount]);
   }
   UART3_WAIT_AND_SEND('+' );
   UART3_WAIT_AND_SEND( bDAT_NumID_Registered+0x30 );
   UART3_WAIT_AND_SEND( bRrefreshBusrtIdCount+0x30 );
    UART3_WAIT_AND_SEND('+' );
    if( bRemoveID_Flag == 1 )
    {
      bDAT_NumID_Registered--;
      bRrefreshBusrtIdCount--;
    }
   if( bDAT_NumID_Registered > 1 )
   {
     if( bRrefreshBusrtIdCount == bDAT_NumID_Registered-1 )
     {
       bRrefreshBusrtIdCount = 1;
     }
     else
     {
      bRrefreshBusrtIdCount++;
     }
   }
   else
   {
     bRrefreshBusrtIdCount = 1;
   }


   UART3_WAIT_AND_SEND( bRrefreshBusrtIdCount+0x30 );
   wAPP_STATE_RB_NEXT_TIME_OUT = wTIM_SysTickCounter; // take note where the systick is so we know when to send the next RB
   bAPP_STATE_RB_TIME_OUT_FLAG = 1;
  return 1;
}
#endif






/*******************************************************************************
* Function Name  : ACK_NACK_Response
* Description    : This function Sends and Ack or Nack to the sender ID containing
*                  the last checksum received
* Input          : u16 wSenderID - iD of the receiver of the ack/nack message
*                  u8 bCheckSum - the checsum that was received last
*                  u8 bNACK_OR_ACK - nack or ack tag
* Output         : None
* Return         : 1 upon success
*******************************************************************************/
u8 ACK_NACK_Response( u16 wSenderID, u8 bCheckSum, u8 bNACK_OR_ACK )
{

  DAT_NetworkSettings = SCAN_Network_Switches();
  DAT_AB_ID_Struct = ScanID_Values();

  GP_Buffer[0] = mRF_PROT_GARBAGE_BYTE();
  GP_Buffer[1] = mRF_PROT_START_BYTE();
  GP_Buffer[2] = RfPacket.RfStartByte = DAT_NetworkSettings.StartByte;
  GP_Buffer[3] = RfPacket.RfPreambleByte = DAT_NetworkSettings.PreambleByte;
  GP_Buffer[4] = ( DAT_AB_ID_Struct.AB_ID_0&0xFF00 ) >> 8;
  GP_Buffer[5] = ( DAT_AB_ID_Struct.AB_ID_0&0x00FF );
  GP_Buffer[6] = ( wSenderID&0xFF00 ) >> 8;
  GP_Buffer[7] = ( wSenderID&0x00FF );
  GP_Buffer[8] = RfPacket.RfIndexByteH = mMSB_FROM_WORD( mRF_PROT_ACK_NACK_INDEX() );
  GP_Buffer[9] = RfPacket.RfIndexByteL = mLSB_FROM_WORD( mRF_PROT_ACK_NACK_INDEX() );
  GP_Buffer[10] = RfPacket.RfTagByte = bNACK_OR_ACK;
  GP_Buffer[11] = RfPacket.RfVersionByte = mRF_PROT_ACK_NACK_INDEX_VERSION_BYTE();
  GP_Buffer[12] = RfPacket.RfLengthByte = 0x01;
  GP_Buffer[13] = bCheckSum;
  GP_Buffer[14] = CheckSumGenerator( GP_Buffer, 12, 2);
  GP_Buffer[15] = mRF_PROT_END_BYTE();

  RFSendPacket( (char * )GP_Buffer, 16 );
  #ifdef mDEBUG_MODE
  Debug_Message( "ACK/NACK sent!\r\n");
  Convert_ASCII( GP_Buffer, 15+(bDAT_NumID_Registered*2) );
  #endif

  return 1;
}

/*******************************************************************************
* Function Name  : PedButttonMessage
* Description    : your function's description
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 PedButttonMessage( u8 bPedButtonCheckFlashTAG )
{
  u8 bPED_ButtonAB_Status[256];
  u8 bPED_Status = 0x31;

  DAT_NetworkSettings = SCAN_Network_Switches();
  DAT_AB_ID_Struct = ScanID_Values();

  bRF_PROT_PED_Flag = 1; // make sure this flag is set up so the next ack is only for the PED button burst

  GP_Buffer[0] = mRF_PROT_GARBAGE_BYTE();
  GP_Buffer[1] = mRF_PROT_START_BYTE();
  GP_Buffer[2] = RfPacket.RfStartByte = DAT_NetworkSettings.StartByte;
  GP_Buffer[3] = RfPacket.RfPreambleByte = DAT_NetworkSettings.PreambleByte;
  GP_Buffer[4] = ( DAT_AB_ID_Struct.AB_ID_0&0xFF00 ) >> 8;
  GP_Buffer[5] = ( DAT_AB_ID_Struct.AB_ID_0&0x00FF );

  if( bPedButtonCheckFlashTAG == mRF_PROT_PED_BUTTON_CHECK_TAG() )
  {
    bRF_PROT_PED_Flag = 1; // make sure this flag is set up so the next ack is only for the PED button burst
    if( DAT_AB_ID_Struct.AB_ALL_ID[bPedBurstIdCount] != DAT_AB_ID_Struct.AB_ALL_ID[DAT_AB_ID_Struct.MY_ID_POSITION] )
    {
      GP_Buffer[6] = ( DAT_AB_ID_Struct.AB_ALL_ID[bPedBurstIdCount]&0xFF00 ) >> 8;
      GP_Buffer[7] = ( DAT_AB_ID_Struct.AB_ALL_ID[bPedBurstIdCount]&0x00FF );
      wAPP_STATE_TempID = DAT_AB_ID_Struct.AB_ALL_ID[bPedBurstIdCount];
    }
  }
  else
  {
    GP_Buffer[6] = ( mRF_PROT_GLB_RECEIVER_ID()&0xFF00 ) >> 8;
    GP_Buffer[7] = ( mRF_PROT_GLB_RECEIVER_ID()&0x00FF );
  }

  GP_Buffer[8] = RfPacket.RfIndexByteH = mMSB_FROM_WORD( mRF_PROT_PED_BUTTON_INDEX()  );
  GP_Buffer[9] = RfPacket.RfIndexByteL = mLSB_FROM_WORD( mRF_PROT_PED_BUTTON_INDEX()  );
  GP_Buffer[10] = RfPacket.RfTagByte = bPedButtonCheckFlashTAG;
  GP_Buffer[11] = RfPacket.RfVersionByte = mRF_PROT_PED_BUTTON_VERSION_BYTE();
  GP_Buffer[12] = RfPacket.RfLengthByte = 0x00;
  GP_Buffer[13] = bAPP_STATE_TempCheckSum = CheckSumGenerator( GP_Buffer, 11, 2);
  GP_Buffer[14] = mRF_PROT_END_BYTE();






  RFSendPacket( (char * )GP_Buffer, 15+RfPacket.RfLengthByte );

  #ifdef mDEBUG_MODE
  Debug_Message( "PED button Burst sent!\r\n");
  Convert_ASCII( GP_Buffer, 15+RfPacket.RfLengthByte );
  #endif

  if( bPedButtonCheckFlashTAG == mRF_PROT_PED_BUTTON_CHECK_TAG() )
  {


    if( RFReceivePacket( bBuffer,32, 1000 ) )
      {


       if( RF_ParseOutMessage( bBuffer, 64 ) == 3 ) // the return value might have to be different might wanna use the TAG of the message as the return value
       {                                            // for ParseOutMessage

         #ifdef mDEBUG_MODE
         Debug_Message("ack for PED burst\r\n");
         #endif
         bPED_ButtonAB_Status[bPedBurstIdCount] = 0x31;
       }
       else
       {
         #ifdef mDEBUG_MODE
         Debug_Message("??no ack for PED burst\r\n");
         #endif
         bPED_ButtonAB_Status[bPedBurstIdCount] = 0x30;
         bPED_Status = 0x30;
       }
       // if this has Receive timed out then supervisor should no which unit did not respond
     }
     else
     {
       #ifdef mDEBUG_MODE
       Debug_Message("no ack for PED burst\r\n");
       #endif
       bPED_ButtonAB_Status[bPedBurstIdCount] = 0x30;
     }
     //UART3_WAIT_AND_SEND(bPedBurstIdCount);




    if(  bPedBurstIdCount == bDAT_NumID_Registered-2 ) // it might not need to be -1 // this means that all units in network were sent the check message
    {
       #ifdef mDEBUG_MODE
       Debug_Message("all ids done\r\n");

       #endif
        bPedBurstIdCount = 0;
        if( bPED_Status == 0x30 ) // at least one unit failed to send back an ACK
        {
          return cAPP_STATE_PED_PARTIAL_FLASH; // it was -1
        }
        else
        {
          return cAPP_STATE_PED_FULL_FLASH; //it was 1
        }
     }
     else
     {
       #ifdef mDEBUG_MODE
       Debug_Message("still more ids\r\n");
       #endif
       bPedBurstIdCount++;
     }
  }



  return 0;

}
