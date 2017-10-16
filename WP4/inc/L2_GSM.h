/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : L2_GSM.h
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : June 10, 2009
* Description        : Header file for L2_GSM.c
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  
  u8 bL2_GSM_RSP1;
  
}tpL2_GSM_AT_POSSIBLE_RSP;

/* Exported constants --------------------------------------------------------*/
#define cAT_CMD                             "AT\r\n"
#define cAT_CMD_VOICE                       "AT+FCLASS=8\r\n"
#define cAT_CMD_CARRIER_DETECT               "AT+COPS=?\r\n"
#define cAT_CMD_DIAL_TEST                    "ATD2504151169\r\n"

#define cAT_CMD_ANSWER                      "ATA\r\n"
#define cAT_CMD_HELLO                       "HELLO\r\n"
#define cAT_CMD_AUDIO_PATH_HW               "AT#CAP=0\r\n"
#define cAT_CMD_AUDIO_PATH_SW_HF            "AT#CAP=1\r\n"
#define cAT_CMD_AUDIO_PATH_SW_MT            "AT#CAP=2\r\n"
#define cAT_CMD_AUTO_ANSWER_1_RINGS         "ATS0=1\r\n" 
#define cAT_CMD_SOFTWARE_RESET              "ATZ0\r\n"

#define cAT_RSP_ERROR                       "ERROR\r\n"
#define cAT_RSP_NO_CARRIER                  "NO CARRIER\r\n"
#define cAT_RSP_OK                          "OK\r\n"


#define cL2_GSM_NO_TIMEOUT                  0x00
#define cL2_GSM_TIM1_TIMEOUT                0x31
/* Exported macro ------------------------------------------------------------*/
#define mL2_GSM_SEND_AT_CMD_USART2(x)       UART2_WAIT_AND_SEND(x) //do { while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){ }  USART_SendData(USART2, x); } while (0)


extern u8 bL2_GSM_RspIndex[];

/* Exported functions ------------------------------------------------------- */
u8 L2_GSM_WaitForCommand( u16 wTimeOutsms ); 
u16 L2_GSM_RspLookUpTable( u8 * pbUSART_RX_Buffer ); 