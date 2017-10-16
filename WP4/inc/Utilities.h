/*------------------------------------------------------------------------------
  	$File:		Utilities.h	
  	$Module:  	Utilities
  	$Prefix:  	UTIL
  	$Language:	ANSI C
  	$Description:
		
  	$Notes:

  	$Author:	Juan Ramirez, 2009-Sept-22
  	--------------------------------------------------------------------------
  	$Copyright (c) 2004-2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#ifndef __UTIL_H__
#define __UTIL_H__

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- M A C R O   D E F I N I T I O N S -----
  ------------------------------------------------------------------------------
 */
#define mLSB_FROM_WORD(x) (x&0x00FF)
#define mMSB_FROM_WORD(x) (x&0xFF00)>>8
#define mWORD_FROM_BYTES(msb, lsb) ( lsb  + ( msb << 8 ) )
#define mLWORD_FROM_BYTES(msb, midmsb, midlsb, lsb)  ( lsb  + ( midlsb << 8 ) + ( midmsb << 16 ) + ( msb << 24 ) )


// pass the Long word 32bit (lwVar) this would five the highest byte out of the lw XXxxxxxx
#define mHI_BYTE_FROM_LW(lwVar)                             ( (lwVar >> 24)&0x000000FF )  

// pass the Long word 32bit (lwVar) this would five the mid highest byte out of the lw xxXXxxxx
#define mMID_HI_BYTE_FROM_LW(lwVar)                         ( (lwVar >> 16)&0x000000FF )

// pass the Long word 32bit (lwVar) this would five mid low byte out of the lw xxxxXXxx
#define mMID_LOW_BYTE_FROM_LW(lwVar)                        ( (lwVar >> 8)&0x000000FF )

// pass the Long word 32bit (lwVar) this would five lowest byte out of the lw xxxxxxXX
#define mLOW_BYTE_FROM_LW(lwVar)                        ( (lwVar)&0x000000FF )


/*------------------------------------------------------------------------------
				----- C O N S T A N T S -----
  ------------------------------------------------------------------------------
 */
#define cUTIL_PointerTypeErrStruct                      0
#define cUTIL_PointerTypeErrStructSizeofBuffer          13
#define cUTIL_PointerTypeErrStructSizeofTimeStamp       7

/*------------------------------------------------------------------------------
				----- E X P O R T E D   T Y P E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
 	$Type: tpXXX_
	$Description:
	$End
 */
typedef struct
{
  u8 * pbBuffer;
  u16  wSizeofBuffer;
}tsUTIL_ByteArrayStruct;


/*------------------------------------------------------------------------------
				----- E X P O R T E D   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
				----- E X P O R T E D   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

u16 YencEncode( u8 * pbStrBuffer, u16 wStrSize, u8 * bReturnStr );
u8 IsEscapeChar( u8 bChar );
u8 CheckSumCal( u8 * pbBuffer, u16 wLength, u8 bStartPosition );


char itoa(int value, char* result, int base);




void Strtok( const char * source, char * dest, const char  token );


void DEBUG_Strtok( const char * source, char * dest, const char  token );

u8 NumOfCmds( u8 * pbBuffer, u8 bChar );


char *replace_str( char *orig, char *rep, char *str  );

u16 SizeOf( u8 * pbPointer );

u8 Copy( const u8 * pbData, u8 * pbBuffer, u16 wSize, u16 bStartByte );


void UTIL_PrintfLongWordOut( u32 lwLongWord );
void UTIL_PrintfWordOut( u16 wWord );
void UTIL_PrintfByteOut( u8 bByte );

u8 UTIL_BuildByteArray( void * vpPointer, tsUTIL_ByteArrayStruct * tsUTIL_ByteArrayBuilder, u8 bTypeOfPointer );

u8 UTIL_InStr( u8 * pbStr, u8 bInStr, u16 * pwReturnFlag );


u8 UTIL_StripCmd( u8 * pbBuffer, u8 * pbTempBuffer , u8 bStartByte, u8 bEndCharacter );

void UTIL_AsciiToHex ( u8 * pbBuffer, u16 wLength );

u8 UTIL_InRange( u32 lwVal, u32 lwFrom, u32 lwTo );

#endif // __UTIL_H__

