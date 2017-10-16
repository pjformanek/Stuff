/*------------------------------------------------------------------------------
  	$File:		SYS.c
  	$Module:  	System Managment
  	$Prefix:  	SYS
  	$Language:	ANSI C

  	$Description:

  	$Notes:

  	$Author:	Jramirez, Jul 09, 2010
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __SYS_H__
#define __SYS_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "XPLAT.h"

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define mSYS_IWDG_ReloadCounter()                         IWDG_ReloadCounter()

#define mSYS_ADCx_ReadSolarVoltage()                      SYS_ReadADCx( cSYS_ADCx_SOLAR_CHANNEL, eSYS_ADCx_RETURN_VOLTAGE_VAL )
#define mSYS_ADCx_ReadBatteryVoltage()                    SYS_ReadADCx( cSYS_ADCx_BATT_CHANNEL, eSYS_ADCx_RETURN_VOLTAGE_VAL )

#define mSYS_ADCx_ReadSolarBin()                          SYS_ReadADCx( cSYS_ADCx_SOLAR_CHANNEL, eSYS_ADCx_RETURN_BIN_VAL )
#define mSYS_ADCx_ReadBatteryBin()                        SYS_ReadADCx( cSYS_ADCx_BATT_CHANNEL, eSYS_ADCx_RETURN_BIN_VAL )
 
#define mSYS_ADCx_ReadBatteryAverageBin()                 SYS_ReadADCx( cSYS_ADCx_BATT_CHANNEL, eSYS_ADCx_RETURN_BIN_VAL | eSYS_ADCx_RETURN_AVE_VAL )
#define mSYS_ADCx_ReadSolarAverageBin()                   SYS_ReadADCx( cSYS_ADCx_SOLAR_CHANNEL, eSYS_ADCx_RETURN_BIN_VAL | eSYS_ADCx_RETURN_AVE_VAL )

#define mSYS_ADCx_ReadBatteryAverageVoltage()             SYS_ReadADCx( cSYS_ADCx_BATT_CHANNEL, eSYS_ADCx_RETURN_VOLTAGE_VAL | eSYS_ADCx_RETURN_AVE_VAL )
#define mSYS_ADCx_ReadSolarAverageVoltage()               SYS_ReadADCx( cSYS_ADCx_SOLAR_CHANNEL, eSYS_ADCx_RETURN_VOLTAGE_VAL | eSYS_ADCx_RETURN_AVE_VAL )
 


/* Simple led  macro for main status (smt) led on WP4 HW Ver. 0.1 */
#define mGPIO_LED_SMT_TOGGLE()              GPIO_WriteBit(cGPIO_LED_SMT_GPIOx, cGPIO_LED_SMT_PIN, (teGPIO_BitAction)((1-GPIO_ReadOutputDataBit(cGPIO_LED_SMT_GPIOx, cGPIO_LED_SMT_PIN))));

#define mGPIO_LED_SMT(x)                 GPIO_WriteBit(cGPIO_LED_SMT_GPIOx, cGPIO_LED_SMT_PIN, x ); // pass ecGPIO_BitAction_SET or ecGPIO_BitAction_CLEAR

#if 0
#define mGPIO_SOLAR_LDO(x)               GPIO_WriteBit(cGPIO_SOLAR_LDO_GPIOx, cGPIO_SOLAR_LDO_PIN, x ); // pass ecGPIO_BitAction_SET or ecGPIO_BitAction_CLEAR
#endif                                                                                                         // or HI and LOW

#define mGPIO_SOLAR_LDO(x)               GPIO_WriteBit(cGPIO_SOLAR_BULK_CHARGE_GPIOx, cGPIO_SOLAR_BULK_CHARGE_PIN, x ); // pass ecGPIO_BitAction_SET or ecGPIO_BitAction_CLEAR
#define mGPIO_SOLAR_LDO_TOGGLE()         GPIO_WriteBit(cGPIO_SOLAR_BULK_CHARGE_GPIOx, cGPIO_SOLAR_BULK_CHARGE_PIN, (teGPIO_BitAction)((1-GPIO_ReadOutputDataBit(cGPIO_SOLAR_BULK_CHARGE_GPIOx, cGPIO_SOLAR_BULK_CHARGE_PIN))));
                                                                                                        // or HI and LOW

#define mGPIO_12V_DC_DC(x)               GPIO_WriteBit(cGPIO_12V_DC_DC_ENABLE_PIN_GPIOx, cGPIO_12V_DC_DC_ENABLE_PIN, x ); // pass ecGPIO_BitAction_SET or ecGPIO_BitAction_CLEAR
#define mGPIO_12V_DC_DC_TOGGLE()         GPIO_WriteBit(cGPIO_12V_DC_DC_ENABLE_PIN_GPIOx, cGPIO_12V_DC_DC_ENABLE_PIN, (teGPIO_BitAction)((1-GPIO_ReadOutputDataBit(cGPIO_12V_DC_DC_ENABLE_PIN_GPIOx, cGPIO_12V_DC_DC_ENABLE_PIN))));
                                                                                                        // or HI and LOW


#define mGPIO_RS232_ENABLE(x)            GPIO_WriteBit(cGPIO_RS232_INTERFACE_ENABLE_PIN_GPIOx, cGPIO_RS232_INTERFACE_ENABLE_PIN, x ); // pass ecGPIO_BitAction_SET or ecGPIO_BitAction_CLEAR
#define mGPIO_RS232_ENABLE_TOGGLE()      GPIO_WriteBit(cGPIO_RS232_INTERFACE_ENABLE_PIN_GPIOx, cGPIO_RS232_INTERFACE_ENABLE_PIN, (teGPIO_BitAction)((1-GPIO_ReadOutputDataBit(cGPIO_RS232_INTERFACE_ENABLE_PIN_GPIOx, cGPIO_RS232_INTERFACE_ENABLE_PIN))));
                                                                                                        // or HI and LOW


#define mGPIO_RS232_FORCE_OFF(x)          GPIO_WriteBit(cGPIO_RS232_INTERFACE_FORCE_ON_PIN_GPIOx, cGPIO_RS232_INTERFACE_FORCE_ON_PIN, x ); // pass ecGPIO_BitAction_SET or ecGPIO_BitAction_CLEAR
#define mGPIO_RS232_FORCE_OFF_TOGGLE()    GPIO_WriteBit(cGPIO_RS232_INTERFACE_FORCE_ON_PIN_GPIOx, cGPIO_RS232_INTERFACE_FORCE_ON_PIN, (teGPIO_BitAction)((1-GPIO_ReadOutputDataBit(cGPIO_RS232_INTERFACE_FORCE_ON_PIN_GPIOx, cGPIO_RS232_INTERFACE_FORCE_ON_PIN))));
                                                                                                        // or HI and LOW

#define mGPIO_WD_ENABLE(x)            GPIO_WriteBit(cGPIO_WD_PIN_GPIOx, cGPIO_WD_PIN, x ); // pass ecGPIO_BitAction_SET or ecGPIO_BitAction_CLEAR
#define mGPIO_WD_ENABLE_TOGGLE()      GPIO_WriteBit(cGPIO_WD_PIN_GPIOx, cGPIO_WD_PIN, (teGPIO_BitAction)((1-GPIO_ReadOutputDataBit(cGPIO_WD_PIN_GPIOx, cGPIO_WD_PIN))));



#define mSYS_Random_Byte()            (SYS_Generate_Random_Number( 0 )&0x00FF)

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

#define cSYS_ADCx_BATT_CHANNEL                            ADC_Channel_10
#define cSYS_ADCx_SOLAR_CHANNEL                           ADC_Channel_11

// CURRENT DEFINES FOR 12V DC/ DC COVERTER CONTROL LINE 

#define cRCC_APBxPeriph_12V_DC_DC_ENABLE                 RCC_APB2Periph_GPIOE
#define cGPIO_12V_DC_DC_ENABLE_PIN_GPIOx                 GPIOE
#define cGPIO_12V_DC_DC_ENABLE_PIN                       GPIO_Pin_15


// CURRENT DEFINE FOR THE REMOTE TRANSMITTER

#define cRCC_APBxPeriph_W16               RCC_APB2Periph_GPIOB
#define cGPIO_W16_GPIOx                   GPIOB
#define cGPIO_W16_PIN                     GPIO_Pin_2

// adder later to remote txmittr

#define cRCC_APBxPeriph_W13               RCC_APB2Periph_GPIOB
#define cGPIO_W13_GPIOx                   GPIOB
#define cGPIO_W13_PIN                     GPIO_Pin_15

// CURRENT DEFINES FOR THE OPTIONAL RS232 INTERFACE

#define cRCC_APBxPeriph_RS232_INTERFACE_ENABLE           RCC_APB2Periph_GPIOD
#define cGPIO_RS232_INTERFACE_ENABLE_PIN_GPIOx           GPIOD
#define cGPIO_RS232_INTERFACE_ENABLE_PIN                 GPIO_Pin_3

#define cRCC_APBxPeriph_RS232_INTERFACE_FORCE_ON         RCC_APB2Periph_GPIOD
#define cGPIO_RS232_INTERFACE_FORCE_ON_PIN_GPIOx         GPIOD
#define cGPIO_RS232_INTERFACE_FORCE_ON_PIN               GPIO_Pin_4

// CURRENT DEFINES REGARDING PED PINS
#define cRCC_APBxPeriph_GPIO_PED          RCC_APB2Periph_GPIOA
#define cGPIO_PED_PIN_GPIOx               GPIOA
#define cGPIO_PED_PIN                     GPIO_Pin_8
#define cGPIO_PIN_SOURCE_PED_PIN          GPIO_PinSource8
#define cGPIO_PORT_SOURCE_PED_PIN         GPIO_PortSourceGPIOA
#define cEXTI_LINE_PED_PIN                EXTI_Line8


// CURRENT DEFINES Aux PB input

#define cRCC_APBxPeriph_AUX_PB                    RCC_APB2Periph_GPIOB
#define cGPIO_AUX_PB_GPIOx                        GPIOB
#define cGPIO_AUX_PB_PIN                          GPIO_Pin_14
#define cGPIO_PIN_SOURCE_AUX_PB_PIN          GPIO_PinSource14
#define cGPIO_PORT_SOURCE_AUX_PB_PIN         GPIO_PortSourceGPIOB
#define cEXTI_LINE_AUX_PB_PIN                EXTI_Line14

// defines regarding trigger input (for speed sensor)
#define cRCC_APBxPeriph_GPIO_SPEED          RCC_APB2Periph_GPIOB
#define cGPIO_SPEED_PIN_GPIOx               GPIOB
#define cGPIO_SPEED_PIN                     GPIO_Pin_14
#define cGPIO_PIN_SOURCE_SPEED_PIN          GPIO_PinSource14
#define cGPIO_PORT_SOURCE_SPEED_PIN         GPIO_PortSourceGPIOB
#define cEXTI_LINE_SPEED_PIN                EXTI_Line14

//CURRENT DEFINES REGARDING Led's on new board version 0.1


#define cGPIO_LED_SMT_GPIOx                     GPIOB
#define cRCC_APBxPerih_GPIO_LED_SMT             RCC_APB2Periph_GPIOB
#define cGPIO_LED_SMT_PIN                       GPIO_Pin_12


//watchdog pin
#define cRCC_APBxPeriph_GPIO_WD           RCC_APB2Periph_GPIOE
#define cGPIO_WD_PIN_GPIOx                GPIOE
#define cGPIO_WD_PIN                      GPIO_Pin_6

#define cGPIO_lockout_GPIOx           GPIOC
#define cRCC_APBxPeriph_GPIO_lockout  RCC_APB2Periph_GPIOC
#define cGPIO_lockout_PIN             GPIO_Pin_6

#define cGPIO_Boot_Option_JW_GPIOx                   GPIOB
#define cRCC_APBxPeriph_GPIO_Boot_Option_JW          RCC_APB2Periph_GPIOB
#define cGPIO_Boot_Option_JW_PIN                     GPIO_Pin_13

/*------------------- Solar LDO -------------------*/

#define cGPIO_SOLAR_LDO_GPIOx                   GPIOE
#define cRCC_APBxPeriph_GPIO_SOLAR_LDO          RCC_APB2Periph_GPIOE
#define cGPIO_SOLAR_LDO_PIN                     GPIO_Pin_5


#define cGPIO_SOLAR_BULK_CHARGE_GPIOx           GPIOC
#define cRCC_APBxPeriph_GPIO_BULK_CHARGE        RCC_APB2Periph_GPIOC
#define cGPIO_SOLAR_BULK_CHARGE_PIN             GPIO_Pin_13


/*------------------- Solar LDO END -------------------*/

/*------------------- Power ADC -------------------*/
#define cGPIO_SOLAR_ADC_GPIOx                   GPIOC
#define cRCC_APBxPeriph_GPIO_SOLAR_ADC          RCC_APB2Periph_GPIOC
#define cRCC_APBxPeriph_ADCx_SOLAR_ADC          RCC_APB2Periph_ADC1
#define cGPIO_SOLAR_ADC_PIN                     GPIO_Pin_1


#define cGPIO_BATT_ADC_GPIOx                   GPIOC
#define cRCC_APBxPeriph_GPIO_BATT_ADC          RCC_APB2Periph_GPIOC
#define cRCC_APBxPeriph_ADCx_BATT_ADC          RCC_APB2Periph_ADC1
#define cGPIO_BATT_ADC_PIN                     GPIO_Pin_0


/*------------------- Power ADC END -------------------*/

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */


/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef enum eSYS_ADCx_RETURN_TYPE {
  eSYS_ADCx_RETURN_VOLTAGE_VAL = 0x01,
  eSYS_ADCx_RETURN_BIN_VAL,
  eSYS_ADCx_RETURN_AVE_VAL = 0x04,  

}eSYS_ADCx_RETURN_TYPE;

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */
u8 SYS_Dimming ( void );
u8 SYS_Dimming_Ceiling ( tsXplatCmdPacketStruct * tsXplatCmdPacket );
u8 SYS_Dimming_OnOff ( tsXplatCmdPacketStruct * tsXplatCmdPacket );
void SYS_Dimming_Values_Init();
void SYS_Init( void );
void SYS_Task( void );
void SYS_Reset( void );
//void SYS_ReloadInWatchDogTimer( void );

void SYS_ADCxConfig( void );
u16 SYS_ReadADCx( u8 bAdcChannel, u8 bAdcTypeFlags );

u8 SYS_XplatGetVoltagesRspFuncHandler( tsXplatCmdPacketStruct * tsXplatCmdPacket );
u8 SYS_XplatGetTempRspFuncHandler( tsXplatCmdPacketStruct * tsXplatCmdPacket );

void SYS_SchGetVoltagesRspActivity( u16 wDuration, u16 wInterval, u8 bFlag );
void SYS_SchGetTempRspActivity( u16 wDuration, u16 wInterval, u8 bFlag );


void SYS_CLKConfig_STOP_Wake(void);

bool SYS_Get_PED_Status();

void SYS_Set_PED_Status( bool status );

bool SYS_Get_SPEED_Status();
void SYS_Set_SPEED_Status( bool status );

bool SYS_Get_AUX_PED_Status();
void SYS_Set_AUX_PED_Status( bool status );

u8 SYS_Get_OLDSZ_Status();
void SYS_Set_OLDSZ_Status( u8 status );

u32 SYS_GetFlashDurationValue( void );
void SYS_EnterSleepMode();
//void SYS_EnterSleepMode( u32 ulSleepTime );
void SYS_Test( void );
void GPIO_WATCHDOG_Configuration( void );
void GPIO_lockout_Configuration( u8 what );

void SYS_KICK_THE_DOG ( u8 bSleep );

void GPIO_PED_Configuration( void );
void EXTINT_PED_Configuration( void );
void NVIC_PED_Configuration( FunctionalState NewState );

u16 SYS_Generate_Random_Number( u16 wSeed );
void GPIO_SPEED_Configuration( void );
void EXTINT_SPEED_Configuration( void );
void NVIC_SPEED_Configuration( FunctionalState NewState );


void EXTINT_AUX_PB_Configuration( void );
void GPIO_AUX_PB_Configuration( void ) ;
void NVIC_AUX_PB_Configuration( FunctionalState NewState );

void GPIO_W16_Configuration( void );
void GPIO_W13_Configuration( void );
void GPIO_JW_Configuration( void );

void SYS_Set_Sleep_Type_Flag( bool boSleep_Type );
bool SYS_Get_Sleep_Type_Flag( void );

void SYS_Set_Debug_Flag( bool boDebugFlag );
bool SYS_Get_Debug_Flag( void );


u8 SYS_Enter_Debug_FuncHandler( tsXplatCmdPacketStruct * tsXplatCmdPacket );
u8 SYS_Exit_Debug_FuncHandler( tsXplatCmdPacketStruct * tsXplatCmdPacket );

void SYS_OnResetNotification( void );
void SYS_IncrementResetCount( void );

#endif // __SYS_H__

