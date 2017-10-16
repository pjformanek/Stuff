/*------------------------------------------------------------------------------
  	$File:		HW_Boot.c
  	$Module:	post Reset Hardware initialization 
  	$Prefix:  HW
  	$Language:	ANSI C
  
  	$Description:
			This file contains the HW_Reset() function. This is the only public 
			function that should be coded in this source unit. Where possible,
			HW_Reset() or the private functions coded here in this source unit should 
			call those external public functions used by the remainder of the WP4 
			App.
		
  	$Notes:
			A general guideline to follow is that all hardware entitites (and 
			software entities, for that matter), should be initialized through
			 single interface function that is named using the format 

					 	"u8 <function_name>_Init( void )"

			...there are important benefits to be gained from this practice (not 
					listed here).
  
  	$Author:	KGANS, 2009-March-24
  	--------------------------------------------------------------------------
  	$Copyright (c) 2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_HW_BOOT_c

/*------------------------------------------------------------------------------
							------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "HW_Def.h"
//#include "CC1101_Config.h"
//#include "stm32f10x_lib.h"
//#include "SPI_Config.h"
//#include "Includes.h"

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
	$Function: 	HW_Reset
	$Description: Initializes the WP4 hardware following reset
	$Inputs:	args: none
	$Outputs:	return: none
	$Assumptions:	1) All RAM is automaticall cleared by reset or by execution
										of other boot code immediately following reset and
										prior to this function being called.
	$WARNINGS:
	$End
*/
void HW_Reset( void )
{
	/* disable interrupts
	*/

	/* disable watchdog
	*/

	/* set flash wait states 
	*/

	/* stabilize crystal and set micro clock rate
	*/

  /* System Clocks Configuration **********************************************/
  RCC_Configuration(); 
  
  /* Set up Configuration for GPIO */
  GPIO_Configuration();
  
  /* Set up Configuration for USART2 and USART3 */
  USART_Configuration(); 
  
	#ifdef mCC1101_ENABLE  
  /* Set up Configguration for SPI1 */
  SPI_Configuration();  
	#endif
  
  /* NVIC configuration */
  NVIC_Configuration();
  
  /* Set up Configuration for EXTI4 and EXTI5 */
  EXTINT_Configuration();
  
  //Set up current timers ... don't do much at the moment, tiggered by the button 
  //interupt to run and will be disabled upon the appropriate timer interrupt 
  //and spit an indication out usart3
  //TIM1_Configuration( 1000 );
  //TIM2_Configuration( 25 );
	#ifdef mSYS_TIM_ENABLE
  SysTick_Configuration( mTIMx_SYS_TICK_1s() );
	#endif
}


/*
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/




/*******************************************************************************
* Function Name  : CC1101_BootConfiguration
* Description    : Configuration settings for CC1101
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CC1101_BootConfiguration( void )
{
  /* Reset CCxxxx */
  TI_CC_PowerupResetCCxxxx();               
  
  /* Write RF settings to config reg */	
  writeRFSettings();                       
  
  /* Write PATABLE */	
  TI_CC_SPIWriteBurstReg( TI_CCxxx0_PATABLE, paTable, paTableLen );
  
  /* CC1101 chip select ... turn CSn pin off */
  GPIO_ClearBits(pcHW_SPI1_GPIOx, cHW_SPI1_CSn_PIN);  
}


/*******************************************************************************
* Function Name  : GSM_BootConfiguration
* Description    : Configurations for Telit device
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GSM_BootConfiguration( void )
{
  Send_AT_CMD_USART2 ( mAT_PURGE_TX_BUFFER() ); 
  Send_AT_CMD_USART3 ( mAT_PURGE_TX_BUFFER() );  
  
  DO_ATcommands();  
}



/*******************************************************************************
* Function Name  : your function
* Description    : your function's description
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Check_Valid_Data( void )
{  
  u8 bTimeOutFlag, bRandomSleepFlag;
  
  SCAN_CheckDataStruct =  SCAN_Data_Init();
  
  if( SCAN_CheckDataStruct.AB_ID_Flag == 1 )
  {
    #ifdef mDEBUG_MODE
    Debug_Message( "ID Found\r\n");
    #endif    
  }
  else
  {
    // function to go sleep for random time
    bRandomSleepFlag = RamdonSleepWakeUp( rand() );
    
    #ifdef mDEBUG_MODE
    Debug_Message( "Sending SFM.....\r\n");
    #endif
    
    SearchForMasterBurst();
    
    
    TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SRX);  
     
    #ifdef mDEBUG_MODE
    Debug_Message( "SFM Time-out set!\r\n");
    #endif
    
    bTimeOutFlag = RFReceivePacket( bRxBuffer, 17, 1000 );      
 
    if( bTimeOutFlag == 1 )
    {     
      RF_ParseOutMessage( bRxBuffer, 64 );
      #ifdef mDEBUG_MODE
      Debug_Message( "Message recieved\r\n");
      #endif      
      GLB_SupervisorFlag = 0;      
      RF_Main_App();  
      
    }
    else
    {
      TIM_Cmd(TIM1, DISABLE);
      #ifdef mDEBUG_MODE
      Debug_Message( "No Supervisor found\r\n");
      Debug_Message( "Becoming Supervisor now\r\n");
      #endif      
      GLB_SupervisorFlag = 1;   
      RF_Main_App();
    }
  }
    
  
}




/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : GPIO_USART2Configuration
* Description    : Configures USART2 GPIO ( Telit device )
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_USART2Configuration( void )
{
  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = mHW_USART2_TX_PIN();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(mHW_USART2_GPIOx(), &GPIO_InitStructure);
    
  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = mHW_USART2_RX_PIN();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(mHW_USART2_GPIOx(), &GPIO_InitStructure);   
}

/*******************************************************************************
* Function Name  : GPIO_USART3Configuration
* Description    : Configures USART3 GPIO ( Debugger )
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_USART3Configuration( void )
{
  /* remap USART3 to PC.10 and PC.11*/
  GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);  
  
   /* Configure USART3 Tx (PC.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = mHW_USART3_TX_PIN();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(mHW_USART3_GPIOx(), &GPIO_InitStructure);
    
  /* Configure USART3 Rx (PC.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = mHW_USART3_RX_PIN();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(mHW_USART3_GPIOx(), &GPIO_InitStructure);   
}

/*******************************************************************************
* Function Name  : GPIO_SPI1Configuration
* Description    : Configures SPI1 GPIO ( CC1101 )
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_SPI1Configuration( void )
{
  /* Configure SPI1 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = cHW_SPI1_SCK_PIN | cHW_SPI1_MISO_PIN | cHW_SPI1_MOSI_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(pcHW_SPI1_GPIOx, &GPIO_InitStructure);
  
  /*Configure PA.4 pin: NSS or CSn CC1101*/
  GPIO_InitStructure.GPIO_Pin = cHW_SPI1_CSn_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(pcHW_SPI1_GPIOx, &GPIO_InitStructure);
  
  /*Configure PA.9 pin: GDO_0 PIN From CC1101*/
  GPIO_InitStructure.GPIO_Pin = mHW_SPI1_GD0_PIN();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(mHW_SPI1_GD0_GPIOx(), &GPIO_InitStructure);
  
  /*Configure PB.6 pin: GDO_2 PIN From  CC1101*/
  GPIO_InitStructure.GPIO_Pin = mHW_SPI1_GD2_PIN();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(mHW_SPI1_GD0_GPIOx(), &GPIO_InitStructure);
  
}

/*******************************************************************************
* Function Name  : GPIO_LEDConfiguration
* Description    : Configures test LED
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_LEDConfiguration( void )
{
  /* Configure PC.06 and PC.07 to LED outputs*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);   
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
  
  
}



/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Calls all main GPIO configuration functions
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration( void )
{ 
  GPIO_LEDConfiguration();
#ifdef mCC1101_ENABLE
  GPIO_SPI1Configuration();
#endif
  GPIO_USART3Configuration();
  GPIO_USART2Configuration();
  GPIO_EXTINTConfiguration();
#ifdef mDTMF_ENABLE
  GPIO_DTMFConfiguration();
#endif
  
#ifdef mMP3_ENABLE
  GPIO_MP3Configuration();
#endif
}


/*******************************************************************************
* Function Name  : GPIO_Init_Configuration
* Description    : Configure all unused GPIO port pins in Analog Input mode 
*                  (floating input trigger OFF)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Init_Configuration( void )
{
  /*******************************************************************************************/
   /* Configure all unused GPIO port pins in Analog Input mode (floating input
     trigger OFF), this will reduce the power consumption and increase the device
     immunity against EMI/EMC ************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /*******************************************************************************************/
  
}

/*******************************************************************************
* Function Name  : GPIO_EXTINTConfiguration
* Description    : Configures all GPIO that will be used as external interrupts
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_EXTINTConfiguration( void )
{

//  /* Configure Key Button2 GPIO Pin as input floating (Key Button EXTI Line) */
//  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY_BUTTON2;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIO_KEY_BUTTON2, &GPIO_InitStructure);
  
  //  /* Configure Key Button3 GPIO Pin as input floating (Key Button EXTI Line) */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY_BUTTON3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_KEY_BUTTON3, &GPIO_InitStructure);
  
#ifdef mGSM_ENABLE  
  //  /* Configure RING PIN GPIOA Pin10 as internal pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_RING;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIO_RING, &GPIO_InitStructure);
#endif
  
#ifdef mDTMF_ENABLE 
  /* Configure DTMF PC.6 as internal pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_DTMF_Rx;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIO_DTMF, &GPIO_InitStructure);
#endif
//  /* Configure DTMF Tx (PC.7) as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin = mHW_USART3_TX_PIN();
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIO_DTMF, &GPIO_InitStructure);    
  
}

/*******************************************************************************
* Function Name  : GPIO_DTMFConfiguration 
* Description    : Configures pins used by the DTMF chip
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_DTMFConfiguration( void )
{
/* Configure DTMF Rx (PB.15) as internal pull-down */
  GPIO_InitStructure.GPIO_Pin = mHW_DTMF_D3();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(mHW_DTMF_GPIOx(), &GPIO_InitStructure);   

  /* Configure DTMF Rx (PB.14) as internal pull-down */
  GPIO_InitStructure.GPIO_Pin = mHW_DTMF_D2();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(mHW_DTMF_GPIOx(), &GPIO_InitStructure);   

  /* Configure DTMF Rx (PB.13) as internal pull-down */
  GPIO_InitStructure.GPIO_Pin = mHW_DTMF_D1();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(mHW_DTMF_GPIOx(), &GPIO_InitStructure); 
  
  /* Configure DTMF Rx (PB.12) as internal pull-down */
  GPIO_InitStructure.GPIO_Pin = mHW_DTMF_D0();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(mHW_DTMF_GPIOx(), &GPIO_InitStructure);
  
  /* Configure DTMF PWDN (PC.7) as OUTPUT */
  GPIO_InitStructure.GPIO_Pin = mHW_DTMF_PWDN_PIN();
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( mHW_DTMF_PWDN_GPIOx(), &GPIO_InitStructure );
}


/*******************************************************************************
* Function Name  : NOT NEEDED juan clean up
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_MP3Configuration( void )
{
  /* Configure DTMF PWDN (PC.7) as OUTPUT */
  GPIO_InitStructure.GPIO_Pin = mHW_MP3_BB_PIN() ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( mHW_MP3_BB_GPIOx(), &GPIO_InitStructure );
  
  /* Configure DTMF PWDN (PC.7) as OUTPUT */
  GPIO_InitStructure.GPIO_Pin = mHW_MP3_CS_PIN() ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( mHW_MP3_CS_GPIOx(), &GPIO_InitStructure );
  
}







/*
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/


/*******************************************************************************
* Function Name  : TI_CC_SPIWriteReg
* Description    : Writes an specific CC1101 register
* Input          : char addr - address of the register
*                  char value - value to be
*                  written to the register  
* Output         : None
* Return         : None
*******************************************************************************/
void TI_CC_SPIWriteReg( char addr, char value )
{
    /* CC1101 chip select ... turn CSn pin on*/
    GPIO_ClearBits( pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN );

    /* Wait for CCxxxx ready */
    while( ( GPIO_ReadInputDataBit( pcHW_SPI1_GPIOx, cHW_SPI1_MISO_PIN ) ) );

    /* Clear flag */
    //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );

    /* Send SPI1 data */
    SPI_I2S_SendData( SPI1, addr );

    /* Wait for SPI1 Tx buffer empty */
    while( RESET == SPI_I2S_GetFlagStatus( SPI1, SPI_I2S_FLAG_TXE ) );

    /* Clear flag */
    SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );

    /* Send SPI1 data */
    SPI_I2S_SendData( SPI1, value );

    /* Wait for SPI1 Tx buffer empty */
    while( SPI_I2S_GetFlagStatus( SPI1, SPI_I2S_FLAG_TXE ) == RESET );

    /* CC1101 chip select ... turn CSn pin off */
    GPIO_SetBits( pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN );


   
    
    /*TI_CC_CSn_PxOUT &= ~TI_CC_CSn_PIN;      // /CS enable
    while (TI_CC_SPI_USCIB1_PxIN&TI_CC_SPI_USCIB1_SOMI);// Wait for CCxxxx ready
    UC1IFG &= ~UCB1RXIFG;                     // Clear flag
    UCB1TXBUF = addr;                       // Send address
    while (!(UC1IFG&UCB1RXIFG));              // Wait for TX to finish
    UC1IFG &= ~UCB1RXIFG;                     // Clear flag
    UCB1TXBUF = value;                      // Send data
    while (!(UC1IFG&UCB1RXIFG));              // Wait for TX to finish
    TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;       // /CS disable*/
}

/*******************************************************************************
* Function Name  : TI_CC_Wait
* Description    : Simple Delay Function for TI_CC functions
* Input          : unsigned int cycles - number cycles to burn 
* Output         : None
* Return         : None
*******************************************************************************/
void TI_CC_Wait(unsigned int cycles)
{
  while(cycles>15)                          // 15 cycles consumed by overhead
    cycles = cycles - 6;                    // 6 cycles consumed each iteration
}


/*******************************************************************************
* Function Name  : TI_CC_PowerupResetCCxxxx
* Description    : Function that powers up the CC1101 properly whenever there is 
*                  a reset of power up
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TI_CC_PowerupResetCCxxxx(void)
{
	/* 
		the SO pin	will go low immediately after taking CSn low. If
		CSn is taken low before reset is completed,
		the SO pin will first go high, indicating that the
		crystal oscillator is not stabilized, before going
		low as shown in Figure 22.


		Manual Reset
		The other global reset possibility on CC1101
		uses the SRES command strobe. By issuing
		this strobe, all internal registers and states are
		set to the default, IDLE state. The manual
		power-up sequence is as follows (see Figure
		23):

		• Set SCLK = 1 and SI = 0, to avoid
			potential problems with pin control mode
			(see Section 11.3 on page 33).

		• Strobe CSn low / high.
		
		• Hold CSn low and then high for at least 40us 
			relative to pulling CSn low

		• Pull CSn low and wait for SO to go low
			(CHIP_RDYn).
		• Issue the SRES strobe on the SI line.

		• When SO goes low again, reset is
			complete and the chip is in the IDLE state.

		CSn
		SO
		XOSC Stable
		XOSC and voltage regulator switched on
		SI SRES
		40 us
		Figure 23: Power-On Reset with SRES
		19.2 Crystal Control
		The crystal oscillator (XOSC) is either
		automatically controlled or always on, if
		MCSM0.XOSC_FORCE_ON is set.
		In the automatic mode, the XOSC will be
		turned off if the SXOFF or SPWD command
		strobes are issued; the state machine then
		goes to XOFF or SLEEP respectively. This
		can only be done from the IDLE state. The
		XOSC will be turned off when CSn is released
		(goes high). The XOSC will be automatically
		turned on again when CSn goes low. The
		state machine will then go to the IDLE state.
		The SO pin on the SPI interface must be
		pulled low before the SPI interface is ready to
		be used as described in Section 10.1 on page
		30.
		If the XOSC is forced on, the crystal will
		always stay on even in the SLEEP state.



		Note that the above reset procedure is
		only required just after the power supply is
		first turned on. If the user wants to reset
		the CC1101 after this, it is only necessary to
		issue an SRES command strobe

	*/



  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits( pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN );
  TI_CC_Wait(30);

  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
  TI_CC_Wait(30);

  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
  TI_CC_Wait(45);
  
  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( pcHW_SPI1_GPIOx, cHW_SPI1_MISO_PIN ) ) );
  /* Send SPI1 Strobe */
  SPI_I2S_SendData(SPI1, HW_CC1101_ADDRS_STROBE_SRES);
  /* Clear flag */
    //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
 
  
  
  /*TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;
  TI_CC_Wait(30);
  TI_CC_CSn_PxOUT &= ~TI_CC_CSn_PIN;
  TI_CC_Wait(30);
  TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;
  TI_CC_Wait(45);

  TI_CC_CSn_PxOUT &= ~TI_CC_CSn_PIN;        // /CS enable
  while (TI_CC_SPI_USCIB1_PxIN&TI_CC_SPI_USCIB1_SOMI);// Wait for CCxxxx ready
  UCB1TXBUF = HW_CC1101_ADDRS_STROBE_SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  UC1IFG &= ~UCB1RXIFG;                       // Clear flag
  while (!(UC1IFG&UCB1RXIFG));                // Wait for end of addr TX
  while (TI_CC_SPI_USCIB1_PxIN&TI_CC_SPI_USCIB1_SOMI);
  TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;         // /CS disable*/
}



/*******************************************************************************
* Function Name  : your function
* Description    : your function's description
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
// 868 MHz
// Product = CC1100
// Crystal accuracy = 40 ppm
// X-tal frequency = 26 MHz
// RF output power = 0 dBm
// RX filterbandwidth = 540.000000 kHz
// Deviation = 0.000000
// Return state:  Return to RX state upon leaving either TX or RX
// Datarate = 250.000000 kbps
// Modulation = (7) MSK
// Manchester enable = (0) Manchester disabled
// RF Frequency = 868.000000 MHz
// Channel spacing = 199.951172 kHz
// Channel number = 0
// Optimization = Sensitivity
// Sync mode = (3) 30/32 sync word bits detected
// Format of RX/TX data = (0) Normal mode, use FIFOs for RX and TX
// CRC operation = (1) CRC calculation in TX and CRC check in RX disabled
// Forward Error Correction = (0) FEC disabled
// Length configuration = (1) Variable length packets, packet length configured by the first received byte after sync word.
// Packetlength = 255
// Preamble count = (2)  4 bytes
// Append status = 1
// Address check = (0) No address check
// FIFO autoflush = 0
// Device address = 0
// GDO0 signal selection = ( 6) Asserts when sync word has been sent / received, and de-asserts at the end of the packet
// GDO2 signal selection = (11) Serial Clock
void writeRFSettings(void)
{
    // Write register settings
    TI_CC_SPIWriteReg(TI_CCxxx0_FIFOTHR, 0x07); // GDO2 output pin config.
    TI_CC_SPIWriteReg(HW_CC1101_ADDRS_STROBE_SYNC1,   0xD3); // GDO2 output pin config.
    TI_CC_SPIWriteReg(HW_CC1101_ADDRS_STROBE_SYNC0,   0x91); // GDO2 output pin config.
    
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG2,   0x29); // GDO2 output pin config.  used to be 0x0B
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG0,   0x06); // GDO0 output pin config.
    
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTLEN,   0x40); // Packet length. /// was working with 0x03
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL1, 0x00); // Packet automation control.
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL0, 0x00); // Packet automation control.
    
    TI_CC_SPIWriteReg(TI_CCxxx0_ADDR,     0x00); // Device address.
    TI_CC_SPIWriteReg(TI_CCxxx0_CHANNR,   0x00); // Channel number.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL1,  0x0B); // Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL0,  0x00); // Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ2,    0x23); // Freq control word, high byte
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ1,    0x31); // Freq control word, mid byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ0,    0x3B); // Freq control word, low byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG4,  0x2D); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG3,  0x3B); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG2,  0x73); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG1,  0x22); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG0,  0xF8); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_DEVIATN,  0x00); // Modem dev (when FSK mod en)
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM1 ,   0x00); //MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM0 ,   0x18); //MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_FOCCFG,   0x1D); // Freq Offset Compens. Config
    TI_CC_SPIWriteReg(TI_CCxxx0_BSCFG,    0x1C); //  Bit synchronization config.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL2, 0xC7); // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL1, 0x00); // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL0, 0xB2); // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND1,   0xB6); // Front end RX configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND0,   0x10); // Front end RX configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL3,   0xEA); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL2,   0x0A); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL1,   0x00); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL0,   0x11); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSTEST,   0x59); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST2,    0x88); // Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST1,    0x31); // Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST0,    0x0B); // Various test settings.
}



/*******************************************************************************
* Function Name  : TI_CC_SPIWriteBurstReg
* Description    : Writes multi bytes to a register - used for fifos mostly 
* Input          : char addr - address of the reigster 
*                  char *buffer - buffer with the data to be written
*                  char count -  number of bytes to be written 
* Output         : None
* Return         : None
*******************************************************************************/
void TI_CC_SPIWriteBurstReg(char addr, char *buffer, char count)
{
    unsigned int i;

    /* CC1101 chip select ... turn CSn pin on*/
    GPIO_ClearBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
    /* Wait for CCxxxx ready */
    while( ( GPIO_ReadInputDataBit( pcHW_SPI1_GPIOx, cHW_SPI1_MISO_PIN ) ) );
    /* Clear flag */
    //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
    /* Send SPI1 address */
    SPI_I2S_SendData(SPI1, addr | TI_CCxxx0_WRITE_BURST );
    /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    for (i = 0; i < count; i++)
    {
      /* Clear flag */
      //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
      /* Send SPI1 address */
      SPI_I2S_SendData(SPI1, buffer[i]);      
      /* Wait for SPI1 Tx buffer empty */
      while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    }
    /* CC1101 chip select ... turn CSn pin off */
    GPIO_SetBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
    
    
    /*TI_CC_CSn_PxOUT &= ~TI_CC_CSn_PIN;      // /CS enable
    while (TI_CC_SPI_USCIB1_PxIN&TI_CC_SPI_USCIB1_SOMI);// Wait for CCxxxx ready
    UC1IFG &= ~UCB1RXIFG;
    UCB1TXBUF = addr | TI_CCxxx0_WRITE_BURST;// Send address
    while (!(UC1IFG&UCB1RXIFG));              // Wait for TX to finish
    for (i = 0; i < count; i++)
    {
      UC1IFG &= ~UCB1RXIFG;
      UCB1TXBUF = buffer[i];                // Send data
      while (!(UC1IFG&UCB1RXIFG));            // Wait for TX to finish
    }
    while (!(UC1IFG&UCB1RXIFG));
    TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;       // /CS disable*/    
}


/*******************************************************************************
* Function Name  : TI_CC_SPIStrobe
* Description    : Sends command strobes to the CC1101
* Input          : char strobe - byte command strobe
* Output         : None
* Return         : None
*******************************************************************************/
void TI_CC_SPIStrobe(char strobe)
{
  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( pcHW_SPI1_GPIOx, cHW_SPI1_MISO_PIN ) ) );
  /* Clear flag */
   //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
  /* Send SPI1 address */
  SPI_I2S_SendData(SPI1, strobe); 
  /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* CC1101 chip select ... turn CSn pin off */
    GPIO_SetBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
    
    
  /*UC1IFG &= ~UCB1RXIFG;                       // Clear flag
  TI_CC_CSn_PxOUT &= ~TI_CC_CSn_PIN;        // /CS enable
  while (TI_CC_SPI_USCIB1_PxIN&TI_CC_SPI_USCIB1_SOMI);// Wait for CCxxxx ready
  UCB1TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (!(UC1IFG&UCB1RXIFG));                // Wait for end of addr TX
  TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;         // /CS disable*/
}

/*******************************************************************************
* Function Name  : RFSendPacket
* Description    : Function to send a RF packet( writes to CC1101 fifo )
* Input          : char *txBuffer - buffer that hold the packet to be sent
*                  char size - number of bytes to be sent 
* Output         : None
* Return         : None
*******************************************************************************/
void RFSendPacket( char *txBuffer, char size )
{	
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SIDLE);
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFRX);
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFTX);
        
        TI_CC_SPIWriteBurstReg( TI_CCxxx0_TXFIFO, txBuffer, size );
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_STX);
      

       
        while( !( GPIO_ReadInputDataBit( mHW_SPI1_GD0_GPIOx(), mHW_SPI1_GD0_PIN() ) ) );
        //while (!(TI_CC_GDO0_PxIN&TI_CC_GDO0_PIN));
                                                // Wait GDO0 to go hi -> sync TX'ed
        
        while( ( GPIO_ReadInputDataBit( mHW_SPI1_GD0_GPIOx(), mHW_SPI1_GD0_PIN() ) ) );
        //while (TI_CC_GDO0_PxIN&TI_CC_GDO0_PIN);
                                              // Wait GDO0 to clear -> end of pkt
        #ifdef mDEBUG_MODE
        Debug_Message("Sending ....\r\n");
        #endif
}




/*******************************************************************************  juan clean up
* Function Name  : RFReceivePacket
* Description    : Function to be receive a packet ( Reads CC1101 fifo )
* Input          : char *rxBuffer - Buffer where data will be stored
*                  char *length - 
* Output         : None
* Return         : CRC_OK bit or 0 if error
*******************************************************************************/
u8 RFReceivePacket( u8 *pbRxBuffer, u8 bLength, u16 bTimeOutms )   // juan clean up
{
  
  u8 bTimeOutFlag = 0;
  
    TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SIDLE);
    TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFRX); 
    TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFTX);
       
    
    TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SRX);  
    #ifdef mDEBUG_MODE
    //Debug_Message("Receiving!\r\n");
    //Debug_Message(".");   // IT SEEMS THAT WITHOUT THESE TWO DEBUG_MESSAGES THE TIMING FOR THE SPI RECEIVE GETS SCREWED UP juan clean up
    //Delay(0x02);
    
    #endif
   
    TIM1_Configuration( bTimeOutms );
    TIM_Cmd(TIM1, ENABLE); 
    while( !( GPIO_ReadInputDataBit( mHW_SPI1_GD0_GPIOx(), mHW_SPI1_GD0_PIN() ) ) )
    {
      if( TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET )
      {
          TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
          #ifdef mDEBUG_MODE
          //Debug_Message( "Receive Timed-out\r\n");
          Debug_Message(".");
          #endif   
          bTimeOutFlag = 1;
          TIM_Cmd(TIM1, DISABLE);
          break;        
      }     
    }
    // TIM_Cmd(TIM1, DISABLE); // THIS WAS HERE INSTEAD OF UP THERE
    while( ( GPIO_ReadInputDataBit( mHW_SPI1_GD0_GPIOx(), mHW_SPI1_GD0_PIN() ) ) );
    if( bTimeOutFlag )
    {
      return 0;
    }
    else
    {
      //UART3_WAIT_AND_SEND( TI_CC_SPIReadReg(TI_CCxxx0_RXFIFO) );
      //Delay( 123 );
      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, (char*)pbRxBuffer, 64); // Pull data
      TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SIDLE);
      TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFRX); 
      
      // RF_ParseOutMessage( (u8*)pbRxBuffer, 64 );    
      #ifdef mDEBUG_MODE
      Convert_ASCII( pbRxBuffer, bLength );
      #endif    
      
    }
    return 1;
}

/*char RFReceivePacket(char *rxBuffer, char *length)
{
  char status[2];
  char pktLen;
  if ((TI_CC_SPIReadStatus(TI_CCxxx0_RXBYTES) & TI_CCxxx0_NUM_RXBYTES))
  {
    pktLen = TI_CC_SPIReadReg(TI_CCxxx0_RXFIFO); // Read length byte
    if (pktLen <= *length)                  // If pktLen size <= rxBuffer
    {
      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, rxBuffer, pktLen); // Pull data
      *length = pktLen;                     // Return the actual size
      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, status, 2);
                                            // Read appended status bytes
      return (char)(status[TI_CCxxx0_LQI_RX]&TI_CCxxx0_CRC_OK);
    }                                       // Return CRC_OK bit
    else
    {
      *length = pktLen;                     // Return the large size
      TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFRX);      // Flush RXFIFO
      return 0;                             // Error
    }
  }
  else
      return 0;                             // Error

}*/





/*******************************************************************************
* Function Name  : TI_CC_SPIReadReg
* Description    : Reads a byte from specific register
* Input          : char addr - address of the register
* Output         : None
* Return         : char x - value in register
*******************************************************************************/
char TI_CC_SPIReadReg(char addr)
{
  char x;
  
  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( pcHW_SPI1_GPIOx, cHW_SPI1_MISO_PIN ) ) );
  /* Send SPI1 data */
  SPI_I2S_SendData(SPI1, addr | TI_CCxxx0_READ_SINGLE);
  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* Send SPI1 data */
  SPI_I2S_SendData(SPI1, 0);
  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* Read Data */
  x = SPI_I2S_ReceiveData( SPI1 );
  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
  
  
  return x;

//  TI_CC_CSn_PxOUT &= ~TI_CC_CSn_PIN;        // /CS enable
//  while (TI_CC_SPI_USART0_PxIN&TI_CC_SPI_USART0_SOMI);// Wait for CCxxxx ready
//  U0TXBUF = (addr | TI_CCxxx0_READ_SINGLE); // Send address
//  while (!(IFG1&URXIFG0));                  // Wait for TX to finish
//  IFG1 &= ~URXIFG0;                         // Clear flag set during last write
//  U0TXBUF = 0;                              // Dummy write so we can read data
//  while (!(IFG1&URXIFG0));                  // Wait for RX to finish
//  x = U0RXBUF;                              // Read data
//  TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;         // /CS disable
  
//  return x;

}

/*******************************************************************************
* Function Name  : TI_CC_SPIReadBurstReg
* Description    : Reads multi bytes from register( mostly used to read a fifo )
* Input          : char addr - address of register
*                  char *buffer - buffer where data will be stored
*                  char count - number of bytes to be read  
* Output         : None
* Return         : None
*******************************************************************************/
void TI_CC_SPIReadBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;
  
  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( pcHW_SPI1_GPIOx, cHW_SPI1_MISO_PIN ) ) );
  /* Send SPI1 data */
  SPI_I2S_SendData(SPI1, addr | TI_CCxxx0_READ_BURST);
  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* Send SPI1 data */
  SPI_I2S_SendData(SPI1, 0);
  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  
  for (i = 0; i < (count-1); i++)
  {
    /* Send SPI1 data */
    SPI_I2S_SendData(SPI1, 0);
    /* Wait for SPI1 Tx buffer empty */
    //while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    buffer[i] = SPI_I2S_ReceiveData( SPI1 );
    /* Wait for SPI1 Rx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    //Delay(0xFFF);
  }
  buffer[count - 1] = SPI_I2S_ReceiveData( SPI1 );
  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);

//  TI_CC_CSn_PxOUT &= ~TI_CC_CSn_PIN;        // /CS enable
//  while (TI_CC_SPI_USART0_PxIN&TI_CC_SPI_USART0_SOMI);// Wait for CCxxxx ready
//  IFG1 &= ~URXIFG0;                         // Clear flag
//  U0TXBUF = (addr | TI_CCxxx0_READ_BURST);  // Send address
//  while (!(IFG1&UTXIFG0));                  // Wait for TXBUF ready
//  U0TXBUF = 0;                              // Dummy write to read 1st data byte
//  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
//  while (!(IFG1&URXIFG0));                  // Wait for end of addr byte TX
//  IFG1 &= ~URXIFG0;                         // Clear flag
//  while (!(IFG1&URXIFG0));                  // Wait for end of 1st data byte TX
//  // First data byte now in RXBUF
//  for (i = 0; i < (count-1); i++)
//  {
//    U0TXBUF = 0;                            //Initiate next data RX, meanwhile..
//    buffer[i] = U0RXBUF;                    // Store data from last data RX
//    while (!(IFG1&URXIFG0));                // Wait for end of data RX
//  }
//  buffer[count-1] = U0RXBUF;                // Store last RX byte in buffer
//  TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;         // /CS disable
}




/*******************************************************************************
* Function Name  : TI_CC_SPIReadStatus
* Description    : Reads a status byte
* Input          : char addr - address of register
* Output         : None
* Return         : char x - status byte  read
*******************************************************************************/
// For status/strobe addresses, the BURST bit selects between status registers
// and command strobes.
char TI_CC_SPIReadStatus(char addr)
{
  char x;
  
  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( pcHW_SPI1_GPIOx, cHW_SPI1_MISO_PIN ) ) );
  /* Send SPI1 data */
  SPI_I2S_SendData(SPI1, addr | TI_CCxxx0_READ_BURST);
  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* Send SPI1 data */
  SPI_I2S_SendData(SPI1, 0);
  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* Read Data */
  x = SPI_I2S_ReceiveData( SPI1 );
  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(pcHW_SP1_CSn_GPIOx, cHW_SPI1_CSn_PIN);
  return x;

//  TI_CC_CSn_PxOUT &= ~TI_CC_CSn_PIN;        // /CS enable
//  while (TI_CC_SPI_USART0_PxIN & TI_CC_SPI_USART0_SOMI);// Wait for CCxxxx ready
//  IFG1 &= ~URXIFG0;                         // Clear flag set during last write
//  U0TXBUF = (addr | TI_CCxxx0_READ_BURST);  // Send address
//  while (!(IFG1&URXIFG0));                  // Wait for TX to finish
//  IFG1 &= ~URXIFG0;                         // Clear flag set during last write
//  U0TXBUF = 0;                              // Dummy write so we can read data
//  while (!(IFG1&URXIFG0));                  // Wait for RX to finish
//  x = U0RXBUF;                              // Read data
//  TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;         // /CS disable
//  return x;
}

#undef cMEM_USERCLASS_ID_HW_BOOT_c


