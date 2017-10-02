/*------------------------------------------------------------------------------
$File:		I2C_Config.c
$Module:  	Configurations for the I2C peripherals
$Prefix:  	I2C
$Language:	ANSI C

$Description:

$Notes:

$Author:	Jramirez, May 15, 2010
--------------------------------------------------------------------------
$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
--------------------------------------------------------------------------
$End
----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_I2C_CONFIG_c

/*------------------------------------------------------------------------------
------ I N C L U D E   F I L E S ------
------------------------------------------------------------------------------
*/
#include "GLB.h"
#include "MEM.h"
#include "ERR.h"
#include "platform_config.h"
#include "EXTINT_Config.h"
#include "NVIC_Config.h"
#include "GPIO_Config.h"
#include "Utilities.h"
#include "I2C_Config.h"	

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

/*------------------------------------------------------------------------------
----- L O C A L   V A R I A B L E S -----
------------------------------------------------------------------------------
*/
I2C_InitTypeDef I2C_InitStructure;

static u8 bI2C1_OnFlag = 0;
static u8 bI2C2_OnFlag = 0;
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
	$Function: GPIO_I2C1Configuration
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_I2C2Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Configure I2C2 pins (PB.10 and PB.11) as SCL and SDA  */
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_I2C2, ENABLE );

  GPIO_InitStructure.GPIO_Pin =  cGPIO_I2C2_SCL_PIN | cGPIO_I2C2_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(cGPIO_I2C2_GPIOx, &GPIO_InitStructure);
}

/*------------------------------------------------------------------------------
        $Function: GPIO_I2C_Supply_Configurations
        $Description: confifures the pin that controls the supply for all I2C devices
                      enables the U8 which creates VCC3 3v
        
        $Inputs: none
        $Outputs: none
        $Assumptions:
        $WARNINGS:
        $End
*/
void GPIO_I2C_Supply_Configurations( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Configure I2C1 pins (PB.6 and PB.7) as SCL and SDA  */
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_I2C_Supply, ENABLE );

  GPIO_InitStructure.GPIO_Pin =  cGPIO_I2C_Supply_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(cGPIO_I2C_Supply_GPIOx, &GPIO_InitStructure);
}



/*------------------------------------------------------------------------------
	$Function: GPIO_I2C1Configuration
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_I2C1Configuration( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Configure I2C1 pins (PB.6 and PB.7) as SCL and SDA  */
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_I2C1, ENABLE );

  GPIO_InitStructure.GPIO_Pin =  cGPIO_I2C1_SCL_PIN | cGPIO_I2C1_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(cGPIO_I2C1_GPIOx, &GPIO_InitStructure);
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
void I2C1_Configuration( void )
{
  I2C_InitTypeDef I2C_InitStructure;
  
  if( !bI2C1_OnFlag )
  {
 
    // sets up and enables the U8 power suppply for all I2C devices creates VCC3
    //GPIO_I2C_Supply_Configurations();
    
    
    bI2C1_OnFlag = 1;
    
    I2C_Cmd(I2C1, ENABLE);
    
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1 ,ENABLE );
    
    GPIO_I2C1Configuration();
    
    /* I2C configuration ------------------------------------------------------ */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x30;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 400000; //all other I2c devices working with this 400khz
    
    I2C_Init(I2C1, &I2C_InitStructure);
    
    
    
    
  }
  //I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_BUF, ENABLE);
  
  
}


void I2C1_Test( void )
{
  
  /* I2C configuration ------------------------------------------------------ */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x30;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = 100000;
  
  I2C_DeInit( I2C1 );
  I2C_Init(I2C1, &I2C_InitStructure);
}


void I2C1_Write( u8 bData, u8 bSlaveAddress ) 
{
  /* initiate start sequence */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* check start bit flag */
  while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));
  /*send write command to chip*/
  I2C_Send7bitAddress(I2C1, bSlaveAddress<<1, I2C_Direction_Transmitter);
  /*check master is now in Tx mode*/
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  /*mode register address*/
  I2C_SendData(I2C1, bData);
  /*wait for byte send to complete*/
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  /*clear bits*/
  I2C_SendData(I2C1, 0x00);
  /*wait for byte send to complete*/
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  /*generate stop*/
  I2C_GenerateSTOP(I2C1, ENABLE);
  /*stop bit flag*/
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
  
  
}


/*------------------------------------------------------------------------------
$Function: EE_I2C_ByteWrite
$Description: Writes a byte to the EEprom

$Inputs: u8 bBuffer - data to be written
u32 lwWriteAddr - Address where data is going to be written to
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
//void EE_I2C_ByteWrite( u8 bBuffer, u32 lwWriteAddr )
//{
//#define cEE_I2C_W_ADDRESS_LOW         0xA0
//#define cEE_I2C_W_ADDRESS_HIGH        0xA8
//  
//#define cEE_I2C_R_ADDRESS_LOW         0xA1
//#define cEE_I2C_R_ADDRESS_HIGH        0xA9
//  
//#define cEE_I2C_BUS_PORT              I2C1
//  
//  
//  u8 bHiByte = 0, bLoByte = 0,bEeAddress = 0;
//
//  bHiByte = mMSB_FROM_WORD( lwWriteAddr );
//  bLoByte = mLSB_FROM_WORD( lwWriteAddr );
//  
//  //printf(" hi = %x lo = %x\n", bHiByte, bLoByte);
//  
//  if( lwWriteAddr > 0xFFFF )
//  {
//    bEeAddress = cEE_I2C_W_ADDRESS_HIGH;
//    //printf("lwWriteAddr > 0xFFFF= %x\n", bEeAddress );
//  }
//  else
//  {
//    bEeAddress = cEE_I2C_W_ADDRESS_LOW;
//    //printf("lwWriteAddr < 0xFFFF= %x\n", bEeAddress );
//  }
//  
//  
//  /* initiate start sequence */
//  I2C_GenerateSTART(I2C1, ENABLE);
//  /* check start bit flag */
//  while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));
//  
//  
//  /* Send PCA9634 address for write */
//  I2C_Send7bitAddress(cEE_I2C_BUS_PORT, bEeAddress, I2C_Direction_Transmitter);
//  
//  /*check master is now in Tx mode*/
//  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
//  
//  /* Send high byte of address to the EE*/
//  I2C_SendData( cEE_I2C_BUS_PORT, bHiByte );
//  
//  /* Test on EV8 and clear it */
//  while(!I2C_CheckEvent(cEE_I2C_BUS_PORT, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//  
//  /*clear bits*/
//  I2C_SendData(I2C1, 0x00);
//  /*wait for byte send to complete*/
//  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//  
//  /* Send low byte of address to the EE*/
//  I2C_SendData( cEE_I2C_BUS_PORT, bLoByte );
//  
//  /* Test on EV8 and clear it */
//  while(!I2C_CheckEvent(cEE_I2C_BUS_PORT, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//  
//  /*clear bits*/
//  I2C_SendData(I2C1, 0x00);
//  /*wait for byte send to complete*/
//  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//  
//  /* Send the byte to be written */
//  I2C_SendData(cEE_I2C_BUS_PORT, bBuffer);
//  
//  /* Test on EV8 and clear it */
//  while(!I2C_CheckEvent(cEE_I2C_BUS_PORT, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//  
//  /*clear bits*/
//  I2C_SendData(I2C1, 0x00);
//  /*wait for byte send to complete*/
//  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//  
//  /* Send STOP condition */
//  I2C_GenerateSTOP(cEE_I2C_BUS_PORT, ENABLE);
//  
//  /*stop bit flag*/
//  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
//}



/*------------------------------------------------------------------------------
	$Function: EE_I2C_ByteRead
	$Description: Writes one byte to the I2C EEPROM.

	$Inputs: u32 lwReadAddr - EEPROM internal address to read from.
	$Outputs: returns byte read from lwReadAddr
	$Assumptions:
	$WARNINGS:
	$End
*/
//u8 EE_I2C_ByteRead( u32 lwReadAddr )
//{
//  u8 bByte = 0;
//
//  u8 bHiByte = 0, bLoByte = 0, bEeAddress = 0;
//
//  bHiByte = mMSB_FROM_WORD( lwReadAddr );
//  bLoByte = mLSB_FROM_WORD( lwReadAddr );
//  //printf(" hi = %x lo = %x\n", bHiByte, bLoByte);
//
//
//  /* Disable Acknowledgement */
//  I2C_AcknowledgeConfig(cEE_I2C_BUS_PORT, DISABLE);
//
//  if( lwReadAddr > 0xFFFF )
//  {
//    bEeAddress = cEE_I2C_R_ADDRESS_HIGH;
//    //printf("lwReadAddr > 0xFFFF = %x\n", bEeAddress );
//  }
//  else
//  {
//    bEeAddress = cEE_I2C_R_ADDRESS_LOW;
//    //printf("lwReadAddr < 0xFFFF = %x\n", bEeAddress );
//  }
//
//  
//  /*re-enable ACK bit incase it was disabled last call*/
//  I2C_AcknowledgeConfig(I2C1, ENABLE);
//  /* Test on BUSY Flag */
//  while (I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
//  /* Enable the I2C peripheral */
//  /*======================================================*/
//  I2C_GenerateSTART(I2C1, ENABLE);
//  /* Test on start flag */
//  while (!I2C_GetFlagStatus(I2C1,I2C_FLAG_SB));
//  
//  /* Send EEPROM address for write */
//  I2C_Send7bitAddress(I2C1, bEeAddress, I2C_Direction_Transmitter);
//
//  /* Test on EV6 and clear it */
//  while(!I2C_CheckEvent(cEE_I2C_BUS_PORT, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
//  
//  
//  /* Send the device's internal address to write to */
//  I2C_SendData(I2C1,bHiByte);
//  /* Test on TXE FLag (data sent) */
//  while (!I2C_GetFlagStatus(I2C1,I2C_FLAG_TXE));
//  
//  /*clear bits*/
//  I2C_SendData(I2C1, 0x00);
//  /*wait for byte send to complete*/
//  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//
//  /* Send low byte of address to the EE*/
//  I2C_SendData( cEE_I2C_BUS_PORT, bLoByte );
//  /* Test on TXE FLag (data sent) */
//  while (!I2C_GetFlagStatus(I2C1,I2C_FLAG_TXE));
//
//
//  /* Send STRAT condition a second time */
//  I2C_GenerateSTART(cEE_I2C_BUS_PORT, ENABLE);
//
//  /* Test on start flag */
//  while (!I2C_GetFlagStatus(I2C1,I2C_FLAG_SB));
//
//  /* Send EEPROM address for read */
//  I2C_Send7bitAddress(cEE_I2C_BUS_PORT, bEeAddress, I2C_Direction_Receiver);
//
//  /* Test on EV6 and clear it */
//  while(!I2C_CheckEvent(cEE_I2C_BUS_PORT, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
//
//  
//  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
//  bByte = I2C_ReceiveData(I2C1);
//    
//    /* Send STOP Condition */
//    I2C_GenerateSTOP(I2C1, ENABLE);
//    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF)); // stop bit flag
//
//
//  
//  
//  
//  return bByte;
//}

void I2C2_Configuration( void )
{

  if( !bI2C2_OnFlag )
  {
    // sets up and enables the U8 power suppply for all I2C devices creates VCC3
    //GPIO_I2C_Supply_Configurations();
    
    bI2C2_OnFlag = 1;
    
    I2C_Cmd(I2C2, ENABLE);
    
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2 ,ENABLE );

    GPIO_I2C2Configuration();
    
    /* I2C configuration ------------------------------------------------------ */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x30;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 400000; //all other I2c devices working with this 400khz

    I2C_Init(I2C2, &I2C_InitStructure);
  }
  //I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_BUF, ENABLE);


}


#undef cMEM_USERCLASS_ID_I2C_CONFIG_c
