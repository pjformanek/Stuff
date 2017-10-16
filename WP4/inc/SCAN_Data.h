/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : SCAN_Data.h
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Jan 6, 2009
* Description        : Header file for SCAN_Data.c
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  u8 AB_ID_Flag;
  u8 AB_ID;
  u8 NumOfABinNetwork;
  
  
}SCAN_CheckDataTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
SCAN_CheckDataTypeDef SCAN_Data_Init( void );
DAT_NetworkSettingsTypeDef SCAN_Network_Switches( void );
DAT_MainAppSettingsTypeDef SCAN_Main_App_Switches( void );
