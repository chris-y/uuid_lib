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
#include <proto/utility.h>
#include <dos/dos.h>
#include <libraries/uuid.h>
#include <proto/uuid.h>
#include <stdarg.h>
#include <stdio.h>

#include "uuid_v4.h"
#include "uuid_v5.h"
#include "uuid_preset.h"

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
	struct TagItem *ti;
	ULONG ver = 4;
	ULONG preset = 0;
	uuid_t *namespace = NULL;
	const char *name = NULL;
	bool ret = false;
	
	if((ti = IUtility->FindTagItem(UUID_Version, taglist)))
		ver = (ULONG)ti->ti_Data;

	if((ti = IUtility->FindTagItem(UUID_Preset, taglist)))
		preset = (ULONG)ti->ti_Data;

	if((ti = IUtility->FindTagItem(UUID_Namespace, taglist)))
		namespace = (uuid_t *)ti->ti_Data;

	if((ti = IUtility->FindTagItem(UUID_Name, taglist)))
		name = (const char *)ti->ti_Data;

	if((ver == 5) && ((name == NULL) || (namespace == NULL)))
		return NULL;
		
	uuid_t *uuid = IExec->AllocVecTags(sizeof(uuid_t),
				AVT_Type, MEMF_PRIVATE,
				TAG_DONE);

	if(uuid == NULL) return NULL;

	if(preset != 0) {
		ret = uuid_preset(uuid, preset);
	} else if(ver == 5) {
		ret = uuidv5(uuid, namespace, name);
	} else {
		ret = uuidv4(uuid);
	}
	
	if(ret == true) {
		return uuid;
	} else {
		IExec->FreeVec(uuid);
		return NULL;
	}
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

