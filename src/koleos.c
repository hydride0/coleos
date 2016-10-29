#include "koleos.h"

int main(int argc, char **argv) {
    char *path[PATH_LEN] = { "/usr/bin", "/usr/local/bin" };
    char abs_path[20];
    char *command;
    char **arg;

    for (;;) { // loops until the end of time...
        char prompt[20];
        build_prompt(prompt);
        command = readline(prompt);
        int arg_no;
        arg = parse_command(command, &arg_no);
        
        if (!(strcmp(command, "exit") ) ) //  ...or until "exit" is inserted
            break; 

        add_history(command); // command is added in history so you can access it afterwards with arrows

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
    free(command);
    free(arg);
    return 0;
}
