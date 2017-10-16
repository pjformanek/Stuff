/*------------------------------------------------------------------------------
	$File:		HW_PORTS.h	
	$Module:  Hardware Master Definition file
 	$Prefix:  HW
 	$Language: ANSI C
 	$Description:
		This file defines I/O PORT usage for a specific revision of hardware.
		
 	$Notes:
 	$Author:	KGANS, 2009-March-23
 	--------------------------------------------------------------------------
 	$Copyright (c) 2009 J.S. Foster Corporation  	All Rights Reserved
 	--------------------------------------------------------------------------
 	$End
	----------------------------------------------------------------------------*/

#ifndef cHW_PORTS_H
#define cHW_PORTS_H

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
			----- P O R T   M A P P I N G  and  A C C E S S -----
  ------------------------------------------------------------------------------
*/

#if 0
#define mHW_CurrentDrainMinimization()\
	mHW_UART1_RS232_INACTIVE()

#define mHW_CurrentDrainResume()\
	mHW_UART1_RS232_ACTIVE()
#endif

#if 0
/*  >>>>>>>>  WMS V2 Example >>>>>>>>>>>>>>>>>>>>>>>>>> */

// ------------------
// ----- PORT 0 -----
// ------------------


// -----------------------------------------------------------------------------
// P0_0 : UART-1 RS232 Voltage Level-Shifter
//			Note: This pin is also applied as SCK by the CC1010 HW during 
//					in-circuit flash programming
//
#define mHW_PORT_P0_0_Init() \
	\
	PORTDIRBIT(0,0,cPxDIR_PinAsOutput);\
	mHW_UART1_RS232_ACTIVE()

#define mHW_UART1_RS232_ACTIVE()  	PORTBIT(0,0) = (cPxDATA_H)
#define mHW_UART1_RS232_INACTIVE()	PORTBIT(0,0) = (cPxDATA_L)

/* <<<<<<<<<<<<<<<<<<<<<<  WMS V2 Example <<<<<<<<<<<<<<<<<<<<< */
#endif

  //CURRENT DEFINES REGARDING LEDS ...must be changed if want to use any LEDS
  //other than LED15 & LED16 ...as those are the ony ones configured to PORTC 
  #define GPIO_LED                          GPIOC
  #define RCC_APB2Periph_GPIO_LED           RCC_APB2Periph_GPIOC


  //CURRENT DEFINES REGARDING USART2  -SPM
  #define GPIO_USART2                       GPIOA
  #define GPIO_USART3                       GPIOC


  //CURRENT DEFINES REGARDING External Interrupts from button2 on dev board
  #define GPIO_KEY_BUTTON2                   GPIOB
  #define RCC_APB2Periph_GPIO_KEY_BUTTON2    RCC_APB2Periph_GPIOB
  #define GPIO_PIN_KEY_BUTTON2               GPIO_Pin_5   
  #define EXTI_LINE_KEY_BUTTON2              EXTI_Line5   
  #define GPIO_PORT_SOURCE_KEY_BUTTON2       GPIO_PortSourceGPIOB
  #define GPIO_PIN_SOURCE_KEY_BUTTON2        GPIO_PinSource5  


  //CURRENT DEFINES REGARDING External Interrupts from button3 on dev board
  #define GPIO_KEY_BUTTON3                   GPIOC
  #define RCC_APB2Periph_GPIO_KEY_BUTTON3    RCC_APB2Periph_GPIOC
  #define GPIO_PIN_KEY_BUTTON3               GPIO_Pin_4   
  #define EXTI_LINE_KEY_BUTTON3              EXTI_Line4   
  #define GPIO_PORT_SOURCE_KEY_BUTTON3       GPIO_PortSourceGPIOC
  #define GPIO_PIN_SOURCE_KEY_BUTTON3        GPIO_PinSource4  


  //CURRENT DEFINES REGARDING External Interrupts from PA.10 for incoming Ring
  #define GPIO_RING                         GPIOA
  #define RCC_APB2Periph_GPIO_RING          RCC_APB2Periph_GPIOA
  #define GPIO_PIN_RING                     GPIO_Pin_10
  #define EXTI_LINE_RING                    EXTI_Line10 
  #define GPIO_PORT_SOURCE_RING             GPIO_PortSourceGPIOA
  #define GPIO_PIN_SOURCE_RING              GPIO_PinSource10  

  //CURRENT DEFINES REGARDING External Interrupts from PC.6 for incoming DTMF
  #define GPIO_DTMF                         GPIOC
  #define RCC_APB2Periph_GPIO_DTMF          RCC_APB2Periph_GPIOC
  #define GPIO_PIN_DTMF_Rx                  GPIO_Pin_6
  #define EXTI_LINE_DTMF                    EXTI_Line6
  #define GPIO_PORT_SOURCE_DTMF             GPIO_PortSourceGPIOC
  #define GPIO_PIN_SOURCE_DTMF              GPIO_PinSource6
  
  //CURRENT DEFINES REGARDING PB12-15 DMTF inputs
  #define mHW_DTMF_GPIOx()      GPIOB
  #define mHW_DTMF_D3()         GPIO_Pin_15
  #define mHW_DTMF_D2()         GPIO_Pin_14
  #define mHW_DTMF_D1()         GPIO_Pin_13
  #define mHW_DTMF_D0()         GPIO_Pin_12
  #define GPIO_PIN_DTMF_Tx      GPIO_Pin_7
  
  //CURRENT DEFINES REGARDING MP3 BIT BANGING & CS FOR MP3 MOD  PB7 SDA1  PB10 SCL2 
  #define mHW_MP3_BB_GPIOx()         GPIOB
  #define mHW_MP3_CS_GPIOx()         GPIOB
  #define mHW_MP3_BB_PIN()           GPIO_Pin_7
  #define mHW_MP3_CS_PIN()           GPIO_Pin_10
  

  //CURRENT DEFINES REGARDING SPI1
  #define pcHW_SPI1_GPIOx        GPIOA
  #define pcHW_SP1_CSn_GPIOx     GPIOA

//JUAN
//  #define cHW_SPI1_CSn_PIN      GPIO_Pin_4
//  #define cHW_SPI1_SCK_PIN      GPIO_Pin_5
//  #define cHW_SPI1_MISO_PIN     GPIO_Pin_6
//  #define cHW_SPI1_MOSI_PIN     GPIO_Pin_7

  //CURRENT DEFINES REGARDING PWDN ON DTMP DECODER ( CP PIN )
  #define mHW_DTMF_PWDN_GPIOx()					GPIOC
  #define RCC_APB2Periph_GPIO_DTMF_PWDN RCC_APB2Periph_GPIOC
  #define mHW_DTMF_PWDN_PIN()						GPIO_Pin_7

  //CURRENT DEFINES REGARDING GDO_0
  #define mHW_SPI1_GD0_GPIOx()          GPIOA
  #define RCC_APB2Periph_GPIO_GDO_0     RCC_APB2Periph_GPIOA
  #define mHW_SPI1_GD0_PIN()            GPIO_Pin_9

  //CURRENT DEFINES REGARDING GDO_2
  #define mHW_SPI1_GD2_GPIOx()               GPIOB
  #define RCC_APB2Periph_GPIO_GDO_2          RCC_APB2Periph_GPIOB
  #define mHW_SPI1_GD2_PIN()                 GPIO_Pin_6

  //CURRENT DEFINES REGARDINF USART2
  #define mHW_USART2_GPIOx()      GPIOA
  #define mHW_USART2_TX_PIN()     GPIO_Pin_2
  #define mHW_USART2_RX_PIN()     GPIO_Pin_3

  //CURRENT DEFINES REGARDINF USART3  
  #define mHW_USART3_GPIOx()      GPIOC
  #define mHW_USART3_TX_PIN()     GPIO_Pin_10
  #define mHW_USART3_RX_PIN()     GPIO_Pin_11

/* ----------------------
	External 900 MHz PA
	...not populated on
		the Tandem Kit
		(CC1101 EM)
	---------------------*/
#define mHW_RFC_Tx_ExtPA_OFF() {}
#define mHW_RFC_Tx_ExtPA_ON() {}

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

#endif // cHW_PORTS_H

