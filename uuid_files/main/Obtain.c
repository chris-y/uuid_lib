/* :ts=4
 *  $VER: Obtain.c $Revision$ (07-Oct-2018)
 *
 *  This file is part of uuid.
 *
 *  Copyright (c) 2018 Hyperion Entertainment CVBA.
 *  All Rights Reserved.
 *
 * $Id$
 *
 * $Log$
 *
 *
 */


#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <libraries/uuid.h>
#include <proto/uuid.h>
#include <stdarg.h>

/****** uuid/main/Obtain ******************************************
*
*   NAME
*      Obtain -- Description
*
*   SYNOPSIS
*      ULONG Obtain(void);
*
*   FUNCTION
*
*   INPUTS
*
*   RESULT
*       The result ...
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

ULONG _uuid_Obtain(struct UuidIFace *Self)
{
  return (uint32)0;
}

