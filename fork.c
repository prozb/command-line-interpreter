#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include  <sys/types.h>
#include  <sys/wait.h>

#include "main.h"

int main(void){
    // __pid_t pid1 = fork();

    // if(pid1 < 0){
    //     perror("fork error\n");
    //     exit(-1);
    // }   
    // printf("%d\n", pid1);

    char *cmd   = "asdas";

    printf("starting\n");
    Command command;
    command.program   = cmd;
    command.arguments[0] = "asdasd";
    command.arguments[1] = "-la";
    command.arguments[2] = NULL;

    __pid_t pid = fork();
    printf("pid after fork: %d\n", pid);
    if(pid < 0){
        printf("error by creating process\n");
    }else if(pid == 0){
        int i = 0;
        printf("starting calculation\n");
        while(i++ < 5){
            sleep(1);
        }
        printf("executing command: %s\n", *(command.arguments));
        if(execvp(command.program,  command.arguments)){
            printf("execuing ok\n");
            return 0;
        }else{
            printf("failed\n");
            return 1;
        }
    }else{
        int status;
        printf("waiting for child process\n");
        if(wait(&status) == pid){
            printf("child process %d ended\n", pid);
            printf("success: %d\n", WIFEXITED(status));
        }else{
            wait(&status);
        }
    }
    return 0;
}