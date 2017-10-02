/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : SCAN_Data.c
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Jan 6, 2009
* Description        : Scans all switch values and buttons
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "Includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
DAT_NetworkSettingsTypeDef DAT_NetworkSettingsStructure;
DAT_MainAppSettingsTypeDef DAT_MainAppSettingsStructure;
SCAN_CheckDataTypeDef SCAN_CheckDataStructure;
DAT_AB_IDTypeDef DAT_AB_IDStruct;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : SCAN_Network_Switches
* Description    : Scans all network switches and sets up the values on the struct
* 				   for testing purposes all values will be hardcoded for now
*                  in future use this functions will read all switches and set up
*                  all data accordingly 
* Input          : None
* Output         : None
* Return         : DAT_NetworkSettingsTypeDef - struct containing all the network
* 				   values
*******************************************************************************/
DAT_NetworkSettingsTypeDef SCAN_Network_Switches( void )
{
  DAT_NetworkSettingsStructure.NetworkID = 0x32;
  DAT_NetworkSettingsStructure.PreambleByte = 0x0A;
  DAT_NetworkSettingsStructure.StartByte = 0x03; 
  DAT_NetworkSettingsStructure.bSubNetworkID = 0x36;
  DAT_NetworkSettingsStructure.PreambleByte = 0x55;
  DAT_NetworkSettingsStructure.StartByte = 0x0A; 
  
  return DAT_NetworkSettingsStructure;
}

/*******************************************************************************
* Function Name  : SCAN_Main_App_Switches
* Description    : Scans main app switch setting up the app structure
* 				   for testing purposes all values will be hardcoded for now
*                  in future use this functions will read all switches and set up
*                  all data accordingly 
* Input          : None
* Output         : None
* Return         : DAT_MainAppSettingsTypeDef - struct containg all app settings
*******************************************************************************/
DAT_MainAppSettingsTypeDef SCAN_Main_App_Switches( void )
{
  DAT_MainAppSettingsStructure.App_Switch = 0x31; // making this a crosswalk AB this should  
  DAT_MainAppSettingsStructure.bDuration_Switch = 0x03;
  return DAT_MainAppSettingsStructure;
}




/*******************************************************************************
* Function Name  : SCAN_Data_Init
* Description    : calls all other scan functions and returns to important values 
* 				   for firmware to run on boot up
* 				   for testing purposes all values will be hardcoded for now
*                  in future use this functions will read all switches and set up
*                  all data accordingly 
* Input          : None
* Output         : None
* Return         : SCAN_CheckDataTypeDef - struct containg important values for 
* 				   boot up
*******************************************************************************/
SCAN_CheckDataTypeDef SCAN_Data_Init( void )
{
  SCAN_Main_App_Switches();
  
  SCAN_Network_Switches();
  
  DAT_AB_IDStruct = DAT_AB_ID_Values();
  
  SCAN_CheckDataStructure.AB_ID_Flag = DAT_AB_IDStruct.AB_JOINED_FLAG ;
  
  SCAN_CheckDataStructure.AB_ID = DAT_AB_IDStruct.AB_ID_0;
  
  return SCAN_CheckDataStructure;
}



