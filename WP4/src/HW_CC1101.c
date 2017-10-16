/*------------------------------------------------------------------------------
  	$File:		HW_CC1101.c
  	$Module:	Hardware interfaces (SPI) to TI Chipcon CC1101 chip
  	$Prefix:  HW
  	$Language:	ANSI C
  
  	$Description:
			This file contains the interface to the	TI Chipcon CC1101 900 MHz
			ISM band transceiver.

			---------------------------------------
			Basic Programmer's Model for the CC1101:
			------

				-- 13 command strobe registers....................... 0x30..0x3C
					set internal state or mode; write to 0x3D is 
					SNOP but the Chip Status Byte will be returned 
					for this and all other strobe address writes
					(see Datasheet, Rev E, Table 41) 

				-- 47 normal 8-bit configuration registers .......... 0x00..0x2E
					(see Datasheet, Rev E, Table 42) 

				-- 12 read-only status registers .................... 0x30..0x3D
					overlaid on strobe register addresses
					(see Datasheet, Rev E, Table 43) 

				-- 1 Tx output power table (PATABLE)
					accessed via single register .................... 0x3E

				-- 2 FIFOs (TX and RX)
					accessed via single register .................... 0x3F 
					...write operations write to the TX FIFO
					...read operations write to the RX FIFO
						(see Chip Status Byte returned during FIFO 
							read / write in Datasheet, Rev E, Table 23)

  	$Notes:
			<> 	All transactions on the SPI interface start with a 
				header byte containing a R/W¯ bit, a burst access 
				bit (B), and a 6-bit address (A5 – A0)

			<>	MAX SCLK frequency for burst access is 6.5 MHz

			<> 	Status registers cannot be read using burst access

			<> 	Full read-write burst access is available for the 
				config registers in the range of 0x00..0x2E. This is 
				useful as it allows a block of "image" registers to be 
				maintained in RAM which then can then be written any 
				time in burst update of multiple registers without risk 
				of corrupting previous configuration (i.e., config data 
				bits that do not differ from image data will be 
				unaffected by "image" write)
  
  	$Author:	JRAMIREZ, KGANS, 2009-March-23
  	--------------------------------------------------------------------------
  	$Copyright (c) 2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_HW_CC1101_c

/*------------------------------------------------------------------------------
							------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "stm32f10x_lib.h" // for debugging only!!
#include "platform_config.h" // for debugging only??
#include "HW_Def.h"
#include "HW_Code.h"
#include "HW_CC1101.h"

#include "CC1101_Config.h"
#include "SPI_Config.h"
#include "USART_Debug.h"
extern void HW_SYS_InlineDelay_10us( u32 lwMultiplier );

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define mHW_CC1101_QryChipState()\
	((cHW_CC1101_ChipStatusByte_STATE_MASK)&(bMEM_HW_CC1101_chipStatusByte))

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
	$Function: Local_HW_CC1101_SPI1_Enable
	$Description: Asserts CC1101 chip select and waits for Master I/O Select
					to indicate ready status
	$Inputs: args:	u8 bRegAddrs: address of the register
			 		u8 bRegData: 8-bit data to be written to register
	$Outputs: return: none
	$WARNINGS:
	$End
*/
void Local_HW_CC1101_SPI1_Enable( void ) 
{
	u32 lwTemp = 0;

	/* CC1101 chip select ... turn CSn pin on */
	GPIO_ClearBits( mHW_SP1_CSn_GPIOx(), mHW_SPI1_CSn_PIN() );

	/* Wait for CCxxxx ready */
	while( ( GPIO_ReadInputDataBit( mHW_SPI1_GPIOx(), mHW_SPI1_MISO_PIN() ) ) )
	{
		if( ++lwTemp > 0x000FFFFF ) {
			lwTemp = 0; /* breakpoint */
		}
	}
}

/*------------------------------------------------------------------------------
	$Function: Local_HW_CC1101_SPI1_Write
	$Description: Writes a single specific CC1101 register
	$Inputs:	args: u8 bRegAddrs: address of the register
									u8 bRegData: 8-bit data to be written to register
	$Outputs:	return: none
	$WARNINGS:
	$End
*/
void Local_HW_CC1101_SPI1_Write( u16 wInData ) 
{
	u32 lwTemp = 0;

	/* Send SPI1 reg addrs 
	*/
	SPI_I2S_SendData( SPI1, wInData );

	/* Wait for SPI1 Tx buffer empty 
	*/
	while( RESET == SPI_I2S_GetFlagStatus( SPI1, SPI_I2S_FLAG_TXE ) )
	{
		if( ++lwTemp > 0x000FFFFF ) {
			/////// ASSERT or ERR report?
			lwTemp = 0; /* breakpoint */
		}
	}
}

/*------------------------------------------------------------------------------
				----- G L O B A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
	$Function: HW_CC1101_ReqSetRegData
	$Description: Writes a sequence of bytes from appointed memory location to a 
					set of contiguous registers in the CC1101.
	$Inputs: args: u8 bRegAddrs: address of the first register
			 		u8 bRegData: 8-bit data to be written to register
			 		u8 bNumBytes: number of register to be written
	$Outputs: return: none
	$WARNINGS:
	$End
*/
void HW_CC1101_ReqSetRegData( u8 bRegAddrs, u8 * pbRegData, u8 bNumBytes )
{
	u8 b;

	/* activate CC1101 */
	Local_HW_CC1101_SPI1_Enable();

	/* Send SPI1 register addrs */
	Local_HW_CC1101_SPI1_Write( bRegAddrs | (TI_CCxxx0_WRITE_BURST) );

	for( b = 0; b < bNumBytes; b++ )
	{
		/* Write one byte of data to SPI1 bus */
		Local_HW_CC1101_SPI1_Write( pbRegData[b] );
	}

	/* CC1101 chip select ... turn CSn pin off */
	GPIO_SetBits( mHW_SP1_CSn_GPIOx(), mHW_SPI1_CSn_PIN() );
}

/*------------------------------------------------------------------------------
	$Function: HW_CC1101_ReqSetRegData_single
	$Description: Writes a single specific CC1101 register
	$Inputs: args:	u8 bRegAddrs: address of the register
			 		u8 bRegData: 8-bit data to be written to register
	$Outputs: return: none
	$WARNINGS:
	$End
*/
void HW_CC1101_ReqSetRegData_single( u8 bRegAddrs, u8 bRegData )
{
	#if 0 // since STROBE does not require any data, we may keep seperate
	/* special treatment for STROBE addresses */
	if( ((HW_CC1101_ADDRS_STROBE_RESET) <= bRegAddrs) 
			&& 
		((HW_CC1101_ADDRS_STROBE_SNOP) >= bRegAddrs) )
	{
		/* read the Chip Status Byte (pushed onto SPI bus following
			 every STROBE write */
		HW_CC1101_ReqStrobe( bRegAddrs );
	}
	#endif
	/* activate CC1101 */
	Local_HW_CC1101_SPI1_Enable();

	/* Send SPI1 register addrs */
	Local_HW_CC1101_SPI1_Write( bRegAddrs );

	/* Clear flag */
	SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );

	/* Send SPI1 register data */
	Local_HW_CC1101_SPI1_Write( bRegData );

	/* CC1101 chip select ... turn CSn pin off */
	GPIO_SetBits( mHW_SP1_CSn_GPIOx(), mHW_SPI1_CSn_PIN() );
}

/*------------------------------------------------------------------------------
	$Function: HW_CC1101_ReqSetState
	$Description: Performs the operation requested using the CC1101 strobe
					facility and stores the result code (Chip Status Byte)
					returned via the SPI bus in a static local variable. 

	$Inputs: args: none
	$Outputs: return: error code
	$Assumptions: Local chip status byte data is up to date and matches the 
					chip state.
	$WARNINGS:
	$End
*/
u8 HW_CC1101_ReqSetChipState( u8 bState )
{
	#define cHW_CC1101_ReqSetState_MAX_REPEAT 	(2)
	#define cDLY 								(0x00000FFF)
	u8	bError = 0;
	u16	wRepeat = 0,
			wDly;

	/* excute loop until requested state is reached
	*/
	do
	{
		/* check device state and exit once STATE matches request
			...macro is used rather than consuming additional
					cycles unecessarily doing an SPI access
			...also, delay loop is only used if this is not the first 
				time through outer loop
		*/
		wDly = 0;
		while( wDly++ < (cDLY * wRepeat) ) {
			if( mHW_CC1101_QryChipState() == bState ) { break; }
		}
		if( mHW_CC1101_QryChipState() == bState ) { break; }
		
		/* try to switch to the requested state
		*/
		switch( bState )
		{
			case cHW_CC1101_ChipStatusByte_IDLE:
			{
				HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SIDLE );
				break;
			}
			case cHW_CC1101_ChipStatusByte_FSTXON:
			{
				HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SFSTXON );
				break;
			}
			case cHW_CC1101_ChipStatusByte_TX:
			{
				HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_STX );
				break;
			}
			case cHW_CC1101_ChipStatusByte_CALIBRATE:
			{
				HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SCAL );
				break;
			}
			default:
			{
				// error, unintended state
				break;
			}
		}
	} while( (cHW_CC1101_ReqSetState_MAX_REPEAT) < (wRepeat)++ );

	/* check for failure or switch error
	*/
	if( (cHW_CC1101_ReqSetState_MAX_REPEAT) < wRepeat )
	{
		/* error
		*/
		bError = 1;
	}

	return( bError );
	#undef cHW_CC1101_ReqSetState_MAX_REPEAT
	#undef cDLY
}

/*------------------------------------------------------------------------------
	$Function: HW_CC1101_ReqStrobe
	$Description: Writes a single byte "strobe" command to the CC1101 and then
					reads back the response data
	$Inputs: args: u8 bStrobeCommandId
	$Outputs: return: none
	$WARNINGS:
	$End
*/
void HW_CC1101_ReqStrobe( u8 bStrobeCommandId )
{
	/* activate CC1101 */
	Local_HW_CC1101_SPI1_Enable();

	/* Send strobe command */
	Local_HW_CC1101_SPI1_Write( bStrobeCommandId );

	/* read the Chip Status Byte */
	bMEM_HW_CC1101_chipStatusByte = SPI_I2S_ReceiveData( SPI1 );

	/* CC1101 chip select ... turn CSn pin off */
	GPIO_SetBits( mHW_SP1_CSn_GPIOx(), mHW_SPI1_CSn_PIN() );
}

/*------------------------------------------------------------------------------
	$Function: HW_CC1101_QryRegData
	$Description: Reads a sequence of bytes from set of contiguous registers in 
					the CC1101 using "burst" access and stores them at the 
					appointed RAM memory location. 

					If the registers are status registers in the range of
					0x30...0x3D, burst access is not available and the data is 
					then, instead, read byte-by-byte.

	$Inputs: args: u8 bRegAddrs: address of the first register
			 	   u8 pbRegData: appointed address for read data
				   u8 bNumBytes: number of registers to be read
	$Outputs: return: none
	$Assumptions: First address indicates range of addresses to be accessed
			  		(burst access will be used for any non-status registers)
	$WARNINGS:
	$End
*/
void HW_CC1101_QryRegData( u8 bRegAddrs, u8 * pbRegData, u8 bNumBytes )
{
  u8	b;
  
	/* check if burst or single access should be used 
	*/
	if( (bRegAddrs >= (cHW_CC1101_RegType_STATUS_MIN_ADDRS))
				&&
		(bRegAddrs <= (cHW_CC1101_RegType_STATUS_MAX_ADDRS)) )
	{
		/* read one or more bytes, one at a time */
		for( b = 0; b < bNumBytes; b++ )
		{
			HW_CC1101_QryRegData_single( bRegAddrs + b, &pbRegData[b] );
		}
	} 
	else /* use burst access ... see Assumptions */
	{ 
		/* activate CC1101 */
		Local_HW_CC1101_SPI1_Enable();

		/* Send SPI1 register addrs */
		Local_HW_CC1101_SPI1_Write( bRegAddrs | (TI_CCxxx0_READ_BURST) );

		/* read multiple bytes into appointed location */
		for( b = 0; b < bNumBytes; b++ )
		{
			/* Do SPI1 dummy write */
			Local_HW_CC1101_SPI1_Write( 0 );

			/* Wait for SPI1 Tx buffer empty */
			pbRegData[b] = SPI_I2S_ReceiveData( SPI1 );
		}

		/* CC1101 chip select ... turn CSn pin off */
		GPIO_SetBits( mHW_SP1_CSn_GPIOx(), mHW_SPI1_CSn_PIN() );
	}
}

/*------------------------------------------------------------------------------
	$Function: HW_CC1101_QryRegData_single
	$Description: reads the data of a single specific CC1101 register
	$Inputs: args: u8 bRegAddrs: address of the register
			 		u8 * pbRegData: address in RAM where data read from
							chip is to be stored
	$Outputs: return: none
	$WARNINGS:
	$End
*/
void HW_CC1101_QryRegData_single( u8 bRegAddrs, u8 * pbRegData )
{
	/* activate CC1101 */
	Local_HW_CC1101_SPI1_Enable();

	/* Send SPI1 addrs, then data */
	Local_HW_CC1101_SPI1_Write( bRegAddrs | (TI_CCxxx0_READ_SINGLE) );
	Local_HW_CC1101_SPI1_Write( 0 );

	/* read 16-bit data, truncate data, discard MSB
			...see SPI_FirstBit_MSB		
	*/
	*pbRegData = SPI_I2S_ReceiveData( SPI1 );
	/* ----------------- 
			Note: SPI supports either 8-bit or 16-bit data.
					SPI1-DR is, therefore, a 16-bit register.
					... the code comment below demonstrates the intent 
							of the above statement 
		
					wTemp = SPI_I2S_ReceiveData( SPI1 );
					pb = (u8 *)&wTemp;
					*pbRegData = pb[0];
	*/

	/* CC1101 chip select ... turn CSn pin off */
	GPIO_SetBits( mHW_SP1_CSn_GPIOx(), mHW_SPI1_CSn_PIN() );
}

/*------------------------------------------------------------------------------
	$Function: HW_CC1101_QryChipStatusByte
	$Description: Returns the most current value store in the local static
					Chip Status Byte record. Caller may call this function
					requesting a refreshed value or may take advantage
					of previous capture of the status that would have taken 
					place during a previous Strobe or Rx / Tx FIFO operation.

				Note: In interest of efficiency, local functions should
						access bMEM_HW_CC1101_chipStatusByte directly
						whenever possible, especially since they may
						"know" whether or not the _chipStatusByte data is
						current, given that the interface to the device
						is chiefly implemented in this file.
	$Inputs: args: none
	$Outputs: return: none
	$Assumptions: 
	$WARNINGS:
	$End
*/
u8 HW_CC1101_QryChipStatusByte( u8 bRefresh )
{
	if( bRefresh ) {
		HW_CC1101_ReqStrobe( HW_CC1101_ADDRS_STROBE_SNOP );
	}
	return( bMEM_HW_CC1101_chipStatusByte );
}

/*------------------------------------------------------------------------------
	$Function: HW_CC1101_QryChipState
	$Description: Returns the most current STATE value store in the CC1101
					(an update of local static Chip Status Byte record
						results from a call to this function).
	$Inputs: args: none
	$Outputs: return: u8: ChipStatusByte STATE bits
	$Assumptions: 
	$WARNINGS:
	$End
*/
u8 HW_CC1101_QryChipState( void )
{
	return( (cHW_CC1101_ChipStatusByte_STATE_MASK) & (HW_CC1101_QryChipStatusByte( 1 )) );
}


/*------------------------------------------------------------------------------
	$Function: HW_CC1101_PowerupReset
	$Description: Resets the CC1101 chip following reset of the WP4 
					microprocessor

		Application Notes:
		-----------------
		The SO pin	will go low immediately after taking CSn low. If CSn is taken 
		low before reset is completed, the SO pin will first go high, indicating that 
		the	crystal oscillator is not stabilized, before going low as shown in Figure 
		22.

		_____Manual Reset_____
		The other global reset possibility on CC1101 uses the SRES command strobe. 
		By issuing this strobe, all internal registers and states are	set to the 
		default, IDLE state. The manual	power-up sequence is as follows (see Figure
		23):

		• Set SCLK = 1 and SI = 0, to avoid	potential problems with pin control mode
			(see Section 11.3 on page 33).

		• Strobe CSn low / high.

		• Hold CSn low and then high for at least 40us relative to pulling CSn low

		• Pull CSn low and wait for SO to go low (CHIP_RDYn).

		• Issue the SRES strobe on the SI line.

		• When SO goes low again, reset is complete and the chip is in the IDLE state.

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

-------------
p. 49
change the signal that is output on the GDO0
pin. The default setting is to output a clock
signal with a frequency of CLK_XOSC/192.
However, to optimize performance in TX and
RX, an alternative GDO setting from the
settings found in Table 40 on page 60 should
be selected.


-------------



	$Inputs:			args: none
	$Outputs:			return: none
	$WARNINGS:	1) The condition of the chip must be established 
									(i.e. is this reset due to power-up OR
												was the MPU simpy reset?). 
												
		CAN WE SAFELY ALWAYS PERFORM THE POWER-UP RESET SEQUENCE?
									
	$End
*/
void HW_CC1101_PowerupReset( void )
{
	/* CC1101 chip select ... turn CSn pin off */
	GPIO_SetBits( mHW_SP1_CSn_GPIOx(), mHW_SPI1_CSn_PIN() );

	/* TI_CC_Wait(30);
	*/
	HW_SYS_InlineDelay_10us( 4 );

	/* CC1101 chip select ... turn CSn pin on*/
	GPIO_ClearBits( mHW_SP1_CSn_GPIOx(), mHW_SPI1_CSn_PIN() );

	/* TI_CC_Wait(30);
	*/
	HW_SYS_InlineDelay_10us( 4 );

	/* CC1101 chip select ... turn CSn pin off */
	GPIO_SetBits( mHW_SP1_CSn_GPIOx(), mHW_SPI1_CSn_PIN() );

	/* TI_CC_Wait(45);
	*/
	HW_SYS_InlineDelay_10us( 6 ); /* ????????????????????????????????????? */

	/* send reset strobe
	*/
	HW_CC1101_ReqStrobe( HW_CC1101_ADDRS_STROBE_SRES );
}

#if 1
/*------------------------------------------------------------------------------
	$Function: 		HW_CC1101_TxPacket
	$Description: Initializes the CC1101 chip via strob commands and then writes
								appointed data to CC1101 Tx FIFO.
	$Inputs:			args: 
	$Outputs:			return: none
	$WARNINGS:
	$End
*/
void HW_CC1101_TxPacket( u8 * pbBuf, u8 bNumBytes )
{
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SIDLE );
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SFRX );
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SFTX );

	TI_CC_SPIWriteBurstReg( TI_CCxxx0_TXFIFO, pbBuf, bNumBytes );

	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_STX );

	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SIDLE );
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SFRX );
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SFTX );

	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SRX );
}


/* do a burst read of the CC1101 Rx FIFO
*/
void HW_CC1101_SPI_BurstTest( void )
{
	u8	pbRxBuf[128];
//	u8 bTimeOutFlag = 0;
  
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SIDLE );
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SFRX) ; 
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SFTX );
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SRX) ; 
    
//	while( 1 ) 
//	{ 
		HW_CC1101_QryRegData( TI_CCxxx0_RXFIFO, pbRxBuf, 64 );
		Convert_ASCII( pbRxBuf, 32 );
//	}
      
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SIDLE );
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SFRX) ; 
	HW_CC1101_ReqStrobe( cHW_CC1101_ADDRS_STROBE_SFTX );
}
#endif

#undef cMEM_USERCLASS_ID_HW_CC1101_c


