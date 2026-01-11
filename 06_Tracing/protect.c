#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>

int unlink(const char *pathname) {
    static int (*real_unlink)(const char *) = NULL;
    
    if (!real_unlink) {
        real_unlink = dlsym(RTLD_NEXT, "unlink");
    }
    
    if (strstr(pathname, "PROTECT") != NULL) {
        return 0;
    }
    
    return real_unlink(pathname);
}
