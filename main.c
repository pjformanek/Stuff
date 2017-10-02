/*------------------------------------------------------------------------------
$File:		main.c
$Module:  	Main program body
$Prefix:  	MAIN
$Language:	ANSI C

$Description:

$Notes:

$Author:	Jramirez, Aug 22, 2008
--------------------------------------------------------------------------
$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
--------------------------------------------------------------------------
$End
----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_MAIN_c

/*------------------------------------------------------------------------------
------ I N C L U D E   F I L E S ------
------------------------------------------------------------------------------
*/


#include "GLB.h"
#include "MEM.h"
#include "BLD.h"
#include "Includes.h"

#ifdef cERR_ENABLE
#include "ERR.h"
#endif // ********** END OF cERR_ENABLE **********



#include "SYS.h"

#include "SW_Config.h"

#ifdef cGLB_GSM_ENABLE
#include "GSM_Telit_Config.h"
#endif // ********** END OF cGLB_GSM_ENABLE **********

#include "TimerManager.h"
#include "TimeManager.h"

#include "XPLAT_PROT.h"


//#ifdef cGLB_BT_ENABLE
#include "Bluetooth.h"
//#endif // ********** END OF cGLB_BT_ENABLE **********

#ifdef cGLB_LED_ENABLE
#include "LED.h"
#endif // ********** END OF cGLB_LED_ENABLE **********

#ifdef cGLB_RF_ENABLE
#include "RF_State.h"
#include "SX_Config.h"
#endif // ********** END OF cGLB_RF_ENABLE **********




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

void XWALK_Init( void );

////////////////////////////////////////////////////////////////////////////////
/* Private function prototypes -----------------------------------------------*/
//FOR DEBUGGING
////////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
////////////////////////////////////////////////////////////////////////////////



/*------------------------------------------------------------------------------
----- L O C A L   V A R I A B L E S -----
------------------------------------------------------------------------------
*/
u8 bAuxPBTimerMultiplier = 0;
u8 bAuxPBPreventTxOnRepeatFlag = 0;
u8 boff_tx_twice_flag = 0;
u32 lwAuxPBRefreshTimeStamp = 0;
u32 lwAuxPBTimeStamp = 0;
u8 bAuxPBPreventTxOffRepeatFlag = 0;
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
$Function: main
$Description: Main program.

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$Endc
*/
int main( void )
{
  Main_BootConfiguration();
  
  // inits debug serial port
  XPLAT_Init();
  
  SYS_Init();   // Init for internal system operations
#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE

#ifdef cGLB_RF_ENABLE
  printf("\nSx_Init\n");
  SX_Init();     // Init the semtech 
#endif // END OF cGLB_RF_ENABLE   
  printf("\nTIME_Init\n");
  TIME_Init();//has I2C1 config in here
#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE
  printf("\nTimer_Init\n");
  //PLL lock issues inside here
  TIMER_Init(); // start 100ms system tick 
#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE
#ifdef cGLB_LED_ENABLE
  printf("\nLED_Init\n");
  LED_Init(); // init LED module and turn off LEDs; needs I2C1 to be init (the init isnt in this code)
  
#endif // END OF cGLB_LED_ENABLE 
  
#ifdef cERR_ENABLE
  printf("\nErr_Init\n");
  ERR_Init(); // init error module
  //ERR_Dump(); // debug only
#endif // END OF cERR_ENABLE
  
  
#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE 
  
  
  
  
#ifdef cGLB_BT_ENABLE
  BT_Init(); // init Bluetooth module and turn the BT off
#endif // END OF cGLB_BT_ENABLE
  
#ifdef cGLB_GSM_ENABLE
  printf("\nTelit_Init\n");
  GSM_Telit_Init();
#endif // END OF cGLB_GSM_ENABLE

#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE
  
  printf("\nSwitch_Init\n");
  SW_Init();    // init the switches   
  
  __enable_interrupt();  
  
#ifdef cGLB_GSM_ENABLE
  
#if cGLB_NO_CONFIGS_FOR_GSM != 0
  printf("\nGSM setup\n");
  GSM_Telit_InitSetUp();
#endif // END OF cGLB_NO_CONFIGS_FOR_GSM
  
#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE
  
#endif // END OF cGLB_GSM_ENABLE
  
  
#ifdef cRF_Sync_Enable
  RF_State_Init();
#endif // END OF cRF_Sync_Enable
   
  
#ifdef cGLB_RF_ENABLE
  SX_SetRf( 0, RF_RECEIVER );
#endif // END OF cGLB_RF_ENABLE
  
#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE
#ifdef cGLB_BT_ENABLE
  u8 pp = 0; 
#endif // END OF cGLB_BT_ENABLE   
 
  SYS_OnResetNotification();
  
#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE 
#ifdef cGLB_PRODUCT_XWALK
  XWALK_Init();
#endif // END OF cGLB_PRODUCT_XWALK
  GPIO_lockout_Configuration(0);
  
  
   
  
  
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/    
#ifdef cGLB_PRODUCT_24HR
  // Switches Task
  SW_Task();
  global_TurnOnLights = 1;//turn on lights
  mGPIO_LED_SMT(OFF);
  while( 1 )
  {
#ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE   
    // Switches Task
    SW_Task();
#ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE       
    XPLAT_PROT_Task();
#ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE       
    XPLAT_Task();
    
#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE
#ifdef cGLB_LED_ENABLE
    LED_TASK();
#endif // END OF cGLB_LED_ENABLE
#ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE
    SYS_Task();

#ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
#endif // END OF cWD_ENABLE
#ifdef cAllow_Sleep
    // deint the switches in order to save power
    SW_DeInit( FALSE );
    
    SYS_EnterSleepMode();
    
    // reinit the switches so that they are set properly 
    // after sleep
    SW_DeInit( TRUE );
#endif // END OF cAllow_Sleep  
  
  }
#endif //end 24hour
  
#ifdef cGLB_PRODUCT_XWALK
  RF_Pre_Send_A_Packet();
  global_TurnOnLights = 2;//turn off lights
  vu8 bPedOkToGoFlag = 1;
  u32 lwAuxPBTxOnTimeStamp = TIMER_GetTimeStamp( 0 );
  u32 lwAuxPBTxOffTimeStamp = TIMER_GetTimeStamp( 0 );
  u8 bAuxPBTxOnFlag = 0;
  u8 bAuxPBTxOffCount = 0;
  u8 bAuxPBTxOnCount = 0;
  #ifdef cWD_ENABLE
  SYS_KICK_THE_DOG(0);
  #endif // END OF cWD_ENABLE
  SYS_ResetCount( 1 );
  lwPedDelayTimeStamp = TIMER_GetTimeStamp( 0 );
//  SYS_Set_PED_Status( FALSE );
//  SYS_Set_AUX_PED_Status( FALSE );
//  LED_TASK(); // make lights off right away   
  //SYS_Test(); // for Jim only 
  while( 1 )
  {
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    //printf("\r\n%i\r\n",global_FlashDuration);
    //mUSART_DEBUG_WAIT_AND_SEND('W');
    SW_Task();
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    //mUSART_DEBUG_WAIT_AND_SEND('P');
    //USART1Output();
    XPLAT_PROT_Task();
    //USART1Input();
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    //mUSART_DEBUG_WAIT_AND_SEND('x');
    //USART1Output();
    XPLAT_Task();
    SYS_Task();
    //USART1Input();
    //mUSART_DEBUG_WAIT_AND_SEND('V');
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    // if unit is on training mode or other mode then block those messages   


        
      //#ifdef cGLB_RF_ENABLE

          //global_TurnOnLights = 1;         
          //LED_TASK(); // make lights flash right away 
          
          ////////////////////////////////////////custom////////////////
          //          static u8 cuztum = 1;
          //          cuztum ^= 1;
          //          if (cuztum){
          //            
          //            global_Flash_Forever = 1;
          //            global_TurnOnLights = 1;
          //            LED_TASK(); // make lights flash right away
          //          }
          //          else{
          //            global_Flash_Forever = 0;
          //            global_TurnOnLights = 2;//turn off leds
          //            LED_TASK(); // make lights flash right away
          //          }
          ///////////////////////////////////////custom/////////////////
                
    #ifdef cGLB_Reservice_Delay
      if (TIMER_HasTimeStampElapsed( lwPedDelayTimeStamp, 
                                     (global_LocalFlashDuration * 10) + 
                                     (global_NetworkAddress*15))){
        bPedOkToGoFlag = 1;
      }
      if( bPedOkToGoFlag == 0 ){
        SYS_Set_PED_Status( FALSE );
      }      
    #else
      if (TIMER_HasTimeStampElapsed( lwPedDelayTimeStamp, 20)){//2 second PED holdoff
        bPedOkToGoFlag = 1;
      }
      if( bPedOkToGoFlag == 0 ){
        SYS_Set_PED_Status( FALSE );
      }      
    #endif
    /////////////////////////// PED ///////////////////////////////////
    
    if( SYS_Get_PED_Status() && bPedOkToGoFlag == 1){
    //#endif //  END OF cGLB_RF_ENABLE
      
        // clear the PED flag 
      SYS_Set_PED_Status( FALSE );
      
      #ifdef cWD_ENABLE
      SYS_KICK_THE_DOG(0);
      #endif // END OF cWD_ENABLE
      if ( RF_State_Get_Busy_Flag() != cRF_State_Busy_Flag ){
        RF_Pre_Send_A_Packet();
        RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Own_Duration,0,0 );
          //mUSART_DEBUG_WAIT_AND_SEND('b');
        global_TurnOnLights = 1;
        #ifdef cGLB_BT_ENABLE
        BT_On();
        USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
        printf("\nped");
        USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
        #endif
        printf("\nped");
        //mUSART_DEBUG_WAIT_AND_SEND('M');
        LED_TASK(); // make lights flash right away
        bPedOkToGoFlag = 0;
      }
      else {
          //mUSART_DEBUG_WAIT_AND_SEND('c');
        static u8 FailCount = 0;
        FailCount++;
        #ifdef cGLB_BT_ENABLE
        BT_On();
        USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
        printf("\nTx Busy");
        USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
        #endif
        printf("\nTx Busy"); // debug only
        SYS_Set_PED_Status( TRUE );
        if ( FailCount == 5){
          global_TurnOnLights = 1;
          //mUSART_DEBUG_WAIT_AND_SEND('M');
          #ifdef cGLB_BT_ENABLE
          BT_On();
          USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
          printf("\nped");
          USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
          #endif
          printf("\nped");
          LED_TASK(); // make lights flash right away
        }
        else if ( FailCount >= 15 ){
          RF_State_Set_Busy_Flag( cRF_State_NOT_Busy_Flag );
          FailCount = 0;
          SYS_Set_PED_Status( FALSE );
        }
      }
    }
    
    /////////////////////////// W16 / W13/////////////////////////////////////////////////
    
    //cGPIO_AUX_PB_PIN
    //cGPIO_AUX_PB_GPIOx
    if (!GPIO_ReadInputDataBit( cGPIO_W13_GPIOx, cGPIO_W13_PIN )){ //w13 in
       
      if (!GPIO_ReadInputDataBit( cGPIO_W16_GPIOx, cGPIO_W16_PIN )){ // w16 in
        //////////////////////////////// aux  ///////////////////////////////////
        if (!GPIO_ReadInputDataBit( cGPIO_AUX_PB_GPIOx, cGPIO_AUX_PB_PIN )){ //check aux ped
          if( TIMER_HasTimeStampElapsed( lwAuxPBTxOnTimeStamp, 2 *cTIMER_Tick_Interval_1s )){//every sec
            if ( RF_State_Get_Busy_Flag() != cRF_State_Busy_Flag ){
              static u8 abcdefg = 0;
              RF_Pre_Send_A_Packet();
              #ifdef cGLB_DUAL_TX
              u8 popo[2] = {0, 0};
              popo[0] = (global_TX_ID & 0x00FF);
              popo[1] = ((global_TX_ID & 0xFF00) >>8);
              if(popo[0] || popo[1]){
                RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,popo,2 );
              }
              else{
                RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,0,0 );
              }
              #else
              RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,0,0 );
              #endif
              global_TurnOnLights = 3;
              lwAuxPBTxOnTimeStamp = TIMER_GetTimeStamp( 0 );
              printf("\nw16-txon");
              abcdefg++;
              if(abcdefg >= 4){
                GPIO_WriteBit(cGPIO_RELAY_PORT, cGPIO_PE13, ecGPIO_BitAction_CLEAR); //shut off power
              }
            }
            else{
              static u8 bFailzCount = 0;
              bFailzCount++;
              printf("\nTxBusy"); // debug only
              if ( bFailzCount >= 15 ){
                RF_State_Set_Busy_Flag( cRF_State_NOT_Busy_Flag );
                bFailzCount = 0;
              }  
            }
          }
        }
        else{
          if( TIMER_HasTimeStampElapsed( lwAuxPBTxOffTimeStamp, 2*cTIMER_Tick_Interval_1s )){//every sec
            if ( RF_State_Get_Busy_Flag() != cRF_State_Busy_Flag ){
              static int gfedcba = 0;
              RF_Pre_Send_A_Packet();
              #ifdef cGLB_DUAL_TX
              u8 popo[2] = {0, 0};
              popo[0] = (global_TX_ID & 0x00FF);
              popo[1] = ((global_TX_ID & 0xFF00) >>8);
              if(popo[0] || popo[1]){
                RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,popo,2 );
              }
              else{
                RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,0,0 );
              }
              #else
              RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,0,0 );
              #endif
              global_TurnOnLights = 2;
              lwAuxPBTxOffTimeStamp = TIMER_GetTimeStamp( 0 );
              bAuxPBTxOffCount++;
              printf("\nw16-txoff");
              gfedcba++;
              if(gfedcba >= 4){
                GPIO_WriteBit(cGPIO_RELAY_PORT, cGPIO_PE13, ecGPIO_BitAction_CLEAR); //shut off power
              }
            }
            else{
              static u8 bFcunt = 0;
              bFcunt++;
              printf("\nTxBusy"); // debug only
              if ( bFcunt == 5 ){
                global_TurnOnLights = 2;
                //turn off lights
              }
              if ( bFcunt >= 20 ){
                RF_State_Set_Busy_Flag( cRF_State_NOT_Busy_Flag );
                bFcunt = 0;
              }  
            }
          }
        }
     //end aux   
      }
      else{
        static u8 barfing = 0;
        SYS_Set_PED_Status( TRUE );
        barfing++;
        if(barfing >=5){
          GPIO_WriteBit(cGPIO_RELAY_PORT, cGPIO_PE13, ecGPIO_BitAction_CLEAR); //shut off power
        }
      }
    }
    else if (!GPIO_ReadInputDataBit( cGPIO_W16_GPIOx, cGPIO_W16_PIN )){//w16 is low
      if (!GPIO_ReadInputDataBit( cGPIO_AUX_PB_GPIOx, cGPIO_AUX_PB_PIN )){// chec aux is it low
        if( TIMER_HasTimeStampElapsed( lwAuxPBTxOnTimeStamp, 15*cTIMER_Tick_Interval_1s )|| !bAuxPBTxOnFlag || bAuxPBTxOnCount){//every 15 sec
          //repeat every 15 seconds
          bAuxPBTxOffCount = 0;
          if ( RF_State_Get_Busy_Flag() != cRF_State_Busy_Flag ){
            RF_Pre_Send_A_Packet();
            #ifdef cGLB_DUAL_TX
            u8 popo[2] = {0, 0};
            popo[0] = (global_TX_ID & 0x00FF);
            popo[1] = ((global_TX_ID & 0xFF00) >>8);
            if(popo[0] || popo[1]){
              RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,popo,2 );
            }
            else{
              RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,0,0 );
            }
            #else
            RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,0,0 );
            #endif
            global_TurnOnLights = 3;
            lwAuxPBTxOnTimeStamp = TIMER_GetTimeStamp( 0 );
            #ifdef cGLB_BT_ENABLE
            BT_On();
            USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
            printf("\nw16-txon");
            USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
            #endif
            printf("\nw16-txon");
            if( !bAuxPBTxOnFlag ){
              bAuxPBTxOnCount = 1;
            }
            else{
              bAuxPBTxOnCount = 0;
            }
            bAuxPBTxOnFlag = 1;
          }
          else{
            static u8 bFailzCount = 0;
            bFailzCount++;
            #ifdef cGLB_BT_ENABLE
            BT_On();
            USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
            printf("\nTxBusy");
            USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
            #endif
            printf("\nTxBusy"); // debug only
            if ( bFailzCount >= 15 ){
              RF_State_Set_Busy_Flag( cRF_State_NOT_Busy_Flag );
              bFailzCount = 0;
            }  
          }
        }
      }
      else{
        if (bAuxPBTxOnFlag == 1 || bAuxPBTxOffCount != 0 ){
          if( TIMER_HasTimeStampElapsed( lwAuxPBTxOffTimeStamp, 5*cTIMER_Tick_Interval_1s )|| !bAuxPBTxOffCount){//every 5 sec
            bAuxPBTxOnCount = 0;
            if ( RF_State_Get_Busy_Flag() != cRF_State_Busy_Flag ){
              RF_Pre_Send_A_Packet();
              #ifdef cGLB_DUAL_TX
              u8 popo[2] = {0, 0};
              popo[0] = (global_TX_ID & 0x00FF);
              popo[1] = ((global_TX_ID & 0xFF00) >>8);
              if(popo[0] || popo[1]){
                RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,popo,2 );
              }
              else{
                RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,0,0 );
              }
              #else
              RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,0,0 );
              #endif
              global_TurnOnLights = 2;
              lwAuxPBTxOffTimeStamp = TIMER_GetTimeStamp( 0 );
              bAuxPBTxOffCount++;
              #ifdef cGLB_BT_ENABLE
              BT_On();
              USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
              printf("\mw16-txoff");
              USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
              #endif
              printf("\nw16-txoff");
              bAuxPBTxOnFlag = 0;
              if( bAuxPBTxOffCount == 5 ){
                bAuxPBTxOffCount = 0;
              }
            }
            else{
              static u8 bFcunt = 0;
              bFcunt++;
              #ifdef cGLB_BT_ENABLE
              BT_On();
              USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
              printf("\nTxBusy");
              USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
              #endif
              printf("\nTxBusy"); // debug only
              if ( bFcunt == 5 ){
                global_TurnOnLights = 2;
              }
              if ( bFcunt >= 20 ){
                RF_State_Set_Busy_Flag( cRF_State_NOT_Busy_Flag );
                bFcunt = 0;
              }  
            }
          }
        }
      }      
    }//************************************

    
//////////////////////////////////////////////////////////////////////////
////////////////////////////////// W16  ////////////////////////////////////
//    if (!GPIO_ReadInputDataBit( cGPIO_W16_GPIOx, cGPIO_W16_PIN )){
//      if( TIMER_HasTimeStampElapsed( lwAuxPBTxOnTimeStamp, 15*cTIMER_Tick_Interval_1s )|| !bAuxPBTxOnFlag || bAuxPBTxOnCount){//every 15 sec
//        //repeat every 15 seconds
//        bAuxPBTxOffCount = 0;
//        if ( RF_State_Get_Busy_Flag() != cRF_State_Busy_Flag ){
//          RF_Pre_Send_A_Packet();
//          #ifdef cGLB_DUAL_TX
//          u8 popo[2] = {0, 0};
//          popo[0] = (global_TX_ID & 0x00FF);
//          popo[1] = ((global_TX_ID & 0xFF00) >>8);
//          if(popo[0] || popo[1]){
//            RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,popo,2 );
//          }
//          else{
//            RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,0,0 );
//          }
//          #else
//          RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,0,0 );
//          #endif
//          global_TurnOnLights = 3;
//          lwAuxPBTxOnTimeStamp = TIMER_GetTimeStamp( 0 );
//          #ifdef cGLB_BT_ENABLE
//          BT_On();
//          USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
//          printf("\nw16-txon");
//          USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
//          #endif
//          printf("\nw16-txon");
//          if( !bAuxPBTxOnFlag ){
//            bAuxPBTxOnCount = 1;
//          }
//          else{
//            bAuxPBTxOnCount = 0;
//          }
//          bAuxPBTxOnFlag = 1;
//        }
//        else{
//          static u8 bFailzCount = 0;
//          bFailzCount++;
//          #ifdef cGLB_BT_ENABLE
//          BT_On();
//          USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
//          printf("\nTxBusy");
//          USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
//          #endif
//          printf("\nTxBusy"); // debug only
//          if ( bFailzCount >= 15 ){
//            RF_State_Set_Busy_Flag( cRF_State_NOT_Busy_Flag );
//            bFailzCount = 0;
//          }  
//        }
//      }
//    }
//    else{
//      if (bAuxPBTxOnFlag == 1 || bAuxPBTxOffCount != 0 ){
//        if( TIMER_HasTimeStampElapsed( lwAuxPBTxOffTimeStamp, 5*cTIMER_Tick_Interval_1s )|| !bAuxPBTxOffCount){//every 5 sec
//          bAuxPBTxOnCount = 0;
//          if ( RF_State_Get_Busy_Flag() != cRF_State_Busy_Flag ){
//            RF_Pre_Send_A_Packet();
//          #ifdef cGLB_DUAL_TX
//            u8 popo[2] = {0, 0};
//            popo[0] = (global_TX_ID & 0x00FF);
//            popo[1] = ((global_TX_ID & 0xFF00) >>8);
//            if(popo[0] || popo[1]){
//              RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,popo,2 );
//            }
//            else{
//              RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,0,0 );
//            }
//          #else
//            RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,0,0 );
//          #endif
//            global_TurnOnLights = 2;
//            lwAuxPBTxOffTimeStamp = TIMER_GetTimeStamp( 0 );
//            bAuxPBTxOffCount++;
//            #ifdef cGLB_BT_ENABLE
//            BT_On();
//            USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
//            printf("\mw16-txoff");
//            USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
//            #endif
//            printf("\nw16-txoff");
//            bAuxPBTxOnFlag = 0;
//            if( bAuxPBTxOffCount == 5 ){
//              bAuxPBTxOffCount = 0;
//            }
//          }
//          else{
//            static u8 bFcunt = 0;
//            bFcunt++;
//            #ifdef cGLB_BT_ENABLE
//            BT_On();
//            USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
//            printf("\nTxBusy");
//            USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
//            #endif
//            printf("\nTxBusy"); // debug only
//            if ( bFcunt == 5 ){
//              global_TurnOnLights = 2;
//            }
//            if ( bFcunt >= 20 ){
//              RF_State_Set_Busy_Flag( cRF_State_NOT_Busy_Flag );
//              bFcunt = 0;
//            }  
//          }
//        }
//      }
//    }
//////////////////////////////////////////////////end w16///////////////////////////////////
    
      //bAuxPBTxOffFlag = 0;
//    if( TIMER_HasTimeStampElapsed( lwAuxPBTimeStamp, bAuxPBTimerMultiplier*cTIMER_Tick_Interval_1s ) )// 0-2 sec
//    {
//      if (GPIO_ReadInputDataBit( cGPIO_AUX_PB_GPIOx, cEXTI_LINE_AUX_PB_PIN )){
//        //if (SYS_Get_AUX_PED_Status()){//false then transmit "OFF"
//        //SYS_Set_AUX_PED_Status(FALSE);
//        if ( !bAuxPBPreventTxOffRepeatFlag ){
//          bAuxPBTimerMultiplier = 1;
//          SYS_Set_OLDSZ_Status(0x40);
//          bAuxPBPreventTxOffRepeatFlag = 1;
//          bAuxPBPreventTxOnRepeatFlag = 0;
//          boff_tx_twice_flag = 12;
//          lwAuxPBRefreshTimeStamp = TIMER_GetTimeStamp( 0 );
//          //RTC_I2C_ByteWrite( 0x05, 0x0D );
//          if (!GPIO_ReadInputDataBit( cGPIO_REMOTE_GPIOx, cGPIO_REMOTE_PIN )){
//            bAuxPBPreventTxOffRepeatFlag = 0;
//          }
//        }
//        else{
//          if (boff_tx_twice_flag){
//            if( TIMER_HasTimeStampElapsed( lwAuxPBRefreshTimeStamp, 20*cTIMER_Tick_Interval_1s ) )
//            {
//              lwAuxPBRefreshTimeStamp = TIMER_GetTimeStamp( 0 );
//              boff_tx_twice_flag -= 1;
//              printf("\ntx_off\n");
//              SYS_Set_OLDSZ_Status(0x40);
//            }
//          }
//        }
//        //}
//      }
//      else{
//        //if (!SYS_Get_AUX_PED_Status()){//true then transmit "ON"
//        //  SYS_Set_AUX_PED_Status(TRUE);
//        if( !bAuxPBPreventTxOnRepeatFlag ){
//          bAuxPBTimerMultiplier = 2;
//          SYS_Set_OLDSZ_Status(0x80);
//          bAuxPBPreventTxOnRepeatFlag = 1;
//          bAuxPBPreventTxOffRepeatFlag = 0;
//          //RTC_I2C_ByteWrite( 0x04, 0x0D );
//          if (!GPIO_ReadInputDataBit( cGPIO_REMOTE_GPIOx, cGPIO_REMOTE_PIN )){
//            bAuxPBPreventTxOnRepeatFlag = 0;
//          }
//          lwAuxPBRefreshTimeStamp = TIMER_GetTimeStamp( 0 );
//        }
//        else{
//          if( TIMER_HasTimeStampElapsed( lwAuxPBRefreshTimeStamp, 10*cTIMER_Tick_Interval_1m ) )
//          {
//            bAuxPBPreventTxOnRepeatFlag = 0;
//          }
//        }
//        //}
//      }
//      lwAuxPBTimeStamp = TIMER_GetTimeStamp( 0 );
//    }
    //////////////////// end aux  /////////////////////////
    #ifdef cGLB_PRODUCT_OLDSZ_READER 
    if( (SYS_Get_OLDSZ_Status()==0x80 || SYS_Get_OLDSZ_Status()==0x40)
       && (RF_State_Get_Busy_Flag() != cRF_State_Busy_Flag)){
         
      #ifdef cWD_ENABLE
      SYS_KICK_THE_DOG(0);
      #endif // END OF cWD_ENABLE
      if( SYS_Get_OLDSZ_Status() == 0x80){
        RF_Pre_Send_A_Packet();
        //XPLAT_Packet_Builder( cXPLAT_CMD_ID_Flash_On, cXPLAT_STATUS_ACK, bSeq, 0 , 0, cSX_RF_ENABLE ); 
        RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_On,0,0 );
        SYS_Set_OLDSZ_Status(0x20);
        //printf("!\n");
        global_TurnOnLights = 3;
      }
      else{
          RF_Pre_Send_A_Packet();
          RF_State_Resend_Flash_Message( cXPLAT_CMD_ID_Flash_Off,0,0 );
          SYS_Set_OLDSZ_Status(0x10);
          global_TurnOnLights = 2;
      }
    }
    else if ( (SYS_Get_OLDSZ_Status()==0x80 || SYS_Get_OLDSZ_Status()==0x40)
             && (RF_State_Get_Busy_Flag() == cRF_State_Busy_Flag)){
        static u8 bFailCount = 0;
        bFailCount++;
        printf("\nTxBusy"); // debug only
        #ifdef cWD_ENABLE
        SYS_KICK_THE_DOG(0);
        #endif // END OF cWD_ENABLE 
        if ( bFailCount >= 100 ){
          RF_State_Set_Busy_Flag( cRF_State_NOT_Busy_Flag );
          bFailCount = 0;
        }                         
    }
             
    #endif // END OF cGLB_PRODUCT_OLDSZ_READER
    
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE 
    #ifdef cGLB_LED_ENABLE
    //mUSART_DEBUG_WAIT_AND_SEND('L');
    LED_TASK();
    #endif // END OF cGLB_LED_ENABLE
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    //mUSART_DEBUG_WAIT_AND_SEND('S');
    #ifdef cGLB_RF_ENABLE
    // SEmtech radio tasks
    //mUSART_DEBUG_WAIT_AND_SEND('X');
    SX_Task();
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    #ifdef cRF_Sync_Enable
    //mUSART_DEBUG_WAIT_AND_SEND('R');
    RF_State_Task();
    //mUSART_DEBUG_WAIT_AND_SEND('F');
    #endif // END OF cRF_Sync_Enable
    #endif // END OF cGLB_RF_ENABLE
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    
    #ifdef cAllow_Sleep
    // deint the switches in order to save power
    //mUSART_DEBUG_WAIT_AND_SEND('e');
    SW_DeInit( FALSE );
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE 
    //mUSART_DEBUG_WAIT_AND_SEND('m');
    SYS_EnterSleepMode();
    // reinit the switches so that they are set properly 
    // after sleep
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    //mUSART_DEBUG_WAIT_AND_SEND('M');
    SW_DeInit( TRUE );
    #endif // END OF cAllow_Sleep 
  }
#endif // END OF cGLB_PRODUCT_XWALK
} // **************** END OF MAIN ****************


/*------------------------------------------------------------------------------
$Function: XWALK_Init
$Description: Inits anything that is needed for the 
              XWALK product
$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
#ifdef cGLB_PRODUCT_XWALK
void XWALK_Init( void )
{
  //mGBL_XWALK_SET_DEV_ID(0xFF, 0xFF);
  u16 t = mGLB_XWALK_GET_DEV_ID();
  
  RF_State_Dev_Id_Set( t );
}
#endif // END OF cGLB_PRODUCT_XWALK








#ifdef  DEBUG
/*------------------------------------------------------------------------------
$Function: assert_failed
$Description: Reports the name of the source file and the source line number
where the assert_param error has occurred.

$Inputs: u8* file: file: pointer to the source file name
u32 line: line: assert_param error line source number
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void assert_failed(u8* file, u32 line)
{
  printf("\r\n\r Wrong parameter value detected on\r\n");
  printf("       file  %s\r\n", file);
  printf("       line  %d\r\n", line);
  //Infinite loop
  while (1)
  {
  }
}
#endif




//FOR DEBUGGING/////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------------
$Function: PUTCHAR_PROTOTYPE
$Description: Retargets the C library printf function to the USART.

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/

PUTCHAR_PROTOTYPE
{
  
  //Place your implementation of fputc here
  //e.g. write a character to the USART
#ifdef cHW_DEV_BOARD
  
  if( USART_EnableUsartX_Printf == cUSART_USART_2_ENABLE )
  {
    USART_SendData(USART2, (u8) ch);
    
    // Loop until the end of transmission
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
    {
    }
  }
  else if( USART_EnableUsartX_Printf == cUSART_USART_1_ENABLE )
  {
    USART_SendData(USART1, (u8) ch);
    
    // Loop until the end of transmission
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
    }
    
  }
  else
  {
    USART_SendData(USART3, (u8) ch);
    
    // Loop until the end of transmission
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
    {
    }
  }
  
#else
  if( USART_EnableUsartX_Printf == cUSART_USART_2_ENABLE )
  {
    USART_SendData(USART2, (u8) ch);
    
    // Loop until the end of transmission
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
    {
    }
  }
  else if( USART_EnableUsartX_Printf == cUSART_USART_3_ENABLE )
  {
    USART_SendData(USART3, (u8) ch);
    
    // Loop until the end of transmission
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
    {
    }
    
  }
  else if( USART_EnableUsartX_Printf == cUSART_USART_4_ENABLE )
  {
    USART_SendData(UART4, (u8) ch);
    
    // Loop until the end of transmission
    while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET)
    {
    }
  }
  else
  {
    USART_SendData(USART1, (u8) ch);
    
    // Loop until the end of transmission
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
    }
  }
#endif
  return ch;
}


