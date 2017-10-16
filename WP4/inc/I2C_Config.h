/*------------------------------------------------------------------------------
  	$File:		I2C_Config.h	
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

#ifndef __I2C_H__
#define __I2C_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define mI2C_Power_Supply_On_Off(x)          GPIO_WriteBit( cGPIO_I2C_Supply_GPIOx, \
                                                                  cGPIO_I2C_Supply_PIN, x );

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */
//CURRENT DEFINES REGARDING I2C1
#define cGPIO_I2C1_GPIOx                   GPIOB
#define cRCC_APBxPeriph_GPIO_I2C1          RCC_APB2Periph_GPIOB
#define cGPIO_I2C1_SDA_PIN                 GPIO_Pin_7
#define cGPIO_I2C1_SCL_PIN                 GPIO_Pin_6

//CURRENT DEFINES REGARDING I2C2
#define cGPIO_I2C2_GPIOx                   GPIOB
#define cRCC_APBxPeriph_GPIO_I2C2          RCC_APB2Periph_GPIOB
#define cGPIO_I2C2_SDA_PIN                 GPIO_Pin_11
#define cGPIO_I2C2_SCL_PIN                 GPIO_Pin_10


// defines for the power supply for all I2C devices
#define cRCC_APBxPeriph_GPIO_I2C_Supply   RCC_APB2Periph_GPIOD
#define cGPIO_I2C_Supply_GPIOx            GPIOD
#define cGPIO_I2C_Supply_PIN              GPIO_Pin_7

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
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */
void I2C1_Configuration( void );
void I2C2_Configuration( void );
void I2C1_Test( void );
void GPIO_I2C_Supply_Configurations( void );
#endif // __I2C_H__

