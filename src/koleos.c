#include "koleos.h"

int main(int argc, char **argv) {
    char *path[PATH_LEN] = { "/usr/bin", "/usr/local/bin" };
    char abs_path[20];
    char *command;
    char **arg;

    for (;;) { // loops until the end of time...
        char prompt[30];
        build_prompt(prompt);
        command = readline(prompt);
        //add_history(command);
        int arg_no;
        if ((command = lstrip(command)) != NULL) {
            
            arg = parse_command(command, &arg_no);

            if (!(strcmp(command, "exit") ) ) //  ...or until "exit" is inserted
                break; 
 
            if (dir_exists(arg[0]))
            cd(arg[0]);
            
            else if (!strcmp(arg[0], "cd") )
                cd(arg[1]);
            else {
                for (int i = 0; i < PATH_LEN; i++) {
                    sprintf(abs_path, "%s/%s", path[i], arg[0]); // building path
                    if (access(abs_path, X_OK) == 0) // if file exists and is executable
                        break;
                }

                if(fork() == 0) { // executed by child process only
                    if (execv(abs_path, arg) == -1)
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
