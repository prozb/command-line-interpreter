#include <stdio.h>
#include "main.h"

int main(void){
    printf("start\n");
    
    char buffer[MAX_BUFFER_SIZE];  

    while (1)
    {   
        printf(">");
        if(fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL){
            printf("%s", buffer);
        }else{
            printf("\n");
            break;
        }
    }
    

    return 0;
}