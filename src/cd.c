#include "koleos.h"

void cd(const char *path) {
    chdir(path);
}

int dir_exists(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1;
    }
    return 0;
}
