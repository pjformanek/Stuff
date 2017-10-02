/*------------------------------------------------------------------------------
  	$File:		Utilities.c
  	$Module:  	Useful utilities
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

#define cMEM_USERCLASS_ID_UTIL_UTILITIES_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */
#include "GLB.h"
#include "MEM.h"
#include "ERR.h"

#include "USART_Debug.h"
#include "USART_Config.h"

#include "Utilities.h"

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
//tsUTIL_ByteArrayBuilderStruct tsUTIL_ByteArrayBuilder;

/*------------------------------------------------------------------------------
				----- G L O B A L   V A R I A B L E S -----
  ------------------------------------------------------------------------------
 */

/* for DEBUG_Strtok function */
static char * temp;
/* for Strtok function */
static char * tmp;
/*---------------------*/

/*------------------------------------------------------------------------------
				----- L O C A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/


/*------------------------------------------------------------------------------
				----- G L O B A L   F U N C T I O N S -----
  ------------------------------------------------------------------------------
 */



/*------------------------------------------------------------------------------
$Function:
$Description:

$Inputs: none
$Outputs: none
$Assumptions:
$WARNINGS:
$End
*/
u8 UTIL_InRange( u32 lwVal, u32 lwFrom, u32 lwTo )
{
  if( lwVal >= lwFrom && lwVal <= lwTo )
  {   
    return 1;
  }
  
  return 0;
} 



/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/

u16 YencEncode( u8 * pbStrBuffer, u16 wStrSize, u8 * bReturnStr )
{
  //u8 bReturnStr[1000] = { 0 };
  u8 tmp = 0, bTmpSize[5] = {0};
  u16 x = 4, i = 0;

  //for( u16 i=0 ; i<wStrSize ; i++ )
  //printf("\n\n\nthe char %d\n\n\n", pbStrBuffer[x] );
  while( x<wStrSize )
  {
    bReturnStr[i] = ( ( pbStrBuffer[x++]+42 ) % 256 );
    //printf("\n\n\nthe char %x\n\n\n",bReturnStr[i] );
    tmp =  bReturnStr[i];

    if( IsEscapeChar( bReturnStr[i] ) )
    {
      bReturnStr[i] = '=';
      i++;
      //wStrSize++;
      bReturnStr[i] = ( ( tmp+64 ) % 256 );
    }



    i++;

  }
    itoa( i, (char*)bTmpSize, 10 );
    //printf("\n\n\nstr size here %s\n\n\nint size here %d\n", bTmpSize, i );


  return i;

}


/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 IsEscapeChar( u8 bChar )
{
  u8 bScapeCharArray[12] = { 0,1,9,10,13,25,32,37,38,43,46,61 };//{ 0, 9, 10, 13, 32, 38, 46, 61 };

  for( u16 x=0 ; x<12 ; x++ )
  {
    if( bChar == bScapeCharArray[x] )
    {
      return 1;
    }
  }
  return 0;
}




/*******************************************************************************
* Function Name  : CheckSumGenerator
* Description    : Generates a check sum on an incoming or outgoin RF packet
* Input          : u8 * pbBuffer - pointer to the RF packet
* 				   u8 bLength - length of the RF packet( it also determines
* 				   the last byte that should be counted in the checksum
* 				   u8 bStartPosition - the first byte in the packet where the
* 				   funciton starts creating the checksum
* Output         : none
* Return         : u8 bCheckSum - the actual checksum
*******************************************************************************/
u8 CheckSumCal( u8 * pbBuffer, u16 wLength, u8 bStartPosition )
{
  u8  bCheckSum = 0;
  u32 j = bStartPosition, i = 0;

  //printf("length = %d\n", wLength);


  while( i < wLength-1 )
  {
    bCheckSum = bCheckSum + pbBuffer[j];
    //printf("cal check = %d\n",bCheckSum );
    j++;
    i++;
  }

  printf( "CHECK = %d\n", bCheckSum );



  return bCheckSum;
}





/*
char itoa( int value, char* result, int base )
{
  // check that the base if valid
  if (base < 2 || base > 36) { *result = '\0'; return 0; }

  char* ptr = result, *ptr1 = result, tmp_char;
  int tmp_value;

  do
  {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
  } while ( value );

  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while(ptr1 < ptr)
  {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
  return 1;
}

*/



/*******************************************************************************
* Function Name  : DEBUG_Strtok
* Description    : Function that breaks strings into tokkens according to a delimiter
* Input          : const char * source - source string
*                  char * dest - buffer where tokken is to be stored
*                  const char  token - token where string will be broken
* Output         : None
* Return         : None
*******************************************************************************/
void DEBUG_Strtok( const char * source, char * dest, const char  token )
{
    if( source != NULL )
    {
        temp = (char*)source;

        while(*temp)
        {
                *dest++ = *temp++;
                if(*temp == token)
                {
                    temp++;
                    break;
                }
        }
    }
    else
    {
        while(*temp)
        {

                *dest++ = *temp++;
                if(*temp == token)
                {
                    temp++;
                    break;
                }
        }
    }
    *dest++ = '\0';
}




/*******************************************************************************
* Function Name  : str_replace
* Description    : Function that
* Input          : const char *search - string to look for
*                  const char *replace - string that will replace search string
*                  char *subject - original string
* Output         : None
* Return         : char *replaced - replaced string
*******************************************************************************/
char *replace_str( char *orig, char *rep, char *str  )
{
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
    return str;

  strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  return buffer;
}


/*******************************************************************************
* Function Name  : DEBUG_NumOfCmds
* Description    : Function counts how many commands are in the debug string according
*                  to a delimiter see cDEBUG_AT_END_CMD
* Input          : u8 * pbBuffer - source string
                   u8 bChar - delimiter
* Output         : None
* Return         : u8 bCount - how many delimters it found therefor how many cmds
*******************************************************************************/
u8 NumOfCmds( u8 * pbBuffer, u8 bChar )
{
  u8 bCount = 0;
  while( *pbBuffer )
  {
    if( *pbBuffer++ == bChar )
    {
      bCount++;
    }
  }
  return bCount;
}


/*******************************************************************************
* Function Name  : Strtok
* Description    : Function that breaks strings into tokkens according to a delimiter
* Input          : const char * source - source string
*                  char * dest - buffer where tokken is to be stored
*                  const char  token - token where string will be broken
* Output         : None
* Return         : None
*******************************************************************************/
void Strtok( const char * source, char * dest, const char  token )
{
    if( source != NULL )
    {
        tmp = (char*)source;

        while(*tmp)
        {
                *dest++ = *tmp++;
                if(*tmp == token)
                {
                    tmp++;
                    break;
                }
        }
    }
    else
    {
        while(*tmp)
        {

                *dest++ = *tmp++;
                if(*tmp == token)
                {
                    tmp++;
                    break;
                }
        }
    }
    *dest++ = '\0';
}

/*******************************************************************************
* Function Name  : Strtok
* Description    : Function that breaks strings into tokkens according to a delimiter
* Input          : const char * source - source string
*                  char * dest - buffer where tokken is to be stored
*                  const char  token - token where string will be broken
* Output         : None
* Return         : None
*******************************************************************************/
u16 SizeOf( u8 * pbPointer )
{
  u16 i = 0;

  while( pbPointer[i] != 0x00 )
  {
    //printf(" i = %d\n", i );
    i++;
  }
  return i;
}

/*******************************************************************************
* Function Name  : Strtok
* Description    : Function that breaks strings into tokkens according to a delimiter
* Input          : const char * source - source string
*                  char * dest - buffer where tokken is to be stored
*                  const char  token - token where string will be broken
* Output         : None
* Return         : None
*******************************************************************************/
u8 Copy( const u8 * pbData, u8 * pbBuffer, u16 wSize, u16 bStartByte )
{
  u16 i = 0, j = bStartByte;

  printf(" j = %d\n size = %d\n data = %s\n", j , wSize, pbData );

    while( i < wSize )
    {
      pbBuffer[i] = pbData[j];
      i++;
      j++;
    }


  printf("data =  %s\n buf = %s\n", pbData, pbBuffer );
  return 1;
}


/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void UTIL_PrintfLongWordOut( u32 lwLongWord )
{
  printf( "%c", (lwLongWord&0xFF000000)>>24 );
  printf( "%c", (lwLongWord&0x00FF0000)>>16 );
  printf( "%c", (lwLongWord&0x0000FF00)>>8 );
  printf( "%c", (lwLongWord&0x000000FF) );
}


/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void UTIL_PrintfWordOut( u16 wWord )
{
  printf( "%c", (wWord&0xFF00)>>8 );
  printf( "%c", (wWord&0x00FF) );
}

/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void UTIL_PrintfByteOut( u8 bByte )
{
  printf( "%c", bByte );
}


/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 UTIL_BuildByteArray( void * vpPointer, tsUTIL_ByteArrayStruct * tsUTIL_ByteArray, u8 bTypeOfPointer )
{
  switch( bTypeOfPointer )
  {
    case cUTIL_PointerTypeErrStruct:
      {
        if( tsUTIL_ByteArray->wSizeofBuffer >= cUTIL_PointerTypeErrStructSizeofBuffer )
        {
          tsERR_ErrorEntryStruct * ErrorEntry;
          ErrorEntry = (tsERR_ErrorEntryStruct*)vpPointer;

          tsUTIL_ByteArray->pbBuffer[0] = (ErrorEntry->lwCmdId&0xFF000000)>>24;
          tsUTIL_ByteArray->pbBuffer[1] = (ErrorEntry->lwCmdId&0x00FF0000)>>16;
          tsUTIL_ByteArray->pbBuffer[2] = (ErrorEntry->lwCmdId&0x0000FF00)>>8;
          tsUTIL_ByteArray->pbBuffer[3] = (ErrorEntry->lwCmdId&0x000000FF);

          tsUTIL_ByteArray->pbBuffer[4] = (ErrorEntry->wCmdData&0xFF00)>>8;
          tsUTIL_ByteArray->pbBuffer[5] = (ErrorEntry->wCmdData&0x00FF);

          u8 count = 6; // continues to count after the five

          for( u8 i=0; i<cUTIL_PointerTypeErrStructSizeofTimeStamp; i++ )
          {
            tsUTIL_ByteArray->pbBuffer[count] = ErrorEntry->pbTimeStamp[i];
            count++;
          }

          //Convert_ASCII( tsUTIL_ByteArray->pbBuffer, tsUTIL_ByteArray->wSizeofBuffer );
#if 0 // debug only
          for( u8 i=0; i < tsUTIL_ByteArray->wSizeofBuffer; i++ )
          {
            //mUSART_DEBUG_WAIT_AND_SEND( tsUTIL_ByteArray->pbBuffer[i] );
            printf( "%.2x ", tsUTIL_ByteArray->pbBuffer[i] );
          }
#endif
        }
        else
          return 0;

        break;
      }
    default:
      {
        printf(" UTIL_BuildByteArray Not Valid pointer type");
        break;
      }
  }

  return 1;
}


/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/
void UTIL_AsciiToHex ( u8 * pbBuffer, u16 wLength )
{  
  u16 i = 0, Local_Index = 0;  
  
  for (i=0; i < (wLength-1); i++)    
  {    
    if ( pbBuffer[i] >= 0x30 && pbBuffer[i] <= 0x39 )      
    {      
      pbBuffer[i] = (pbBuffer[i] - 0x30) << 4;      
    }    
    else if (pbBuffer[i] >= 0x41 && pbBuffer[i] <= 0x46 )      
    {      
      pbBuffer[i] = (pbBuffer[i] - 0x37) << 4;      
    }    
    if ( pbBuffer[i+1] >= 0x30 && pbBuffer[i+1] <= 0x39 )      
    {      
      pbBuffer[i+1] = (pbBuffer[i+1] - 0x30);      
    }    
    else if (pbBuffer[i+1] >= 0x41 && pbBuffer[i+1] <= 0x46 )      
    {      
      pbBuffer[i+1] = (pbBuffer[i+1] - 0x37);      
    }    
    
    pbBuffer[Local_Index] = pbBuffer[i] | pbBuffer[i+1];
    
    //printf("%.2X ",pbBuffer[Local_Index]);
    //printf("%d , %d\n", i, wLength);
    
    Local_Index++;
    
    i++;    
  }
  
}


/*------------------------------------------------------------------------------
	$Function:
	$Description:

	$Inputs: none
	$Outputs: none
	$Assumptions:
	$WARNINGS:
	$End
*/

u8 UTIL_InStr( u8 * pbStr, u8 bInStr, u16 * pwReturnFlag )
{
  u16 i = 0;
  while( pbStr[i] )
  {
    if( pbStr[i] == bInStr )
    {
      *pwReturnFlag = i;
      return 1;
    }
    i++;
  }
  return 0;
}


/*------------------------------------------------------------------------------
	$Function: DEBUG_StripCmd
	$Description: Strips partial string from the main message

	$Inputs: u8 * pbBuffer - Contains the full message
                 u8 * pbTempBuffer - Variable where the stripped string will be stored
                 u8 bStartByte - Place where to begin parsing
                 u8 bEndCharacter - where to stop parsing
	$Outputs: Next position on array
	$Assumptions:
	$WARNINGS:
	$End
*/
u8 UTIL_StripCmd( u8 * pbBuffer, u8 * pbTempBuffer , u8 bStartByte, u8 bEndCharacter )
{
  u8 i = bStartByte, j = 0;
  
  
  while( pbBuffer[i] != bEndCharacter && pbBuffer[i] )
  {
    pbTempBuffer[j] = pbBuffer[i];
    i++;
    j++;
  }  
  
  return i+1;
}
#undef cMEM_USERCLASS_ID_UTIL_UTILITIES_c