/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : ATcommands.h
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Dec 23, 2008
* Description        : Header file for ATcommands.c
********************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#define mAT_CMD()                             "AT\r\n"
#define mAT_CMD_VOICE()                       "AT+FCLASS=8\r\n"
#define mAT_CMD_CARRIERDETECT()               "AT+COPS=?\r\n"
#define mAT_CMD_DIALTEST()                    "ATD2504151169\r\n"
#define mAT_RESPONSE_OK()                     "OK\r\n"
#define mAT_RESPONSE_ERROR()                  "ERROR\r\n"
#define mAT_PURGE_TX_BUFFER()                 "FFFF\r\n"
#define mAT_CMD_ANSWER()                      "ATA\r\n"
#define mAT_CMD_HELLO()                       "HELLO\r\n"
#define mAT_CMD_AUDIO_PATH_HW()               "AT#CAP=0\r\n"
#define mAT_CMD_AUDIO_PATH_SW_HF()            "AT#CAP=1\r\n"
#define mAT_CMD_AUDIO_PATH_SW_MT()            "AT#CAP=2\r\n"
#define mAT_CMD_NO_CARRIER()                  "NO CARRIER\r\n"
#define mAT_CMD_AUTO_ANSWER_1_RINGS()         "ATS0=1\r\n" 
#define mAT_CMD_SOFTWARE_RESET()              "ATZ0\r\n"
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Send_AT_CMD_USART2 ( u8* command );
void Send_AT_CMD_USART3 ( u8* command );
void DO_ATcommands ( void );
void AT_App_Main( u8  TelitCHar );