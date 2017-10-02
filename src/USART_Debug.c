/*------------------------------------------------------------------------------
  	$File:		USART_Debug.c
  	$Module:  	Debug functions use for debugging purposes
  	$Prefix:  	USART
  	$Language:	ANSI C

  	$Description:
		
  	$Notes:

  	$Author:	Jramirez, Dec 23, 2008
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_USART_DEBUG_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "MEM.h"
#include "USART_Config.h"

#include "USART_Debug.h"


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


u8 bBatteryState = 4;


//GLB


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
	$Function: Debug_Message
	$Description: Takes a string input and outputs it to the serial port usart3

	$Inputs: u8 * msg - pointer to message string containing ASCII message
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/

void Debug_Message( u8 * msg )
{
#if 1
	u8 i = 0;
	while( msg[i] )
	{
	  UART3_WAIT_AND_SEND( msg[i] );
          i++;
	}
#endif
}


/*------------------------------------------------------------------------------
	$Function: Receive_Message
	$Description: Takes a string input and outputs it to the serial port usart3

	$Inputs: u8 * msg - pointer to message string containing ASCII message
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void Receive_Message( u8 * msg )
{
	//u8 i = 0;


//	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){ }
//        USART_SendData(USART3, msg[i]);
//	if( msg[i] == mUART_CONFIG_START_CHAR() )
//    {
//		i = 0x01;
//		while( msg[i] != mUART_CONFIG_END_CHAR() )
//		{
//			UART1_WAIT_AND_RECEIVE( msg[i] );
//			i++;
//		}
//		msg[i] = mUART_CONFIG_END_CHAR(); // make sure that the last char is the  " ] "
//		
//	}
	

}


//----------------------------------------------------------------------------
//  void Convert_HEX(...)
//
//  Description:
//   	performs the necessesary conversions between ASCCI to HEX values, if this string
//		does not end in 0x5D or " ] " then the function will keep runing forever
//		the function is only meant to work for converting configuration strings into hex values
//		that the firmware can use.
//  Arguments:
//      u8 * str
//			a pointer to an ASCII string with an " ]" or 0x5D as ending char
//
//  Return value:
//      void
//----------------------------------------------------------------------------
/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void Convert_HEX( u8 * str )
{
	//u8 i = 0;
	//u8 j = 0;
		
//	if( str[i] ==  mUART_CONFIG_START_CHAR() )
//	{
//		UART1_Config_Data[j] = str[i];
//		i = j = 0x01;
//		while( str[i] != mUART_CONFIG_END_CHAR() )
//		{
//			if( str[i]>=0x30 && str[i]<=0x39 )   { str[i] = ( ( str[i] - 0x30 ) << 4 ); }
//			if( str[i]>=0x41 && str[i]<=0x46 )   { str[i] = ( ( str[i] - 0x37 ) << 4 ); }
//			if( str[i+1]>=0x30 && str[i+1]<=0x39 )   { str[i+1] = ( str[i+1] - 0x30 ); }
//			if( str[i+1]>=0x41 && str[i+1]<=0x46 )   { str[i+1] = ( str[i+1] - 0x37 ); }
//			UART1_Config_Data[j] = ( str[i] + str[i+1] );
//			j++;
//			i = i + 2;	
//		}
//		UART1_Config_Data[j] = str[i];
//	}
}




//----------------------------------------------------------------------------	   /////// need to review this funciton to not use u8 length
//  void Convert_ASCII(...)
//
//  Description:
//      It uses the built-in
//	    #define UART3_WAIT_AND_SEND(x) to step through each byte on the string
//		and send it to the UART1
//
//  Arguments:
//      BYTE * msg
//			a pointer to "code unsigned char" string.
//
//  Return value:
//      void
//----------------------------------------------------------------------------
/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void Convert_ASCII( u8 * str, u8 SizeOfString )
{
	u8 i = 0;
	u8 str_h, str_l;
	while( i < SizeOfString )
	{
		str_h = ( str[i]&0xF0 ) >> 4;
		str_l = ( str[i]&0x0F );

		if( str_h > 0x00 && str_h <= 9 )   { str_h = str_h + 0x30; }

		if( str_h >= 0x0A && str_h <= 0x0F )   { str_h = str_h + 0x37; }

		if( str_l > 0x00 && str_l <= 9 )   { str_l = str_l + 0x30; }

		if( str_l >= 0x0A && str_l <= 0x0F )   { str_l = str_l + 0x37; }

#ifdef cHW_DEV_BOARD
                UART3_WAIT_AND_SEND( str_h );
                UART3_WAIT_AND_SEND( str_l );

#else
                UART1_WAIT_AND_SEND( str_h );
                UART1_WAIT_AND_SEND( str_l );
#endif
		

		i++;
	}
	printf( "\n" );
}






#undef cMEM_USERCLASS_ID_USART_DEBUG_c