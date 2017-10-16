/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : DAT_Access.c
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Jan 6, 2009
* Description        : your description
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "Includes.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static DAT_AB_IDTypeDef DAT_AB_IDStructure;
u8 bDAT_NumID_Registered;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : DAT_AB_ID_Values
* Description    : This function reads EEprom to see if any ID have been stored in
* 				   it or if the unit is part of any network.
* 				   for testing purposes all values will be hardcoded for now
*                  in future use this functions will read all switches and set up
*                  all data accordingly 
* Input          : None
* Output         : None
* Return         : DAT_AB_IDTypeDef - struct to the AB id
*******************************************************************************/
DAT_AB_IDTypeDef DAT_AB_ID_Values( void )
{
  //This function gets AB id from eeprom again for testing purposes this is hard coded for now 
  DAT_AB_IDStructure.AB_JOINED_FLAG = 0;
  DAT_AB_IDStructure.AB_ID_0 = 0xFFFF;
  return  DAT_AB_IDStructure;   
  
}

/*******************************************************************************
* Function Name  : Build_AB_ID_TableValues
* Description    : Writes ID to EE prom, ID position tables.
* 				   for testing purposes all values will be hardcoded for now
*                  in future use this functions will read all switches and set up
*                  all data accordingly 
* Input          : u16 wAB_ID - the id to be stored
* 				   u8 bID_Position - the position where this id is on the table 
* 				   provided by the supervisor
* 				   s8 bMyID_Position - a flag that tells the function that the id
* 				   to be stored is the device;s id so set up the neccesesary flag
* Output         : None
* Return         : None
*******************************************************************************/
void Build_AB_ID_TableValues( u16 wAB_ID, u8 bID_Position, s8 bMyID_Position )
{
  if( bMyID_Position == 1 ) // Record where in the network that own ID is
  {  
    DAT_AB_IDStructure.AB_ID_COUNT = bDAT_NumID_Registered;
    DAT_AB_IDStructure.MY_ID_POSITION = bID_Position;
    DAT_AB_IDStructure.AB_ALL_ID[bID_Position] = wAB_ID;
    DAT_AB_IDStructure.AB_ID_0 = wAB_ID;
  }
    
 /* if( bID_Position == 0 ) // this means is its own id and should go first is eeprom
  {
    DAT_AB_IDStructure.AB_JOINED_FLAG = 1;
    DAT_AB_IDStructure.AB_ID_0 = wAB_ID;
    DAT_AB_IDStructure.AB_ALL_ID[0] = wAB_ID;
  }*/                 // MAY NOT NEED THIS JUST SAVE THE ID IN WHATEVER ORDER THE POSITION SAYS TO DO IT IN
  else
  {
     DAT_AB_IDStructure.AB_ID_COUNT = bDAT_NumID_Registered; // might need that +1 after bDAT_NumID_Registered juan clean up 
     DAT_AB_IDStructure.AB_ALL_ID[bID_Position] = wAB_ID;    
  }
  
}


/*******************************************************************************
* Function Name  : ValidateNewRandomData
* Description    : Function validates any id that gets generated so that no same id gets
* 				   saved into memory. 
* Input          : u16 RandomData - the random ID that needs to be validated
* Output         : None
* Return         : s8 - -1 if ID belongs to GLB ID's
* 				   0 ID already belong to the network 
* 				   1 ID is not registered yet
* 				   2 ID is own device ID
* 				   3 ID is supervisors id
*******************************************************************************/
s8 ValidateNewRandomData( u16 RandomData )
{
  u8 i;
  
  if( (RandomData == mRF_PROT_GLB_SENDER_ID()) || (RandomData == mRF_PROT_GLB_RECEIVER_ID()) )
  {
    return -1;    
  }
  else if( RandomData == DAT_AB_IDStructure.AB_ID_0  )
  {
    return 2;
  }
  else if( RandomData == DAT_AB_IDStructure.AB_ALL_ID[0])
  {
    return 3;     
  }
  else
  {
    for( i=1;i<bDAT_NumID_Registered;i++)
    {
      if( RandomData == DAT_AB_IDStructure.AB_ALL_ID[i] )
      {
        return 0; 
      }
    }
  }
  return 1;
}
  
  

/*******************************************************************************
* Function Name  : ScanID_Values
* Description    : Function will read all ID values and return them so they can be used 
* 				   by other functions
* 				   for testing purposes all values will be hardcoded for now
*                  in future use this functions will read all switches and set up
*                  all data accordingly 
* Input          : None
* Output         : None
* Return         : DAT_AB_IDTypeDef - struct containing ID table
*******************************************************************************/
DAT_AB_IDTypeDef ScanID_Values( void )
{
  return DAT_AB_IDStructure;  
}




/*******************************************************************************
* Function Name  : s8 RemoveID_Value( u8 bID_Position )
* Description    : Removes the desired ID from id table and moves all other units
*                  up in the ID table, here i could update the ID count variable
* Input          : u8 bID_Position, the position on the table that needs to be erased
* Output         : None
* Return         : s8 - 0 didnt remove any ID 
* 					    1 removing ID other that supervisor ID 
* 					    2 remo
*******************************************************************************/
s8 RemoveID_Value( u8 bID_Position )
{
  //u8 i = bID_Position;
  if( bID_Position != 0 )
  {
    while( bID_Position < bDAT_NumID_Registered )// THIS MAY NEED TO BE <= 
    {
      DAT_AB_IDStructure.AB_ALL_ID[bID_Position] = DAT_AB_IDStructure.AB_ALL_ID[bID_Position+1];
      bID_Position++;
    }
    //bDAT_NumID_Registered--;
    return 1; 
  }
  else
  {
    while( bID_Position < bDAT_NumID_Registered )// THIS MAY NEED TO BE <= 
    {
      DAT_AB_IDStructure.AB_ALL_ID[bID_Position] = DAT_AB_IDStructure.AB_ALL_ID[bID_Position+1];
      
      if( DAT_AB_IDStructure.AB_ID_0 == DAT_AB_IDStructure.AB_ALL_ID[bID_Position] )
      {
        DAT_AB_IDStructure.MY_ID_POSITION = bID_Position;
      }
      
      bID_Position++;
    }
    
    
    if( DAT_AB_IDStructure.AB_ID_0 == DAT_AB_IDStructure.AB_ALL_ID[0] )
    {
      GLB_SupervisorFlag = 1; //this should only happen if that unit becomes the supervisor 
    }
    wAPP_STATE_RB_NEXT_TIME_OUT = wGLB_SYS_TICK_COUNTER; // take note where the systick is so we know when to send the next RB
    bAPP_STATE_RB_TIME_OUT_FLAG = 1;
    
    return 2;
  }

   
}



/*******************************************************************************
* Function Name  : WriteID_Status
* Description    : function that writes the status of ID to memory 
* 				   for testing purposes all values will be hardcoded for now
*                  in future use this functions will read all switches and set up
*                  all data accordingly 
* Input          : u8 bID_Position - ID position that needs to be written
*  			       u8 bData - status of id to to be written
* Output         : None
* Return         : s8 - returns 1 upon success
*******************************************************************************/
s8 WriteID_Status( u8 bID_Position, u8 bData )
{
  DAT_AB_IDStructure.bDAT_AB_ID_STATUS[bID_Position] = bData;
  return 1;
}
