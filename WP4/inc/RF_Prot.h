/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : RF_Prot.h
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Dec 23, 2008
* Description        : Header file for RF_Prot.c
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct 
{
  u8 RfStartByte;
  u8 RfPreambleByte;
  u8 RfIndexByteH;
  u8 RfIndexByteL;
  u8 RfTagByte;
  u8 RfVersionByte;
  u8 RfLengthByte;
  
}RF_PacketTypeDef;

typedef struct
{
  u8 bAB_JoinedFlag;
  u16 bAB_ID_0;
  u16 bAB_ALL_ID[256];
  
}RF_AB_ID_DataTypeDef;


extern u8 bRF_PROT_PED_Flag;
extern s8 bRF_PROT_IntRxGetFlag;
extern u8 bRF_PROT_TxFlag;
extern u8 bRF_PROT_RmID_RefreshFlag;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define mRF_PROT_GLB_SENDER_ID()                        0xFFED
#define mRF_PROT_GLB_RECEIVER_ID()                      0xAAAA

#define mRF_PROT_START_BYTE()                           0x5B
#define mRF_PROT_END_BYTE()                             0x5D
#define mRF_PROT_GARBAGE_BYTE()                         0x99

#define mRF_PROT_LIGHT_INDEX_H_BYTE()                   0x00
#define mRF_PROT_LIGHT_INDEX_L_BYTE()                   0x73
#define mRF_PROT_LIGHT_ON_TAG_BYTE()                    0x35  
#define mRF_PROT_LIGHT_OFF_TAG_BYTE()                   0x34

#define mRF_PROT_DOOR_INDEX_H_BYTE()                    0x00
#define mRF_PROT_DOOR_INDEX_L_BYTE()                    0x65
#define mRF_PROT_DOOR_LOCK_TAG_BYTE()                   0x35  
#define mRF_PROT_DOOR_UNLOCK_TAG_BYTE()                 0x34

#define mRF_PROT_SFM_INDEX()                            0x0080 // might wanna join low and hight byte that way if anything chnages this will change accordingly
#define mRF_PROT_SFM_INDEX_H_BYTE()                     0x00
#define mRF_PROT_SFM_INDEX_L_BYTE()                     0x80
#define mRF_PROT_SFM_TAG_BYTE()                         0x3F
#define mRF_PROT_SFM_VERSION_BYTE()                     0x01


#define mRF_PROT_SFM_RESPONSE_TAG_BYTE()                0x4E
#define mRF_PROT_SFM_RESPONSE_VERSION_BYTE()            0x01

#define mRF_PROT_RB_INDEX()                             0x0015

#define mRF_PROT_RB_SENT_TAG()                          0x27
#define mRF_PROT_RB_SENT_VERSION_BYTE()                 0x01

#define mRF_PROT_RB_RESPONSE_TAG()                      0x30
#define mRF_PROT_RB_RESPONSE_VERSION_BYTE()             0x01

#define mRF_PROT_ACK_NACK_INDEX()                       0x0023
#define mRF_PROT_ACK_NACK_INDEX_VERSION_BYTE()          0x01

#define mRF_PROT_ACK_TAG()                              0x35
#define mRF_PROT_NACK_TAG()                             0x34

#define mRF_PROT_PED_BUTTON_INDEX()                     0x0045
#define mRF_PROT_PED_BUTTON_VERSION_BYTE()              0x01

#define mRF_PROT_PED_BUTTON_CHECK_TAG()                 0x31
#define mRF_PROT_PED_BUTTON_FULL_FLASH_TAG()            0x34
#define mRF_PROT_PED_BUTTON_PARTIAL_FLASH_TAG()         0x35

                            

/* Exported functions ------------------------------------------------------- */
void RF_Main_App( void );
void RF_FillBufferAndSend( u8 * BufferArray, u8 Length );
void SearchForMasterBurst( void );
void SearchForMasterResponse( u16 wReceiverID );
s8 RF_ParseOutMessage( u8 * pbRxBuffer, u8 blength );
u8 CheckSumGenerator( u8 * pbBuffer, u8 bLength, u8 bStartPosition );
u8 RefreshBurst( void );
u8 ACK_NACK_Response( u16 wSenderID, u8 bCheckSum, u8 bNACK_OR_ACK );
u8 PedButttonMessage( u8 bPedButtonCheckFlashTAG );
