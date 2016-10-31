#include "koleos.h"

void build_prompt(char *prompt_buffer) {
    char *user = getpwuid(getuid())->pw_name;
    char *current_dir = getcwd(NULL, 0);
    char hostname[10];
    gethostname(hostname, 10);
    sprintf(prompt_buffer, "\033[38;5;131m┌[%s]\033[m\n\033[38;5;131m└[%s@%s]>>\033[m ", current_dir, user, hostname);
}

char *lstrip(char *str) {
    while (isspace(*str)) str++;
    if (*str == 0)
        return NULL;
    return str;
}
