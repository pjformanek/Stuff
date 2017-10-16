/******************** (C) COPYRIGHT 2008 JSF Technologies **********************
* File Name          : App_Main.h
* Author             : Juan Ramirez
* Version            : V0.0.1
* Date               : Dec 23, 2008
* Description        : Header file for App_Main.c
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
/* Global Variables ----------------------------------------------------------*/
static u8 GlobalPasswordState;
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  u8 PassByteH;
  u8 PassByteM;
  u8 PassByteL;
  
}APP_PassWordTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define mAPP_DTMF_LIGHT_INDEX()       0x31
#define mAPP_DTMF_LIGHT_ON_TAG()      0x31
#define mAPP_DTMF_LIGHT_OFF_TAG()     0x32

#define mAPP_DTMF_DOOR_INDEX()        0x32
#define mAPP_DTMF_DOOR_LOCK_TAG()     0x31
#define mAPP_DTMF_DOOR_UNLOCK_TAG()   0x32

#define mAPP_ERROR()                  99

#define mAPP_PASS_BYTE_H              0x31
#define mAPP_PASS_BYTE_M              0x32
#define mAPP_PASS_BYTE_L              0x33

/* Exported functions ------------------------------------------------------- */
void App_Main( void );

#ifdef mDTMF_ENABLE
u8 PasswordCheck( u8 DTMFval );

void ResetValues( void );
#endif