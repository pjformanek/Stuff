/*------------------------------------------------------------------------------
  	$File:		UART_Config.c
  	$Module:  	Configuration for UARTS
  	$Prefix:  	UART
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Aug 22, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_USART_CONFIG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "MEM.h"
#include "NVIC_Config.h"
#include "GPIO_Config.h"

#include "platform_config.h"

#include "TimerManager.h"
#include "USART_Config.h"

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;
/*------------------------------------------------------------------------------
				----- D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define USART1_DR_Base  0x40013804
#define USART2_DR_Base  0x40004404

#define Baud9600    0xAEC8
#define Baud19200   0x56E4
#define Baud38400   0x2AF2
#define Baud57600   0x1C4C
#define Baud115200  0x0DA6

#define Pixel_640x480 0x00
#define Pixel_320x240 0x11
#define Pixel_160x120 0x22

#define PwrSave_ON  0x01
#define PwrSave_OFF 0x00
/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */
#define cUSART1_OnFlag              0x01
#define cUSART2_OnFlag              0x02
#define cUSART3_OnFlag              0x04
#define cUSART4_OnFlag              0x08
#define cUSART5_OnFlag              0x10


//CURRENT DEFINES REGARDING USART1
#define cGPIO_USART1_GPIOx                 GPIOA
#define cGPIO_USART1_TX_PIN                GPIO_Pin_9
#define cGPIO_USART1_RX_PIN                GPIO_Pin_10
#define cRCC_APBxPeriph_GPIO_USART1        RCC_APB2Periph_GPIOA

//CURRENT DEFINES REGARDING USART2
#define cGPIO_USART2_GPIOx                 GPIOA
#define cGPIO_USART2_TX_PIN                GPIO_Pin_2
#define cGPIO_USART2_RX_PIN                GPIO_Pin_3
#define cRCC_APBxPeriph_GPIO_USART2        RCC_APB2Periph_GPIOA

//CURRENT DEFINES REGARDING USART3
#define cGPIO_USART3_GPIOx                 GPIOB
#define  cGPIO_USART3_TX_PIN               GPIO_Pin_10
#define cGPIO_USART3_RX_PIN                GPIO_Pin_11
#define cRCC_APBxPeriph_GPIO_USART3        RCC_APB2Periph_GPIOB

//CURRENT DEFINES REGARDING USART4
#define cGPIO_USART4_GPIOx                 GPIOC
#define cGPIO_USART4_TX_PIN                GPIO_Pin_10
#define cGPIO_USART4_RX_PIN                GPIO_Pin_11
#define cRCC_APBxPeriph_GPIO_USART4        RCC_APB2Periph_GPIOC

//CURRENT DEFINES REGARDING USART5
#define cGPIO_USART5_TX_GPIOx                 GPIOC
#define cGPIO_USART5_RX_GPIOx                 GPIOD
#define cGPIO_USART5_TX_PIN                   GPIO_Pin_12
#define cGPIO_USART5_RX_PIN                   GPIO_Pin_2
#define cRCC_APBxPeriph_TX_GPIO_USART5        RCC_APB2Periph_GPIOC
#define cRCC_APBxPeriph_RX_GPIO_USART5        RCC_APB2Periph_GPIOD



/*------------------------------------------------------------------------------
				----- L O C A L   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N   P R O T O T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- L O C A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
USART_InitTypeDef USART_InitStructure;


vu8 USART_EnableUsart2Printf = 0;
vu8 USART_EnableUsart3Printf = 0;
vu8 USART_EnableUsart1Printf = 0;

vu8 USART_EnableUsartX_Printf = 0;

static u8 bUSARTx_OnFlag = 0x00;
static u16 wSize = 0;
u8 RxBuffer2[10];

/*------------------------------------------------------------------------------
				----- G L O B A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

vu16 wUsart3Count = 0;

vu16 wUsart1Count = 0;
vu16 wUsart1Count2 = 0;
vu16 wUsart2Count = 0;
vu16 wUsart2Count2 = 0;
vu16 wUart4Count = 0;
vu16 wUart4Count2 = 0;

vu8 bUSART1_RX_IntFlag = 0;
vu8 bUSART2_RX_IntFlag = 0;
vu8 bUSART3_RX_IntFlag = 0;
vu8 bUART4_RX_IntFlag = 0;
#if 1
vu8 bUSART3_RX_Buffer[1] = {0};
#else
vu8 bUSART3_RX_Buffer[cUSART_MAX_BUFFER_LENGTH] = {0};
#endif

vu8 bUSART1_RX_Buffer[cUSART_MAX_BUFFER_LENGTH] = {0};
vu8 bUSART1_RX_Buffer2[cUSART_MAX_BUFFER_LENGTH] = {0};
vu8 bUSART2_RX_Buffer[cUSART_MAX_BUFFER_LENGTH] = {0};
vu8 bUSART2_RX_Buffer2[cUSART_MAX_BUFFER_LENGTH] = {0};
vu8 bUART4_RX_Buffer[cUSART_MAX_BUFFER_LENGTH] = {0};
vu8 bUART4_RX_Buffer2[cUSART_MAX_BUFFER_LENGTH] = {0};

vu8 bUSART_debugTriggerUsart2 = 0;

vu32 lwUSART1TimeStamp = 0;
vu8 setTimer1 = 0;
vu8 buffToggle1 = 0;

vu32 lwUSART2TimeStamp = 0;
vu8 setTimer2 = 0;
vu8 buffToggle2 = 0;

vu32 lwUART4TimeStamp = 0;
vu8 setTimer4 = 0;
vu8 buffToggle4 = 0;
//static u8 bUSART_Usart2CountBufferFlag = 0;
/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */


void USART1Output( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Configure USART2 Rx (PA.03) as output open drain */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART1_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init( cGPIO_USART1_GPIOx, &GPIO_InitStructure );
}
void USART1Input( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Configure USART2 Rx (PA.03) as output open drain */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART1_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init( cGPIO_USART1_GPIOx, &GPIO_InitStructure );  
}
void USART5Output( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Configure USART2 Rx (PA.03) as output open drain */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART5_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init( cGPIO_USART5_RX_GPIOx, &GPIO_InitStructure );
}
void USART5Input( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Configure USART2 Rx (PA.03) as output open drain */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART5_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init( cGPIO_USART5_RX_GPIOx, &GPIO_InitStructure );  
}
/*------------------------------------------------------------------------------
	$Function: GPIO_USART1Configuration
	$Description: Configures USART1 GPIO

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_USART1Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_USART1 , ENABLE );

  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART1_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_USART1_GPIOx, &GPIO_InitStructure );

  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART1_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init( cGPIO_USART1_GPIOx, &GPIO_InitStructure );
  
  RCC_APB2PeriphClockCmd( cGPIO_APBxPeriph_GPIO_USBSENSE , ENABLE );
  
  /* Configure USART1 USBSENSE (PB.5) as input floating */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USBSENSE_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init( cGPIO_USBSENSE_GPIOx, &GPIO_InitStructure );
}

/*------------------------------------------------------------------------------
	$Function: NVIC_USART1_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_USART1_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}



/*------------------------------------------------------------------------------
	$Function: GPIO_USART2Configuration
	$Description: Configures USART2 GPIO ( Telit device )

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_USART2Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_USART2 , ENABLE );

  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART2_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_USART2_GPIOx, &GPIO_InitStructure );

  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART2_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init( cGPIO_USART2_GPIOx, &GPIO_InitStructure );
}

/*------------------------------------------------------------------------------
	$Function: NVIC_USART2_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_USART2_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the USART2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}


/*------------------------------------------------------------------------------
	$Function: GPIO_USART3Configuration
	$Description: Configures USART3 GPIO ( Debugger )

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_USART3Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
#ifdef cHW_DEV_BOARD
  /* remap USART3 to PC.10 and PC.11*/
  GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE); // >> No remap needed for new board Ver 0.1 <<
#endif

  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_USART3 , ENABLE );

   /* Configure USART3 Tx (PB.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART3_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_USART3_GPIOx, &GPIO_InitStructure );

  /* Configure USART3 Rx (PB.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART3_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init( cGPIO_USART3_GPIOx, &GPIO_InitStructure );
}

/*------------------------------------------------------------------------------
	$Function: NVIC_USART3_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_USART3_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the USART3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  // was 3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // was 3
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}
/*------------------------------------------------------------------------------
	$Function: NVIC_USART5_Configuration
	$Description: Configures the nested vectored interrupt controller.

	$Inputs: FunctionalState NewState - Enable or disable state
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void NVIC_USART5_Configuration( FunctionalState NewState )
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the USART3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  // was 3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        // was 3
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
}

/*------------------------------------------------------------------------------
	$Function: GPIO_USART4Configuration
	$Description: Configures USART3 GPIO ( Debugger )

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_USART4Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_USART4 , ENABLE );

  /* Configure USART3 Tx (PB.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART4_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_USART4_GPIOx, &GPIO_InitStructure );

  /* Configure USART3 Rx (PB.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART4_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init( cGPIO_USART4_GPIOx, &GPIO_InitStructure );
}

/*------------------------------------------------------------------------------
	$Function: GPIO_USART5Configuration
	$Description: Configures USART3 GPIO ( Debugger )

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_USART5Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_TX_GPIO_USART5 , ENABLE );
  //RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_RX_GPIO_USART5 , ENABLE );

  /* Configure UART5 Tx (PC.12) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART5_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( cGPIO_USART5_TX_GPIOx, &GPIO_InitStructure );

  /* Configure UART5 Rx (PD.02) as input floating */
  GPIO_InitStructure.GPIO_Pin = cGPIO_USART5_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init( cGPIO_USART5_RX_GPIOx, &GPIO_InitStructure );
}

/*------------------------------------------------------------------------------
				----- G L O B A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
	$Function: USART_Usart1Config
	$Description: Main usart configuration for usart1

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void USART_Usart1Config( void )
{
  if( !(bUSARTx_OnFlag&cUSART1_OnFlag) )
  {
    bUSARTx_OnFlag |= cUSART1_OnFlag;
    GPIO_USART1Configuration();

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE );

    /*----------------------------------USART1 SETTINGS---------------------------------------------*/
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure USART1 */
    USART_Init(USART1, &USART_InitStructure);

    /* Enable USART1 Receive interrupts */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);


    /* Enable USART1 Transmit interrupts */
   // USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

    /* Enable the USART1 */
    USART_Cmd(USART1, ENABLE);

    NVIC_USART1_Configuration( ENABLE );
  }
}

/*------------------------------------------------------------------------------
	$Function: USART_Usart2Config
	$Description: Main usart configuration for usart2

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void USART_Usart2Config( void )
{

  if( !(bUSARTx_OnFlag&cUSART2_OnFlag) )
  {
    bUSARTx_OnFlag |= cUSART2_OnFlag;
    GPIO_USART2Configuration();

    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );

    /*----------------------------------USART2 SETTINGS---------------------------------------------*/
    // GSM Telit
    USART_InitStructure.USART_BaudRate = 115200;
//#ifdef COLE_MODE
//    USART_InitStructure.USART_BaudRate = 38400;
//#endif
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure USART2 */
    USART_Init(USART2, &USART_InitStructure);

    /* Enable USART2 Receive interrupts */
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); 
    
    /* Enable USART2 Transmit interrupts */
    //USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

    /* Enable the USART2 */
    USART_Cmd(USART2, ENABLE);

    NVIC_USART2_Configuration( ENABLE );
  }
}

/*------------------------------------------------------------------------------
	$Function: USART_Usart3Config
	$Description: Main usart configuration for usart3

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void USART_Usart3Config( void )
{
  if( !(bUSARTx_OnFlag&cUSART3_OnFlag) )
  {
    bUSARTx_OnFlag |= cUSART3_OnFlag;
    GPIO_USART3Configuration();

    /* USARTx configuration ------------------------------------------------------*/
    /* USARTx configured as follow:
    - BaudRate = 38400 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */


    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3, ENABLE );

    /*----------------------------------USART3 SETTINGS---------------------------------------------*/
    // Debug port RS232
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure USART3 */
    USART_Init(USART3, &USART_InitStructure);

    /* Enable USART3 Receive interrupts */
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
    /* Enable USART3 Transmit interrupts */
    //USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

    /* Enable the USART3 */
    USART_Cmd(USART3, ENABLE);

    NVIC_USART3_Configuration( ENABLE );
  }

}

/*------------------------------------------------------------------------------
	$Function: USART_Usart1Config
	$Description: Main usart configuration for usart4

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void USART_Usart4Config( void )
{
  if( !(bUSARTx_OnFlag&cUSART4_OnFlag) )
  {
    bUSARTx_OnFlag |= cUSART4_OnFlag;
    GPIO_USART4Configuration();

    RCC_APB1PeriphClockCmd( RCC_APB1Periph_UART4, ENABLE );

    USART_InitStructure.USART_BaudRate = 9600;//115200
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure UART4 */
    USART_Init(UART4, &USART_InitStructure);

    /* Enable UART4 Receive interrupts */
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);


    /* Enable USART2 Transmit interrupts */
    //USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

    /* Enable the UART4 */
    USART_Cmd(UART4, ENABLE);
    /*---------------------------------------------------------------------------------------------*/
  }
}

/*------------------------------------------------------------------------------
	$Function: USART_Usart5Config
	$Description: Main usart configuration for usart1

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void USART_Usart5Config( void )
{
  if( !(bUSARTx_OnFlag&cUSART5_OnFlag) )
  {
    bUSARTx_OnFlag |= cUSART5_OnFlag;
    GPIO_USART5Configuration();

    RCC_APB1PeriphClockCmd( RCC_APB1Periph_UART5, ENABLE );
#ifdef cGLB_PRODUCT_OLDSZ_READER
    USART_InitStructure.USART_BaudRate = 38400;
    //printf("UART5\n");
#else
    USART_InitStructure.USART_BaudRate = 115200;
#endif
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure UART5 */
    USART_Init(UART5, &USART_InitStructure);

    /* Enable UART5 Receive interrupts */
    
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(UART5, USART_IT_FE, ENABLE);
    //USART_ITConfig(UART5, USART_IT_ORE, ENABLE);
    //USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);

    /* Enable the USART5 */
    USART_Cmd(UART5, ENABLE);
    NVIC_USART5_Configuration( ENABLE );
    /*---------------------------------------------------------------------------------------------*/
  }
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
void USART_Config_Usart1IdleIt( FunctionalState ENABLE )
{
  USART_ITConfig( USART1, USART_IT_IDLE, ENABLE );
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
void USART_Config_Usart2IdleIt( FunctionalState ENABLE )
{
  USART_ITConfig( USART2, USART_IT_IDLE, ENABLE );
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
void USART_Config_Usart3IdleIt( FunctionalState ENABLE )
{
  USART_ITConfig( USART3, USART_IT_IDLE, ENABLE );
}

void  Usart_DMAInit( void )
{
   /* Configure the GPIO ports */
  //GPIO_USART1Configuration();
  //GPIO_USART2Configuration();
  
  /* System Clocks Configuration */
  /* DMA1 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  /* Enable USART1, GPIOA, GPIOB and AFIO clocks */
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE); 
  /* Enable USART2 clock */     
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
  /* Setup NVIC channels */
  NVIC_DMA1_Ch4_Configuration(ENABLE);
  NVIC_DMA1_Ch6_Configuration(ENABLE); 

  /* Enable USART2 Receive interrupts */
  USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
  USART_ITConfig(USART2, USART_IT_IDLE, DISABLE); 
  /* Init USART struct */
//  USART_InitStructure.USART_BaudRate = 38400;
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;
//  USART_InitStructure.USART_Parity = USART_Parity_No;
//  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  /* Configure USART1 */
//  USART_Init(USART1, &USART_InitStructure);
  /* Configure USART2 */
//  USART_Init(USART2, &USART_InitStructure);
  


  /* Enable the USART1 */
  //USART_Cmd(USART1, ENABLE);
  /* Enable the USART2 */
  //USART_Cmd(USART2, ENABLE);
  DMA_USART2_RX( );
}


/*******************************************************************************
* Function Name  : DMA_Configuration
* Description    : Configures the DMA.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void DMA_USART2_RX( void )
//{
//  DMA_Cmd(DMA1_Channel6, DISABLE); 
//  
//  DMA_InitTypeDef DMA_InitStructure;
//
//  /* DMA1 Channel6 (triggered by USART2 Rx event) Config */
//  DMA_DeInit(DMA1_Channel6);  
//  DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_DR_Base;
//  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)RxBuffer2;
//  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//  DMA_InitStructure.DMA_BufferSize = 10;
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
//  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
//  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
//  DMA_Init(DMA1_Channel6, &DMA_InitStructure);
//  DMA_ITConfig(DMA1_Channel6, DMA_IT_HT, ENABLE);
//  DMA_ClearFlag(DMA1_FLAG_TC6);
//  DMA_Cmd(DMA1_Channel6, ENABLE);
//  /* Enable USART2 DMA Rx request */
//  USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
//}

//void DMA_USART1_TX ( void )
//{
//  DMA_Cmd(DMA1_Channel4, DISABLE);  
//  
//  DMA_InitTypeDef DMA_InitStructure;
//  
//  /* DMA1 Channel4 (triggered by USART1 Tx event) Config */
//  DMA_DeInit(DMA1_Channel4); 
//  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
//  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)RxBuffer2;
//  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
//  DMA_InitStructure.DMA_BufferSize = 10;
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
//  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
//  DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
//  DMA_ClearFlag(DMA1_FLAG_TC4);
//  DMA_Cmd(DMA1_Channel4, ENABLE);
//  /* Enable USART1 DMA TX request */
//  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);  
//}

void LSY201_GO ( void )
{
  DMA_Cmd(DMA1_Channel6, DISABLE);
  USART_DMACmd(USART2, USART_DMAReq_Rx, DISABLE);

  USART_Usart1Config();
  USART_Usart2Config();
  __enable_interrupt();
  
  LSY201_Set_Baud_Rate ( Baud115200 );
  //LSY201_Set_Image_Size ( Pixel_640x480 );
  //LSY201_Reset();
  //LSY201_Compression_Ratio ( 0x01 );
  LSY201_PowerSave ( PwrSave_ON ); 
  LSY201_PowerSave ( PwrSave_OFF );
  //LSY201_Take_Picture();
  //LSY201_Get_Picture();
  
  if (( wSize % 0x0A ) != 0 )
  {
    wSize = ( wSize / 0x0A ) + 1;
  }
  else
  {
    wSize /= 0x0A;
  }
  Usart_DMAInit();
  //sleep micro
}
void LSY201_RequestCam( u8 * pbCmd, u8 bCmdLen, u8 * pbBuffer, u8 bBufferLen, u32 lwTimeOut )
{
  u8 bCount = 0;
  u8 i = 0;
  u32 LSY201_Time_Stamp = TIMER_GetTimeStamp( 0 );
  bUSART2_RX_IntFlag = 0x80;
  USART_EnableUsartX_Printf = cUSART_USART_2_ENABLE;
  for ( i=0;i<bCmdLen;i++)
  {
    printf( "%c", pbCmd[i]);
  }
  if (bCmdLen != 16)
  {
    //while time out
    while( !TIMER_HasTimeStampElapsed( LSY201_Time_Stamp, lwTimeOut ))
    {
      if ( bUSART2_RX_IntFlag == 1 )
      {
        bUSART2_RX_IntFlag = 0x80;
        pbBuffer[bCount++] = USART_ReceiveData(USART2);
      }
      if ( bCount >=bBufferLen )
        break;
    }
    USART_EnableUsartX_Printf = cUSART_USART_1_ENABLE;
    
    for( i=0;i<bCount;i++)
    {
      printf("%c",pbBuffer[i]);
    }
  }
}

//possible input
// Baud9600     (0xAEC8)
// Baud19200    (0x56E4)
// Baud38400    (0x2AF2)
// Baud57600    (0x1C4C)
// Baud115200   (0x0DA6)
void LSY201_Set_Baud_Rate ( u16 wBaudRate )
{
  u8 LSY201_ResponseBuffer[6] = {0};
  u8 LSY201_Baud[] = {0x56, 0x00, 0x24, 0x03, 0x01, 0xFF, 0xFF};
  LSY201_Baud[5] = wBaudRate >> 8;
  LSY201_Baud[6] = wBaudRate;
  LSY201_RequestCam( LSY201_Baud, 7, LSY201_ResponseBuffer, 6, 1 );
  
  /* Disable the USART2 */
  USART_Cmd(USART2, DISABLE);
  
  USART_InitStructure.USART_BaudRate = wBaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  /* Configure USART2 */
  USART_Init(USART2, &USART_InitStructure);
  
  /* Enable the USART2 */
  USART_Cmd(USART2, ENABLE);
}

//Possible Inputs
//Pixel_640x480 (0x00)
//Pixel_320x240 (0x11)
//Pixel_160x120 (0x22)
void LSY201_Set_Image_Size ( u16 wPixelSize ) // must reset cam after
{
  u8 LSY201_ResponseBuffer[6] = {0};
  u8 LSY201_Pixel[] = {0x56, 0x00, 0x31, 0x05, 0x04, 0x01, 0x00, 0x19, 0xFF};
  LSY201_Pixel[8] = wPixelSize;
  LSY201_RequestCam( LSY201_Pixel, 9, LSY201_ResponseBuffer, 6, 1 );
}

void LSY201_Reset ( void )
{
  u8 LSY201_ResponseBuffer[78] = {0};
  u8 LSY201_Reset[] = {0x56, 0x00, 0x26, 0x00};
  LSY201_RequestCam( LSY201_Reset, 4, LSY201_ResponseBuffer, 78, 24 );
}

void LSY201_Take_Picture ( void )
{
  u8 LSY201_ResponseBuffer[6] = {0};  
  u8 LSY201_TakePic[] = {0x56, 0x00, 0x36, 0x01, 0x00};
  LSY201_RequestCam( LSY201_TakePic, 5, LSY201_ResponseBuffer, 6, 1 );
}

void LSY201_Get_Picture ( void )
{
  u8 LSY201_ResponseBuffer[9] = {0};   
  u8 LSY201_GetSize[] = {0x56, 0x00, 0x34, 0x01, 0x00};
  u8 LSY201_Read[] = {0x56, 0x00, 0x32, 0x0C, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x01};
  
  LSY201_RequestCam( LSY201_GetSize, 5, LSY201_ResponseBuffer, 9, 1 );
  
  LSY201_Read[12]=LSY201_ResponseBuffer[7];
  LSY201_Read[13]=LSY201_ResponseBuffer[8];
  wSize = ( LSY201_ResponseBuffer[7] << 8 ) + LSY201_ResponseBuffer[8];
  LSY201_RequestCam( LSY201_Read, 16, LSY201_ResponseBuffer, 9, 1 );
}

void LSY201_Stop ( void )
{
  u8 LSY201_ResponseBuffer[6] = {0};   
  u8 LSY201_Stop[] = {0x56, 0x00, 0x36, 0x01, 0x03};
  LSY201_RequestCam( LSY201_Stop, 5, LSY201_ResponseBuffer, 6, 1 );
}
//Possible Inputs
//PwrSave_ON (0x01)
//PwrSave_OFF (0x00)
void LSY201_PowerSave ( u16 wMode )
{
  u8 LSY201_ResponseBuffer[6] = {0};   
  u8 LSY201_Pwr[] = {0x56, 0x00, 0x3E, 0x03, 0x00, 0x01, 0xFF};
  
  LSY201_Pwr[6] = wMode;
  LSY201_RequestCam( LSY201_Pwr, 7, LSY201_ResponseBuffer, 6, 1 );  
}

//Possible Inputs
//0x00 to 0xFF
void LSY201_Compression_Ratio ( u16 wRatio )
{
  u8 LSY201_ResponseBuffer[7] = {0};   
  u8 LSY201_Set_Compression_Ratio[] = {0x56, 0x00, 0x31, 0x05, 0x01, 0x01, 0x12, 0x04, 0xFF}; 
  
  LSY201_Set_Compression_Ratio[8] = wRatio;
  LSY201_RequestCam( LSY201_Set_Compression_Ratio, 9, LSY201_ResponseBuffer, 7, 1 );
  
}

u8 LSY201_Transfer_IsDone ( void )
{
  static u16 wCount = 0;
  
  wCount++;
  if ( wCount >= wSize )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
#undef cMEM_USERCLASS_ID_USART_CONFIG_c
