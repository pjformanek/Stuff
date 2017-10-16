/*------------------------------------------------------------------------------
  	$File:		UART_Config.h	
  	$Module:  	Header file for UART_Config.c
  	$Prefix:  	UART
  	$Language:	ANSI C
  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Dec 23, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __USART_H__
#define __USART_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define UART5_WAIT_AND_SEND(x) do { while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET){ }  USART_SendData(UART5, x); } while (0)
#define UART4_WAIT_AND_SEND(x) do { while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET){ }  USART_SendData(UART4, x); } while (0)
#define UART3_WAIT_AND_SEND(x) do { while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET){ }  USART_SendData(USART3, x); } while (0)
#define UART2_WAIT_AND_SEND(x) do { while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){ }  USART_SendData(USART2, x); } while (0)
#define UART1_WAIT_AND_SEND(x) USART_SendData(USART1, x);

#define mUSART_GSM_RECEIVE()   USART_ReceiveData( USART2 )

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */
#define cUSART_MAX_BUFFER_LENGTH     256

#ifdef cHW_DEV_BOARD

#define cUSART_USART_DEBUG_ENABLE     cUSART_USART_3_ENABLE
#define cUSART_USART_GSM_ENABLE       cUSART_USART_2_ENABLE
#define cUSART_USART_SD_ENABLE        cUSART_USART_1_ENABLE
#define mUSART_DEBUG_WAIT_AND_SEND(x) UART3_WAIT_AND_SEND(x)
#define mUSART_GSM_WAIT_AND_SEND(x)   UART2_WAIT_AND_SEND(x)
#define mUSART_SD_WAIT_AND_SEND(x)    UART1_WAIT_AND_SEND(x)

#else

#define cUSART_GSM_RX_IntFlag         bUSART2_RX_IntFlag


#define cUSART_USART_DEBUG_ENABLE     cUSART_USART_1_ENABLE
#define cUSART_USART_GSM_ENABLE       cUSART_USART_2_ENABLE
#define cUSART_USART_SD_ENABLE        cUSART_USART_2_ENABLE
#define cUSART_USART_BT_ENABLE        cUSART_USART_4_ENABLE


#define mUSART_DEBUG_WAIT_AND_SEND(x) UART1_WAIT_AND_SEND(x)
#define mUSART_GSM_WAIT_AND_SEND(x)   UART2_WAIT_AND_SEND(x)
#define mUSART_SD_WAIT_AND_SEND(x)    UART1_WAIT_AND_SEND(x)
#define mUSART_BT_WAIT_AND_SEND(x)    UART4_WAIT_AND_SEND(x)

// pass a byte here 
#define mUSART_SIMPLE_DEBUG_BYTE_MSG(x)    mUSART_DEBUG_WAIT_AND_SEND('\n');  \
                                      mUSART_DEBUG_WAIT_AND_SEND(x); \
                                      mUSART_DEBUG_WAIT_AND_SEND('\n');


#endif


#define cUSART_USART_1_ENABLE        1
#define cUSART_USART_2_ENABLE        2
#define cUSART_USART_3_ENABLE        3
#define cUSART_USART_4_ENABLE        4
#define cUSART_USART_5_ENABLE        5

#define cUSART_TEST 10


/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */
//usart 1 is usb and gets this sense line for preventing sleep when usb connected
#define cGPIO_USBSENSE_GPIOx               GPIOB
#define cGPIO_USBSENSE_PIN                 GPIO_Pin_5
#define cGPIO_APBxPeriph_GPIO_USBSENSE     RCC_APB2Periph_GPIOB
/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
extern vu16 wUsart1Count;
extern vu16 wUsart1Count2;
extern vu16 wUsart2Count;
extern vu16 wUsart2Count2;
extern vu16 wUsart3Count;
extern vu16 wUart4Count;
extern vu16 wUart4Count2;

extern vu8 USART_EnableUsart1Printf;
extern vu8 USART_EnableUsart2Printf;
extern vu8 USART_EnableUsart3Printf;

extern vu8 USART_EnableUsartX_Printf;


extern vu8 bUSART1_RX_IntFlag;
extern vu8 bUSART2_RX_IntFlag;
extern vu8 bUSART3_RX_IntFlag;
extern vu8 bUART4_RX_IntFlag;

extern vu32 lwUSART1TimeStamp;
extern vu8 setTimer1;
extern vu8 buffToggle1;

extern vu32 lwUSART2TimeStamp;
extern vu8 setTimer2;
extern vu8 buffToggle2;

extern vu32 lwUART4TimeStamp;
extern vu8 setTimer4;
extern vu8 buffToggle4;

#if 1
extern vu8 bUSART3_RX_Buffer[1];
#else
extern vu8 bUSART3_RX_Buffer[cUSART_MAX_BUFFER_LENGTH];
#endif

extern vu8 bUSART1_RX_Buffer[cUSART_MAX_BUFFER_LENGTH];
extern vu8 bUSART1_RX_Buffer2[cUSART_MAX_BUFFER_LENGTH];
extern vu8 bUSART2_RX_Buffer[cUSART_MAX_BUFFER_LENGTH];
extern vu8 bUSART2_RX_Buffer2[cUSART_MAX_BUFFER_LENGTH];
extern vu8 bUART4_RX_Buffer[cUSART_MAX_BUFFER_LENGTH];
extern vu8 bUART4_RX_Buffer2[cUSART_MAX_BUFFER_LENGTH];
extern vu8 bUSART_debugTriggerUsart3;
extern vu8 bUSART_debugTriggerUsart2;

//static u8 bUSART_Usart2CountBufferFlag;

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */
void USART_Config_Usart1IdleIt( FunctionalState NewState );
void USART_Config_Usart2IdleIt( FunctionalState NewState );
void USART_Config_Usart3IdleIt( FunctionalState NewState );

void USART_Usart1Config( void );
void USART_Usart2Config( void );
void USART_Usart3Config( void );
void USART_Usart4Config( void );
void USART_Usart5Config( void );
void DMA_USART2_RX( void );
void DMA_USART1_TX( void );
void LSY201_GO( void );
void LSY201_RequestCam( u8 * pbCmd, u8 bCmdLen, u8 * pbBuffer, u8 bBufferLen, u32 lwTimeOut );
void LSY201_Set_Baud_Rate ( u16 wBaudRate );
void LSY201_Set_Image_Size ( u16 wPixelSize );
void LSY201_Reset ( void );
void LSY201_Take_Picture ( void );
void LSY201_Get_Picture ( void );
void LSY201_Stop ( void );
void LSY201_PowerSave ( u16 wMode );
void LSY201_Compression_Ratio ( u16 wRatio );
u8 LSY201_Transfer_IsDone ( void );

void USART1Input ( void );
void USART1Output (void );
void USART5Input ( void );
void USART5Output ( void );

#endif // __USART_H__
