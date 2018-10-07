/* genuuid */

#include <proto/exec.h>
#include <proto/uuid.h>
#include <stdio.h>

struct UuidBase *UuidBase;
struct UuidIFace *IUuid;

int main(void)
{
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

	void *uuid = IUuid->UuidA(NULL);
	char str[40];

	if(uuid != NULL) {
		IUuid->UuidToText(uuid, str);

		printf("%s\n", str);
		
		IUuid->FreeUuid(uuid);
	}

	IExec->DropInterface(IUuid);
	IExec->CloseLibrary(UuidBase);

	return 0;
}
