/* :ts=4
 *  $VER: UuidA.c $Revision$ (07-Oct-2018)
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
#include <stdio.h>

#include "uuid_v4.h"

/****** uuid/main/UuidA ******************************************
*
*   NAME
*      UuidA -- Description
*      Uuid -- Vararg stub
*
*   SYNOPSIS
*      void * UuidA(const struct TagItem * taglist);
*      void * Uuid(...);
*
*   FUNCTION
*
*   INPUTS
*       taglist - 
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

void *UuidA(const struct TagItem * taglist)
{
	return (void *)uuidv4();
}

void * VARARGS68K _uuid_Uuid(struct UuidIFace *Self,
       ...);

void * _uuid_Uuid(struct UuidIFace *Self,
       ...)
{
    va_list ap;
    struct TagItem *tags;

    va_startlinear(ap, Self);
    tags = va_getlinearva(ap, struct TagItem *);

    return Self->UuidA(
        tags);

}

void * _uuid_UuidA(struct UuidIFace *Self,
       const struct TagItem * taglist)
{
  return UuidA(taglist);
}

