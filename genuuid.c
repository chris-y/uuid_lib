/* genuuid */
/* gcc -o genuuid genuuid.c -Iinclude
*/

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/uuid.h>
#include <stdio.h>

struct UuidBase *UuidBase;
struct UuidIFace *IUuid;

int main(int argc, char **argv)
{
	ULONG ver = 1;
	char *name = NULL;
	char *namespace = NULL;
	LONG rarray[] = {0, 0, 0};
	struct RDArgs *args;
	STRPTR template = "VERSION=VER/K/N,NAMESPACE/K,NAME/K";

	enum
	{
		A_VERSION,
		A_NAMESPACE,
		A_NAME
	};
	
	UuidBase = IExec->OpenLibrary("uuid.library", 1L);
	if(UuidBase) {
		IUuid = (struct UuidIFace *)IExec->GetInterface(UuidBase, "main", 1, NULL);
		if (!IUuid) {
			IExec->DropInterface(IUuid);
			return 5;
		}
	} else {
		return 5;
	}

	if(argc != 0) {
		// cli startup

		args = IDOS->ReadArgs(template,rarray,NULL);

		if(args) {
			if(rarray[A_VERSION]) {
				ver = *(ULONG *)rarray[A_VERSION];
			}

			if(rarray[A_NAMESPACE])
				namespace = strdup((char *)rarray[A_NAMESPACE]);

			if(rarray[A_NAME])
				name = strdup((char *)rarray[A_NAME]);

			IDOS->FreeArgs(args);
		} else {
			return 5;
		}
	}

/*
	void *uuid_ns = IUuid->Uuid(UUID_Preset, UUID_NS_DNS,
						TAG_DONE);
*/

	void *uuid;
	int p=0;

	uuid = IUuid->Uuid(UUID_Version, ver,
//						UUID_Namespace, uuid_ns,
//						UUID_Name, name,
						TAG_DONE);
	
	char str[37];

/*
	if(uuid_ns != NULL) {
		IUuid->UuidToText(uuid_ns, str);

		printf("namespace: %s name: %s\n", str, name);
		
		IUuid->FreeUuid(uuid_ns);
	}
*/

	if(uuid != NULL) {
		IUuid->UuidToText(uuid, str);

		printf("[ver %d] %s\n", ver, str);
		
		IUuid->FreeUuid(uuid);
	} else {
		printf("[unable to allocate uuid]\n");
	}

	IExec->DropInterface(IUuid);
	IExec->CloseLibrary(UuidBase);

	return 0;
}
