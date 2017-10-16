/*------------------------------------------------------------------------------
  	$File:		HW_CC1101.h
  	$Module:	Hardware
  	$Prefix:  	HW
  	$Language:	ANSI C
  
  	$Description:
			This file contains register address and data definitions for the 
			configuration of the TI Chipcon CC1101 900 MHz ISM band transceiver
		
  	$Notes:
  
  	$Author:	JRAMIREZ, KGANS, 2009-March-23
  	--------------------------------------------------------------------------
  	$Copyright (c) 2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef cHW_CC1101_H
#define cHW_CC1101_H

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

//////////////
/////////////   BAAAAD  ...couldn't IAR to find file (?)  
/////////////			...Options->C/C++->Preprocessor looked OK
/////////////
#define cBLD_RFC_PROT_NUM_FREQS						(51)

/* ...about the frequency multiplier
		... if we want to use the "CHANNEL" facility of the CC1101 we have to define
			smaller frequency steps (26MHz crystal limits the width of a channel to about
			405 kHz and we want 500 kHz steps  ... therefore, we define 102 channels
			instead of 51 and then only use the even channels
*/
#define	cRFC_CC1101_FREQ_MULTIPLIER					(2)

#define cpbHW_CC1010_INIT_DATA_NUM_ENTRIES			pcbHW_Code_CC1101_RegData_InitData_NUM_ENTRIES[0]
#define cHW_CC1101_PATABLE_Profile_DEFAULT_INDEX 	(1)

/* 	------------------------------
		--- Register Access Ranges ---
		------------------------------ 
*/
#define cHW_CC1101_RegType_BLOCKED			(0)
#define cHW_CC1101_RegType_CONFIG			(1)
#define cHW_CC1101_RegType_STATUS			(2)
#define cHW_CC1101_RegType_DATA				(3)
#define cHW_CC1101_RegType_RESERVED			(4)

#define mHW_CC1101_SetBits(cbToken_FLAGS,bToken_data) 	((bToken_data)|=(cbToken_FLAGS))
#define mHW_CC1101_ClearBits(cbToken_FLAGS,bToken_data) ((bToken_data)&=(~(cbToken_FLAGS)))

//#define cpbHW_CC1101_INIT_DATA_NUM_ENTRIES	pcbHW_Code_CC1101_RegData_InitData_NUM_ENTRIES[0]
//#define	cpbHW_CC1101_PATABLE_NUM_BYTES		pcbHW_Code_CC1101_PATABLE_NUM_BYTES[0]

/* 	------------------------------
	--- Register Access Ranges ---
	------------------------------ 
*/

/* these definitions have no relation to CC1101 registers and are only defined
	for the purposes of creating register data tables
*/
#define cHW_CC1101_RegType_BLOCKED			(0)
#define cHW_CC1101_RegType_CONFIG			(1)
#define cHW_CC1101_RegType_STATUS			(2)
#define cHW_CC1101_RegType_DATA				(3)
#define cHW_CC1101_RegType_RESERVED			(4)

#define cHW_CC1101_RegType_CONFIG_MIN_ADDRS	(0x00)
#define cHW_CC1101_RegType_CONFIG_MAX_ADDRS	(0x2E)
#define cHW_CC1101_RegType_STATUS_MIN_ADDRS	(0x30)
#define cHW_CC1101_RegType_STATUS_MAX_ADDRS	(0x3D)

/* 	-------------------------------
	--- Configuration Registers ---
	------------------------------- 
*/
#define cHW_CC1101_ADDRS_CONFIG_IOCFG2       0x00        // GDO2 output pin configuration
#define cHW_CC1101_ADDRS_CONFIG_IOCFG1       0x01        // GDO1 output pin configuration
#define cHW_CC1101_ADDRS_CONFIG_IOCFG0       0x02        // GDO0 output pin configuration
#define cHW_CC1101_ADDRS_CONFIG_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define cHW_CC1101_ADDRS_CONFIG_SYNC1        0x04        // Sync word, high byte
#define cHW_CC1101_ADDRS_CONFIG_SYNC0        0x05        // Sync word, low byte
#define cHW_CC1101_ADDRS_CONFIG_PKTLEN       0x06        // Packet length
#define cHW_CC1101_ADDRS_CONFIG_PKTCTRL1     0x07        // Packet automation control
#define cHW_CC1101_ADDRS_CONFIG_PKTCTRL0     0x08        // Packet automation control
#define cHW_CC1101_ADDRS_CONFIG_ADDR         0x09        // Device address
#define cHW_CC1101_ADDRS_CONFIG_CHANNR       0x0A        // Channel number
#define cHW_CC1101_ADDRS_CONFIG_FSCTRL1      0x0B        // Frequency synthesizer control
#define cHW_CC1101_ADDRS_CONFIG_FSCTRL0      0x0C        // Frequency synthesizer control
#define cHW_CC1101_ADDRS_CONFIG_FREQ2        0x0D        // Frequency control word, high byte
#define cHW_CC1101_ADDRS_CONFIG_FREQ1        0x0E        // Frequency control word, middle byte
#define cHW_CC1101_ADDRS_CONFIG_FREQ0        0x0F        // Frequency control word, low byte
#define cHW_CC1101_ADDRS_CONFIG_MDMCFG4      0x10        // Modem configuration
#define cHW_CC1101_ADDRS_CONFIG_MDMCFG3      0x11        // Modem configuration
#define cHW_CC1101_ADDRS_CONFIG_MDMCFG2      0x12        // Modem configuration
#define cHW_CC1101_ADDRS_CONFIG_MDMCFG1      0x13        // Modem configuration
#define cHW_CC1101_ADDRS_CONFIG_MDMCFG0      0x14        // Modem configuration
#define cHW_CC1101_ADDRS_CONFIG_DEVIATN      0x15        // Modem deviation setting
#define cHW_CC1101_ADDRS_CONFIG_MCSM2        0x16        // Main Radio Cntrl State Machine config
#define cHW_CC1101_ADDRS_CONFIG_MCSM1        0x17        // Main Radio Cntrl State Machine config
#define cHW_CC1101_ADDRS_CONFIG_MCSM0        0x18        // Main Radio Cntrl State Machine config
#define cHW_CC1101_ADDRS_CONFIG_FOCCFG       0x19        // Frequency Offset Compensation config
#define cHW_CC1101_ADDRS_CONFIG_BSCFG        0x1A        // Bit Synchronization configuration
#define cHW_CC1101_ADDRS_CONFIG_AGCCTRL2     0x1B        // AGC control
#define cHW_CC1101_ADDRS_CONFIG_AGCCTRL1     0x1C        // AGC control
#define cHW_CC1101_ADDRS_CONFIG_AGCCTRL0     0x1D        // AGC control
#define cHW_CC1101_ADDRS_CONFIG_WOREVT1      0x1E        // High byte Event 0 timeout
#define cHW_CC1101_ADDRS_CONFIG_WOREVT0      0x1F        // Low byte Event 0 timeout

/* -----------------------------------------------------------------------------
	WORCTRL - Wake On Radio control
*/
#define cHW_CC1101_ADDRS_CONFIG_WORCTRL		(0x20)
#define cHW_CC1101_WORCTRL_bits_RC_CAL		(0x08)
#define cHW_CC1101_WORCTRL_bits_RC_PD		(0x80)

/* -----------------------------------------------------------------------------
	 FREND1 – Front End TX Configuration
*/
#define cHW_CC1101_ADDRS_CONFIG_FREND1		(0x21)

/* -----------------------------------------------------------------------------
	 FREND0 – Front End TX Configuration
*/
#define cHW_CC1101_ADDRS_CONFIG_FREND0		(0x22)
#define cHW_CC1101_FREND0_bits_PA_POWER		(0x07)

/* -----------------------------------------------------------------------------
	FSCAL3       - // Frequency synthesizer calibration
*/
#define cHW_CC1101_ADDRS_CONFIG_FSCAL3       (0x23)

/* -----------------------------------------------------------------------------
	FSCAL2       - // Frequency synthesizer calibration
*/
#define cHW_CC1101_ADDRS_CONFIG_FSCAL2       (0x24)
/* -----------------------------------------------------------------------------
	FSCAL1       - // Frequency synthesizer calibration
*/
#define cHW_CC1101_ADDRS_CONFIG_FSCAL1       (0x25)
/* -----------------------------------------------------------------------------
	FSCAL0       - // Frequency synthesizer calibration
*/
#define cHW_CC1101_ADDRS_CONFIG_FSCAL0       (0x26)
/* -----------------------------------------------------------------------------
	RCCTRL1      - // RC oscillator configuration
*/
#define cHW_CC1101_ADDRS_CONFIG_RCCTRL1      (0x27)
/* -----------------------------------------------------------------------------
	RCCTRL0      - // RC oscillator configuration
*/
#define cHW_CC1101_ADDRS_CONFIG_RCCTRL0      (0x28)
/* -----------------------------------------------------------------------------
	FSTEST       - // Frequency synthesizer cal control
*/
#define cHW_CC1101_ADDRS_CONFIG_FSTEST       (0x29)
/* -----------------------------------------------------------------------------
	PTEST        - // Production test
*/
#define cHW_CC1101_ADDRS_CONFIG_PTEST        (0x2A)
/* -----------------------------------------------------------------------------
	AGCTEST      - // AGC test
*/
#define cHW_CC1101_ADDRS_CONFIG_AGCTEST      (0x2B)
/* -----------------------------------------------------------------------------
	TEST2        - // Various test settings
*/
#define cHW_CC1101_ADDRS_CONFIG_TEST2        (0x2C)
/* -----------------------------------------------------------------------------
	TEST1        - // Various test settings
*/
#define cHW_CC1101_ADDRS_CONFIG_TEST1        (0x2D)
/* -----------------------------------------------------------------------------
	TEST0        - // Various test settings
*/
#define cHW_CC1101_ADDRS_CONFIG_TEST0        (0x2E)

/* -----------------------------------------------------------------------------
	NULL_ADDRS   - // DUMMY, NULL terminate TBL
*/
#define cHW_CC1101_ADDRS_CONFIG_NULL		(0xFF)

/* 	-----------------------
	--- Strobe Commands ---
	----------------------- 
*/

/* Reset chip 
*/
#define cHW_CC1101_ADDRS_STROBE_SRES	(0x30)

/* Enable/calibrate freq synthesizer 
*/
#define cHW_CC1101_ADDRS_STROBE_SFSTXON	(0x31)

/* Turn off crystal oscillator */
#define cHW_CC1101_ADDRS_STROBE_SXOFF	(0x32)

/* Calibrate freq synthesizer  
	and then go to Idle */
#define cHW_CC1101_ADDRS_STROBE_SCAL	(0x33)

/* Enable RX 
*/
#define cHW_CC1101_ADDRS_STROBE_SRX		(0x34)

/* Enable TX 
*/
#define cHW_CC1101_ADDRS_STROBE_STX		(0x35)

/* Exit RX / TX (or CALIBRATE, or FSTXON...)
*/
#define cHW_CC1101_ADDRS_STROBE_SIDLE	(0x36)

/* AFC adjustment of freq synthesizer
*/
#define cHW_CC1101_ADDRS_STROBE_SAFC	(0x37)        

/* Start automatic RX polling sequence
*/
#define cHW_CC1101_ADDRS_STROBE_SWOR	(0x38)        

/* Enter pwr down mode when CSn goes hi
*/
#define cHW_CC1101_ADDRS_STROBE_SPWD	(0x39)        

/* Flush the RX FIFO buffer.
*/
#define cHW_CC1101_ADDRS_STROBE_SFRX	(0x3A)        

/* Flush the TX FIFO buffer.
*/
#define cHW_CC1101_ADDRS_STROBE_SFTX	(0x3B)        

/* Reset real time clock.
*/
#define cHW_CC1101_ADDRS_STROBE_SWORRST	(0x3C)        

/* No operation but causes ChipStatusByte to be output on the SPI bus 
*/
#define cHW_CC1101_ADDRS_STROBE_SNOP	(0x3D)


/* 	------------------------
	--- Status Registers ---
	------------------------ 
*/
#define TI_CCxxx0_PARTNUM      0x30        // Part number
#define TI_CCxxx0_VERSION      0x31        // Current version number
#define TI_CCxxx0_FREQEST      0x32        // Frequency offset estimate
#define TI_CCxxx0_LQI          0x33        // Demodulator estimate for link quality
#define TI_CCxxx0_RSSI         0x34        // Received signal strength indication

/* 	--------------------------------------------------
	MARCSTATE – Main Radio Control State Machine State
	--------------------------------------------------

		This data is contained in bits 4..0 of MARCSTATE 
		bits 7..5 are reserved 	...see also CC1101 DS, Rev E, Fig. 22, p. 49

		Note: SLEEP or XOFF states can only be active CSn is high 
				(chip not selected) so will never be read.
*/
#define cHW_CC1101_ADDRS_STATUS_MARCSTATE					(0x35)
#define cHW_CC1101_MARCSTATE_RESERVED_BITS					(0xE0)

#define cHW_CC1101_MARCSTATE_SLEEP_SLEEP					(0x00)
#define cHW_CC1101_MARCSTATE_IDLE_IDLE						(0x01)
#define cHW_CC1101_MARCSTATE_XOFF_XOFF						(0x02)
#define cHW_CC1101_MARCSTATE_MANCAL_VCOON_MC				(0x03)
#define cHW_CC1101_MARCSTATE_MANCAL_REGON_MC				(0x04)
#define cHW_CC1101_MARCSTATE_MANCAL_MANCAL					(0x05)
#define cHW_CC1101_MARCSTATE_FS_WAKEUP_VCOON				(0x06)
#define cHW_CC1101_MARCSTATE_FS_WAKEUP_REGON				(0x07)
#define cHW_CC1101_MARCSTATE_CALIBRATE_STARTCAL				(0x08)
#define cHW_CC1101_MARCSTATE_SETTLING_BWBOOST				(0x09)
#define cHW_CC1101_MARCSTATE_SETTLING_FS_LOCK				(0x0A)
#define cHW_CC1101_MARCSTATE_SETTLING_IFADCON				(0x0B)
#define cHW_CC1101_MARCSTATE_ENDCAL_CALIBRATE				(0x0C)
#define cHW_CC1101_MARCSTATE_RX_RX							(0x0D)
#define cHW_CC1101_MARCSTATE_RX_RX_END						(0x0E)
#define cHW_CC1101_MARCSTATE_RX_RX_RST						(0x0F)
#define cHW_CC1101_MARCSTATE_TXRX_SETTLING_TXRX_SWITCH		(0x10)
#define cHW_CC1101_MARCSTATE_RXFIFO_OVERFLOW_RXFIFO_OVERFLOW (0x11)
#define cHW_CC1101_MARCSTATE_FSTXON_FSTXON					(0x12)
#define cHW_CC1101_MARCSTATE_TX_TX							(0x13)
#define cHW_CC1101_MARCSTATE_TX_TX_END						(0x14)
#define cHW_CC1101_MARCSTATE_RXTX_SWITCH_RXTX_SETTLING		(0x15)
#define cHW_CC1101_MARCSTATE_TXFIFO_UNDERFLOW_TXFIFO_UNDERFLOW (0x16)



/* High byte of WOR timer 
*/
#define TI_CCxxx0_WORTIME1     0x36        
#define TI_CCxxx0_WORTIME0     0x37        // Low byte of WOR timer
#define TI_CCxxx0_PKTSTATUS    0x38        // Current GDOx status and packet status
#define TI_CCxxx0_VCO_VC_DAC   0x39        // Current setting from PLL cal module
#define TI_CCxxx0_TXBYTES      0x3A        // Underflow and # of bytes in TXFIFO
#define TI_CCxxx0_RXBYTES      0x3B        // Overflow and # of bytes in RXFIFO


/* 	-------------------------------------
	RCCTRL1 – RC Oscillator Configuration
	-------------------------------------
*/
#define cHW_CC1101_ADDRS_STATUS_RCCTRL1					(0x3C)

/* 	-------------------------------------
	RCCTRL0 – RC Oscillator Configuration
	-------------------------------------
*/
#define cHW_CC1101_ADDRS_STATUS_RCCTRL0					(0x3D)



#define TI_CCxxx0_NUM_RXBYTES  0x7F        // Mask "# of bytes" field in _RXBYTES

/* 	----------------------------------------
	--- Miscellaneous Register Addresses ---
	----------------------------------------
*/

#define cHW_CC1101_ADDRS_ARRAY_PATABLE	(0x3E)
#define cHW_CC1101_PATABLE_NUM_BYTES	(8)

#define cHW_CC1101_ADDRS_ARRAY_TXFIFO	(0x3F)
#define cHW_CC1101_ADDRS_ARRAY_RXFIFO	(0x3F)

/* 	---------------------
	--- Miscellaneous ---
	---------------------
*/

/* Masks for appended status bytes
*/
#define TI_CCxxx0_LQI_RX       0x01        // Position of LQI byte
#define TI_CCxxx0_CRC_OK       0x80        // Mask "CRC_OK" bit within LQI byte

/* Definitions to support burst/single access:
*/
#define TI_CCxxx0_WRITE_BURST  0x40
#define TI_CCxxx0_READ_SINGLE  0x80
#define TI_CCxxx0_READ_BURST   0xC0


/* 	--------------------------
	--- CC1101 Main States ---
	--------------------------

	These are the states that are returned in the "ChipStatusByte"
	...of note, SLEEP cannot be reported in the ChipStatusByte.

	The state data can only be matched after the other bit-flags in the 
	ChipStatusByte data have been masked. Macros defined below
	are implicit of this intent
*/
#define mHW_CC1101_ChipStatusByte_CREATE_MASK(bToken_state) ((bToken_state)<<(4))

#define mHW_CC1101_ChipStatusByte_isState(bToken_ChipStatusByte_data,bToken_cHW_CC1101_ChipStatusByte_STATE) \
		((bToken_ChipStatusByte_data)&(bToken_cHW_CC1101_ChipStatusByte_STATE)==(bToken_cHW_CC1101_ChipStatusByte_STATE))

#define cHW_CC1101_ChipStatusByte_STATE_MASK (mHW_CC1101_ChipStatusByte_CREATE_MASK(7))


/* 	----------
	IDLE State 
	----------
	also reported for some transitional states, instead
	of SETTLING or CALIBRATE
*/
#define cHW_CC1101_ChipStatusByte_IDLE				(mHW_CC1101_ChipStatusByte_CREATE_MASK(0x00))

/*	--------
	RX State
	--------
	Receive mode
*/
#define cHW_CC1101_ChipStatusByte_RX				(mHW_CC1101_ChipStatusByte_CREATE_MASK(0x01))

/*	--------
	TX State
	--------
	Transmit mode
*/
#define cHW_CC1101_ChipStatusByte_TX				(mHW_CC1101_ChipStatusByte_CREATE_MASK(0x02))

/*	------------
	FSTXON State
	------------
	Fast Tx ready
*/
#define cHW_CC1101_ChipStatusByte_FSTXON			(mHW_CC1101_ChipStatusByte_CREATE_MASK(0x03))

/*	---------------
	CALIBRATE State
	---------------
	Frequency synthesizer calibration is running
*/
#define cHW_CC1101_ChipStatusByte_CALIBRATE			(mHW_CC1101_ChipStatusByte_CREATE_MASK(0x04))

/*	--------------
	SETTLING State
	---------------
	PLL is settling 
*/
#define cHW_CC1101_ChipStatusByte_SETTLING			(mHW_CC1101_ChipStatusByte_CREATE_MASK(0x05))

/*	---------------------
	RXFIFO_OVERFLOW State
	---------------------
	RX FIFO has overflowed. 
		...read out any useful data, then flush the FIFO with SFRX
*/
#define cHW_CC1101_ChipStatusByte_RXFIFO_OVERFLOW	(mHW_CC1101_ChipStatusByte_CREATE_MASK(0x06))

/*	----------------------
	TXFIFO_UNDERFLOW State
	----------------------
	TX FIFO has underflowed. Acknowledge with SFTX
*/
#define cHW_CC1101_ChipStatusByte_TXFIFO_OVERFLOW	(mHW_CC1101_ChipStatusByte_CREATE_MASK(0x07))


/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*--------------------------------------------------------------------
 	$Type: tpHW_CC1101_perFreqCalData
	$Description:
		Creates the structure for populating arrays of calibration
		data. It is intended that this data will be part of any manual 
		frequency calibration process implemented.
	$End
 */
typedef struct tpHW_CC1101_perFreqCalData_tag 
{
	u8	bFSCAL1;

} tpHW_CC1101_perFreqCalData;

/*--------------------------------------------------------------------
 	$Type: tpHW_CC1101_allFreqCalData
	$Description:
		Creates the structure for transceiver calibration data that
		does not change with frequency
		data. It is intended that this data will be part of any manual 
		frequency calibration process implemented.
	$End
 */
typedef struct tpHW_CC1101_allFreqCalData_tag 
{
	u8	bFSCAL3;
	u8	bFSCAL2;
	u8	bRCCTRL1;
	u8	bRCCTRL0;

} tpHW_CC1101_allFreqCalData;

/*--------------------------------------------------------------------
 	$Type: tpHW_CC1101_RegData
	$Description:
		Creates the structure for populating arrays of configuration 
		parameters.
	$End
 */
typedef struct tpHW_CC1101_RegData_tag 
{
	u8	bRegAddrs;
	u8	bRegType;
	u8	bRegData;

} tpHW_CC1101_RegData;

/*--------------------------------------------------------------------
 	$Type: tpHW_CC1101_PATABLE_Profile
	$Description:
		Creates the structure for populating array of CC1101
		power amplifier ramping data (PATABLE).
	$End
*/
typedef struct tpHW_CC1101_PATABLE_Profile_tag 
{
	u8	pbData[cHW_CC1101_PATABLE_NUM_BYTES];

} tpHW_CC1101_PATABLE_Profile;

/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
*/
extern const tpHW_CC1101_RegData ppcHW_CC1101_code_RegData_init[];
extern const tpHW_CC1101_PATABLE_Profile ppcHW_CC1101_code_PATABLE_Profile[];

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

extern void HW_CC1101_ReqSetRegData( u8 bRegAddrs, u8 * pbRegData, u8 bNumBytes );
extern void HW_CC1101_ReqSetRegData_single( u8 bRegAddrs, u8 bRegData );
extern u8 HW_CC1101_ReqSetChipState( u8 bState );
extern void HW_CC1101_ReqStrobe( u8 bStrobeCommandId );
extern void HW_CC1101_QryRegData( u8 bRegAddrs, u8 * pbRegData, u8 bNumBytes );
extern void HW_CC1101_QryRegData_single( u8 bRegAddrs, u8 * pbRegData );
extern u8 HW_CC1101_QryChipStatusByte( u8 bRefresh );
extern u8 HW_CC1101_QryChipState( void );
extern void HW_CC1101_PowerupReset( void );
#if 0
extern void HW_CC1101_TxPacket( u8 * pbBuf, u8 bNumBytes );
extern void HW_CC1101_SPI_BurstTest( void );
#endif

#endif /* cHW_CC1101_H */