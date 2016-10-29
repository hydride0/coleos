#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <pwd.h>
#define PATH_LEN 2

int main(int argc, char **argv) {
    // Gets username from password structure using uid returned by getuid() 
    char *user = getpwuid(getuid())->pw_name;
    char *path[PATH_LEN] = {"/usr/bin", "/usr/local/bin" };
    // Gets hostname
    char hostname[10];
    gethostname(hostname, 10);
    // Creates nice prompt 
    char prompt[10];
    sprintf(prompt, "[ %s@%s ]>> ", user, hostname);
    // Buffer used to build path of program
    char abs_path[20];

    for (;;) { // loops until the end of time...
        char *command = readline(prompt);
        if (!(strcmp(command, "exit") ) ) //  ...or until "exit" is inserted
            break; 
        add_history(command); // command is added in history so you can access it afterwards with arrows

        for (int i = 0; i < PATH_LEN; i++) {
            sprintf(abs_path, "%s/%s", path[i], command); // building path
            if (access(abs_path, X_OK) == 0) // if file exits and is executable
                break;
        }

        if(fork() == 0) { // executed by child process only
            if (execl(abs_path, command, NULL) == -1)
                perror(command); // print error message if exec fails
            exit(0); // child exits
        }
        else
            wait(0); // parent process waits for the child to terminate
    }
    return 0;
}
