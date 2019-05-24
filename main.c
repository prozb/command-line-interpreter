#include <stdio.h>
#include "main.h"

int main(void){
    printf("start\n");
    
    char buffer[MAX_BUFFER_SIZE];  

    while (*(fgets(buffer, MAX_BUFFER_SIZE, stdin)) != EOF)
    {
        printf("%s\n", buffer);
    }
    

    return 0;
}