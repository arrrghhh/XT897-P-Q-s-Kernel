#ifndef _RIVA_COREDUMP_HEADER
#define _RIVA_COREDUMP_HEADER

void *create_riva_coredump_device(const char *dev_name);
int do_riva_coredump(void *handle);

#endif
