/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : DAT_Access.h
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Jan 06, 2009
* Description        : Header file for DAT_Access.c
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct 
{
  u8 NetworkID;
  u8 PreambleByte; 
  u8 StartByte;
  u8 bSubNetworkID;
  u8 bSubPreambleByte; 
  u8 bSubStartByte;
  
}DAT_NetworkSettingsTypeDef;

typedef struct 
{
  u8 App_Switch;  
  u8 bDuration_Switch;
}DAT_MainAppSettingsTypeDef;


typedef struct
{
  u8 AB_JOINED_FLAG;
  u16 AB_ID_0;
  u16 AB_ALL_ID[256];
  u8 AB_ID_COUNT;
  u8 MY_ID_POSITION;
  u8 bDAT_AB_ID_STATUS[256];
}DAT_AB_IDTypeDef;

extern u8 bDAT_NumID_Registered;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
DAT_AB_IDTypeDef DAT_AB_ID_Values( void );
s8 ValidateNewRandomData( u16 RandomData );
void Build_AB_ID_TableValues( u16 wAB_ID, u8 bID_Position, s8 bMyID_Position );
DAT_AB_IDTypeDef ScanID_Values( void );
s8 RemoveID_Value( u8 bID_Position );
s8 WriteID_Status( u8 bID_Position, u8 bData );



