/*------------------------------------------------------------------------------
  	$File:		SPI_Config.h	
  	$Module:  	Header file for SPI_Config.c
  	$Prefix:  	SPI
  	$Language:	ANSI C
  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Dec 23, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __SPI_H__
#define __SPI_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */
#define cMAX_BUFFER_SIZE_SPI1  256


//CURRENT DEFINES REGARDING POWER AMPLIFIER TX / RX AND BUTTON FOR TESTING PA
#define cGPIO_PA_TX_GPIOx                       GPIOB
#define cRCC_APBxPeriph_GPIO_PA_TX              RCC_APB2Periph_GPIOB
#define cGPIO_PA_TX_PIN                         GPIO_Pin_8

#define cGPIO_PA_RX_GPIOx                       GPIOB
#define cRCC_APBxPeriph_GPIO_PA_RX              RCC_APB2Periph_GPIOB
#define cGPIO_PA_RX_PIN                         GPIO_Pin_9

//CURRENT DEFINES REGARDING SPI1
#define cGPIO_SPI1_GPIOx                  GPIOA
#define cRCC_APBxPeriph_GPIO_SPI1         RCC_APB2Periph_GPIOA
#define cGPIO_SPI1_SCK_PIN                GPIO_Pin_5
#define cGPIO_SPI1_MISO_PIN               GPIO_Pin_6
#define cGPIO_SPI1_MOSI_PIN               GPIO_Pin_7

#define cGPIO_SPI1_CSn_GPIOx              GPIOA
#define cRCC_APBxPeriph_GPIO_SPI1_CSn     RCC_APB2Periph_GPIOA
#define cGPIO_SPI1_CSn_PIN                GPIO_Pin_4



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
#if 0
extern vu8 bSPI1_RX_BufferA[cMAX_BUFFER_SIZE_SPI1] ;
//extern u8 bSPI1_RX_BufferB[cMAX_BUFFER_SIZE_SPI1];
extern vu8 bSPI1_RX_IntFlag;
extern u16 wSPI1Count;
#endif

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */
void SPI1_Configuration( void );

#endif // __SPI_H__
