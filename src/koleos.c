#include "koleos.h"

int main(int argc, char **argv) {
    char *path[PATH_LEN] = { "/usr/bin", "/usr/local/bin" };
    char abs_path[50];
    char *command;
    NARGV *arg;

    for (;;) { // loops until the end of time...
        char prompt[70];
        build_prompt(prompt);
        command = readline(prompt);
        int arg_no;

        if ((command = lstrip(command)) != NULL) {
            add_history(command);    
            arg = nargv_parse(command);

            if (!(strcmp(command, "exit") ) ) //  ...or until "exit" is inserted
                break;
 
            if (dir_exists(arg->argv[0]))
                cd(arg->argv[0]);
            
            else if (!strcmp(arg->argv[0], "cd") ) {
                if (dir_exists(arg->argv[1]))
                    cd(arg->argv[1]);
                else perror("cd");
            }
            
            else {
                for (int i = 0; i < PATH_LEN; i++) {
                    sprintf(abs_path, "%s/%s", path[i], arg->argv[0]); // building path
                    if (access(abs_path, X_OK) == 0) // if file exists and is executable
                        break;
                }

                if(fork() == 0) { // executed by child process only
                    if (execv(abs_path, arg->argv) == -1)
                        perror(command); // prints error message if exec fails
                    exit(0); // child exits
                }
                else
                    wait(0); // parent process waits for the child to terminate
            }
        }
    }
    free(command);
    free(arg);
    return 0;
}
