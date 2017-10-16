/*--------------------------------------------------------------------------
$Filename:      BLD.h
$Prefix:        BLD

$Description:
        This file contains macro definitions that configure the build of the
        WP4 project.This file should be reviewed before building each 
        F/W release to ensure that all desired build options (including
        version definitions) are properly set.

$CAUTION:	This file only applies to 'c' source files. Files that are
                          are outside this scope (e.g. .asm files) must be 
                          controlled through some separate mechanism.

$Author:	KGANS, JRAMIREZ, originated 2009-Mar-6
                PFormanek, Oct. 11, 2017
--------------------------------------------------------------------------
$Copyright (c) 2004-2009 J.S.FOSTER Corporation 	All Rights Reserved
--------------------------------------------------------------------------
$End
----------------------------------------------------------------------------*/

#ifndef BLD_H
#define BLD_H

/*----------------------------------------------------------------------------
			----- M A S T E R   D E F I N I T I O N S -----
  ----------------------------------------------------------------------------*/

#define cBLD_HW_Revision (cBLD_HW_Revision_TandemDevKit1)

/* available revisions */
#define cBLD_HW_Revision_TandemDevKit1 (1) /* IAR STM-32-SK brd +	Chipcon Smart RF04EB 1.9 brd */


/*	------------------------
  	--- TEST Flags --- 
	------------------------
*/
#define	cBLD_TEST_HW					(1)
#define cBLD_PreReleaseSourceReview 	(0)	/* set this flag to expose all 
												questionable source statements */

/* should be defined as cBLD_DEBUG_PRINT_release for all F/W releases 
*/
#define cBLD_DEBUG_PRINT (cBLD_DEBUG_PRINT_debug)
#define cBLD_DEBUG_PRINT_release	(1)
#define cBLD_DEBUG_PRINT_debug		(2)

/*----------------------------------------------------------------------------
			----- I N C L U D E   F I L E S -----
  ----------------------------------------------------------------------------*/
#if cBLD_TEST_HW == 1
#include "BLD_TEST.h"
#endif

/*----------------------------------------------------------------------------
			-----   A P P L I C A T I O N   O P T I O N S   -----
  ----------------------------------------------------------------------------*/

#define	cBLD_L1												(0)
#define	cBLD_PRE											(1)



/*----------------------------------------------------------------------------
			-----   R F C   O P T I O N S   -----
  ----------------------------------------------------------------------------*/

#define cBLD_RFC_PROT_TxMsgId_ClassBasic_WMS_RMTACTIVE_MODEA	(1)

#define cBLD_HW_CC1101_PA_TABLE_RAMPING	(0)


#endif // BLD_H

