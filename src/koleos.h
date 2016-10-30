#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <pwd.h>
#include <dirent.h>
#define PATH_LEN 2

char **parse_command(char *cmd, int *arg_no);
void build_prompt(char *prompt_buffer);
void cd(const char *path);
int dir_exists(const char *path);
