#include "koleos.h"

char **parse_command(char *cmd, int *arg_no) {
    char buffer[strlen(cmd)+1];
    strcpy(buffer, cmd);
    char count_buffer[strlen(cmd)+1];
    strcpy(count_buffer, cmd);

    int token_no = 0;
    char *token = strtok(count_buffer, " ");
    while ( token != NULL ) {
        token_no++;
        token = strtok(NULL, " ");
    }

    char **args = malloc((token_no+1) * sizeof(char *));
    int k = 0; 
    token = strtok(buffer, " ");
    while ( token != NULL ) {
        args[k] = malloc(strlen(token)+1);
        strcpy(args[k], token);
        args[k][strlen(token)+1] = '\0';
        k++;
        token = strtok(NULL, " ");
    }
    args[token_no] = (char *) 0;
    *arg_no = k;
    return args;
}
        

void build_prompt(char *prompt_buffer) {
    char *user = getpwuid(getuid())->pw_name;
    char *current_dir = getcwd(NULL, 0);
    char hostname[10];
    gethostname(hostname, 10);
    sprintf(prompt_buffer, "\033[38;5;131m┌[%s]\033[m\n\033[38;5;131m└[%s@%s]>>\033[m ", current_dir, user, hostname);
}
