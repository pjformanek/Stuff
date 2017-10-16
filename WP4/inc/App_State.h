/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : App_State.h
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Jan 6, 2009
* Description        : Header file for App_State.c
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define mAPP_STATE_NETWORK_SENDER_FLAG()        0
#define mAPP_STATE_NR_SENDER_FLAG()             1
#define mAPP_STATE_OWN_SENDER_FLAG()            2
#define mAPP_STATE_SUPERVISOR_SENDER_FLAG()     3
#define mAPP_STATE_GLB_SENDER_FLAG()           -1

#define mAPP_STATE_NETWORK_RECEIVER_FLAG()        0
#define mAPP_STATE_NR_RECEIVER_FLAG()             1
#define mAPP_STATE_OWN_RECEIVER_FLAG()            2
#define mAPP_STATE_SUPERVISOR_RECEIVER_FLAG()     3
#define mAPP_STATE_GLB_RECEIVER_FLAG()           -1

#define cAPP_STATE_PED_BUTTON_PUSHED            1
#define cAPP_STATE_PED_FLASH_READY              2
#define cAPP_STATE_PED_PARTIAL_FLASH            3
#define cAPP_STATE_PED_FULL_FLASH               4
#define cAPP_STATE_PED_RESEND_BUTTON            5


extern u8 bAPP_STATE_TempCheckSum;
extern u16 wAPP_STATE_TempID;

extern u16 wAPP_STATE_RB_NEXT_TIME_OUT;
extern u8 bAPP_STATE_RB_TIME_OUT_FLAG;

extern u16 wAPP_STATE_PED_BUTTON_TIME_OUT;
extern u8 bAPP_STATE_PED_BUTTON_TIME_OUT_FLAG;

extern u8 bPED_AB_Status;

extern u16 wAPP_STATE_SFM_TIME_OUT;
extern u8  bAPP_STATE_SFM_Flag;
/* Exported functions ------------------------------------------------------- */
u8 RamdonSleepWakeUp( u16 wSeed );
s8 App_State( u8 * pbRxBuffer, u8 blength );

