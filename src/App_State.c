/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : App_State.c
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Jan 6, 2009
* Description        : Main State Machine
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "Includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static DAT_AB_IDTypeDef DAT_AB_IDStructure;

u8 bAPP_STATE_TempCheckSum = 0;
u16 wAPP_STATE_TempID = 0;

u16 wAPP_STATE_PED_BUTTON_TIME_OUT = 0;
u8 bAPP_STATE_PED_BUTTON_TIME_OUT_FLAG = 0;
u8 bPED_AB_Status = 0x30;

u16 wAPP_STATE_SFM_TIME_OUT = 0;
u8  bAPP_STATE_SFM_Flag = 0;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : App_State
* Description    : Main Application State machine, it deals with all the RF messages
* Input          : u8 * pbRxBuffer - pointer to an array containg the RF packet
*		   u8 bLength - Length of the RF packet coming in
* Output         : None
* Return         : s8 - There are different return values for different packets
*		   they will be added as they are coded
*******************************************************************************/
s8 App_State( u8 * pbRxBuffer, u8 bLength )
{
  u8 state = 0;
  s8 bSenderFlag = -7, bReceiverFlag = -7;
  u8 j = 4, i = 0, k = 0, t = 0;
  u16 wTempWord = 0, wTempAB_ID = 0;
  
  DAT_AB_IDStructure = ScanID_Values();
  
  while ( j != 1 )
  {
    switch( state )
    {
    case 0: //  CHECKING SENDER ID
      //word = lsb + ( msb << 8 );      
      wTempWord = pbRxBuffer[5] + ( pbRxBuffer[4] << 8 );
    
      bSenderFlag = ValidateNewRandomData( wTempWord );
      switch( bSenderFlag )
      {
      case mAPP_STATE_OWN_SENDER_FLAG() :
        #ifdef mDEBUG_MODE
        Debug_Message( "Error\r\n");
        Debug_Message( "Own Tx ID\r\n");  // this should not happen unless the same ID is in the same network juan clean up
        Debug_Message( "Another Unit has my ID\r\n");
        #endif
        
        j = 1;
        state = 0;
        break;
        
      case mAPP_STATE_NR_SENDER_FLAG():
        #ifdef mDEBUG_MODE
        Debug_Message( "ID not recognized\r\n");   // this could be a problem juan clean up
        Debug_Message("Sender ID does not belong to network\r\n");
        #endif
        
        //j = 1;
        state = 1;
        break;
        
      case mAPP_STATE_SUPERVISOR_SENDER_FLAG():
        #ifdef mDEBUG_MODE
        Debug_Message( "Supervisor ID\r\n");   // this could be a problem juan clean up
        Debug_Message("ID belongs to network\r\n");
        #endif
        
        //j = 1;
        state = 1;
        break;
        
      case mAPP_STATE_NETWORK_SENDER_FLAG() :
        #ifdef mDEBUG_MODE
        Debug_Message( "ID recognized\r\n");
        Debug_Message("Sender ID belongs to network\r\n");
        #endif
        
        state = 1;
        break;
        
      case mAPP_STATE_GLB_SENDER_FLAG():
        #ifdef mDEBUG_MODE
        Debug_Message( "GLB ID recognized\r\n");
        Debug_Message("Sender ID belongs to GLB network\r\n");
        #endif
        
        state = 1;
        break;
        
      default:
        #ifdef mDEBUG_MODE
        Debug_Message( "Error Sender ID App State\r\n");
        #endif
        state = 0;
        j = 1;
        break;               
      }
      break;
      
    case 1: // CHECKING RECEIVER ID
      wTempWord = pbRxBuffer[7] + ( pbRxBuffer[6] << 8 );
      bReceiverFlag = ValidateNewRandomData( wTempWord );
      switch( bReceiverFlag )
      {
      case mAPP_STATE_SUPERVISOR_RECEIVER_FLAG():
        #ifdef mDEBUG_MODE
        Debug_Message( "Supervisor ID\r\n");   // this could be a problem juan clean up
        Debug_Message("ID belongs to network\r\n");
        #endif
        j = 1;
       
        state = 0;
        break;
      case mAPP_STATE_OWN_RECEIVER_FLAG():
        #ifdef mDEBUG_MODE
        Debug_Message( "Own Rx ID\r\n");  
        #endif

        state = 2;
        break;
        
      case mAPP_STATE_NR_RECEIVER_FLAG():
        #ifdef mDEBUG_MODE
        Debug_Message( "ID not recognized\r\n");
        Debug_Message("Receiver ID does not belong to network\r\n");
        #endif        
        j = 1;
        state = 0;
        break;
        
      case mAPP_STATE_NETWORK_RECEIVER_FLAG(): // THIS SHOULD PROBABLY KICK ME OUT AS WELL SINCE THE MESSAGE IS NOT FOR ME AND IS NOT FOR THE GLB RECEIVER ID 0xAAAA
        #ifdef mDEBUG_MODE
        Debug_Message( "ID recognized\r\n");
        Debug_Message("Receiver ID belongs to network\r\n");
        #endif
        j = 1;
        //state = 2;
        state = 0;
        break;
        
      case mAPP_STATE_GLB_RECEIVER_FLAG():
        #ifdef mDEBUG_MODE
        Debug_Message( "GLB ID recognized\r\n");
        Debug_Message("Receiver ID belongs to GLB network\r\n");
        #endif
        bReceiverFlag = -1;
        state = 2;
        break;
        
      default:
        #ifdef mDEBUG_MODE
        Debug_Message( "Error Receiver ID App State\r\n");
        #endif
        state = 0;
        j = 1;
        break;               
      }
      
      break;
      
    case 2: //  CHECKING INDEX ID
    
      wTempWord = pbRxBuffer[9] + ( pbRxBuffer[8] << 8 );
      switch( wTempWord )
      {
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case mRF_PROT_SFM_INDEX():
          
            if( mRF_PROT_GLB_RECEIVER_ID() == ( pbRxBuffer[7] + ( pbRxBuffer[6] << 8 ) ) )
            {
              #ifdef mDEBUG_MODE
              Debug_Message( "SFM Index received\r\n");
              #endif
              
              switch( pbRxBuffer[10] ) //  CHECKING TAG ID
              {
              //===================================================================================================  
              case mRF_PROT_SFM_TAG_BYTE():  
                if(  GLB_SupervisorFlag ) // make sure that the unit is the network supervisor other wise ignore message
                {
                  if( mRF_PROT_GLB_SENDER_ID() == ( pbRxBuffer[5] + ( pbRxBuffer[4] << 8 ) ) )
                  {
                    if( pbRxBuffer[11] == mRF_PROT_SFM_VERSION_BYTE() && pbRxBuffer[12] == 0 ) //  CHECKING VERSION AND LENGTH
                    {
                      if( pbRxBuffer[13] == CheckSumGenerator( pbRxBuffer, 11+pbRxBuffer[12], 2 ) )   //  CHECKING CHECKSUM
                      {
                        if( pbRxBuffer[14] == mRF_PROT_END_BYTE() )
                        {
                          wTempAB_ID = RandomAB_ID_Generator( rand() );   
                          
                          Build_AB_ID_TableValues( wTempAB_ID , bDAT_NumID_Registered, 0 );          
                          WriteID_Status( bDAT_NumID_Registered, 0x30 );
                          SearchForMasterResponse( wTempAB_ID );
                          
                          bDAT_NumID_Registered++; // make sure next id that gets added does not overwrite the ones in memory
                                          // this should be done right after any Build_Ab_ID_TableValues  function call
                          
                          #ifdef mDEBUG_MODE
                          Debug_Message( "SFM message decoded successfully\r\n");
                          #endif
                          // send Refresh Burst  
                          // May need to add a delay here to give the receiver enought time to react to this message
                          bAPP_STATE_RB_TIME_OUT_FLAG = 0;
                          while( t < bDAT_NumID_Registered-1 )
                          {
                            Delay( 0xFFFF );
                            RefreshBurst(); // this function should return the value of the checksum 
                            
                            t++;
                          } 
                          
                          
                            
                          state = 0;
                          j = 1;  
                          return 1; // change to mRF_PROT_SFM_TAG_BYTE()
                        }
                        else
                        {
                          #ifdef mDEBUG_MODE
                          Debug_Message( "Wrong ending character SFM message\r\n");                
                          #endif                
                          state = 0;
                          j = 1;     
                          return -1;
                        }
                      }
                      else
                      {
                        #ifdef mDEBUG_MODE
                        Debug_Message( "Wrong Checksum SFM message\r\n");                
                        #endif                
                        state = 0;
                        j = 1;
                        return -1;
                      }
                      
                    }
                    else
                    {
                      #ifdef mDEBUG_MODE
                      Debug_Message( "Wrong version and/or length in SFM message\r\n");
                      #endif
                      state = 0;
                      j = 1;
                      return -1;
                      
                    }
                  }
                  else
                  {
                    #ifdef mDEBUG_MODE
                    Debug_Message( "Wrong sender SFM message\r\n");
                    #endif
                    state = 0;
                    j = 1;      
                    return -1;
                  }
                }
                else
                {
                  #ifdef mDEBUG_MODE
                  Debug_Message( "I am not Supervisor\r\n");
                  #endif
                  state = 0;
                  j = 1;
                  return -1;
                }
                //break;
                //=================================================================================
              case mRF_PROT_SFM_RESPONSE_TAG_BYTE():
                if( pbRxBuffer[11] == mRF_PROT_SFM_VERSION_BYTE() && pbRxBuffer[12] == 3 ) //  CHECKING VERSION AND LENGTH
                {                 
                  if( pbRxBuffer[ 13+pbRxBuffer[12] ] == CheckSumGenerator( pbRxBuffer, 11+pbRxBuffer[12], 2 ) )   //  CHECKING CHECKSUM
                  {
                    if( pbRxBuffer[14+( pbRxBuffer[12] )] == mRF_PROT_END_BYTE() )
                    {
                      wTempAB_ID =  mWORD_FROM_BYTES( pbRxBuffer[4], pbRxBuffer[5] );
                      Build_AB_ID_TableValues( wTempAB_ID , 0, 0 );  // registering Supervisor ID 
                      bDAT_NumID_Registered++;
                      
                      wTempAB_ID = mWORD_FROM_BYTES(pbRxBuffer[13], pbRxBuffer[14]);
                      Build_AB_ID_TableValues( wTempAB_ID , pbRxBuffer[15], 1 ); // everything was working fine with pbRxBuffer[14] but it seems to
                      bDAT_NumID_Registered++;                                    // that the right value should be pbRxBuffer[15]
                      
                      state = 0;
                      j = 1;  
                      return mRF_PROT_SFM_RESPONSE_TAG_BYTE();
                    }
                    else
                    {
                      #ifdef mDEBUG_MODE
                      Debug_Message( "Wrong ending character SFM Response message\r\n");                
                      #endif                
                      state = 0;
                      j = 1;   
                      return -1;
                    }
                  }
                  else
                  {
                    #ifdef mDEBUG_MODE
                    Debug_Message( "Wrong Checksum SFM Response message\r\n");                
                    #endif                
                    state = 0;
                    j = 1;
                    return -1;
                  }
                    
                }
                else
                {
                  #ifdef mDEBUG_MODE
                  Debug_Message( "Wrong version and/or length in SFM Response message\r\n");
                  #endif
                  state = 0;
                  j = 1;
                  return -1;
                }  
               // break;
                
              default:
                #ifdef mDEBUG_MODE
                Debug_Message( "Wrong tag id in SFM Response message\r\n");
                #endif
                state = 0;
                j = 1;
                return -1;
                //break;     
                
              }
              
            }            
            else
            {
              #ifdef mDEBUG_MODE
              Debug_Message( "Wrong Sender and Receiver ID in SFM Response message\r\n");
              #endif
              state = 0;
              j = 1;
              return -1;
            }  
            //break;
            //==========================================================================================
            
          
        //////////////////////////////////////////////////////////////////////////
   
       case mRF_PROT_RB_INDEX():    
            
        if( DAT_AB_IDStructure.AB_ID_0 == ( pbRxBuffer[7] + ( pbRxBuffer[6] << 8 ) ) )
        {
            #ifdef mDEBUG_MODE
            Debug_Message( "RB Index received\r\n");
            #endif
            switch( pbRxBuffer[10] ) //  CHECKING TAG ID
            {
              //===================================================================================================
              case mRF_PROT_RB_SENT_TAG():
                
                //////////////DAT_AB_IDStructure = ScanID_Values();
                if( pbRxBuffer[11] == mRF_PROT_RB_SENT_VERSION_BYTE() )   //  CHECKING VERSION
                {
                  i = 0;
                  k = 13;
                  bDAT_NumID_Registered = pbRxBuffer[12]/2; 
                  while( i<=pbRxBuffer[12] )
                  {
                    wTempAB_ID = mWORD_FROM_BYTES( pbRxBuffer[k], pbRxBuffer[k+1] );
                    if( wTempAB_ID == DAT_AB_IDStructure.AB_ID_0 )
                    {
                      Build_AB_ID_TableValues( wTempAB_ID, i, 1 );
                    }
                    else
                    {
                      Build_AB_ID_TableValues( wTempAB_ID, i, 0 );
                    }
                    i++;
                    k=k+2;
                  }
                  
                  if( CheckSumGenerator( pbRxBuffer,  11+(pbRxBuffer[12]) , 2) == pbRxBuffer[ 13+(pbRxBuffer[12]) ] )
                  {                    
                    if( pbRxBuffer[14+(pbRxBuffer[12])] == mRF_PROT_END_BYTE() )
                    {
                      #ifdef mDEBUG_MODE
                      Debug_Message( "Refresh Burst received correctly\r\n");
                      #endif
                      /////////////////========================================================================================////////////////////
                      //MAJOR PROBLEM HERE LOCK UP OCCURS IF THAT DELAY OR ANY OTHER FUNCTION IS NOT INTRODUCED IN HERE 
                      // THE PROBLEM SEEMED TO GONE AWAY BY REMOVING OPTIMAZATION
                      
                      //wTempAB_ID = mWORD_FROM_BYTES( pbRxBuffer[5], pbRxBuffer[4] );
                      //ACK_NACK_Response( wTempAB_ID, pbRxBuffer[ 13+(pbRxBuffer[12]) ], mRF_PROT_ACK_TAG() );
                      //Delay(500);
                      ACK_NACK_Response( ( pbRxBuffer[5] + ( pbRxBuffer[4] << 8 ) ), pbRxBuffer[ 13+(pbRxBuffer[12]) ], mRF_PROT_ACK_TAG() );                   
                      wAPP_STATE_RB_NEXT_TIME_OUT = wGLB_SYS_TICK_COUNTER; // take note where the systick is so we know when to send the next RB
                      bAPP_STATE_RB_TIME_OUT_FLAG = 1;
                      //Delay(500);
                      //RandomAB_ID_Generator( 1235 );
                      
                      state = 0;
                      j = 1;
                      return 1; // change to mRF_PROT_RB_SENT_TAG()
                    }
                    else
                    {
                      #ifdef mDEBUG_MODE
                      Debug_Message( "Wrong End Byte received\r\n");
                      #endif
                      state = 0;
                      j = 1;
                      return -1;
                    }
                   }
                  else
                  {
                    #ifdef mDEBUG_MODE
                    Debug_Message( "Wrong CheckSum received\r\n");
                    #endif
                    state = 0;
                    j = 1;
                    return -1;
                  }
                  
                }
                else
                {
                  #ifdef mDEBUG_MODE
                  //Delay(100);                       // OK WITH DELAY HERE THE PRINTF WORKS WITHOUT LOCKING THE MICRO
                  Debug_Message( "Wrong RB sent version received\r\n");
                  #endif
                  state = 0;
                  j = 1;
                  return -1;
                }
                //break;
              //===================================================================================================
              case mRF_PROT_RB_RESPONSE_TAG():
                if( pbRxBuffer[11] == mRF_PROT_RB_RESPONSE_VERSION_BYTE() )// I may not need this juan clean up
                {
                }
                else
                {                  
                }
                break;
              //===================================================================================================
                
            default:
              #ifdef mDEBUG_MODE
              Debug_Message( "Wrong RB sent Tag received\r\n");
              #endif
              state = 0;
              j = 1;
              return -1;
              //break;
            }
        }
        else
        {
          #ifdef mDEBUG_MODE
          Debug_Message( "Receipient not recognized\r\n");
          #endif
          state = 0;
          j = 1;
          return -1;
        }
      
        break;
        //////////////////////////////////////////////////////////////////////////
      
      case mRF_PROT_ACK_NACK_INDEX():
        if( ( ( bSenderFlag == mAPP_STATE_NETWORK_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_OWN_RECEIVER_FLAG() ) ) ||
            ( ( bSenderFlag == mAPP_STATE_SUPERVISOR_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_OWN_RECEIVER_FLAG() ) ) ||
            ( ( bSenderFlag == mAPP_STATE_GLB_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_OWN_RECEIVER_FLAG() ) )  ||
            ( ( bSenderFlag == mAPP_STATE_GLB_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_GLB_RECEIVER_FLAG() ) )  
           ) 
        
        {                                                                                                               // TO BE AN && NOT AN || juan clean up
          switch( pbRxBuffer[10] ) // checking tag
          {
            case mRF_PROT_ACK_TAG():
              if( pbRxBuffer[11] == mRF_PROT_ACK_NACK_INDEX_VERSION_BYTE() && pbRxBuffer[12] == 0x01 ) //  CHECKING VERSION AND LENGTH
              {
                if( bGLB_RB_Flag )
                {
                  if( bAPP_STATE_TempCheckSum == pbRxBuffer[13] )
                  {
                   // UART3_WAIT_AND_SEND( (wAPP_STATE_TempID&0xff00) >> 8 );
                   // UART3_WAIT_AND_SEND( (wAPP_STATE_TempID&0x00ff) );
                    
                    if( wAPP_STATE_TempID == ( pbRxBuffer[5] + ( pbRxBuffer[4] << 8 ) ) ) // making sure that the receiver id is the same as the one
                    {                                                                     // the RB was sent to    
                      bGLB_RB_Flag = 0;
                      #ifdef mDEBUG_MODE
                      Debug_Message("ACK/NACK received correctly!!\r\n");
                      #endif
                      state = 0;
                      j = 1;
                      return 2; // THIS SHOULD BE A DIFFERENT VALUE SO WE KNOW THAT AN ACK HAS COME BACK   // change to  RB burst flag
                    }
                    else
                    {
                      #ifdef mDEBUG_MODE
                      Debug_Message("ACK/NACK received incorrectly\r\n");
                      #endif
                      state = 0;
                      j = 1;
                      return -2; // THIS SHOULD BE A DIFFERENT VALUE SO WE KNOW THAT AN ACK HAS COME BACK  // this may need to be just a error return 
                                                                                                           // we may wanna know what kind of error
                    }
                  }
                  else
                  {
                    #ifdef mDEBUG_MODE
                    Debug_Message("ACK/NACK is not for RB that unit should be considered not avaliable\r\n");
                    #endif
                    state = 0;
                    j = 1;
                    return -1;                    
                  }                  
                }
                
                if( bRF_PROT_PED_Flag )
                {
                  if( bAPP_STATE_TempCheckSum == pbRxBuffer[13] )
                  {
                   // UART3_WAIT_AND_SEND( (wAPP_STATE_TempID&0xff00) >> 8 );
                   // UART3_WAIT_AND_SEND( (wAPP_STATE_TempID&0x00ff) );
                    
                    if( wAPP_STATE_TempID == ( pbRxBuffer[5] + ( pbRxBuffer[4] << 8 ) ) ) // making sure that the receiver id is the same as the one
                    {                                                                     // the RB was sent to    
                      bRF_PROT_PED_Flag = 0;
                      #ifdef mDEBUG_MODE
                      Debug_Message("ACK/NACK received correctly!!\r\n");
                      #endif
                      state = 0;
                      j = 1;
                      return 3; // THIS SHOULD BE A DIFFERENT VALUE SO WE KNOW THAT AN ACK HAS COME BACK   / change to PED BUTTON FLAG
                    }
                    else
                    {
                      #ifdef mDEBUG_MODE
                      Debug_Message("ACK/NACK received incorrectly\r\n");
                      #endif
                      state = 0;
                      j = 1;
                      return -3; // THIS SHOULD BE A DIFFERENT VALUE SO WE KNOW THAT AN ACK HAS COME BACK
                    }
                  }
                  else
                  {
                    #ifdef mDEBUG_MODE
                    Debug_Message("ACK/NACK is not for RB that unit should be considered not avaliable\r\n");
                    #endif
                    state = 0;
                    j = 1;
                    return -1;                    
                  }                  
                }
                
                #ifdef mDEBUG_MODE
                Debug_Message("ACK/NACK received correctly\r\n");
                #endif
                state = 0;
                j = 1;
                return 1;
              }
              else
              {
                #ifdef mDEBUG_MODE
                Debug_Message("Wrong Version or length ACK/NACK\r\n");
                #endif
                state = 0;
                j = 1;
                return -1;
              }
              //break;
            //===========================================================  
            case mRF_PROT_NACK_TAG():
              break;          
            //===========================================================  
            default:
              #ifdef mDEBUG_MODE
              Debug_Message("Error in tag ACK/NACK\r\n");
              #endif
              state = 0;
              j = 1;
              return -1;
              //break;
          }
        }
        else
        {
          #ifdef mDEBUG_MODE
          Debug_Message("Wrong Sender/Receiver ACK/NACK\r\n");
          #endif
          state = 0;
          j = 1;
          return -1;
        }
       // break;
        
        //////////////////////////////////////////////////////////////////////////
        
      case mRF_PROT_PED_BUTTON_INDEX():
        #ifdef mDEBUG_MODE
        Debug_Message("PED Button Index recived\r\n");
        #endif
        if( ( ( bSenderFlag == mAPP_STATE_NETWORK_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_OWN_RECEIVER_FLAG() ) ) ||
            ( ( bSenderFlag == mAPP_STATE_NETWORK_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_GLB_RECEIVER_FLAG() ) ) ||
            ( ( bSenderFlag == mAPP_STATE_SUPERVISOR_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_GLB_RECEIVER_FLAG() ) ) ||
            ( ( bSenderFlag == mAPP_STATE_SUPERVISOR_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_OWN_RECEIVER_FLAG() ) ) ||
            ( ( bSenderFlag == mAPP_STATE_GLB_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_OWN_RECEIVER_FLAG() ) )  ||
            ( ( bSenderFlag == mAPP_STATE_GLB_SENDER_FLAG() ) && ( bReceiverFlag == mAPP_STATE_GLB_RECEIVER_FLAG() ) )             
           ) 
        {                                                                                                               
          switch( pbRxBuffer[10] ) // checking tag
          {
            case mRF_PROT_PED_BUTTON_CHECK_TAG():
              if( pbRxBuffer[11] == mRF_PROT_PED_BUTTON_VERSION_BYTE() && pbRxBuffer[12] == 0x00 ) //  CHECKING VERSION AND LENGTH
              {
                if( pbRxBuffer[ 13+pbRxBuffer[12] ] == CheckSumGenerator( pbRxBuffer, 11+pbRxBuffer[12], 2 ) )   //  CHECKING CHECKSUM
                  {
                    if( pbRxBuffer[14+( pbRxBuffer[12] )] == mRF_PROT_END_BYTE() )
                    {
                      #ifdef mDEBUG_MODE
                      Debug_Message("PED Check Button message recived\r\n");
                      #endif
                      ACK_NACK_Response( ( pbRxBuffer[5] + ( pbRxBuffer[4] << 8 ) ), pbRxBuffer[ 13+(pbRxBuffer[12]) ], mRF_PROT_ACK_TAG() ); 
                      state = 0;
                      j = 1;
                      return 1; //CHANGE TO  mRF_PROT_PED_BUTTON_CHECK_TAG()
                    }
                  }
              }
              else
              {
                #ifdef mDEBUG_MODE
                Debug_Message("Wrong Version/TAG PED Check message\r\n");
                #endif
                state = 0;
                j = 1;
                return -1;
              }
              break;
              //===========================================================  
            case mRF_PROT_PED_BUTTON_FULL_FLASH_TAG():
              if( pbRxBuffer[11] == mRF_PROT_PED_BUTTON_VERSION_BYTE() && pbRxBuffer[12] == 0x00 ) //  CHECKING VERSION AND LENGTH
              {
                if( pbRxBuffer[ 13+pbRxBuffer[12] ] == CheckSumGenerator( pbRxBuffer, 11+pbRxBuffer[12], 2 ) )   //  CHECKING CHECKSUM
                  {
                    if( pbRxBuffer[14+( pbRxBuffer[12] )] == mRF_PROT_END_BYTE() )
                    {
                      if( bAPP_STATE_PED_BUTTON_TIME_OUT_FLAG == 0 )
                      {
                        #ifdef mDEBUG_MODE
                        Debug_Message("PED Full Flash Button message recived\r\n");
                        #endif
                        bAPP_STATE_PED_BUTTON_TIME_OUT_FLAG = cAPP_STATE_PED_FLASH_READY;  
                        bPED_AB_Status = cAPP_STATE_PED_FULL_FLASH;
                      }
                      wAPP_STATE_PED_BUTTON_TIME_OUT = wGLB_SYS_TICK_COUNTER; 
                      state = 0;
                      j = 1;
                      return 1; // CHANGE TO mRF_PROT_PED_BUTTON_FULL_FLASH_TAG()
                    }
                  }
              }
              else
              {
                #ifdef mDEBUG_MODE
                Debug_Message("Wrong Version/TAG PED Full Flash message\r\n");
                #endif
                state = 0;
                j = 1;
                return -1;
              }
              break;
              //===========================================================  
            case mRF_PROT_PED_BUTTON_PARTIAL_FLASH_TAG():
              if( pbRxBuffer[11] == mRF_PROT_PED_BUTTON_VERSION_BYTE() && pbRxBuffer[12] == 0x00 ) //  CHECKING VERSION AND LENGTH
              {
                if( pbRxBuffer[ 13+pbRxBuffer[12] ] == CheckSumGenerator( pbRxBuffer, 11+pbRxBuffer[12], 2 ) )   //  CHECKING CHECKSUM
                  {
                    if( pbRxBuffer[14+( pbRxBuffer[12] )] == mRF_PROT_END_BYTE() )
                    {
                      #ifdef mDEBUG_MODE
                      Debug_Message("PED Partial Flash Button message recived\r\n");
                      #endif
                      if( bAPP_STATE_PED_BUTTON_TIME_OUT_FLAG == 0 )
                      {
                       bAPP_STATE_PED_BUTTON_TIME_OUT_FLAG = cAPP_STATE_PED_FLASH_READY;  
                       bPED_AB_Status = cAPP_STATE_PED_PARTIAL_FLASH;
                      }
                      wAPP_STATE_PED_BUTTON_TIME_OUT = wGLB_SYS_TICK_COUNTER;
                      state = 0;
                      j = 1;
                      return 1; // CHANGE TO mRF_PROT_PED_BUTTON_PARTIAL_FLASH_TAG()
                    }
                  }
              }
              else
              {
                #ifdef mDEBUG_MODE
                Debug_Message("Wrong Version/TAG PED Partial Flash message\r\n");
                #endif
                state = 0;
                j = 1;
                return -1;
              }
              break;
              //=========================================================== 
            default:
              #ifdef mDEBUG_MODE
              Debug_Message("Error in tag PED Button\r\n");
              #endif
              state = 0;
              j = 1;
              return -1;
              
          }
        }
        else
        {
          #ifdef mDEBUG_MODE
          Debug_Message( "Error PED index App State!!\r\n");
          #endif
          state = 0;
          j = 1;
          return -1;
        }
        break;
        //////////////////////////////////////////////////////////////////////////
      default:
        #ifdef mDEBUG_MODE
        Debug_Message( "Error index App State\r\n");
        #endif
        state = 0;
        j = 1;
        return -1;
        //break;
      }
      
      break;
  
      
    default:
      #ifdef mDEBUG_MODE
      Debug_Message( "Error App State\r\n");
      #endif
      state = 0;
      j = 1;
      return -1;
      //break;
    }
  }
  
  return -1;
  
}

/*******************************************************************************
* Function Name  : RamdonSleepWakeUp
* Description    : Sets up a ramdon timeout where the unit will sleep until the 
*		   the timeout runs out.
* Input          : u16 wRamdonSeed - a ramdon seed can be inserted to the function
*		   to add to its ramdonness
* Output         : None
* Return         : u8 - returns 1 upon succesfully timed out or zero if failed
*******************************************************************************/
u8 RamdonSleepWakeUp( u16 wRamdonSeed )
{
  
  u16 wRamdonTimeout;
  u8 bRamdonSleepFlagTO = 0;
  
  wRamdonTimeout = RNG( rand() );
  
  TIM1_Configuration( ( wRamdonTimeout+252 ) );  // might wanna change this so the 252 is rand() instead juan clean up
  TIM_Cmd(TIM1, ENABLE); 
  // Need to send unit to sleep then wake up before timeout has expired
  while(1)
  {
    if( TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET )
    {
      TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
      TIM_Cmd(TIM1, DISABLE); 
      #ifdef mDEBUG_MODE
      Debug_Message( "Ramdon Sleep Timed-out\r\n");
      #endif
      bRamdonSleepFlagTO = 1;
      break;
    }    
  }  
  
  return bRamdonSleepFlagTO;  
}






