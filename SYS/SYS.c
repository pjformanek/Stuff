/*------------------------------------------------------------------------------
$File:		SYS.c
$Module:  	System Managment
$Prefix:  	SYS
$Language:	ANSI C

$Description:

$Notes:

$Author:	Jramirez, Jul 09, 2010
                PFormanek, Oct 06, 2017
--------------------------------------------------------------------------
$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
--------------------------------------------------------------------------
$End
----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_SYS_c

/*------------------------------------------------------------------------------
------ I N C L U D E   F I L E S ------
------------------------------------------------------------------------------
*/
#include "GLB.h"
#include "MEM.h"
#include "ERR.h"
#include "LED.h"
#include "Delay.h"
#include "platform_config.h"
#include "GSM_Telit_Config.h"
#include "GPIO_Config.h"
#include "TimerManager.h"
#include "XPLAT_Prot.h"
#include "USART_Config.h"
#include "RTC_I2C_Config.h"
#include "RF_State.h"
#include "StorageManager.h"
#include "I2C_Config.h"
#include "Bluetooth.h"

#include "TimeManager.h"

#include "SYS.h"
#include "SW_Config.h"

/*------------------------------------------------------------------------------
----- M A C R O   D E F I N I T I O N S -----
------------------------------------------------------------------------------
*/
#define mSYS_TURN_BULK_CHARGING()               mGPIO_SOLAR_LDO(ON)       
#define mSYS_TURN_LDO_CHARGING()                  mGPIO_SOLAR_LDO(OFF)  

/*------------------------------------------------------------------------------
----- D E F I N I T I O N S -----
------------------------------------------------------------------------------
*/

/*------------------------------------------------------------------------------
----- C O N S T A N T S -----
------------------------------------------------------------------------------
*/

#define cSYS_CHECK_VOLTAGES_TIMEOUT           (15*cTIMER_Tick_Interval_1s)
#define cSYS_READ_VOLTAGES_TIMEOUT            (30*cTIMER_Tick_Interval_1m)

#ifdef cIWDG_ENABLE
#define cSYS_IWDG_RELOAD_VALUE                3750               // This two values give me a
#define cSYS_IWDG_PRESCALER                   IWDG_Prescaler_32 // time out of 1s roughly
// set the time out to reload the IWDG timer really early so that we dont cause a reset
#define cSYS_IWDG_TIMEOUT_TO_RELOAD           (2*cTIMER_Tick_Interval_1s)
#endif

#define cSYS_DebugMode_Timeout                 (5*cTIMER_Tick_Interval_1s)


// Defines for the LED flash durations all values are in units of seconds

#define cSYS_FLASH_DURATION_0              5
#define cSYS_FLASH_DURATION_1              15
#define cSYS_FLASH_DURATION_2              18
#define cSYS_FLASH_DURATION_3              20
#define cSYS_FLASH_DURATION_4              25
#define cSYS_FLASH_DURATION_5              30
#define cSYS_FLASH_DURATION_6              35
#define cSYS_FLASH_DURATION_7              40
#define cSYS_FLASH_DURATION_8              45
#define cSYS_FLASH_DURATION_9              50
#define cSYS_FLASH_DURATION_10             60
#define cSYS_FLASH_DURATION_11             120
#define cSYS_FLASH_DURATION_12             180
#define cSYS_FLASH_DURATION_13             240
#define cSYS_FLASH_DURATION_14             300
#define cSYS_FLASH_DURATION_15             360

#define cEE_SYS_Dimming_Ceiling            0xCE
#define cEE_SYS_Dimming_Night              0xCF
#define cEE_SYS_Dimming_OnOff              0xD0
/*------------------------------------------------------------------------------
----- L O C A L   T Y P E S -----
------------------------------------------------------------------------------
*/

/*------------------------------------------------------------------------------
----- L O C A L   F U N C T I O N   P R O T O T Y P E S -----
------------------------------------------------------------------------------
*/


void Local_SYS_CheckVoltages( void );
void Local_SYS_ReadVoltages( void );

#ifdef cIWDG_ENABLE
u8 Local_SYS_StartInWatchDogTimer( u16 wReloadValue, u8 bIWDG_Prescaler );
u8 Local_SYS_IsTimeToReloadIWDG( void );
#endif

void GPIO_LED_SMTConfiguration( void );
void GPIO_ADCxConfiguration( void );
void GPIO_RS232_Interface_Configuration( void );
void GPIO_PED_Configuration( void );
void EXTINT_PED_Configuration( void );
void NVIC_PED_Configuration( FunctionalState NewState );
void GPIO_LED_SMTConfiguration( void );
void GPIO_12V_DC_DC_Configuration( void );
void GPIO_SOLAR_Bulk_Chage_Configuration( void );

/*------------------------------------------------------------------------------
----- L O C A L   V A R I A B L E S -----
------------------------------------------------------------------------------
*/
#ifdef cIWDG_ENABLE
static u32 lwIWDG_TimeStamp = 0;
#endif
static u8 bDimmingCeiling = 255;
//static u8 bDimmingNight = 2;
static u8 bDimmingOnOff = 1;

static bool boPedBtnStatus = FALSE;
static bool boSpeedBtnStatus = FALSE;//speed trigger
static bool boAuxBtnStatus = FALSE;
volatile static u8 OLDSZStatus = 0;

static u32 lwCheckVoltagesTimeStamp = 0;
static u32 lwReadVoltagesTimeStamp = 0;

static bool boDebug_Flag = FALSE;
static u32 lwDebug_TimeStamp = 0;

static u8 bState = 0;  // this should only be used locally in ReadVoltages it was put here to test charging nothing else

static bool boSYS_Sleep_Type_Flag = FALSE;

vu32 someTimeStamp = 0;
/*------------------------------------------------------------------------------
----- G L O B A L   V A R I A B L E S -----
------------------------------------------------------------------------------
*/

/*------------------------------------------------------------------------------
----- L O C A L   F U N C T I O N S -----
------------------------------------------------------------------------------
*/



/*------------------------------------------------------------------------------
    $Function: GPIO_ADCxConfiguration
    $Description:

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void GPIO_ADCxConfiguration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable ADC1 and GPIOC clock */
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_ADCx_SOLAR_ADC | cRCC_APBxPeriph_GPIO_SOLAR_ADC, ENABLE );
#ifndef cGLB_PRODUCT_FOB //*PF
  // Configure PC1 (ADC1 Channel1) as analog input for VsolSen---------------
  GPIO_InitStructure.GPIO_Pin = cGPIO_SOLAR_ADC_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(cGPIO_SOLAR_ADC_GPIOx, &GPIO_InitStructure);
#endif  // END OF cGLB_PRODUCT_FOB

  /* Enable ADC1 and GPIOC clock */
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_ADCx_BATT_ADC | cRCC_APBxPeriph_GPIO_BATT_ADC, ENABLE );

  /* Configure PC0 (ADC1 Channel0) as analog input for VbatSen---------------*/
  GPIO_InitStructure.GPIO_Pin = cGPIO_BATT_ADC_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(cGPIO_BATT_ADC_GPIOx, &GPIO_InitStructure);


}

/*------------------------------------------------------------------------------
    $Function: GPIO_RS232_Interface_Configuration
    $Description:

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void GPIO_RS232_Interface_Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_RS232_INTERFACE_ENABLE, ENABLE );

  GPIO_InitStructure.GPIO_Pin = cGPIO_RS232_INTERFACE_ENABLE_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_RS232_INTERFACE_ENABLE_PIN_GPIOx, &GPIO_InitStructure );

  GPIO_WriteBit( cGPIO_RS232_INTERFACE_ENABLE_PIN_GPIOx, cGPIO_RS232_INTERFACE_ENABLE_PIN, ecGPIO_BitAction_CLEAR );
  
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_RS232_INTERFACE_FORCE_ON, ENABLE );

  GPIO_InitStructure.GPIO_Pin = cGPIO_RS232_INTERFACE_FORCE_ON_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_RS232_INTERFACE_FORCE_ON_PIN_GPIOx, &GPIO_InitStructure );

  GPIO_WriteBit( cGPIO_RS232_INTERFACE_FORCE_ON_PIN_GPIOx, cGPIO_RS232_INTERFACE_FORCE_ON_PIN, ecGPIO_BitAction_SET );
  
}

/*------------------------------------------------------------------------------
    $Function: GPIO_PED_Configuration
    $Description: GPIO configs for the ped button 

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void GPIO_PED_Configuration( void ) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_PED , ENABLE );
  
  /* Configure PA.8 pin as internal pull up */
  GPIO_InitStructure.GPIO_Pin = cGPIO_PED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  
 
  GPIO_Init( cGPIO_PED_PIN_GPIOx, &GPIO_InitStructure );
    
  EXTINT_PED_Configuration();
  
  NVIC_PED_Configuration( ENABLE );
}

void GPIO_W16_Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_W16 , ENABLE );
  
  /* Configure test pin PB.2 as internal pull up */
  GPIO_InitStructure.GPIO_Pin = cGPIO_W16_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init( cGPIO_W16_GPIOx, &GPIO_InitStructure );
}
void GPIO_W13_Configuration( void ){
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_W13 , ENABLE );
  
  /* Configure test pin PB.15 as internal pull up */
  GPIO_InitStructure.GPIO_Pin = cGPIO_W13_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init( cGPIO_W13_GPIOx, &GPIO_InitStructure );
}
void GPIO_JW_Configuration( void ){
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_Boot_Option_JW , ENABLE );
  
  /* Configure test pin PB.13 as internal pull up */
  GPIO_InitStructure.GPIO_Pin = cGPIO_Boot_Option_JW_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init( cGPIO_Boot_Option_JW_GPIOx, &GPIO_InitStructure );
}
/*------------------------------------------------------------------------------
    $Function: GPIO_PED_Configuration
    $Description: GPIO configs for the ped button 

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void GPIO_AUX_PB_Configuration( void ) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_AUX_PB , ENABLE );
  
  /* Configure PB.14 pin as internal pull up */
  GPIO_InitStructure.GPIO_Pin = cGPIO_AUX_PB_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  
 
  GPIO_Init( cGPIO_AUX_PB_GPIOx, &GPIO_InitStructure );
    
  EXTINT_AUX_PB_Configuration();
  
  NVIC_AUX_PB_Configuration( ENABLE );  
}

/*------------------------------------------------------------------------------
    $Function: EXTINT_PED_Configuration
    $Description: EXT configs for the ped button 

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void EXTINT_AUX_PB_Configuration( void )
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Connect RING EXTI Line14 to RING GPIO Pin PB.14 */
  GPIO_EXTILineConfig(cGPIO_PORT_SOURCE_AUX_PB_PIN, cGPIO_PIN_SOURCE_AUX_PB_PIN);

  /* Configure Key Button EXTI Line to generate an interrupt on rising and falling edge */
  EXTI_InitStructure.EXTI_Line = cEXTI_LINE_AUX_PB_PIN;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
}


/*------------------------------------------------------------------------------
    $Function: EXTINT_PED_Configuration
    $Description: EXT configs for the ped button 

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void EXTINT_PED_Configuration( void )
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Connect RING EXTI Line to RING GPIO Pin */
  GPIO_EXTILineConfig(cGPIO_PORT_SOURCE_PED_PIN, cGPIO_PIN_SOURCE_PED_PIN);

  /* Configure Key Button EXTI Line to generate an interrupt on falling edge */
  EXTI_InitStructure.EXTI_Line = cEXTI_LINE_PED_PIN;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  
}

/*------------------------------------------------------------------------------
  $Function: NVIC_AUX_PB_Configuration
  $Description: Configures the nested vectored interrupt controller.
                for the AUX button interrupt this is gonna be a active low signal 

  $Inputs: FunctionalState NewState - Enable or disable state
  $Outputs: none
  $Assumptions:
  $WARNINGS:
  $End
*/
void NVIC_AUX_PB_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the Ring Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}

/*------------------------------------------------------------------------------
    $Function: NVIC_PED_Configuration
    $Description: Configures the nested vectored interrupt controller.
                  for the PED button interrupt this is gonna be a active low signal 

    $Inputs: FunctionalState NewState - Enable or disable state
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void NVIC_PED_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the Ring Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}
/*------------------------------------------------------------------------------
    $Function: GPIO_SPEED_Configuration
    $Description: GPIO configs for the speed trigger 

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void GPIO_SPEED_Configuration( void ) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_SPEED , ENABLE );
  
  /* Configure test pin as input floating */
  GPIO_InitStructure.GPIO_Pin = cGPIO_SPEED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  
 
  GPIO_Init( cGPIO_SPEED_PIN_GPIOx, &GPIO_InitStructure );
    
  EXTINT_SPEED_Configuration();
  
  NVIC_SPEED_Configuration( ENABLE );  
}
/*------------------------------------------------------------------------------
    $Function: EXTINT_SPEED_Configuration
    $Description: EXTINT configs for the Speed trigger input

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void EXTINT_SPEED_Configuration( void )
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Connect RING EXTI Line to RING GPIO Pin */
  GPIO_EXTILineConfig(cGPIO_PORT_SOURCE_SPEED_PIN, cGPIO_PIN_SOURCE_SPEED_PIN);

  /* Configure Key Button EXTI Line to generate an interrupt on rising edge */
  EXTI_InitStructure.EXTI_Line = cEXTI_LINE_SPEED_PIN;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/*------------------------------------------------------------------------------
    $Function: NVIC_SPEED_Configuration
    $Description: Configures the nested vectored interrupt controller.
                  for the SPEED trigger - active low signal 

    $Inputs: FunctionalState NewState - Enable or disable state
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void NVIC_SPEED_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the Speed Trigger Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}
/*------------------------------------------------------------------------------
    $Function: GPIO_LEDConfiguration
    $Description:

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void GPIO_LED_SMTConfiguration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Configure PB.12 for SMT LED out put */
  RCC_APB2PeriphClockCmd( cRCC_APBxPerih_GPIO_LED_SMT, ENABLE );

  GPIO_InitStructure.GPIO_Pin = cGPIO_LED_SMT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_LED_SMT_GPIOx, &GPIO_InitStructure );

  mGPIO_LED_SMT(HI);
  Delay(200*610);
  mGPIO_LED_SMT(LOW);
  Delay(200*610);
  mGPIO_LED_SMT(HI);
 
}

/*------------------------------------------------------------------------------
    $Function: GPIO_12V_DC_DC_Configuration
    $Description:

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void GPIO_12V_DC_DC_Configuration( void ) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_12V_DC_DC_ENABLE, ENABLE );

  GPIO_InitStructure.GPIO_Pin = cGPIO_12V_DC_DC_ENABLE_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_12V_DC_DC_ENABLE_PIN_GPIOx, &GPIO_InitStructure );

  GPIO_WriteBit( cGPIO_12V_DC_DC_ENABLE_PIN_GPIOx, cGPIO_12V_DC_DC_ENABLE_PIN, ecGPIO_BitAction_CLEAR );  
}


/*------------------------------------------------------------------------------
    $Function: GPIO_DC_DCConfiguration
    $Description:

    $Inputs: none
    $Outputs: none
    $Assumptions:
    $WARNINGS:
    $End
*/
void GPIO_SOLAR_Bulk_Chage_Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
#if 0
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_SOLAR_LDO, ENABLE );

  GPIO_InitStructure.GPIO_Pin = cGPIO_SOLAR_LDO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_SOLAR_LDO_GPIOx, &GPIO_InitStructure );

  GPIO_WriteBit( cGPIO_SOLAR_LDO_GPIOx, cGPIO_SOLAR_LDO_PIN, ecGPIO_BitAction_CLEAR );
#endif
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_BULK_CHARGE, ENABLE );

  GPIO_InitStructure.GPIO_Pin = cGPIO_SOLAR_BULK_CHARGE_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_SOLAR_BULK_CHARGE_GPIOx, &GPIO_InitStructure );

  GPIO_WriteBit( cGPIO_SOLAR_BULK_CHARGE_GPIOx, cGPIO_SOLAR_BULK_CHARGE_PIN, ecGPIO_BitAction_CLEAR );
  
}


/*------------------------------------------------------------------------------
$Function: Local_SYS_ReadVoltages
$Description: reads the Voltage of the solar panel and batt and decides what type of charging to do

$Inputs: none
$Outputs: u8 bState - the state of the state machine
$Assumptions:
$WARNINGS:
$End
*/
void Local_SYS_ReadVoltages( void )
{
//#define cMAX_BATT_VOLTAGE                           1410           // this equal to 4.901 Volts
//#define cMIN_BATT_VOLTAGE_TO_START_CHARGING         1300           // this equals to 4.2999 Volts
//#define cMIN_BATT_VOLTAGE_TO_END_CHARGING           863            // this equals to 2.999 Volts
  
  
  /* this value is used to make sure that the solar panel voltage is bigger than the batt voltage
  by cCHARGING_THRESHOLD */
//#define cCHARGING_THRESHOLD                         20             
  
  
  // (voltage/0.0034761474609375) =  binary value
  
  
  u16  wSolarV, wBattV = 0;
  
 // mSYS_TURN_LDO_CHARGING(); // need to turn the LDO to get a reading on the SOLAR panels    
  
  wSolarV = (u16)mSYS_ADCx_ReadSolarAverageBin();         // gets an average reading from both the batt and solar panel
  wBattV = (u16)mSYS_ADCx_ReadBatteryAverageBin();
  
  printf("\nSOLAR=\n");
  
  printf( "%d\n\n", wSolarV );
  
  printf("\nBATT=\n");
  
  printf( "%d\n\n", wBattV ); 
  
 // printf("\nState =\n");
  
 // printf( "%d\n\n", bState ); 
  
  
  
//  if( wSolarV > wBattV && ((wSolarV - wBattV) > cCHARGING_THRESHOLD) )
//  {
//    switch( bState )
//    {      
//      case 0:
//        
//        if( wBattV <= cMIN_BATT_VOLTAGE_TO_START_CHARGING && wBattV >= cMIN_BATT_VOLTAGE_TO_END_CHARGING )
//        {        
//          bState = 1;
//          printf("state = 1\n");
//          mSYS_TURN_BULK_CHARGING(); // disables LDO
//        }      
//        else
//        {
//          bState = 2;
//          printf("state 2\n");
//          mSYS_TURN_LDO_CHARGING();  // enables LDO
//        }
//        break;      
//      case 1:
//        printf("LDO OFF 1\n");
//        mSYS_TURN_BULK_CHARGING(); // disables LDO
//        if( wBattV >= cMAX_BATT_VOLTAGE )              
//        {
//          printf("LDO ON 1\n");
//          mSYS_TURN_LDO_CHARGING();  // enables LDO
//          bState = 2;             
//        }
//        break;
//        
//      case 2:
//        printf("LDO ON 2\n");
//        mSYS_TURN_LDO_CHARGING();  // enables LDO
//        if( wBattV <= cMIN_BATT_VOLTAGE_TO_START_CHARGING )
//        {
//          printf("LDO OFF 2\n");
//          mSYS_TURN_BULK_CHARGING(); // disables LDO
//          bState = 1;
//        }
//        break;
//        
//      default:
//          bState = 2;
//          printf("LDO ON DF\n");
//          mSYS_TURN_LDO_CHARGING();  // enables LDO
//        break;
//      
//    }
//  }
//  else
//  {
//    printf("LDO ON 3\n");
//    mSYS_TURN_LDO_CHARGING(); // enables LDO
//    bState = 0;
//  }
//  
//  return bState;
}
  



/*------------------------------------------------------------------------------
$Function: Local_SYS_CheckVoltages
$Description: checks the voltages on the battery and solar panel

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void Local_SYS_CheckVoltages( void )
{  

  
  if( TIMER_HasTimeStampElapsed( lwCheckVoltagesTimeStamp, cSYS_CHECK_VOLTAGES_TIMEOUT) )
  {   
    // get timestamp 
    lwCheckVoltagesTimeStamp = TIMER_GetTimeStamp( 0 );
    
    //Local_SYS_ReadVoltages();
    
  }
  
  if( TIMER_HasTimeStampElapsed( lwReadVoltagesTimeStamp, cSYS_READ_VOLTAGES_TIMEOUT) )
  {
    lwReadVoltagesTimeStamp = TIMER_GetTimeStamp( 0 );
    //SYS_XplatGetVoltagesRspFuncHandler( 0 ); // for testing only uncomment later
  }
}

/*------------------------------------------------------------------------------
$Function: SYS_OnResetNotification
$Description: prints the reset notification to the screen

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_OnResetNotification( void )
{
  printf("\n\n");
  printf(cCOMPANY_NAME"\n\n");
  printf("Product: "cPRODUCT_NAME"\n\n");
  printf("Hardware Version: "cHW_VER"\n\n");
  printf("Software Version: "cSW_VER".8\n\n");
  printf("status text\n>>>\nVbat, Vsol, pwm, duration, network, pattern, RSSI, Reset Count\n");
  printf("Current Time: ");
  TIME_DisplayTime();
  
  printf("**************BEGIN**************\n\n\n\n\n");
}

#ifdef cIWDG_ENABLE
/*------------------------------------------------------------------------------
$Function: Local_SYS_StartInWatchDogTimer
$Description: starts the watchdog timer

$Inputs: u16 wReloadValue - the reload counter value
u8 bIWDG_Prescaler - the prescaler we want to use
$Outputs: returns 1
$Assumptions:
$WARNINGS:
$End
*/
u8 Local_SYS_StartInWatchDogTimer( u16 wReloadValue, u8 bIWDG_Prescaler )
{
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  
  /* IWDG counter clock: 40KHz(LSI) / IWDG_Prescaler  */
  IWDG_SetPrescaler(bIWDG_Prescaler);
  
  /* Set counter reload value to wReloadValue */
  IWDG_SetReload(wReloadValue);
  
  /* Reload IWDG counter */
  IWDG_ReloadCounter();
  
  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
  
  // take timestamp to be able to reload the iwdg in time
  lwIWDG_TimeStamp = TIMER_GetTimeStamp( 0 );
  
  return 1;
}

/*------------------------------------------------------------------------------
$Function: Local_SYS_IsTimeToReloadIWDG
$Description: checks if it is time to reload the IWDG

$Inputs: none
$Outputs: returns 1 if true ) if false
$Assumptions:
$WARNINGS:
$End
*/
u8 Local_SYS_IsTimeToReloadIWDG( void )
{
  if( TIMER_HasTimeStampElapsed( lwIWDG_TimeStamp, cSYS_IWDG_TIMEOUT_TO_RELOAD) )
  {
    return 1;
  }
  else
    return 0;
}
#endif

/*------------------------------------------------------------------------------
----- G L O B A L   F U N C T I O N S -----
------------------------------------------------------------------------------
*/

/*------------------------------------------------------------------------------
$Function: SYS_Init
$Description: inits the system module

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_Init( void )
{
  
  /* ===== START OF POWER SUPPLIES =====
    Here We make sure that all of those supplies are in the off position 
  */
  
  /*
    Makes sure that the GSM power supply is turned off
  
    we do this even if the GSM module is not enabled in order to make sure 
    we are saving as much power as possible
  */
#ifndef cGLB_PRODUCT_FOB //*PF
  GPIO_GSM_PowerSupply();  
 
  // makes sure that the GSM Telit power supply chip is in shutdown
  mGSM_Telit_Power_Supply_On_Off( ON );

  // sets up and enables the U8 power suppply for all I2C devices creates VCC3
  GPIO_I2C_Supply_Configurations();  
  mI2C_Power_Supply_On_Off( ON );
#endif
  
  // enables external 12v power supply
  GPIO_12V_DC_DC_Configuration();
  mGPIO_12V_DC_DC( OFF );
  
#ifndef cGLB_PRODUCT_FOB //*PF 
  GPIO_RS232_Interface_Configuration();
  // active low
#ifndef cGLB_PRODUCT_OLDSZ_READER
  mGPIO_RS232_ENABLE( ON );
#endif
#endif

  
  /* ===== END OF POWER SUPPLIES =====*/
  
  SYS_ADCxConfig();
  
  GPIO_LED_SMTConfiguration();  // GPIO configs for the indicator LED
  
  GPIO_PED_Configuration(); // enable ped button
  
  GPIO_AUX_PB_Configuration(); // enable AUX PB 
  
//  GPIO_W16_Configuration(); // enable boot1 option, jumper low for remote tx
//  GPIO_W13_Configuration();
  
#ifndef cGLB_PRODUCT_FOB //*PF
  GPIO_JW_Configuration(); //enable john weatherbe's boot option pin
#endif

#ifdef cGLB_SPEED_ENABLE
  GPIO_SPEED_Configuration(); //Speed trigger
#endif

#ifndef cGLB_PRODUCT_FOB //*PF
#ifdef cGLB_PRODUCT_OLDSZ_READER
  USART_Usart5Config();
  USART_Usart2Config();
#endif
  GPIO_SOLAR_Bulk_Chage_Configuration();
  mSYS_TURN_LDO_CHARGING();
#endif
  
  // get timestamp 
  lwCheckVoltagesTimeStamp = TIMER_GetTimeStamp( 0 );
  lwReadVoltagesTimeStamp = TIMER_GetTimeStamp( 0 );
//external watchdog
#ifdef cWD_ENABLE
  GPIO_WATCHDOG_Configuration();
#endif
  // Init whatever needs to be init
//#ifdef cIWDG_ENABLE
//  Local_SYS_StartInWatchDogTimer( cSYS_IWDG_RELOAD_VALUE, cSYS_IWDG_PRESCALER );
//#endif
  //SYS_OnResetNotification();
  //printf("\nSYS INIT DONE\n"); // debug only
  
#if 0 // this is enabled if we JUST want to turn on the modem
      // without having to set it up FOR TESTING ONLY
  mGSM_Telit_Power_Supply_On_Off( OFF );

  GSM_Telit_Init();
#endif 
}


/*------------------------------------------------------------------------------
$Function: SYS_EnterSleepMode
$Description: inits the system module

$Inputs: u32 ulSleepTime -  time in ticks that you wish it to go to sleep for 

                            All of these variables can be used to pass the time to go to sleep

                            cTIMER_Tick_Interval_1h
                            cTIMER_Tick_Interval_1m
                            cTIMER_Tick_Interval_1s
                            cTIMER_Tick_Interval_100ms

                            if zero is passed then  go to WFI sleep 


$Outputs: none
$Assumptions: The only way to wake up the device is by using the alarm interrupt 
              rather than the one sec interrupt.  
$WARNINGS:
$End
*/
void SYS_EnterSleepMode1( u32 ulSleepTime )
{
  
  // if zero is passed then  go to WFI sleep 
  if( ulSleepTime == 0 )
  {
    __WFI();
    return;
  }
  
  
#if 1   
  /* Alarm in 3 second */
  RTC_SetAlarm(RTC_GetCounter()+ ulSleepTime);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  
  DBGMCU_Config(DBGMCU_STOP, ENABLE );  
  
  PWR_ClearFlag(PWR_FLAG_WU);
  
  /* Request to enter STOP mode with regulator in low power mode*/
  PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
  
  /* Configures system clock after wake-up from STOP: enable HSE, PLL and select 
  PLL as system clock source (HSE and PLL are disabled in STOP mode) */
  SYS_CLKConfig_STOP_Wake();
#endif
  
}

/*------------------------------------------------------------------------------
$Function: SYS_XplatGetTempRspFuncHandler
$Description: inits the system module

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
u8 SYS_XplatGetTempRspFuncHandler( tsXplatCmdPacketStruct * tsXplatCmdPacket )
{ 
  printf( "\nXplat Get Temp\n" );
  //RTC_I2C_GetTemp();
  
  GSM_Telit_RequestModem( "AT#TEMPMON=1", 1, "OK", 0, 0, 0 );
  
  return 1;
}

/*------------------------------------------------------------------------------
$Function: SYS_Init
$Description: inits the system module

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
u8 SYS_XplatGetVoltagesRspFuncHandler( tsXplatCmdPacketStruct * tsXplatCmdPacket )
{ 
  printf( "\nXplat Get Voltages\n" );
  
#if 0 
  
  uc8 bVoltagesRsp[8] = { 0x00, 0x0D, 0x01, 0x00, 0x00, 0x05, 0x00, 0x00 };
  
  u16 wSolarV, wBattV = 0;
  
  wSolarV = (u16)mSYS_ADCx_ReadSolarAverageBin();         // gets an average reading from both the batt and solar panel
  wBattV = (u16)mSYS_ADCx_ReadBatteryAverageBin();
  
  u8 bVoltagesData[] = { ((wSolarV>>8)&0x00FF), ((wSolarV)&0x00FF), ((wBattV>>8)&0x00FF), ((wBattV)&0x00FF)  };
  
  XPLAT_PacketSender( (u8*)bVoltagesRsp, sizeof(bVoltagesRsp), XPLAT_PROT_GenerateSequenceNumber(), bVoltagesData, sizeof(bVoltagesData) );
  
  
  printf("\nSOLAR=\n");
  
  printf( "%d\n\n", wSolarV );
  
  printf("\nBATT=\n");
  
  printf( "%d\n\n", wBattV );
  
  
#else
#include "CommManager.h"
  char bBuffer[50] ={ 0 };
  float wSolarV, wBattV = 0;
  
  wSolarV = mSYS_ADCx_ReadSolarAverageVoltage();
  
  wBattV = mSYS_ADCx_ReadBatteryAverageVoltage();
    
  sprintf(bBuffer, "  s = %.2fV, b = %.2fV, st = %d ", wSolarV, wBattV, bState );
  
  
  
  GSM_Telit_SendSms( (u8*)bBuffer , NULL);
#endif 
  
  
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
void SYS_SchGetVoltagesRspActivity( u16 wDuration, u16 wInterval, u8 bFlag )   // need some sort of command here to initialize this
{
  static u8 bStartFlag = 0;
  static u32 lwDurationTimeStamp, lwIntervalTimeStamp;
  static u16 wDurationVar, wIntervalVar;
  
  if( bFlag == 1 )
  {
    if( wDuration && wInterval )
    {
      // take timestamp for duration 
      if( !bStartFlag )
      {
        lwDurationTimeStamp = TIMER_GetTimeStamp( 0 );
        lwIntervalTimeStamp = TIMER_GetTimeStamp( 0 );
        
        wDurationVar = wDuration;
        wIntervalVar = wInterval;
        
        printf("SCH Batt turning on\n");
        
        // run the actuall task 
        printf("Starting the SCH Batt running activity\n");
        
        bStartFlag = 1;
      }
    }
  }
  else if( bFlag == 0 )
  {
    // turnoff activity 
    bStartFlag = 0;
    printf("SCH Batt turning off\n");
  }
  else
  {
    if( bStartFlag == 1 )
    {      
      if( !TIMER_HasTimeStampElapsed( lwDurationTimeStamp, (wDurationVar*cTIMER_Tick_Interval_1m)) )
      {
        if( TIMER_HasTimeStampElapsed( lwIntervalTimeStamp, (wIntervalVar*cTIMER_Tick_Interval_1m)) )
        {
          lwIntervalTimeStamp = TIMER_GetTimeStamp( 0 );
          // run the actuall task 
          printf("SCH Batt running activity\n");
        }   
      }
      else
      {
        bStartFlag = 0;
        printf("SCH Batt turning off\n");
      }
    }
  }
}



/*------------------------------------------------------------------------------
$Function: SYS_SchGetTempRspActivity
$Description:

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_SchGetTempRspActivity( u16 wDuration, u16 wInterval, u8 bFlag )   // need some sort of command here to initialize this
{
  static u8 bStartFlag = 0;
  static u32 lwDurationTimeStamp, lwIntervalTimeStamp;
  static u16 wDurationVar, wIntervalVar;
  
  if( bFlag == 1 )
  {
    if( wDuration && wInterval )
    {
      // take timestamp for duration 
      if( !bStartFlag )
      {
        lwDurationTimeStamp = TIMER_GetTimeStamp( 0 );
        lwIntervalTimeStamp = TIMER_GetTimeStamp( 0 );
        
        wDurationVar = wDuration;
        wIntervalVar = wInterval;
        
        printf("SCH Temp turning on\n");
        
        // run the actuall task 
        printf("Starting the SCH Temp running activity\n");
        
        bStartFlag = 1;
      }
    }
  }
  else if( bFlag == 0 )
  {
    // turnoff activity 
    bStartFlag = 0;
    printf("SCH Temp turning off\n");
  }
  else
  {
    if( bStartFlag == 1 )
    {      
      if( !TIMER_HasTimeStampElapsed( lwDurationTimeStamp, (wDurationVar*cTIMER_Tick_Interval_1m)) )
      {
        if( TIMER_HasTimeStampElapsed( lwIntervalTimeStamp, (wIntervalVar*cTIMER_Tick_Interval_1m)) )
        {
          lwIntervalTimeStamp = TIMER_GetTimeStamp( 0 );
          // run the actuall task 
          printf("SCH Temp running activity\n");
        }   
      }
      else
      {
        bStartFlag = 0;
        printf("SCH Temp turning off\n");
      }
    }
  }
}

/*------------------------------------------------------------------------------
$Function: SYS_Set_PED_Status
$Description: sets the value of boPedBtnStatus

$Inputs: bool status -  variable sets the value of boPedBtnStatus
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_Set_PED_Status( bool status )
{
  boPedBtnStatus = status;
}

/*------------------------------------------------------------------------------
$Function: SYS_Get_PED_Status
$Description: Returns the value of the PED button  

$Inputs: none
$Outputs: bool temp - temp variable where the value of boPedBtnStatus is stored
$Assumptions:
$WARNINGS:
$End
*/
bool SYS_Get_PED_Status()
{
  bool temp = boPedBtnStatus;  // save the status temporarily 
  
  return temp;  //return the saved store value of temp
}
/*------------------------------------------------------------------------------
$Function: SYS_Set_AUX_PED_Status
$Description: sets the value of boAUX_PED_Status

$Inputs: bool status -  variable sets the value of boAuxBtnStatus
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_Set_AUX_PED_Status( bool status )
{
  boAuxBtnStatus = status;
}

bool SYS_Get_AUX_PED_Status()
{
  bool temp = boAuxBtnStatus;  // save the status temporarily 
  
  return temp;  //return the saved store value of temp
}
u8 SYS_Get_OLDSZ_Status()
{
  u8 temp = OLDSZStatus;  // save the status temporarily 
  
  return temp;  //return the saved store value of temp
}
void SYS_Set_OLDSZ_Status( u8 status )
{
  OLDSZStatus = status;
}
/*------------------------------------------------------------------------------
$Function: SYS_Set_SPEED_Status
$Description: sets the value of boSpeedBtnStatus

$Inputs: bool status -  variable sets the value of boSpeedBtnStatus
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_Set_SPEED_Status( bool status )
{
  boSpeedBtnStatus = status;
}

/*------------------------------------------------------------------------------
$Function: SYS_Get_SPEED_Status
$Description: Returns the value of the Speed button and resets it back to false 

$Inputs: none
$Outputs: bool temp - temp variable where the value of boSpeedBtnStatus is stored
$Assumptions:
$WARNINGS:
$End
*/

bool SYS_Get_SPEED_Status()
{
  bool temp = boSpeedBtnStatus;  // save the status temporarily 
  
  //boSpeedBtnStatus = FALSE; // clear the status after it has been read
  
  return temp;  //return the saved store value of temp
}
/*------------------------------------------------------------------------------
	$Function: GPIO_WATCHDOG_Configuration
	$Description: GPIO configs for the external watchdog part STM6822

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_WATCHDOG_Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_WD , ENABLE );
  
  /* Configure WD pin as input floating on PE6 */
  GPIO_InitStructure.GPIO_Pin = cGPIO_WD_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 
  GPIO_Init( cGPIO_WD_PIN_GPIOx, &GPIO_InitStructure );
}
void GPIO_lockout_Configuration( u8 what ){
  GPIO_InitTypeDef GPIO_InitStructure;  
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_lockout, ENABLE );
  
  GPIO_InitStructure.GPIO_Pin = cGPIO_lockout_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(cGPIO_lockout_GPIOx, &GPIO_InitStructure);
  
  GPIO_WriteBit( cGPIO_lockout_GPIOx, cGPIO_lockout_PIN, what);
}
/*------------------------------------------------------------------------------
	$Function: SYS_KICK_THE_DOG
	$Description: kick the external watchdog part STM6822 on a toggle basis
                      Internal pullup/pulldown if left for 1.6seconds will cause a reset
                      Input floating is a don't care
	$Inputs: bSleep -> set = set dog to input floating before micro sleeps
                           zero = toggle up/down
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/

void SYS_KICK_THE_DOG ( u8 bSleep )
{
  
#if 1
  GPIO_InitTypeDef GPIO_InitStructure;
  static u8 cWDToggle = 0;
  cWDToggle ^= 1;

  if(cWDToggle)
  {
    /* Configure WD pin as internal pull up */
    GPIO_InitStructure.GPIO_Pin = cGPIO_WD_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    //printf("Dog up\n");
  } 
  else
  {
    /* Configure WD pin as internal pull down */
    GPIO_InitStructure.GPIO_Pin = cGPIO_WD_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    //printf("Dog down\n");
  }
  if(bSleep)
  {
    /* Configure WD pin as input floating */
    GPIO_InitStructure.GPIO_Pin = cGPIO_WD_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    //printf("Dog off\n");
  }
  GPIO_Init( cGPIO_WD_PIN_GPIOx, &GPIO_InitStructure );
#else
  
  mGPIO_WD_ENABLE_TOGGLE();
#endif
}



/*------------------------------------------------------------------------------
	$Function: SYS_Enter_Debug_FuncHandler
	$Description: Function handles reset xplat cmd

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 SYS_Enter_Debug_FuncHandler( tsXplatCmdPacketStruct * tsXplatCmdPacket )
{
  /* this makes sure that the same message doesnt get process twice by making sure that 
     the squence number is different than the previous squence number 
  */
  if( XPLAT_PROT_IsSameSequenceNumber( tsXplatCmdPacket->lwXplatCmdId, tsXplatCmdPacket->bXplatCmdSequence ) )
  {
    mUSART_DEBUG_WAIT_AND_SEND('3');
    return 0;
  }
  
  printf("\nDEBUG TRUE\n"); // debug only 
  SYS_Set_Debug_Flag( TRUE );
  
  return 1;
}


/*------------------------------------------------------------------------------
	$Function: SYS_Enter_Debug_FuncHandler
	$Description: Function handles reset xplat cmd

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 SYS_Exit_Debug_FuncHandler( tsXplatCmdPacketStruct * tsXplatCmdPacket )
{
  /* this makes sure that the same message doesnt get process twice by making sure that 
     the squence number is different than the previous squence number 
  */
  if( XPLAT_PROT_IsSameSequenceNumber( tsXplatCmdPacket->lwXplatCmdId, tsXplatCmdPacket->bXplatCmdSequence ) )
  {
    mUSART_DEBUG_WAIT_AND_SEND('3');
    return 0;
  }
  
  printf("\nDEBUG FALSE\n"); // debug only 
  SYS_Set_Debug_Flag( FALSE );
  
  return 1;
}


/*------------------------------------------------------------------------------
$Function: SYS_Set_Debug_Flag
$Description: Sets the boDebug_Flag and lwDebug_TimeStamp

$Inputs: bool boDebugFlag - if true then it will set the timestamp as well,
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_Set_Debug_Flag( bool boDebugFlag )
{
  boDebug_Flag = boDebugFlag;
  
  if( boDebugFlag == TRUE )
  {
    // stop timers and tasks here 
    RF_State_Set_Rf_State( cRF_State_Do_Nothing );
    RF_State_Machine();
    mUSART_DEBUG_WAIT_AND_SEND('O');
    lwDebug_TimeStamp = TIMER_GetTimeStamp( 0 );
  }
}


/*------------------------------------------------------------------------------
$Function: SYS_Get_Debug_Flag
$Description: returns the value of boDebug_Flag
              if boDebug_Flag == FALSE then it wont check if timeout has occurred

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
bool SYS_Get_Debug_Flag( void )
{
  if( boDebug_Flag == TRUE )
  {
    if( TIMER_HasTimeStampElapsed( lwDebug_TimeStamp, cSYS_DebugMode_Timeout ) )
    {
      boDebug_Flag = FALSE;
    }
  }
  
  return boDebug_Flag;
}




/*------------------------------------------------------------------------------
$Function: SYS_Test
$Description: Tests that Jim would like to run on any hardware board

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_Test( void )
{
  
  u8 x = 1;
  u8 y = 1;
  u8 wd_Flag = 1;
  u8 whl = 0;

  while( SW_GetSwitchValue( cSW_2 ) == 15 ){
    if(!whl){  
      printf( "\n\nWelcome To Jim's Mode\n\n...where there is no free lunch\n" );
      whl = 1;
    } 
    #ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
    #endif // END OF cWD_ENABLE
    
    if( wd_Flag == 1 )
    {
#ifdef cWD_ENABLE
    SYS_KICK_THE_DOG(0);
#endif
    }
    else{
      printf( "Oh Snap!" );
    }
    
    
    
  
    switch( SW_GetSwitchValue( cSW_3 ) )
    {
    case 0:      
      wd_Flag = 1;
      if( SYS_Get_PED_Status() ) 
      {
        printf( "BULK CHARGE = " );
        // clear the button status
        SYS_Set_PED_Status( FALSE ); 
        

        if( GPIO_ReadOutputDataBit(cGPIO_SOLAR_BULK_CHARGE_GPIOx, cGPIO_SOLAR_BULK_CHARGE_PIN) )
        {
          printf( "1\n" );
        }
        else
        {
          printf( "0\n" );
        }
        
        //printf( "Solar = %f\n",mSYS_ADCx_ReadSolarVoltage() );
        //printf( "Battery = %f\n\n",mSYS_ADCx_ReadBatteryVoltage() ); 
        
        mGPIO_SOLAR_LDO_TOGGLE();
      }
      
      break;
      
      
      case 1:
      wd_Flag = 1;
      if( SYS_Get_PED_Status() ) 
      {
        printf( "VCC2 Telit power = " );
        
        //printf("Supply = %d\n", GPIO_ReadInputDataBit( cGPIO_GSM_POWER_SUPPLY_GPIOx, cGPIO_GSM_POWER_SUPPLY_PIN ));
        mGSM_Telit_Power_Supply_On_Off_Toggle();
        
        
        if( GPIO_ReadOutputDataBit( cGPIO_GSM_POWER_SUPPLY_GPIOx, cGPIO_GSM_POWER_SUPPLY_PIN ) )
        {
          printf( "1\n" );
        }
        else
        {
          printf( "0\n" );
        }
        
        // clear the button status
        SYS_Set_PED_Status( FALSE );
      }
      break;
      
      
       case 2:
      
      wd_Flag = 1;
      
      if( SYS_Get_PED_Status() ) 
      {
       
        if( x )
        {
          printf( "VCC3 ON\n\n" );
         mI2C_Power_Supply_On_Off( ON );
         x = 0;
        }
        else
        {
          printf( "VCC3 OFF\n\n" );
          mI2C_Power_Supply_On_Off( OFF );
          x = 1;
        }
        
        SYS_Set_PED_Status( FALSE );
      }     
      break;
      
      
    case 3:
      
      wd_Flag = 1;
      
      if( SYS_Get_PED_Status() ) 
      {
        printf( "12V = " );
        
        // clear the button status
        SYS_Set_PED_Status( FALSE );
        
        mGPIO_12V_DC_DC_TOGGLE();
        
        
        if( GPIO_ReadOutputDataBit( cGPIO_12V_DC_DC_ENABLE_PIN_GPIOx, cGPIO_12V_DC_DC_ENABLE_PIN ) )
        {
          printf( "1\n" );
        }
        else
        {
          printf( "0\n" );
        }
      }
      
      break;
      
    case 4:
      
      wd_Flag = 1;
      
      if( SYS_Get_PED_Status() ) 
      {
        printf( "RS 232 interface = " );
        
        
        
        
        
        mGPIO_RS232_ENABLE_TOGGLE();
        
        
        if( GPIO_ReadOutputDataBit( cGPIO_RS232_INTERFACE_FORCE_ON_PIN_GPIOx, cGPIO_RS232_INTERFACE_FORCE_ON_PIN ) )
        {
          printf( "1\n" );
          mGPIO_RS232_FORCE_OFF(LOW);
        }
        else
        {
          mGPIO_RS232_FORCE_OFF(HI);
          
          printf( "0\n" );
          
          printf("SENDING Echo NOW\n");
          
          Delay(200*cDELAY_Timeout_1ms);
          UART5_WAIT_AND_SEND('H');
          UART5_WAIT_AND_SEND('E');
          UART5_WAIT_AND_SEND('L');
          UART5_WAIT_AND_SEND('L');
          UART5_WAIT_AND_SEND('O');
          UART5_WAIT_AND_SEND(' ');
          UART5_WAIT_AND_SEND('J');
          UART5_WAIT_AND_SEND('I');
          UART5_WAIT_AND_SEND('M');
          
        }
        
        // clear the button status
        SYS_Set_PED_Status( FALSE );
      }
      
      break;
      
    
      
   
      
    case 5:
      
      wd_Flag = 1;
    
      if( SYS_Get_PED_Status() ) 
      {
        if( y == 1 )
        {
          BT_On();
          printf( "Bluetooth ON\n\n" );
          y = 0;
        }
        else
        {
          printf( "Bluetooth OFF\n\n" );
          BT_Off();
          y = 1;
        }
        
        
        // clear the button status
        SYS_Set_PED_Status( FALSE );
      }
      break;
      
    case 15:
      if( SYS_Get_PED_Status() ) 
      {
        wd_Flag ^= 1;
        
        printf( "WD = %d\n", wd_Flag );
        
        // clear the button status
        SYS_Set_PED_Status( FALSE );
      }
      break;
      
    default:
      wd_Flag = 1;
      break;
      
    }
  }
  if(whl){  printf( "\nColour me gone...\n" );}
}



/*------------------------------------------------------------------------------
$Function: SYS_Task
$Description: SYS task

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_Task( void )
{
//#ifdef cIWDG_ENABLE
//  if( Local_SYS_IsTimeToReloadIWDG() )
//  {
//    /* Reload IWDG counter */
//    IWDG_ReloadCounter();
//    
//    // take timestamp to be able to reload the iwdg in time
//    lwIWDG_TimeStamp = TIMER_GetTimeStamp( 0 );
//  }
//#endif
  
  //Local_SYS_CheckVoltages();
  
  /*
    Sch Activities for the SYS modules 
  */
  //SYS_SchGetVoltagesRspActivity( 0, 0, 2 );
  //SYS_SchGetTempRspActivity( 0, 0, 2 );
  
  // holdoff code for multiple remote transmitters
  //idea is to hold out for one repeated ON tx message
  // if you see a repeated ON then don't turn off
//  if ( bOffHoldFlag == 13 ){
//    bOffHoldFlag = 0;
//    //printf("\n&%i",bOffHoldFlag);
//  }
//  else if ( bOffHoldFlag == 10 ){
//    someTimeStamp = TIMER_GetTimeStamp( 0 );
//    bOffHoldFlag = 11;
//    //printf("\n&=i",bOffHoldFlag);
//  }
//  /////////////////////////////////////////////////change this 0 to desired holdoff
//  else if (TIMER_HasTimeStampElapsed( someTimeStamp, 0*cTIMER_Tick_Interval_1s ) && bOffHoldFlag == 11){
//    global_TurnOnLights = 2;
//    bOffHoldFlag = 0;
//    //printf("\n&^i",bOffHoldFlag);
//  }
}

//#ifdef cIWDG_ENABLE
/*------------------------------------------------------------------------------
$Function: SYS_ReloadInWatchDogTimer
$Description: This function can be used by other parts of the application when we know that its operation is longer than the
max lentth of cSYS_IWDG_TIMEOUT_TO_RELOAD so it can reload the IWDG timer variable

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/

//void SYS_ReloadInWatchDogTimer( void )
//{
//  /* Reload IWDG counter */
//  mSYS_IWDG_ReloadCounter();
//}
//#endif

/*------------------------------------------------------------------------------
$Function: SYS_Reset
$Description: manages the type of reset that occurred and reports it to the Err log

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_Reset( void )
{
  if( RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET )
  {
    /* Clear reset flags */
    //RCC_ClearFlag();
    
    //ERR_Post( cXPLAT_CMD_ID_ERROR, cXPLAT_STATUS_ERR_RST_PORRST, cERR_CritLevel_Store_Only );
    
    printf("\n\n\nPOWER RESET\n\n\n");
    //return;
  }
  
  if( RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET )
  {
    /* Clear reset flags */
    //RCC_ClearFlag();
    
    //ERR_Post( cXPLAT_CMD_ID_ERROR, cXPLAT_STATUS_ERR_RST_PINRST, cERR_CritLevel_Store_Only );
    
    printf("\n\n\nPIN RESET\n\n\n");
    //return;
  }
  
  if( RCC_GetFlagStatus(RCC_FLAG_SFTRST) != RESET )
  {
    /* Clear reset flags */
    //RCC_ClearFlag();
    
    //ERR_Post( cXPLAT_CMD_ID_ERROR, cXPLAT_STATUS_ERR_RST_SFTRST, cERR_CritLevel_Store_Only );
    
    printf("\n\n\nSOFTWARE RESET\n\n\n");
    //return;
  }
  
  if( RCC_GetFlagStatus(RCC_FLAG_LPWRRST) != RESET )
  {
    /* Clear reset flags */
    //RCC_ClearFlag();
    
    //ERR_Post( cXPLAT_CMD_ID_ERROR, cXPLAT_STATUS_ERR_RST_LPWRRST, cERR_CritLevel_Store_Only );
    
    printf("\n\n\n LOW POWER RESET\n\n\n");
    //return;
  }
  
  if( RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET )
  {
    /* Clear reset flags */
    // RCC_ClearFlag();
    
    //ERR_Post( cXPLAT_CMD_ID_ERROR, cXPLAT_STATUS_ERR_RST_IWDGRST, cERR_CritLevel_Store_Only );
    
    printf("\n\n\nIWDG RESET\n\n\n");
    //return;
  }
  
  if( RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET )
  {
    /* Clear reset flags */
    //RCC_ClearFlag();
    
    //ERR_Post( cXPLAT_CMD_ID_ERROR, cXPLAT_STATUS_ERR_RST_WWDGRST, cERR_CritLevel_Store_Only );
    
    printf("\n\n\nWWDG RESET\n\n\n");
    //return;
  }
  
  /* Clear reset flags */
  RCC_ClearFlag();
}


/*------------------------------------------------------------------------------
$Function: SYS_Reset
$Description: manages the type of reset that occurred and reports it to the Err log

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
void SYS_ADCxConfig( void )
{
  ADC_InitTypeDef ADC_InitStructure;
  
  GPIO_ADCxConfiguration();
  
  ADC_DeInit(ADC1);
  
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  /* Enable ADC1 DMA */
  //ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  
  /* Enable ADC1 reset calibaration register */
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));
  
  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
}



/*------------------------------------------------------------------------------
	$Function: SYS_GetFlashDurationValue
	$Description: This function returns the current setting for the Flash duration 
                      It takes into account that that setting can be overwritten by the 
                      bluetooth and/or serial connections so it delivers the latest change 
            
                      So if the bluetooth was the last settings it received it will use those and
                      it will ignore the knobs. As soon as a knob position changes then it will use the 
                      knobs as the settings for everything

	$Inputs: none
	$Outputs: lwFlashPattern[t.bSw2] -  returns the vallue in seconds of the lwFlashPattern
                  array according to the index tsSwReadValuesStruct.bSw2 which tells the function 
                  what the real hardware position of the switch is. 
	$Assumptions:
	$WARNINGS:
	$End
*/
u32 SYS_GetFlashDurationValue( void )
{
  uc32 lwFlashPattern[16] = { cSYS_FLASH_DURATION_0, cSYS_FLASH_DURATION_1, cSYS_FLASH_DURATION_2,
                              cSYS_FLASH_DURATION_3, cSYS_FLASH_DURATION_4, cSYS_FLASH_DURATION_5,
                              cSYS_FLASH_DURATION_6, cSYS_FLASH_DURATION_7, cSYS_FLASH_DURATION_8,
                              cSYS_FLASH_DURATION_9, cSYS_FLASH_DURATION_10, cSYS_FLASH_DURATION_11,
                              cSYS_FLASH_DURATION_12, cSYS_FLASH_DURATION_13, cSYS_FLASH_DURATION_14,
                              cSYS_FLASH_DURATION_15
                            }; 
  
  tsSwReadValuesStruct t = SW_GetSwitches();
  
  
  return lwFlashPattern[t.bSw2]; // return the value of the array given by the index of the sw2 postion
}



/*------------------------------------------------------------------------------
$Function: SYS_ReadADCx
$Description: manages the reads to the ADC for both the BATT and the SOLAR PANEL 

$Inputs: u8 bAdcChannel - the ADC channel that we want to read
                          cSYS_ADCx_BATT_CHANNEL
                          cSYS_ADCx_SOLAR_CHANNEL
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
u16 SYS_ReadADCx( u8 bAdcChannel, u8 bAdcTypeFlags )
{
  u16 Val = 0;   // variable where the ADCx Value will be stored
  
  /* ADC1 regular channel configuration */
  ADC_RegularChannelConfig(ADC1, bAdcChannel, 1, ADC_SampleTime_55Cycles5);
  ADC_Cmd(ADC1, ENABLE);
 
  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
  Val = ADC_GetConversionValue(ADC1); 
    /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
  Val = ADC_GetConversionValue(ADC1); 
  return Val;  
}

/*------------------------------------------------------------------------------
        $Function: SYS_Generate_Random_Number
        $Description: Geenerates a random number using the RTC_GetCounter func 
                      as one of its seeds. It can also take another seed as a parameter which 
                      will then XOR with teh RTC_GetCounter func returnde value
        
        $Inputs: none
        $Outputs: none
        $Assumptions:
        $WARNINGS:
        $End
*/
u16 SYS_Generate_Random_Number( u16 wSeed )
{
  
  u32 timeTemp = RTC_I2C_Get_Counter();
  srand( (unsigned)(timeTemp) );
  
  //srand( (unsigned)(RTC_ReturnCounter(0)^wSeed) );
  
  u16 wTemp = rand();
  
  return wTemp;
}




/*******************************************************************************
* Function Name  : SYSCLKConfig_STOP
* Description    : Configures system clock after wake-up from STOP: enable HSE, PLL
*                  and select PLL as system clock source.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SYS_CLKConfig_STOP_Wake(void)
{
  ErrorStatus HSEStartUpStatus;
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
      /* Select HSE as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);	

    /* Wait till HSE is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x04)
    {}   
  }
  //NVIC_GenerateSystemReset();
  NVIC_SCBDeInit();
}
/*------------------------------------------------------------------------------
	$Function: SYS_Dimming_OnOff
	$Description: gets the sys dimming on off
	$Inputs: tsXplatCmdPacketStruct * tsXplatCmdPacket - sys dimming onoff command
	$Outputs: u8 - success
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 SYS_Dimming_OnOff ( tsXplatCmdPacketStruct * tsXplatCmdPacket )
{   
  if( tsXplatCmdPacket->wXplatCmdLen > cXPLAT_STANDARD_PACKET_SIZE )
  {
    STORE_EE_ByteWrite(tsXplatCmdPacket->bXplatPayloadSwingBuffer_1[0], cEE_SYS_Dimming_OnOff);
    bDimmingOnOff = tsXplatCmdPacket->bXplatPayloadSwingBuffer_1[0];      
    XPLAT_Packet_Builder( cXPLAT_CMD_ID_SYS_Dimming_OnOff_Rsp, cXPLAT_STATUS_ACK, tsXplatCmdPacket->bXplatCmdSequence, 
                          0 , 0, tsXplatCmdPacket->bXplatPacketReturnOutputType );       
  }
  else
  {
    unsigned char pBufferz[2] = {0};
    pBufferz[0] = bDimmingOnOff;
    XPLAT_Packet_Builder( cXPLAT_CMD_ID_SYS_Dimming_OnOff_Rsp, cXPLAT_STATUS_ACK, tsXplatCmdPacket->bXplatCmdSequence, 
                          pBufferz , 1, tsXplatCmdPacket->bXplatPacketReturnOutputType );
  }
  return 1;
}
///*------------------------------------------------------------------------------
//	$Function: SYS_Dimming_Ceiling
//	$Description: gets the dimming ceiling
//	$Inputs: tsXplatCmdPacketStruct * tsXplatCmdPacket - sys dimming ceiling command
//	$Outputs: u8 - success
//	$Assumptions:
//	$WARNINGS:
//	$End
//*/
u8 SYS_Dimming_Ceiling ( tsXplatCmdPacketStruct * tsXplatCmdPacket )
{   
  if( tsXplatCmdPacket->wXplatCmdLen > cXPLAT_STANDARD_PACKET_SIZE )
  { 
    STORE_EE_ByteWrite(tsXplatCmdPacket->bXplatPayloadSwingBuffer_1[0], cEE_SYS_Dimming_Ceiling);
    bDimmingCeiling = tsXplatCmdPacket->bXplatPayloadSwingBuffer_1[0];
    XPLAT_Packet_Builder( cXPLAT_CMD_ID_SYS_Dimming_Ceiling_Rsp, cXPLAT_STATUS_ACK, tsXplatCmdPacket->bXplatCmdSequence, 
                          0 , 0, tsXplatCmdPacket->bXplatPacketReturnOutputType );     
  }
  else
  {
    unsigned char pBufferz[2] = {0};
    pBufferz[0] = bDimmingCeiling;

    XPLAT_Packet_Builder( cXPLAT_CMD_ID_SYS_Dimming_Ceiling_Rsp, cXPLAT_STATUS_ACK, tsXplatCmdPacket->bXplatCmdSequence, 
                          pBufferz , 1, tsXplatCmdPacket->bXplatPacketReturnOutputType );
  }
  return 1;
}
void SYS_Dimming_Values_Init( void )
{
//  bDimmingCeiling = STORE_EE_ByteRead( cEE_SYS_Dimming_Ceiling );
//
//  if ( STORE_EE_ByteRead( cEE_SYS_Dimming_OnOff ) == 255 )//255 is the ee default
//  {
//    bDimmingOnOff = 1;
//  }
//  else
//  {
//    bDimmingOnOff = STORE_EE_ByteRead( cEE_SYS_Dimming_OnOff );
//  }
}
u8 SYS_Dimming ( void )
{
  u8 pwm_value = 255;
  static u8 JSFSTROBEdimmingFlag = 0;
  float Vsol = 0, Vbat = 0;
  
  Vbat  = ((float)17.5 * (float)mSYS_ADCx_ReadBatteryAverageBin())/ (float)4096;   
  Vsol  = ((float)21.6 * (float)mSYS_ADCx_ReadSolarAverageBin())  / (float)4096;
  
  if( Vbat < 11.5 ){        //11.5v
    pwm_value = 155; /*JSFSTROBEdimmingFlag = 4; offsetMUTCD = 400; inSignOffset = 100;*/
  }
  else if( Vbat < 12.1 ){   //12.1v
    switch(JSFSTROBEdimmingFlag){
    case 4:  pwm_value = 155; /*JSFSTROBEdimmingFlag = 4; offsetMUTCD = 400; inSignOffset = 100;*/ break;
    default: pwm_value = 180; /*JSFSTROBEdimmingFlag = 3; offsetMUTCD = 300; inSignOffset = 100;*/ break;
    }
  }
  else if( Vbat < 12.25 ){  //12.25v
    switch(JSFSTROBEdimmingFlag){
    case 3:  pwm_value = 180; /*JSFSTROBEdimmingFlag = 3; offsetMUTCD = 300; inSignOffset = 100;*/ break;
    case 4:  pwm_value = 155; /*JSFSTROBEdimmingFlag = 4; offsetMUTCD = 400; inSignOffset = 100;*/ break;
    default: pwm_value = 205; /*JSFSTROBEdimmingFlag = 2; offsetMUTCD = 200; inSignOffset = 50;*/ break;
    }
  }
  else if( Vbat < 12.40 ){  //12.4v
    switch(JSFSTROBEdimmingFlag){
    case 2:  pwm_value = 205; /*JSFSTROBEdimmingFlag = 2; offsetMUTCD = 200; inSignOffset = 50;*/ break;
    case 3:  pwm_value = 180; /*JSFSTROBEdimmingFlag = 3; offsetMUTCD = 300; inSignOffset = 100;*/ break;
    case 4:  pwm_value = 205; /*JSFSTROBEdimmingFlag = 2; offsetMUTCD = 200; inSignOffset = 50;*/ break;
    default: pwm_value = 230; /*JSFSTROBEdimmingFlag = 1; offsetMUTCD = 100; inSignOffset = 50;*/ break;
    }
  }
  else{
    switch(JSFSTROBEdimmingFlag){
    case 1: if(Vbat > 12.43){
      pwm_value = 255; /* JSFSTROBEdimmingFlag = 0; offsetMUTCD = 0; inSignOffset = 0;*/} 
    else{
      pwm_value = 230; /*JSFSTROBEdimmingFlag = 1; offsetMUTCD = 100; inSignOffset = 50;*/} 
      break;
    default: pwm_value = 255; /*JSFSTROBEdimmingFlag = 0; offsetMUTCD = 0; inSignOffset = 0;*/ break;
    }
  } 
  if(Vsol < 9.00){  //9.0v
    pwm_value -= 127; //50% pwm
  }
  else if(Vsol < 12.00){  //12.0v
    pwm_value -= 76; //70% pwm
  }
  #ifdef cGLB_BT_ENABLE
  BT_On();
  USART_EnableUsartX_Printf = cUSART_USART_4_ENABLE;
  printf("\n>>>\n%0.2f, %0.2f, %d", Vbat, Vsol,pwm_value);
  USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
  #endif
  printf("\n>>>\n%0.2f, %0.2f, %d", Vbat, Vsol,pwm_value);
  return pwm_value;
}

void SYS_Set_Sleep_Type_Flag( bool boSleep_Type )
{
  boSYS_Sleep_Type_Flag = boSleep_Type;
}
bool SYS_Get_Sleep_Type_Flag( void )
{
  return boSYS_Sleep_Type_Flag;
}

/*------------------------------------------------------------------------------
$Function: SYS_EnterSleepMode
$Description: puts unit to sleep

$Inputs: none
$Outputs: none
$Assumptions: The only way to wake up the device is by using the alarm interrupt 
              rather than the one sec interrupt.  
$WARNINGS:
$End
*/
void SYS_EnterSleepMode( void )
{
#ifdef cGLB_PRODUCT_OLDSZ_READER
  //DBGMCU_Config( DBGMCU_SLEEP, ENABLE);
//  GPIO_InitTypeDef GPIO_InitStructure;
  /* Configure USART2 Rx (PA.03) as output open drain */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//  GPIO_Init( GPIOA, &GPIO_InitStructure );

  __WFI();
  
//  /* Configure USART2 Rx (PA.03) as output open drain */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init( GPIOA, &GPIO_InitStructure );  
  
#else
  
  if( SYS_Get_Sleep_Type_Flag()  ||  GPIO_ReadInputDataBit(cGPIO_USBSENSE_GPIOx, cGPIO_USBSENSE_PIN))
  {
    DBGMCU_Config( DBGMCU_SLEEP, ENABLE);
    __WFI();
    return;
  }
  else
  {
    DBGMCU_Config(DBGMCU_STOP, ENABLE );  
    
    PWR_ClearFlag(PWR_FLAG_WU);
    
    /* Request to enter STOP mode with regulator in low power mode*/
    PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
    
    /* Configures system clock after wake-up from STOP: enable HSE, PLL and select 
    PLL as system clock source (HSE and PLL are disabled in STOP mode) */
    SYS_CLKConfig_STOP_Wake();
  }
#endif
  
}

u16 SYS_ResetCount( u8 action ){
  
  #define cEE_ResetCountH               0xDC
  #define cEE_ResetCountL               0xDD
  
  static u16 resetCount = 0;
  
  switch(action){
  case 0:
    //reset case
    resetCount = 0;
    STORE_EE_ByteWrite( 0, cEE_ResetCountH);
    STORE_EE_ByteWrite( 0, cEE_ResetCountL);
    
    //reset rtc too
    RTC_I2C_SetTime(0,0,0,0,0,0,0);
    
    break;
  case 1:
    resetCount = (STORE_EE_ByteRead(cEE_ResetCountH)<<8) + STORE_EE_ByteRead(cEE_ResetCountL);
    //increment case
    if(resetCount == 0xFFFF)
      resetCount = 0;
    resetCount++;
    printf("reset count: %i\n", resetCount);
    STORE_EE_ByteWrite( resetCount>>8, cEE_ResetCountH );
    STORE_EE_ByteWrite( (resetCount & 0x00FF), cEE_ResetCountL);
    break;
  default:
    break;
  }
  return resetCount;
}
#undef cMEM_USERCLASS_ID_SYS_c
