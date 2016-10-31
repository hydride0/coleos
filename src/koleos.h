#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <ctype.h>
#include <pwd.h>
#include <dirent.h>
#include "nargv.h"
#define PATH_LEN 2

void build_prompt(char *prompt_buffer);
void cd(const char *path);
int dir_exists(const char *path);
char *lstrip(char *str);
