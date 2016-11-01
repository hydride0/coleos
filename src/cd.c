#include "koleos.h"
#define __NR_chdir 80
/*void cd(const char *path) {
    chdir(path);
}*/

int dir_exists(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1;
    }
    return 0;
}

void cd(const char *path) {
    ssize_t ret;
    asm volatile
    (
        "syscall"
        : "=a" (ret)
        : "0"(__NR_chdir), "S"(path)
        : "cc", "rcx", "r11", "memory"
    );
}
