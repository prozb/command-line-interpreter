#include <stdio.h>
#include <string.h>

#include "main.h"

int main(void){
    printf("start\n");
    
    char buffer[MAX_BUFFER_SIZE];  
    char *commands[MAX_COMMAND_SIZE];

    while (1)
    {   
        printf(">");
        if(fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL){
            // processing commands separated by semicolons
            // max commands number is 10 and min is 0
            
            if(split_line(buffer, MAX_BUFFER_SIZE, commands, MAX_COMMAND_SIZE, DEFAULT_DELIM)){
                char *current_command;
                int counter = 0;

                while ((current_command = commands[counter++]) != NULL)
                {
                    printf("%d command: %s\n", counter, current_command);
                }
                
            }else
            {  
                printf("info: cannot split line into commands");
            }
            

            //command is maximum 20 words (first word is command name
            // and 19 another are arguments) arguments are separated 
            // by one or more whitespaces

            // the line without commands will be ignored
        }else{
            printf("\n");
            break;
        }
    }
    

    return 0;
}

int split_line(char buffer[], int buffer_s, char *commands[], int commands_s, char *delim){
    char *token = strtok(buffer, delim);
    int counter = 0;

    while (token != NULL && counter < commands_s){
        commands[counter] = token;
        token = strtok(NULL, delim);
        counter++;
    }
    commands[counter] = NULL;

    return 1;
}