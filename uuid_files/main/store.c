/* store.c */

#include <proto/exec.h>
#include <proto/bsdsocket.h>

#include <stdbool.h>
#include <stdio.h>

struct uuid_store {
    bool mac_set;
    UBYTE        mac[16];
    bool clockseq_set;
    UBYTE clockseq[2];
};

static struct uuid_store store = { false, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							false, {0, 0}};

static void store_set_clockseq(void)
{
	if(store.clockseq_set == true) return;

	FILE *rndf = NULL;
	if(rndf = fopen("RANDOM:", "r")) {
		fread(&store.clockseq, 1, 2, rndf);
		fclose(rndf);
		store.clockseq_set = true;
	} 
}

UBYTE *store_get_clockseq(void)
{
	store_set_clockseq();
	return &store.clockseq;
}


UBYTE *store_get_mac(void)
{
	struct Library *SocketBase;
	struct SocketIFace *ISocket;
	
	if(store.mac_set == true) return &store.mac;
	
	if((SocketBase = IExec->OpenLibrary("bsdsocket.library",4))) {
		if((ISocket = (struct SocketIFace *)IExec->GetInterface(SocketBase,"main",1,NULL))) {
			struct List *interfaces = NULL;
			struct Node *interface = NULL;
			if((interfaces = ISocket->ObtainInterfaceList())) {
				if((interface = IExec->GetHead(interfaces))) {
#ifdef DEBUG
					IExec->DebugPrintF("Found interface: %s\n", interface->ln_Name);
#endif

					ISocket->QueryInterfaceTags(interface->ln_Name, IFQ_HardwareAddress, &store.mac, TAG_DONE);
					store.mac_set = true;

#ifdef DEBUG
					IExec->DebugPrintF("MAC address: %02x:%02x:%02x:%02x:%02x:%02x\n", store.mac[0], store.mac[1], store.mac[2], store.mac[3], store.mac[4], store.mac[5]);
#endif

					store_set_clockseq(); // only if mac has changed otherwise use stored ver
				}
				ISocket->ReleaseInterfaceList(interfaces);
			}
			IExec->DropInterface(ISocket);
		}
		IExec->CloseLibrary(SocketBase);
	}

	return &store.mac;
}

void store_save(void)
{
}
