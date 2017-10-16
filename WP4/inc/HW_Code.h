/*------------------------------------------------------------------------------
	$File:		HW_Code.h	
	$Module:  Hardware
 	$Prefix:  HW
 	$Language:	ANSI C

 	$Description:
		This file contains definitions for data structures used to store init data
		for the main processor and perihperals (e.g. CC1101 900 MHz ISM-band 
		transceiver)
		
 	$Notes:
  
 	$Author:	KGANS, 2009-March-22
 	--------------------------------------------------------------------------
 	$Copyright (c) 2009 J.S. Foster Corporation  	All Rights Reserved
 	--------------------------------------------------------------------------
 	
 	$End
	----------------------------------------------------------------------------*/

#ifndef cHW_CODE_H
#define cHW_CODE_H

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/* recoded types to match WP4 coding standard */
#define tpHW_stm32f10x_map_GPIOx	GPIO_TypeDef			/* pointer to struct */
#define tpHW_stm32f10x_gpio_Init	GPIO_InitTypeDef	/* pointer to struct */
#define twHW_Code_GPIOSpeed				GPIOSpeed_TypeDef /* enumerated type, u16; sub-type appointed by GPIO_InitTypeDef */
#define	twHW_Code_GPIOMode				GPIOMode_TypeDef	/* enumerated type, u16; sub-type appointed by GPIO_InitTypeDef */


/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*--------------------------------------------------------------------
 	$Type: tHW_Code_CC1101_RegData
	$Description:
		Creates the structure for populating arrays of configuration 
		parameters.
	$End
 */
typedef struct tpHW_Code_CC1101_RegData_tag 
{
	u8	bRegAddrs;
	u8	bRegType;
	u8	bRegData;

} tpHW_Code_CC1101_RegData;

/*--------------------------------------------------------------------
 	$Type: tHW_Code_CC1101_RegData_FreqCntrl
	$Description:
		Creates the structure for populating arrays of frequency 
			configuration parameters. 

			Is targeted to CC1101 registers
				TI_CCxxx0_FREQ2
				TI_CCxxx0_FREQ1
				TI_CCxxx0_FREQ0
	$End
 */
typedef struct tpHW_Code_CC1101_RegData_FreqCntrl_tag 
{
	u8 bFREQ2_24BitWord_H;
	u8 bFREQ1_24BitWord_M;
	u8 bFREQ2_24BitWord_L;

} tpHW_Code_CC1101_RegData_FreqCntrl;

/*--------------------------------------------------------------------
 	$Type: tHW_Code_GPIO_PORTS_InitData
	$Description:
		Creates structure for populating arrays of configuration 
		parameters for GPIO ports
	$End
 */
#if 0
typedef struct tpHW_Code_GPIO_PORTS_InitData_tag
{
	tpHW_stm32f10x_map_GPIOx * ppGPIOx;
	tpHW_stm32f10x_gpio_Init * ppGPIO_Init;
	
}	tpHW_Code_GPIO_PORTS_InitData;
#else
typedef struct tpHW_Code_GPIO_PORTS_InitData_tag
{
	tpHW_stm32f10x_map_GPIOx * ppGPIOx;
  u16 												wGPIO_Pin;
  twHW_Code_GPIOSpeed					wGPIO_Speed;
  twHW_Code_GPIOMode					wGPIO_Mode;
	
}	tpHW_Code_GPIO_PORTS_InitData;
#endif

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */
extern const tpHW_Code_CC1101_RegData ppcHW_Code_CC1101_RegData_InitData[];
extern const u8 pcbHW_Code_CC1101_RegData_InitData_NUM_ENTRIES[];

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

#endif // cHW_CODE_H

