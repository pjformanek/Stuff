/*------------------------------------------------------------------------------
  	$File:		SPI_Config.c
  	$Module:  	Configuration settings for SPI1 ( CC1101 )
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

#define cMEM_USERCLASS_ID_SPI_CONFIG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "MEM.h"
#include "GPIO_Config.h"

#include "SPI_Config.h"
#include "platform_config.h"


/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define cSPI_GPIO_Default_Speed         GPIO_Speed_10MHz

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
SPI_InitTypeDef  SPI_InitStructure;

u8 bSPI1_RX_BufferA[cMAX_BUFFER_SIZE_SPI1] = { 0 };
//u8 bSPI1_RX_BufferB[cMAX_BUFFER_SIZE_SPI1] = { 0 };
u8 bSPI1_RX_IntFlag = 0;
u16 wSPI1Count = 0;

static u8 bSPI1_OnFlag = 0;

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
	$Function: GPIO_SPI1Configuration
	$Description: Configures SPI1 GPIO ( CC1101 )

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void GPIO_SPI1Configuration( void )
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_SPI1 , ENABLE );

  /* Configure SPI1 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = cGPIO_SPI1_SCK_PIN | cGPIO_SPI1_MISO_PIN | cGPIO_SPI1_MOSI_PIN;
  GPIO_InitStructure.GPIO_Speed = cSPI_GPIO_Default_Speed;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(cGPIO_SPI1_GPIOx, &GPIO_InitStructure);

  /*Configure PA.4 pin: NSS or CSn CC1101*/

  RCC_APB2PeriphClockCmd( cRCC_APBxPeriph_GPIO_SPI1_CSn, ENABLE );

  GPIO_InitStructure.GPIO_Pin = cGPIO_SPI1_CSn_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = cSPI_GPIO_Default_Speed;
  GPIO_Init(cGPIO_SPI1_GPIOx, &GPIO_InitStructure);

  GPIO_WriteBit( cGPIO_SPI1_GPIOx, cGPIO_SPI1_CSn_PIN, ecGPIO_BitAction_SET );


}


/*------------------------------------------------------------------------------
	$Function: SPI1_Configuration
	$Description: Settings for SPI1 ( CC1101 )

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/

void SPI1_Configuration( void )
{
  
  SPI_InitTypeDef  SPI_InitStructure;
  
  if( !bSPI1_OnFlag )
  {
    bSPI1_OnFlag = 1;
    GPIO_SPI1Configuration();

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE );


    /* SPI1 configuration ------------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; /* must be low for CC1101 */
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    //  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    /* for CC1101, all address and data transfer on the SPI interface must be
    done most significant bit first */
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 0;

    /* This parameter is a clock divider which sets the clock rate of the SPI bus
    ... the MAX rate for CC1101 burst is 6.5 MHz
    .. however, while unstated in the CC1101 datasheet there appears to also
    be a lower limit on the clock rate ... 1MHz is the lowest rate at which
    the CC1101 has been run successfully
    */			
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    //SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;

    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);

    //SPI_I2S_ITConfig( SPI1, SPI_I2S_IT_RXNE, ENABLE  );

    /* Enable SPI1 */
    SPI_Cmd(SPI1, ENABLE);

  }

}


#undef cMEM_USERCLASS_ID_SPI_CONFIG_c