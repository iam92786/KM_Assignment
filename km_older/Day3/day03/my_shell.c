#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char cmd[512], *ptr, *args[32];
    int i, ret, err, s;

    while(1) {
        // input command from the user
        printf("cmd> ");
        fgets(cmd, sizeof(cmd), stdin);

        // parse command line args
        i = 0;
        ptr = strtok(cmd, " \t\n");
        args[i++] = ptr;
        do {
            ptr = strtok(NULL, " \t\n");
            args[i++] = ptr;
        }while(ptr != NULL);
        
        // execute the "internal" commands
        if(strcmp(args[0], "exit") == 0)
            break; // _exit(0);
        else if(strcmp(args[0], "cd") == 0) // cmd> cd /home
            chdir(args[1]);
        else if(strcmp(args[0], "neha") == 0)
            printf("Good Morning!\n");
        else {
            // execute the "external" command
            ret = fork();
            if(ret == 0) {
                err = execvp(args[0], args);
                if(err < 0) {
                    perror("bad command");
                    _exit(1);
                }        
            }
            else
                waitpid(ret, &s, 0);
        }
    }
    return 0;
}
