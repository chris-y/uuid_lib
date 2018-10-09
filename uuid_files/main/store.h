/* store.h */

#ifndef _LIBRARIES_UUID_STORE_H_
#define _LIBRARIES_UUID_STORE_H_ 1

struct uuid_store;

UBYTE *store_get_mac(void);
UBYTE *store_get_clockseq(void);

void store_save(void);

#endif
