
#include "main.h"

int main(void){
    printf("start\n");
    
    char buffer[MAX_BUFFER_SIZE];  
    char *commands[MAX_COMMANDS_SIZE];
    Command command_objects [MAX_ARGS_COUNT];
    
    while (1)
    {   
        printf(">");
        if(fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL){
            // processing commands separated by semicolons
            // max commands number is 10 and min is 0
            
            if(split_line(buffer, commands, MAX_COMMANDS_SIZE, DEFAULT_DELIM)){
                char *current_command;
                int counter = 0;

                while ((current_command = commands[counter++]) != NULL)
                {
                    printf("%d command: %s\n", counter, current_command);    
                    //command is maximum 20 words (first word is command name
                    // and 19 another are arguments) arguments are separated 
                    // by one or more whitespaces
                    Command command;
                    get_command(&command, current_command, MAX_ARGS_COUNT, ARGS_DELIM);
                    commands[counter - 1];
                }
            }else
            {  
                printf("info: cannot split line into commands");
            }        
        }else{
            printf("\n");
            break;
        }
    }
    
    return 0;
}

int get_command(Command *command, char *command_s, int max_args_count, char *delim){
    printf ("Splitting string \"%s\" into tokens:\n", command_s);

    char *token = strtok(command_s, delim);
    int counter = 0;

    while (token != NULL && counter <= max_args_count){
        if(counter == 0){
            command->program = token;
            printf("commands: %s\n", token);
        }else{
            command->arguments[counter - 1] = token;
            printf("args: %s\n", token);
        }
        token = strtok(NULL, delim);
        counter++;
    }

    command->arguments[counter - 1] = NULL;

    return 1;
}

int split_line(char buffer[], char *commands[], int commands_s, char *delim){
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