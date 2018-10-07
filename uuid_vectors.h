
/* This file was generated by idltool 53.6. Do not edit */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif

#ifndef LIBRARIES_UUID_H
#include <libraries/uuid.h>
#endif

extern ULONG                VARARGS68K _uuid_Obtain(struct UuidIFace *);
extern ULONG                VARARGS68K _uuid_Release(struct UuidIFace *);
extern void *               VARARGS68K _uuid_UuidA(struct UuidIFace *, const struct TagItem * taglist);
extern void *               VARARGS68K _uuid_Uuid(struct UuidIFace *, ...);
extern void                 VARARGS68K _uuid_FreeUuid(struct UuidIFace *, void * uuid);
extern void                 VARARGS68K _uuid_UuidToText(struct UuidIFace *, void * uuid, char * text);
