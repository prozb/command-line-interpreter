#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include  <sys/types.h>
#include  <sys/wait.h>
#include <signal.h>

#include "main.h"

void killsig_handler(int sig_num){
    printf("\nsigkill pressed!!!%d\n", sig_num);
    exit(0);
}

int main(void){
    printf("starting program\n");
    signal(SIGINT, killsig_handler);
    while(1);
    
    return 0;
}