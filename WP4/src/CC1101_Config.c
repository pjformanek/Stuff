/*------------------------------------------------------------------------------
  	$File:		CC1101_Config.c
  	$Module:  	Configurations for CC1101 Transciver
  	$Prefix:  	CC
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Dec 22, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_CC_CC1101_CONFIG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

#include "GLB.h"
#include "stm32f10x_lib.h"
#include "MEM.h"
#include "Includes.h"

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
char paTable[] = { cCC1101_PA_TABLE_VAL };
char paTableLen = 1;

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
	$Function: TI_CC_SPIWriteReg
	$Description: Writes an specific CC1101 register

	$Inputs: char addr - address of the register
                 char value - value to be written to the register
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TI_CC_SPIWriteReg(char addr, char value)
{
    /* CC1101 chip select ... turn CSn pin on*/
    GPIO_ClearBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
    /* Wait for CCxxxx ready */
    while( ( GPIO_ReadInputDataBit( cGPIO_SPI1_GPIOx, cGPIO_SPI1_MISO_PIN ) ) );
    /* Clear flag */
    //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
    /* Send SPI1 data */
    SPI_I2S_SendData(SPI1, addr);
    /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    /* Clear flag */
    //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
    /* Send SPI1 data */
    SPI_I2S_SendData(SPI1, value);
    /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    /* CC1101 chip select ... turn CSn pin off */
    GPIO_SetBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);


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


/*------------------------------------------------------------------------------
	$Function: TI_CC_Wait
	$Description: Simple Delay Function for TI_CC functions

	$Inputs: unsigned int cycles - number cycles to burn
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TI_CC_Wait(unsigned int cycles)
{
  while(cycles>15)                          // 15 cycles consumed by overhead
    cycles = cycles - 6;                    // 6 cycles consumed each iteration
}



/*------------------------------------------------------------------------------
	$Function: TI_CC_PowerupResetCCxxxx
	$Description: Function that powers up the CC1101 properly whenever there is
                      a reset of power up

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TI_CC_PowerupResetCCxxxx(void)
{

  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
  TI_CC_Wait(30);
  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
  TI_CC_Wait(30);
  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
  TI_CC_Wait(45);

  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( cGPIO_SPI1_GPIOx, cGPIO_SPI1_MISO_PIN ) ) );
  /* Send SPI1 Strobe */
  SPI_I2S_SendData(SPI1, HW_CC1101_ADDRS_STROBE_SRES);
  /* Clear flag */
    //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);



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




/*------------------------------------------------------------------------------
	$Function: writeRFSettings
	$Description:

	$Inputs: Writes all the configuration to the CC1101 registers, in the
 		 near future we will need to make this function take some parameters
 		 such as frequency and power making sure we can change things on the
 		 fly
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
// 915 MHz
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
// RF Frequency = 915.000000 MHz
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
#if 0

  TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG2,   0x29); // GDO2 output pin config.  used to be 0x0B
  TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG0,   0x06); // GDO0 output pin config.

    // Write register settings
    TI_CC_SPIWriteReg(TI_CCxxx0_FIFOTHR,  0x07); // GDO2 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_SYNC1,    0xD3); // GDO2 output pin config. // for AB 0xA5
    TI_CC_SPIWriteReg(TI_CCxxx0_SYNC0,    0x91); // GDO2 output pin config.

    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG2,   0x29); // GDO2 output pin config.  used to be 0x0B
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG0,   0x06); // GDO0 output pin config.

    TI_CC_SPIWriteReg(TI_CCxxx0_PKTLEN,   0x08); // Packet length. /// was working with 0x03
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
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG2,  0x83); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG1,  0x22); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG0,  0xF8); // Modem configuration.

    TI_CC_SPIWriteReg(TI_CCxxx0_DEVIATN,  0x00); // Modem dev (when FSK mod en)

    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM1 ,   0x0F); //MainRadio Cntrl State Machine   // was working with 0x00
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

    TI_CC_SPIWriteReg(TI_CCxxx0_WOREVT1,  0x03); // High byte Event 0 timeout
    TI_CC_SPIWriteReg(TI_CCxxx0_WOREVT0,  0x20); // Low byte Event 0 timeout
    TI_CC_SPIWriteReg(TI_CCxxx0_WORCTRL,  0x38); // Wake On Radio control

    TI_CC_SPIWriteReg(TI_CCxxx0_RCCTRL1,  0x41); // RC oscillator configuration
    TI_CC_SPIWriteReg(TI_CCxxx0_RCCTRL0,  0x00); // RC oscillator configuration
#endif

#if 1
      // Write register settings

    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG2,   0x29); // GDO2 output pin config.  used to be 0x0B
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG0,   0x2E); // GDO0 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG0,   0x06); // GDO0 output pin config.

    TI_CC_SPIWriteReg(TI_CCxxx0_FIFOTHR, 0x07); // GDO2 output pin config.

    TI_CC_SPIWriteReg(TI_CCxxx0_SYNC1,   0xD3); // GDO2 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_SYNC0,   0x91); // GDO2 output pin config.

    TI_CC_SPIWriteReg(TI_CCxxx0_PKTLEN,   0x0A); // Packet length. /// was working with 0x03

    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL1, 0x00); // Packet automation control.
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL0, 0x00); // Packet automation control.

    TI_CC_SPIWriteReg(TI_CCxxx0_ADDR,     0x00); // Device address.
    TI_CC_SPIWriteReg(TI_CCxxx0_CHANNR,   0x00); // Channel number.   reg # 0x0A

    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL1,  0x0F); // Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL0,  0x00); // Freq synthesizer control.

    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ2,    0x23); // Freq control word, high byte
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ1,    0x31); // Freq control word, mid byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ0,    0x3B); // Freq control word, low byte.

    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG4,  0x2D); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG3,  0x3B); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG2,  0x13); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG1,  0x22); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG0,  0xF8); // Modem configuration.

    TI_CC_SPIWriteReg(TI_CCxxx0_DEVIATN,  0x47); // Modem dev (when FSK mod en)

    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM2 ,   0x07); //MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM1 ,   0x0E); //MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM0 ,   0x18); //MainRadio Cntrl State Machine

    TI_CC_SPIWriteReg(TI_CCxxx0_FOCCFG,   0x1D); // Freq Offset Compens. Config
    TI_CC_SPIWriteReg(TI_CCxxx0_BSCFG,    0x1C); //  Bit synchronization config.

    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL2, 0xC7); // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL1, 0x00); // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL0, 0xB2); // AGC control.

    TI_CC_SPIWriteReg(TI_CCxxx0_WOREVT1,  0x03); // High byte Event 0 timeout
    TI_CC_SPIWriteReg(TI_CCxxx0_WOREVT0,  0x20); // Low byte Event 0 timeout

    TI_CC_SPIWriteReg(TI_CCxxx0_WORCTRL,  0x38); // Wake On Radio control

    TI_CC_SPIWriteReg(TI_CCxxx0_FREND1,   0xB6); // Front end RX configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND0,   0x10); // Front end RX configuration.

    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL3,   0xEB); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL2,   0x2B); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL1,   0x2E); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL0,   0x11); // Frequency synthesizer cal.


    TI_CC_SPIWriteReg(TI_CCxxx0_RCCTRL1,  0x41); // RC oscillator configuration
    TI_CC_SPIWriteReg(TI_CCxxx0_RCCTRL0,  0x00); // RC oscillator configuration

    TI_CC_SPIWriteReg(TI_CCxxx0_FSTEST,   0x59); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_PTEST,   0x7F); // Frequency synthesizer cal.

    TI_CC_SPIWriteReg(TI_CCxxx0_AGCTEST,   0x3F); // Frequency synthesizer cal.

    TI_CC_SPIWriteReg(TI_CCxxx0_TEST2,    0x88); // Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST1,    0x31); // Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST0,    0x0B); // Various test settings.
#endif



    /* Write PATABLE */	
    TI_CC_SPIWriteBurstReg( TI_CCxxx0_PATABLE, paTable, paTableLen );
}


/*------------------------------------------------------------------------------
	$Function: TI_CC_SPIWriteBurstReg
	$Description: Writes multi bytes to a register - used for fifos mostly

	$Inputs: char addr - address of the reigster
                 char *buffer - buffer with the data to be written
                 char count -  number of bytes to be written
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TI_CC_SPIWriteBurstReg( u8 bAddr, u8 * pbBuf, u8 bNumBytes )
{
    unsigned int i;

    /* CC1101 chip select ... turn CSn pin on*/
    GPIO_ClearBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
    /* Wait for CCxxxx ready */
    while( ( GPIO_ReadInputDataBit( cGPIO_SPI1_GPIOx, cGPIO_SPI1_MISO_PIN ) ) );
    /* Clear flag */
    //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
    /* Send SPI1 address */
    SPI_I2S_SendData(SPI1, bAddr | TI_CCxxx0_WRITE_BURST );
    /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    for (i = 0; i < bNumBytes; i++)
    {
      /* Clear flag */
      //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
      /* Send SPI1 address */
      SPI_I2S_SendData(SPI1, pbBuf[i]);
      /* Wait for SPI1 Tx buffer empty */
      while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    }
    /* CC1101 chip select ... turn CSn pin off */
    GPIO_SetBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);


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


/*------------------------------------------------------------------------------
	$Function: TI_CC_SPIStrobe
	$Description: Sends command strobes to the CC1101

	$Inputs: char strobe - byte command strobe
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TI_CC_SPIStrobe(char strobe)
{
  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( cGPIO_SPI1_GPIOx, cGPIO_SPI1_MISO_PIN ) ) );
  /* Clear flag */
   //SPI_I2S_ClearFlag( SPI1, SPI_I2S_FLAG_TXE );
  /* Send SPI1 address */
  SPI_I2S_SendData(SPI1, strobe);
  /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* CC1101 chip select ... turn CSn pin off */
    GPIO_SetBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);


  /*UC1IFG &= ~UCB1RXIFG;                       // Clear flag
  TI_CC_CSn_PxOUT &= ~TI_CC_CSn_PIN;        // /CS enable
  while (TI_CC_SPI_USCIB1_PxIN&TI_CC_SPI_USCIB1_SOMI);// Wait for CCxxxx ready
  UCB1TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (!(UC1IFG&UCB1RXIFG));                // Wait for end of addr TX
  TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;         // /CS disable*/
}


/*------------------------------------------------------------------------------
	$Function: RFSendPacket
	$Description: Function to send a RF packet( writes to CC1101 fifo )

	$Inputs: char *txBuffer - buffer that hold the packet to be sent
                 char size - number of bytes to be sent
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void RFSendPacket( char *txBuffer, char size )
{	
        //__disable_interrupt();
#if 1
        bRF_PROT_IntRxGetFlag = 0;

#if 0
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SIDLE);
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFRX);
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFTX);
#endif
        TI_CC_SPIWriteBurstReg( TI_CCxxx0_TXFIFO, txBuffer, size );

        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_STX);




        while( bRF_PROT_IntRxGetFlag != 2 );

        #ifdef mDEBUG_MODE
        Debug_Message("Sending ....\r\n");
        #endif

#if 0
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SIDLE);
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFRX);
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFTX);

         TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SRX);
#endif

#endif

#if 0
        TI_CC_SPIStrobe(TI_CCxxx0_SIDLE);
        TI_CC_SPIStrobe(TI_CCxxx0_SFRX);
        TI_CC_SPIStrobe(TI_CCxxx0_SFTX);

        TI_CC_SPIWriteBurstReg( TI_CCxxx0_TXFIFO, txBuffer, size );
        TI_CC_SPIStrobe(TI_CCxxx0_STX);



        while( !( GPIO_ReadInputDataBit( cGPIO_SPI1_GD0_GPIOx, cGPIO_SPI1_GD0_PIN  ) ) );
        //while (!(TI_CC_GDO0_PxIN&TI_CC_GDO0_PIN));
                                                // Wait GDO0 to go hi -> sync TX'ed

        while( ( GPIO_ReadInputDataBit( cGPIO_SPI1_GD0_GPIOx, cGPIO_SPI1_GD0_PIN  ) ) );
        //while (TI_CC_GDO0_PxIN&TI_CC_GDO0_PIN);
                                              // Wait GDO0 to clear -> end of pkt
#endif

}


/*------------------------------------------------------------------------------
	$Function: RFReceivePacket
	$Description: Function to be receive a packet ( Reads CC1101 fifo )

	$Inputs: u8 *pbRxBuffer - Buffer where data will be stored
                 u8 *bLength - lenght expected to come in
                 u16 bTimeOutms - time out that will be allowed for the receive function to ge tthe message
	$Outputs: CRC_OK bit or 0 if error
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 RFReceivePacket( u8 *pbRxBuffer, u8 bLength, u16 bTimeOutms )   // juan clean up
{
  u8 bTimeOutFlag = 0;
  bRF_PROT_IntRxGetFlag = 2;

    //TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SIDLE);
    //TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFRX);
    //TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFTX);
    //TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SWOR);

    TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SRX);


    if( bTimeOutms == 0 )
    {
      printf("No time out\n");
      printf( "num of bytes = %d\n", TI_CC_SPIReadStatus(TI_CCxxx0_RXBYTES) );
      //USART_SendData(USART3, TI_CC_SPIReadStatus(TI_CCxxx0_RXBYTES) );
      //UART3_WAIT_AND_SEND( TI_CC_SPIReadReg(TI_CCxxx0_RXFIFO) );
      //Delay( 0xFFF );


      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, (char*)pbRxBuffer, 64); // Pull data

      printf("buffer  = %s\n", pbRxBuffer );

      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, (char*)pbRxBuffer, 64); // Pull data

      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, (char*)pbRxBuffer, 64); // Pull data


      TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SIDLE);

      TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFRX);
      TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFTX);


    }
    else
    {
      TIM1_Configuration( bTimeOutms );
      TIM_Cmd(TIM1, ENABLE);
      //     while( !( GPIO_ReadInputDataBit( mHW_SPI1_GD0_GPIOx(), mHW_SPI1_GD0_PIN() ) ) )
      while( bRF_PROT_IntRxGetFlag != 1 )
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
      //TIM_Cmd(TIM1, DISABLE); // THIS WAS HERE INSTEAD OF UP THERE

      //    while( ( GPIO_ReadInputDataBit( mHW_SPI1_GD0_GPIOx(), mHW_SPI1_GD0_PIN() ) ) );

      if( bTimeOutFlag )
      {
         return 0;
      }
      else
      {
        printf("\n");
        bRF_PROT_IntRxGetFlag = 2;
        TI_CC_SPIReadStatus(TI_CCxxx0_RXBYTES);
        USART_SendData(USART3, TI_CC_SPIReadStatus(TI_CCxxx0_RXBYTES) );
        //UART3_WAIT_AND_SEND( TI_CC_SPIReadReg(TI_CCxxx0_RXFIFO) );
        //Delay( 0xFFF );
        TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, (char*)pbRxBuffer, 64); // Pull data

        TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, (char*)pbRxBuffer, 64); // Pull data

        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SIDLE);
        TI_CC_SPIStrobe(HW_CC1101_ADDRS_STROBE_SFRX);


      }
      bRF_PROT_IntRxGetFlag = 2;
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





/*------------------------------------------------------------------------------
	$Function: TI_CC_SPIReadReg
	$Description: Reads a byte from specific register

	$Inputs: char addr - address of the register
	$Outputs: char x - value in register
	$Assumptions:
	$WARNINGS:
	$End
*/
char TI_CC_SPIReadReg(char addr)
{
	#define cBIG_DELAY	(1000000)
  char x;
	u32 lwDelay;

  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);

//  for( lwDelay = cBIG_DELAY; lwDelay; lwDelay-- );

  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( cGPIO_SPI1_GPIOx, cGPIO_SPI1_MISO_PIN ) ) );

//  for( lwDelay = cBIG_DELAY; lwDelay; lwDelay-- );

  /* Send SPI1 data */
  SPI_I2S_SendData(SPI1, addr | TI_CCxxx0_READ_SINGLE);

//  for( lwDelay = cBIG_DELAY; lwDelay; lwDelay-- );

  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

//  for( lwDelay = cBIG_DELAY; lwDelay; lwDelay-- );

  /* Send SPI1 data */
  SPI_I2S_SendData(SPI1, 0);

//  for( lwDelay = cBIG_DELAY; lwDelay; lwDelay-- );

  /* Wait for SPI1 Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

//  for( lwDelay = cBIG_DELAY; lwDelay; lwDelay-- );

  /* Read Data */
  x = SPI_I2S_ReceiveData( SPI1 );

//  for( lwDelay = cBIG_DELAY; lwDelay; lwDelay-- );

  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);


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


/*------------------------------------------------------------------------------
	$Function: TI_CC_SPIReadBurstReg
	$Description: Reads multi bytes from register( mostly used to read a fifo )

	$Inputs: char addr - address of register
                 char *buffer - buffer where data will be stored
                 char count - number of bytes to be read
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void TI_CC_SPIReadBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( cGPIO_SPI1_GPIOx, cGPIO_SPI1_MISO_PIN ) ) );
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
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    buffer[i] = SPI_I2S_ReceiveData( SPI1 );
    /* Wait for SPI1 Rx buffer empty */
    //while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    //Delay(0xFFF);
  }
  buffer[count - 1] = SPI_I2S_ReceiveData( SPI1 );
  /* CC1101 chip select ... turn CSn pin off */
  GPIO_SetBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);

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


/*------------------------------------------------------------------------------
	$Function: TI_CC_SPIReadStatus
	$Description: Reads a status byte

	$Inputs: char addr - address of register
	$Outputs: char x - status byte  read
	$Assumptions:
	$WARNINGS:
	$End
*/
// For status/strobe addresses, the BURST bit selects between status registers
// and command strobes.
char TI_CC_SPIReadStatus(char addr)
{
  char x;

  /* CC1101 chip select ... turn CSn pin on*/
  GPIO_ClearBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
  /* Wait for CCxxxx ready */
  while( ( GPIO_ReadInputDataBit( cGPIO_SPI1_GPIOx, cGPIO_SPI1_MISO_PIN ) ) );
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
  GPIO_SetBits(cGPIO_SPI1_CSn_GPIOx, cGPIO_SPI1_CSn_PIN);
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

#undef cMEM_USERCLASS_ID_CC_CC1101_CONFIG_c


