/*------------------------------------------------------------------------------
  	$File:	 	HW_Code.c
  	$Module: 	Hardware declarations stored in ROM
  	$Prefix:  	HW
  	$Language:	ANSI C
  
  	$Description:
				This file includes all the files that declare ROM const tables.
  	$Notes:
			1) ROM tables are used whenever possible for the following advantages
				-- reduction in the number of lines of invariant software (execution 
						code) which can contain contain bugs
				-- ease of reading executable code 
				-- ease of making future modifications
				-- future modifications will generally be to data, not executable code, 
						which generally reduces the risk of introducing bugs

			2) 	DECLARING OBJECTS CONST 
				  The use of const is not standard across all platforms and compilers.
				  For example, IAR's use and Keil's use are different (e.g. with Keil,
				  const can be applied to RAM)
					(REF: EWARM_DevelopmentGuide.ENU.pdf, Part 2. Reference information p.219)
						...Static and global objects declared const are allocated in ROM

  	$Author:	KGANS, 2009-March-22
  	--------------------------------------------------------------------------
  	$Copyright (c) 2009 J.S. Foster Corporation 	All Rights Reserved
  	--------------------------------------------------------------------------
  	$End
  ----------------------------------------------------------------------------*/

#define cMEM_USERCLASS_ID_HW_CODE_c

/*------------------------------------------------------------------------------
				------ I N C L U D E   F I L E S ------
  ------------------------------------------------------------------------------
 */

#undef cMEM_USERCLASS_ID_HW_CODE_c

