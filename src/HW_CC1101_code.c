/*------------------------------------------------------------------------------
  	$File:		RFC_code.c
  	$Module:	Radio Frequency Communications
  	$Prefix:  	RFC
  	$Language:	ANSI C
  
  	$Description:
		This file contains (ROM) data tables used for configuration of the
		TI Chipcon CC1101 900 MHz ISM band transceiver.

  	$CAUTION:	In some cases, the order of execution that results in reading
				table data and applying it directly to hardware may have been
				assumed by a designer (or implemented without awareness of some
				particular sensitivity). THERFORE, unless there is a good reason
				to change the order of the declarations in the ROM tables, they 
				should be left as is. This is particularly true for bug-fix 
				releases and short-timeline development where there may not be 
				adequate soak time available to expose bugs that are related to 
				the order of set-up of a chip's registers.
				----
				Note: The caution above is not meant to imply that there can or 
						should be any reduction
						i) in each designer's responsibility to their fellow 
								designers; and
						ii) of adequated caution and warning comments thoughout the 
								rest of the source code.

  	$Author:	KGANS, 2009-March-22
  	--------------------------------------------------------------------------
  	$Copyright (c) 2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_RFC_CODE_c

/*------------------------------------------------------------------------------
							------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "HW_CC1101.h"

/*------------------------------------------------------------------------------
			----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define cBLOCK		(cHW_CC1101_RegType_BLOCKED)
#define cCONFIG		(cHW_CC1101_RegType_CONFIG)
#define cSTATUS		(cHW_CC1101_RegType_STATUS)
#define cDATA		(cHW_CC1101_RegType_DATA)
#define	cRESERVED	(cHW_CC1101_RegType_RESERVED)

/* these macros are created to make the ROM tables a bit easier to read
*/
#define c_IOCFG2	cHW_CC1101_ADDRS_CONFIG_IOCFG2		
#define c_IOCFG1	cHW_CC1101_ADDRS_CONFIG_IOCFG1		
#define c_IOCFG0	cHW_CC1101_ADDRS_CONFIG_IOCFG0		
#define c_FIFOTHR	cHW_CC1101_ADDRS_CONFIG_FIFOTHR		
#define c_SYNC1		cHW_CC1101_ADDRS_CONFIG_SYNC1		
#define c_SYNC0		cHW_CC1101_ADDRS_CONFIG_SYNC0		
#define c_PKTLEN	cHW_CC1101_ADDRS_CONFIG_PKTLEN		
#define c_PKTCTRL1	cHW_CC1101_ADDRS_CONFIG_PKTCTRL1	
#define c_PKTCTRL0	cHW_CC1101_ADDRS_CONFIG_PKTCTRL0	
#define c_ADDR		cHW_CC1101_ADDRS_CONFIG_ADDR		
#define c_CHANNR	cHW_CC1101_ADDRS_CONFIG_CHANNR		
#define c_FSCTRL1	cHW_CC1101_ADDRS_CONFIG_FSCTRL1		
#define c_FSCTRL0	cHW_CC1101_ADDRS_CONFIG_FSCTRL0		
#define c_FREQ2		cHW_CC1101_ADDRS_CONFIG_FREQ2		
#define c_FREQ1		cHW_CC1101_ADDRS_CONFIG_FREQ1		
#define c_FREQ0		cHW_CC1101_ADDRS_CONFIG_FREQ0		
#define c_MDMCFG4	cHW_CC1101_ADDRS_CONFIG_MDMCFG4		
#define c_MDMCFG3	cHW_CC1101_ADDRS_CONFIG_MDMCFG3		
#define c_MDMCFG2	cHW_CC1101_ADDRS_CONFIG_MDMCFG2		
#define c_MDMCFG1	cHW_CC1101_ADDRS_CONFIG_MDMCFG1		
#define c_MDMCFG0	cHW_CC1101_ADDRS_CONFIG_MDMCFG0		
#define c_DEVIATN	cHW_CC1101_ADDRS_CONFIG_DEVIATN		
#define c_MCSM2		cHW_CC1101_ADDRS_CONFIG_MCSM2		
#define c_MCSM1		cHW_CC1101_ADDRS_CONFIG_MCSM1		
#define c_MCSM0		cHW_CC1101_ADDRS_CONFIG_MCSM0		
#define c_FOCCFG	cHW_CC1101_ADDRS_CONFIG_FOCCFG		
#define c_BSCFG		cHW_CC1101_ADDRS_CONFIG_BSCFG		
#define c_AGCCTRL2	cHW_CC1101_ADDRS_CONFIG_AGCCTRL2	
#define c_AGCCTRL1	cHW_CC1101_ADDRS_CONFIG_AGCCTRL1	
#define c_AGCCTRL0	cHW_CC1101_ADDRS_CONFIG_AGCCTRL0	
#define c_WOREVT1	cHW_CC1101_ADDRS_CONFIG_WOREVT1		
#define c_WOREVT0	cHW_CC1101_ADDRS_CONFIG_WOREVT0		
#define c_WORCTRL	cHW_CC1101_ADDRS_CONFIG_WORCTRL		
#define c_FREND1	cHW_CC1101_ADDRS_CONFIG_FREND1		
#define c_FREND0	cHW_CC1101_ADDRS_CONFIG_FREND0		
#define c_FSCAL3	cHW_CC1101_ADDRS_CONFIG_FSCAL3		
#define c_FSCAL2	cHW_CC1101_ADDRS_CONFIG_FSCAL2		
#define c_FSCAL1	cHW_CC1101_ADDRS_CONFIG_FSCAL1		
#define c_FSCAL0	cHW_CC1101_ADDRS_CONFIG_FSCAL0		
#define c_RCCTRL1	cHW_CC1101_ADDRS_CONFIG_RCCTRL1		
#define c_RCCTRL0	cHW_CC1101_ADDRS_CONFIG_RCCTRL0		
#define c_FSTEST	cHW_CC1101_ADDRS_CONFIG_FSTEST		
#define c_PTEST		cHW_CC1101_ADDRS_CONFIG_PTEST		
#define c_AGCTEST	cHW_CC1101_ADDRS_CONFIG_AGCTEST		
#define c_TEST2		cHW_CC1101_ADDRS_CONFIG_TEST2		
#define c_TEST1		cHW_CC1101_ADDRS_CONFIG_TEST1		
#define c_TEST0		cHW_CC1101_ADDRS_CONFIG_TEST0		
#define c_NULL		cHW_CC1101_ADDRS_CONFIG_NULL		


/*------------------------------------------------------------------------------
				----- D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
					----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */

/*
	FAQ: Making CC111x compatible with CC1010.
	--------------
	To make CC111x compatible with CC1010 it is first of all necessary to 
	align the basic RF settings, like frequency and data rate.

	Additionally the following key parameters must be aligned:
	* CC1110 Modulation = 2FSK
	* CC1110 Deviation = CC1010 Separation/2
	* CC1110 RX Filterbandwidth. Function of frequency separation, data rate and frequency error.
	   Refer to design note DN005 (http://www.ti.com/litv/pdf/swra122a).
		* [CC111x.SYNC1] = [CC1010.PREAMBLE pattern, e.g. = 0xAA (used in the CC1010 SW Examples)].
		* [CC111x.SYNC0] = [CC1010.BSYNC, e.g. = 0x5A (used in the CC1010 SW Examples)].
		* [CC111x.PKTCTRL0.CRC_EN = 0] if the CC1010 software applies the same CRC calculation as the CC1010 SW Examples.
		   Alternatively, keep [CC111x.PKTCTRL0.CRC_EN = 1], but then the CC1010 software must implement the same CRC calculation
		   as used by the built-in CC111x CRC generator (ref. data sheet for relevant details).
*/

/* Chipcon */
/* Product = CC1101 */
/* Chip version = A   (VERSION = 0x04) */
/* Crystal accuracy = 10 ppm */
/* X-tal frequency = 26 MHz */
/* RF output power = -10 dBm */
/* RX filterbandwidth = 270.833333 kHz */
/* Deviation = 254 kHz */
/* Datarate = 76.766968 kBaud */
/* Modulation = (0) 2-FSK */
/* Manchester enable = (1) Manchester enabled */
/* RF Frequency = 902.499847 MHz */
/* Channel spacing = 249.938965 kHz */
/* Channel number = 0 */
/* Optimization = - */
/* Sync mode = (0) No preamble/sync */
/* Format of RX/TX data = (1) Serial Synchronous mode, used for backwards compatibility */
/* CRC operation = (0) CRC disabled for TX and RX */
/* Forward Error Correction = (0) FEC disabled */
/* Length configuration = (2) Enable infinite length packets. */
/* Packetlength = 255 */
/* Preamble count = (2)  4 bytes */
/* Append status = 1 */
/* Address check = (0) No address check */
/* FIFO autoflush = 0 */
/* Device address = 0 */
/* GDO0 signal selection = (12) Serial Synchronous Data Output */
/* GDO2 signal selection = (11) Serial Clock */
/*
Test Header
FSCTRL1Frequency synthesizer control.			0x0B	0x0B
FSCTRL0Frequency synthesizer control.			0x0C	0x00
FREQ2Frequency control word, high byte.			0x0D	0x22
FREQ1Frequency control word, middle byte.			0x0E	0xB6
FREQ0Frequency control word, low byte.			0x0F	0x27
MDMCFG4Modem configuration.			0x10	0x6B
MDMCFG3Modem configuration.			0x11	0x83
MDMCFG2Modem configuration.			0x12	0x88
MDMCFG1Modem configuration.			0x13	0x23
MDMCFG0Modem configuration.			0x14	0x3B
CHANNRChannel number.			0x0A	0x00
DEVIATNModem deviation setting (when FSK modulation is enabled).			0x15	0x72
FREND1Front end RX configuration.			0x21	0xB6
FREND0Front end TX configuration.			0x22	0x15
MCSM0Main Radio Control State Machine configuration.			0x18	0x18
FOCCFGFrequency Offset Compensation Configuration.			0x19	0x1D
BSCFGBit synchronization Configuration.			0x1A	0x1C
AGCCTRL2AGC control.			0x1B	0xC7
AGCCTRL1AGC control.			0x1C	0x00
AGCCTRL0AGC control.			0x1D	0xB2
FSCAL3Frequency synthesizer calibration.			0x23	0xEA
FSCAL2Frequency synthesizer calibration.			0x24	0x2A
FSCAL1Frequency synthesizer calibration.			0x25	0x00
FSCAL0Frequency synthesizer calibration.			0x26	0x1F
FSTESTFrequency synthesizer calibration.			0x29	0x59
TEST2Various test settings.			0x2C	0x81
TEST1Various test settings.			0x2D	0x35
TEST0Various test settings.			0x2E	0x09
FIFOTHRRXFIFO and TXFIFO thresholds.			0x03	0x47
IOCFG2GDO2 output pin configuration.			0x00	0x0B
IOCFG0DGDO0 output pin configuration. 0x02	0x0C
PKTCTRL1Packet automation control.			0x07	0x04
PKTCTRL0Packet automation control.			0x08	0x12
ADDRDevice address.			0x09	0x00
PKTLENPacket length.			0x06	0xFF
Test Footer

*/



/*	-------------------------------------------
	--- CC1101 Register Initialization Data ---
	-------------------------------------------
*/
const tpHW_CC1101_RegData ppcHW_CC1101_code_RegData_init[] =
{
			/*	bRegAddrs		bRegType	bRegData
				---------		--------	--------	*/
	/* 0x00 */	{c_IOCFG2, 		cCONFIG,	0x0A},	/* GDO2 output pin config 
														0x0A: PLL Lock detector
														0x29: CHIP_RDYn (Juan's code)
													*/
#if 1 ///// TMP RMV for calibration debugging
	/* 0x01 */	{c_IOCFG1, 		cCONFIG,	0x09},	/* GDO1 output pin config,
														0x09==>Clear channel assessment 
																High when RSSI level 
																is below threshold 
																(dependent on the current 
																CCA_MODE setting)
															...pin shared with SPI MISO
																so only valid when CSn is high
																(.e. when CC1101 is NOT selected). 
													*/
#endif
	/* 0x02 */	{c_IOCFG0, 		cCONFIG,	0x06},	/* GDO0 output pin config 
					  								*/
	/* 0x03*/	{c_FIFOTHR,		cCONFIG,	0x40},	/* 	7:	reserved, write 0
														6:	ADC_RETENION: should be set to 1
															before going into SLEEP
															mode if settings with an RX filter 
															bandwidth below 325 kHz are wanted
															at time of wake-up. 
															(we are using 232 kHz)
														5..4:	CLOSE_IN_RX, per DN010, 
																0x0 ==> using 0dB attenuation
																i.e., assume NOT close range usage
																... may need to modify when testing 
																	in LAB, on test jig, etc.
	    												3..0: 	0000: threshold when 
    															TX FIFO bytes= 61 or
					    										RX FIFO bytes = 4 
					    							*/
	/* 0x04*/	{c_SYNC1,		cCONFIG,	0xAA},	/* MS byte of sync word 
													*/
	/* 0x05*/	{c_SYNC0,		cCONFIG,	/*0xA5*/0xAA},	/* LS byte of sync word 
													*/
	/* 0x06 */	{c_PKTLEN,		cCONFIG,	0x07},	/* MAX Packet length (Fixed packet 
														length mode must be set in PKTCTRL0
														and this register should be updated
														for every packet
													*/
	/* 0x07 */	{c_PKTCTRL1, 	cCONFIG,	0xA4},	/* Packet Automation Control
										  				7..5: PQT[2:0] 0x5; Preamble quality estimator threshold. 
														  	A threshold of 4·PQT for is used to gate 
														  	sync word detection ... this is compared with
															internal "bit delta counter" ... we can use this
															to reduce the number of "noise packets 
															that get through (e.g. reduce rish of
															"spontaneous flashing", etc.)
															...if preamble + sync word has 28 bits preceeding
																the phase inversion and we decide we want
																3/4 of these in order to allow packet through
																then (3/4 * 28) / 2 = 4 PQT ==> PQT ~= 5
														4: Reserved (write unused bits with 0)
														3: CRC_AUTOFLUSH, disabled (using WMS CRC)
														2: APPEND_STATUS, enabled
															 2 status bytes contain RSSI and LQI 
																appended to each packet (as well as 
																				CRC OK ... ignored)
														1..0: ADR_CHK[1:0] 0x0 ==> No address check
									   			    */
	/* 0x08*/	{c_PKTCTRL0, 	cCONFIG,	0x00},	/* Packet Automation Control
														7: reserved 
														6: WHITE_DATA; disable whitening because
																		we are using Manchester 
																		encoding															0: Whitening off
														5..4: PKT_FORMAT[1:0] 0x0 ==> Normal mode, 
																		use FIFOs for RX and TX
														3: reserved
														2: CRC_EN disabled (using WMS CRC)
														1..0: LENGTH_CONFIG[1:0] 0x0 ==> Fixed packet 
																							length mode
																	Write PKTLEN reg for every Tx
												    */
	/* 0x09 */	{c_ADDR,		cCONFIG,	0x00},	/* Device Address, DON'T CARE
														disabled by ADR_CHK in PKTCTRL1
													*/
	/* 0x0A */	{c_CHANNR,   	cCONFIG,	0x00},	/* Channel number; 0x00 ==> 902.5 MHz
														8-bit unsigned channel number, multiplied by the 
														channel spacing setting and added to base frequency. 
														...with a 26 MHz crystal the maximum channel 
															spacing is 405 kHz so we set channel spacing 
															to 250 MHz, set the number of channels to 
															102, then use channels 0, 2, 4, ... 98, 100)
   													*/
	/* 0x0B */	{c_FSCTRL1,  	cCONFIG,	0x0B},	/* Freq synthesizer control, per SRFS
													*/
	/* 0x0C */	{c_FSCTRL0,  	cCONFIG,	0x00},	/* Freq synthesizer control, per SRFS
													*/
	/* 0x0D */	{c_FREQ2,    	cCONFIG,	0x22},	/* Freq control word, high byte (902.5 MHz), per SRFS
													*/
	/* 0x0E */	{c_FREQ1,    	cCONFIG,	0xB6},	/* Freq control word, mid byte (902.5 MHz), per SRFS
													*/
	/* 0x0F */	{c_FREQ0,    	cCONFIG,	0x27},	/* Freq control word, low byte (902.5 MHz), per SRFS
													*/
	/* 0x10 */	{c_MDMCFG4,  	cCONFIG,	0x6B},	/* Modem configuration (per SRFS)
													*/
	/* 0x11 */	{c_MDMCFG3,  	cCONFIG,	0x83},	/* Modem configuration, per SRFS
													*/
	/* 0x12 */	{c_MDMCFG2,  	cCONFIG,	0x98},	/* Modem configuration, per SRFS
														GFSK: 0x98
														2-FSK: 0x88
													*/
	/* 0x13 */	{c_MDMCFG1,  	cCONFIG,	/*0x23*/0x23},	/* Modem configuration, per SRFS:0x23
														0010 0011
														7: FEC, disabled
														6..4: NUM_PREAMBLE[2:0]
																	0 = 2bytes
																	1 = 3bytes
																	2 = 4bytes
																	3 = 6bytes
																	4 = 8bytes
																	5 = 12bytes
																	6 = 16bytes
																	7 = 24bytes
														3..2: reserved
														1..0: CHANSPC_E[1:0] 2 bit exponent of channel spacing
													*/
	/* 0x14 */	{c_MDMCFG0,  	cCONFIG,	0x3B},	/* Modem configuration, per SRFS
													*/
	/* 0x15 */	{c_DEVIATN,  	cCONFIG,	0x71},	/* Modem Deviation Setting 
														(when FSK modulation is enabled), per SRFS 
														279 kHz: 0x73 (worked with both 2-FSK and GFSK)
														253 kHz: 0x72  (worked best?)
														229 kHz: 0x71 (did not work as well as 253 kHz)
													*/
	/* 0x16 */	{c_MCSM2,   	cCONFIG,	/*0x07*/0x03},	/* Main Radio Cntrl State Machine Configuration
														7..5: reserved
														4: RX_TIME_RSSI, disabled
														3: RX_TIME_QUAL=1 ==> Continue
															receive if sync word has been found, 
															or if the preamble quality is above 
															threshold (PQT)
														2..0: RX timeout is given by 
																EVENT0*C(RX_TIME, WOR_RES)*26/Xosc, 
																where C is given by the table 
																(see CC1101 DS) and Xosc oscillator 
																frequency in MHz (e.g. Xosc = 26)
													*/
	/* 0x17 */	{c_MCSM1 ,   	cCONFIG,	0x30},	/* Main Radio Cntrl State Machine Configuration
														7..6: reserved
														5..4: CCA_MODE, clear channel indicator
																		use 0x3 ==> CCA=1 unless
																		if RSSI below threshold unless 
																		currently receiving a packet
																		...CCA is given by SPI MISO
																			(see IOCFG1)
														3..2: RXOFF_MODE 0x0 ==> Next state after finishing packet 
																		reception will be IDLE (change 
																		to 0x3 to stay in Rx)
														1..0: TXOFF_MODE 0x0 ==> Next state after finishing packet 
																			transmission will be IDLE (change 
																			to 0x1 if you want next state to be
																			FSTXON (i.e. synthesizer on but not 
																				sending packet))
													 */
	/* 0x18 */	{c_MCSM0 ,   	cCONFIG,	0x08},	/* Main Radio Cntrl State Machine Configuration 
														7..6: reserved
														5..4: FS_AUTOCAL use 0x0 ==> manual calibrate only
																						via SCAL strobe
														3..2: PO_TIMEOUT use 0x2 ==> CHP_RDY (Chip Status Byte)
																						will go low approx. 
																						149 – 155 us after 
																						XOSC started
														1: PIN_CTRL_EN 0x0 ==> control of major	chip states 
																				(SLEEP, IDLE, RX, and TX)
																				using SPI bus is disabled
														0: XOSC_FORCE_ON 0x0 ==> Oscillator will not be forced 
																					to stay on during sleep
													*/
	/* 0x19 */	{c_FOCCFG,   	cCONFIG,	0x1D},	/* Frequency Offset Compensation Configuration
														7..6: reserved
														5: FOC_BS_CS_GATE 
															If set, the demodulator freezes the frequency 
															offset compensation and clock recovery feedback 
															loops until the CS signal goes high.
														4..3: FOC_PRE_K[1:0] 
															The frequency compensation loop gain to be used 
															before a sync word is detected:
																0 (00) K
																1 (01) 2K
																2 (10) 3K
																3 (11) 4K
														2: FOC_POST_K 
															The frequency compensation loop gain to be 
															used after a sync word is detected:
																0 Same as FOC_PRE_K
																1 K/2
														1..0: FOC_LIMIT[1:0] 
															The saturation point for the frequency offset 
															compensation algorithm ... Setting Saturation 
															point (max compensated offset):
																0 (00) ±0 (no frequency offset compensation)
																1 (01) ±BWCHAN/8
																2 (10) ±BWCHAN/4
																3 (11) ±BWCHAN/2
													*/
	/* 0x1A */	{c_BSCFG,    	cCONFIG,	0x1C},	/* Bit Synchronization Configuration
														7..6: BS_PRE_KI[1:0] 
																The clock recovery feedback loop integral 
																gain to be used before a sync word
																is detected (used to correct offsets 
																in data rate):
																	0 (00) KI
																	1 (01) 2KI
																	2 (10) 3KI
																	3 (11) 4KI
														5..4: BS_PRE_KP[1:0] 
																The clock recovery feedback loop proportional 
																gain to be used before a sync word is detected:
																0 (00) KP
																1 (01) 2KP
																2 (10) 3KP
																3 (11) 4KP
														3: BS_POST_KI
															The clock recovery feedback loop integral gain to 
															be used after a sync word is detected:
																0 Same as BS_PRE_KI
																1 KI /2
														2: BS_POST_KP
															The clock recovery feedback loop proportional gain 
															to be used after a sync	word is detected.
																0 Same as BS_PRE_KP
																1 KP
														1..0: BS_LIMIT[1:0]
																The saturation point for the data rate offset 
																compensation algorithm:
																	0 (00) ±0 (No data rate offset 
																				compensation performed)
																	1 (01) ±3.125 % data rate offset
																	2 (10) ±6.25 % data rate offset
																	3 (11) ±12.5 % data rate offset															
													*/
	/* 0x1B */	{c_AGCCTRL2, 	cCONFIG,	0xC7},	/* AGC control 
														7..6: MAX_DVGA_GAIN[1:0] 
															Reduces the maximum allowable DVGA gain.
																0 (00) All gain settings can be used
																1 (01) The highest gain setting can not be used
																2 (10) The 2 highest gain settings can not be used
																3 (11) The 3 highest gain settings can not be used
														5..3: MAX_LNA_GAIN[2:0] 
															Sets the maximum allowable LNA + LNA 2 gain 
															relative to the	maximum possible gain:
																0 (000) Maximum possible LNA + LNA 2 gain
																1 (001) Approx. 2.6 dB below max possible gain
																2 (010) Approx. 6.1 dB below max possible gain
																3 (011) Approx. 7.4 dB below max possible gain
																4 (100) Approx. 9.2 dB below max possible gain
																5 (101) Approx. 11.5 dB below max possible gain
																6 (110) Approx. 14.6 dB below max possible gain
																7 (111) Approx. 17.1 dB below max possible gain
														2..0: MAGN_TARGET[2:0]
															These bits set the target value for the averaged 
															amplitude from the digital channel filter (1 LSB = 0 dB).
																0 (000) 24 dB
																1 (001) 27 dB
																2 (010) 30 dB
																3 (011) 33 dB
																4 (100) 36 dB
																5 (101) 38 dB
																6 (110) 40 dB
																7 (111) 42 dB
													*/
	/* 0x1C */	{c_AGCCTRL1, 	cCONFIG,	0x00},	/* AGC control 
														7: reserved
														6: AGC_LNA_PRIORITY 
															Selects between two different strategies for LNA 
															and LNA 2 gain adjustment. 
																1 ==> the LNA gain is decreased first. 
																0 ==> the LNA 2 gain is decreased to minimum before
																		decreasing LNA gain
														5..4: CARRIER_SENSE_REL_THR[1:0]
															Sets the relative change threshold for asserting 
															carrier sense
																0 (00) Relative carrier sense threshold disabled
																1 (01) 6 dB increase in RSSI value
																2 (10) 10 dB increase in RSSI value
																3 (11) 14 dB increase in RSSI value
														3..0: CARRIER_SENSE_ABS_THR[3:0]
																Sets the absolute RSSI threshold for asserting 
																carrier sense. The 2-complement signed threshold is 
																programmed in steps of 1 dB and is relative to the 
																MAGN_TARGET setting (Equal to channel filter amplitude 
																when AGC has not decreased gain):
																	-8 (1000) Absolute carrier sense threshold disabled
																	-7 (1001) 7 dB below MAGN_TARGET setting
																	… …
																	-1 (1111) 1 dB below MAGN_TARGET setting
																	0 (0000) At MAGN_TARGET setting
																	1 (0001) 1 dB above MAGN_TARGET setting
																	… …
																	7 (0111) 7 dB above MAGN_TARGET setting
													*/
	/* 0x1D */	{c_AGCCTRL0, 	cCONFIG,	0xB2},	/* AGC control 
														7..6: HYST_LEVEL[1:0]
															Sets the level of hysteresis on the magnitude 
															deviation (internal AGC	signal that determine 
															gain changes).
																0 (00) No hysteresis, small symmetric 
																		dead zone, high gain
																1 (01) Low hysteresis, small asymmetric 
																		dead zone, medium gain
																2 (10) Medium hysteresis, medium asymmetric 
																		dead zone, medium gain
																3 (11) Large hysteresis, large asymmetric 
																		dead zone, low gain
														5..4: WAIT_TIME[1:0] 
															Sets the number of channel filter samples from 
															a gain adjustment has been made until the AGC 
															algorithm starts accumulating new samples.
																0 (00) 8
																1 (01) 16
																2 (10) 24
																3 (11) 32
														3..2: AGC_FREEZE[1:0] 
															Control when the AGC gain should be frozen.
																0 (00) Normal operation. Always adjust gain 
																		when required.
																1 (01) The gain setting is frozen when a sync 
																		word has been found.
																2 (10) Manually freeze the analogue gain 
																		setting and	continue to adjust the digital 
																		gain.
																3 (11) Manually freezes both the analogue and the 
																		digital	gain setting. Used for manually 
																		overriding the gain.
														1..0: FILTER_LENGTH[1:0] 
																Sets the averaging length for the amplitude 
																from the channel filter: 
																				samples OOK/ASK decision boundary
																				-------	-------------------------
																	0 (00): 	8 		4 dB
																	1 (01): 	16 		8 dB
																	2 (10): 	32 		12 dB
																	3 (11): 	64 		16 dB
																(Note: the above should be irrelevant for
																		WP4 since using FSK)
													*/
	/* 0x1E */ 	{c_WOREVT1,		cCONFIG,	/*0x87*/0x03},	/* High Byte of Event0 Timeout register
														(1s) 
														////////////////////////////////////////////
														////// WOREVT1, WOREVT0, WORCTRL and MCSM2
														////// still need to be determined
														////////////////////////////////////////////
													*/
	/* 0x1F */ 	{c_WOREVT0,		cCONFIG,	/*0x6B*/0x20},	/* Low Byte Event0 Timeout 
														(1s) 
														////////////////////////////////////////////
														////// WOREVT1, WOREVT0, WORCTRL and MCSM2
														////// still need to be determined
														////////////////////////////////////////////
													*/
	/* 0x20 */ 	{c_WORCTRL,		cCONFIG,	/*0xB2*/0x30},	/* Wake On Radio Control 
														WORCTRL.RC_CAL=0
														////////////////////////////////////////////
														////// WOREVT1, WOREVT0, WORCTRL and MCSM2
														////// still need to be determined
														////////////////////////////////////////////
														7: RC_PD 
															Power down signal to RC oscillator. 
															When written to 0, automatic initial
															calibration will be performed
														6..4: EVENT1[2:0] 
															Timeout setting from register block. 
															Decoded to Event 1 timeout. RC 
															oscillator clock frequency equals 
															FXOSC/750, which is 34.7 – 36 kHz,
															depending on crystal frequency. The 
															table below lists the number of clock
															periods after Event 0 before Event 1 times out.
																0 (000) 4 (0.111 – 0.115 ms)
																1 (001) 6 (0.167 – 0.173 ms)
																2 (010) 8 (0.222 – 0.230 ms)
																3 (011) 12 (0.333 – 0.346 ms)
																4 (100) 16 (0.444 – 0.462 ms)
																5 (101) 24 (0.667 – 0.692 ms)
																6 (110) 32 (0.889 – 0.923 ms)
																7 (111) 48 (1.333 – 1.385 ms)
														3: RC_CAL 
															Enables (1) or disables (0) 
															the RC oscillator calibration.
														2: reserved
														1..0: WOR_RES 
															Controls the Event 0 resolution as well as 
															maximum timeout of the WOR module and 
															maximum timeout under normal RX operation:
																Setting 	Resolution (1 LSB) Max timeout
																-------		------------------------------
																0 (00) 		1 period (28 – 29 ìs) 1.8 – 1.9 seconds
																1 (01) 		25 periods (0.89 – 0.92 ms) 58 – 61 seconds
																2 (10) 		210 periods (28 – 30 ms) 31 – 32 minutes
																3 (11) 		215 periods (0.91 – 0.94 s) 16.5 – 17.2 hours
																		Note that WOR_RES should be 0 or 1 when using 
																WOR because	WOR_RES > 1 will give a very low duty 
																cycle. In normal RX operation all settings of WOR_RES 
																can be used.
													*/
	/* 0x21 */	{c_FREND1,   	cCONFIG,	0xB6},	/* Front end RX configuration 
														7..6: LNA_CURRENT[1:0]
															Adjusts front-end 
															LNA PTAT current output
														5..4: LNA2MIX_CURRENT[1:0] 
																Adjusts front-end PTAT outputs
														3..2: LODIV_BUF_CURRENT_RX[1:0] 
															Adjusts current in RX 
															LO buffer (LO input to mixer)
														1..0: MIX_CURRENT[1:0] 
															R/W Adjusts current in mixer	
													*/
	#if cBLD_HW_CC1101_PA_TABLE_RAMPING	== 1
	/* 0x22 */	{c_FREND0,   	cCONFIG,	0x17},	
	#else
	/* 0x22 */	{c_FREND0,   	cCONFIG,	0x10},
	#endif
													/* Front End TX configuration 
															7..6: reserved 
														5..4: LODIV_BUF_CURRENT_TX[1:0] 
																Adjusts current TX LO buffer 
																(input to PA). 
																...using value from SRFS
														3: reserved
														2..0: PA_POWER[2:0] 
															index to the PATABLE
													*/
	/* 0x23 */	{c_FSCAL3,   	cCONFIG,	0xEA},	/* Frequency Synthesizer Calibration
														7..6: FSCAL3[7:6]  
																the value to write in this 
																field before calibration 
																is given by SRFS
														5..4: CHP_CURR_CAL_EN[1:0] 
																Disable charge pump calibration 
																stage when 0.		
														3..0: FSCAL3[3:0]
																Digital bit vector defining 
																the charge pump output current, 
																on an exponential scale: 
																I_OUT = I0·2FSCAL3[3:0]/4
																...read back data and save for 
																	fast calibration
													*/
	/* 0x24 */	{c_FSCAL2,   	cCONFIG,	0x2A},	/* Frequency Synthesizer Calibration
														7..6: reserved
														5: 		VCO_CORE_H_EN 
																	Choose high (1) / low (0) VCO
														4..0: FSCAL2[4:0] 10 
																Calibration result register. 
																VCO current calibration result 
																and override value.
																...read back data and save for 
																	fast calibration
													*/
	/* 0x25 */	{c_FSCAL1,   	cCONFIG,	0x00},	/* Frequency Synthesizer Calibration
														7..6: reserved
														5..0: FSCAL1[5:0] 
																Calibration result register. 
																Capacitor array setting
																for VCO coarse tuning.
																...read back data and save for 
																	fast calibration
													*/
	/* 0x26 */	{c_FSCAL0,   	cCONFIG,	0x1F},	/* Frequency Synthesizer Calibration 
														7: reserved
														6..0: FSCAL0[6:0] 
															 ... use data per SRFS
															 ... reading back data for 
															 	 fast calibration
															 	 __IS NOT__ required
													*/
	#if 0
	/* 0x27 */	{c_RCCTRL1,   	cBLOCK,		0x00},	/* RC Oscillator Configuration
														7: reserved
														6..0: RC oscillator configuration
																... use data read from 
																	RCCTRL1_STATUS to init
																	this regsiter if
																	WORCTRL.RC_CAL=0
													*/
	/* 0x28 */	{c_RCCTRL0,   	cBLOCK,		0x00},	/* RC Oscillator Configuration
														7: reserved
														6..0: RC oscillator configuration
																... use data read from 
																	RCCTRL0_STATUS to init
																	this regsiter if
																	WORCTRL.RC_CAL=0
													*/
	#endif
	/* 	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 	 	 $CAUTION: Data for (all) registers that follow is lost in SLEEP state	
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/* 0x29 */	{c_FSTEST,   	cCONFIG,  	0x59},	/* FSTEST – Frequency Synthesizer 
																Calibration Control 
																For test only. 
																__DO NOT WRITE__
																 to this register. 
																 (2009Jun12, changing to
																	writing for init only,
																	because that is what all
																	the Chipcon examples do.
													*/
 	/* ~~~~ 	$CAUTION: see above		~~~~~ */
	/* 0x2A */	{c_PTEST,    	cCONFIG,	0x7F},	/* Production Test
														Write 0xBF to make on-chip 
														temperature sensor
														available in the IDLE state 
														___BUT___ the default 0x7F 
														value should then be written 
														back __BEFORE__ leaving the 
														IDLE state
													 */
	#if 0
	/* 0x2B */	{c_AGCTEST,		cBLOCK,		0x3F},	/* AGCTEST – AGC Test
																For test only. 
																__DO NOT WRITE__
																 to this register. 
													*/
	#endif
	/* 0x2C */	{c_TEST2,		cCONFIG,	0x81},	/* TEST2 – Various Test Settings
																-- using 0x81 per SRFS.
																This register will be forced 
																to 0x88 or 0x81 when it wakes
																up from SLEEP mode, depending 
																on the configuration of 
																FIFOTHR.ADC_RETENTION. 
													*/
	/* 0x2D */	{c_TEST1,		cCONFIG,	0x35},	/* TEST1 – Various Test Settings
																-- using 0x35 per SRFS.
																This register will be forced 
																to 0x31 or 0x35 when it wakes
																up from SLEEP mode, depending 
																on the configuration of 
																FIFOTHR.ADC_RETENTION. 
													*/
	/* 0x2E */	{c_TEST0,    	cCONFIG,	0x09},	/* TEST0 – Various Test Settings
																			  0000 1001
														7..2: TEST0[7:2] ...using 0x2 per SRFMS
														1: VCO_SEL_CAL_EN ...using 0x0 
																			0x1 enables VCO selection 
																			calibration stage 
														0: TEST0[0] 	... using 0x1 per SRFS
													*/
	/* 0x0 */	{c_NULL,		cBLOCK,		0x00}	/* DUMMY, NULL terminates lookup TBL 
													*/
};

/*
	Wake On Radio and Rx Timeout 
	
		MSCM2, WOREVT1, WOREVT0 and WORCTRL – Wake On Radio Control Bit

	The RX timeout in us is given by EVENT0*C(RX_TIME, WOR_RES)*26/Xosc, 
	where C is set by bits MCSM2[2:0] and given by the table below and 
	Xosc is the crystal oscillator frequency in MHz.

	MCSM2[2:0] 	WOR_RES = 0	WOR_RES = 1 	WOR_RES = 2 	WOR_RES = 3
	0 (000) 	3.6058 		18.0288 		32.4519 		46.8750
	1 (001) 	1.8029 		9.0144 			16.2260 		23.4375
	2 (010) 	0.9014 		4.5072 			8.1130 			11.7188
	3 (011) 	0.4507 		2.2536 			4.0565 			5.8594
	4 (100) 	0.2254 		1.1268 			2.0282 			2.9297
	5 (101) 	0.1127 		0.5634 			1.0141 			1.4648
	6 (110) 	0.0563 		0.2817 			0.5071 			0.7324
	7 (111) 	  ~~~Until end of packet~~~
*/
#if 0
const tpHW_Code_CC1101_RetgData_RxTimeout ppcHW_Code_CC1101_RegData_RxTimeout[] =
{
};
#endif


#if 0
const u8 pbcHW_Code_CC1101_RegData_InitData_NUM_ENTRIES[1] =
{
	mGLB_Array_NUM_ENTRIES(ppcHW_Code_CC1101_RegData_InitData)
};
#endif


#if 0 /* this was the original intent, based on the CC1101 F/W 
			but was superseded by the use of CC1101 "CHANNEL" */
const tpHW_Code_CC1101_RegData_FreqCntrl ppcHW_Code_CC1101_RegData_FreqCntrl[cBLD_RFC_PROT_NUM_FREQS] =
{
	/*	bFREQ2_24BitWord_H	bFREQ1_24BitWord_M	bFREQ2_24BitWord_L
		------------------	------------------	------------------ */
		{0x22,				0xB6,				0x27},	/* 902.5 MHz */
		{0x22,				0xB6,				0x27},	/* 903 MHz */
		{0x22,				0xB6,				0x27},	/* 903.5 MHz */
		{0x22,				0xB6,				0x27},	/* 904 MHz */
		{0x22,				0xB6,				0x27},	/* 904.5 MHz */
		{0x22,				0xB6,				0x27},	/* 905 MHz */
		{0x22,				0xB6,				0x27},	/* 906 MHz */
		{0x22,				0xB6,				0x27},	/* 907 MHz */
		{0x22,				0xB6,				0x27},	/* 907.5 MHz */
		{0x22,				0xB6,				0x27},	/* 908 MHz */
		{0x22,				0xB6,				0x27},	/* 909.5 MHz */
		{0x22,				0xB6,				0x27},	/* 910 MHz */
		{0x22,				0xB6,				0x27},	/* 910.5 MHz */
		{0x22,				0xB6,				0x27},	/* 911 MHz */
		{0x22,				0xB6,				0x27},	/* 911.5 MHz */
		{0x22,				0xB6,				0x27},	/* 912 MHz */
		{0x22,				0xB6,				0x27},	/* 912.5 MHz */
		{0x22,				0xB6,				0x27},	/* 913 MHz */
		{0x22,				0xB6,				0x27},	/* 913.5 MHz */
		{0x22,				0xB6,				0x27},	/* 914 MHz */
		{0x22,				0xB6,				0x27},	/* 914.5 MHz */
		{0x22,				0xB6,				0x27},	/* 915 MHz */
		{0x22,				0xB6,				0x27},	/* 915.5 MHz */
		{0x22,				0xB6,				0x27},	/* 916 MHz */
		{0x22,				0xB6,				0x27},	/* 916.5 MHz */
		{0x22,				0xB6,				0x27},	/* 917 MHz */
		{0x22,				0xB6,				0x27},	/* 917.5 MHz */
		{0x22,				0xB6,				0x27},	/* 918 MHz */
		{0x22,				0xB6,				0x27},	/* 918.5 MHz */
		{0x22,				0xB6,				0x27},	/* 919 MHz */
		{0x22,				0xB6,				0x27},	/* 919.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
		{0x22,				0xB6,				0x27},	/* 920.5 MHz */
};
#endif

/*	--------------------------------
		--- GPIO Initialization Data ---
		--------------------------------
*/
#if 0
const tpHW_Code_GPIO_PORTS_InitData	ppcHW_Code_GPIO_PORTS_InitData[] =
{
	/*	ppGPIOx						ppGPIO_Init 
			-------						-----------	*/
};
#else
#if 0
const tpHW_Code_GPIO_PORTS_InitData	ppcHW_Code_GPIO_PORTS_InitData[] =
{
					/*	ppGPIOx						wGPIO_Pin				wGPIO_Speed			wGPIO_Mode
	   					-------						---------				-----------			----------	*/
	/* this: */
	/* that: */

/*
		USE THIS ORDER:
  RCC_Configuration(); 
  
  Set up Configuration for GPIO
  GPIO_Configuration();
  
  Set up Configuration for USART2 and USART3
  USART_Configuration(); 
  
	#ifdef mCC1101_ENABLE  
  Set up Configguration for SPI1
  SPI_Configuration();  
	#endif
  
  NVIC configuration
  NVIC_Configuration();
  
  Set up Configuration for EXTI4 and EXTI5
  EXTINT_Configuration();
  
  //Set up current timers ... don't do much at the moment, tiggered by the button 
  //interupt to run and will be disabled upon the appropriate timer interrupt 
  //and spit an indication out usart3
  //TIM1_Configuration( 1000 );
  //TIM2_Configuration( 25 );
	#ifdef mSYS_TIM_ENABLE
  SysTick_Configuration( mTIMx_SYS_TICK_1s() );
	#endif
	*/

};
#endif
#endif

/*	-------------------------------------------------
	--- CC1101 Power Amplifier Ramping Table Data ---
	-------------------------------------------------

	Arrange this table in accordance with
	cHW_CC1101_PATABLE_Profile_DEFAULT_INDEX

	DN013 was referenced when creating the data for this table
	(3.4 CC1101 @ 915 MHz). The method for choosing the PATABLE
	values considered that it was best to choose to make the 
	largest increases in current when the gain is still low (that 
	way if PLL goes out of lock, the spurs would have lower power 
	and therefore be less likely to jeopardize FCC compliance)

	$CAUTION: Register settings from 0x61 to 0x6F 
				are not recommended in the CC1101 PATABLE
*/
const tpHW_CC1101_PATABLE_Profile ppcHW_CC1101_code_PATABLE_Profile[] =
{
	////////// THE VALUES BELOW were in Juan's original CC1101 code
	{0x00, 0x03, 0x0E, 0x25, 0x66, 0x51, 0x50, 0x8E}, /* -0.6dBm */

	#if cBLD_HW_CC1101_PA_TABLE_RAMPING	== 1
	/* 	Choose this set for use with the Tandem Kit where we don't 
		have an external PA
	*/
//	{0x00, 0x0D, 0x1C, 0x25, 0x36, 0x57, 0x8D, 0x84}, /* +3.9dBm */
//	{0x00, 0x03, 0x0F, 0x27, 0x51, 0x88, 0x83, 0x81},
	{0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84}, /* +3.9dBm */

	#else
	/* 	Choose this set for use with the Tandem Kit where we don't 
		have an external PA
	*/
	{0x3D, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D}, 
//	{0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84}, /* +3.9dBm */
//	{0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2}, 
//	{0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0}, 
	#endif

	/////////// UNTESTED???????
	/* 	Choose this set for use with a 30dB gain PA (gives 1/2 watt output)

		...Based on DN013 these values should provide a smooth transition
		as their current consumptions are lower than other choices
		which would provide similar output gains
		...note that the output gains and register values are
			not linear

		0x63 (-3dBm) was the best setting for index=7 based on
		the gain table but is not used because the cautionary 
		note in DN013 disqualifies it.
	*/
	{0x00, 0x02, 0x0D, 0x1C, 0x33, 0x27, 0x8F, 0x53} /* -2.9dBm */
};

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

#undef cMEM_USERCLASS_ID_RFC_CODE_c