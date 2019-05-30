#include "main.h"
#include  <sys/types.h>
#include  <sys/wait.h>

Command command_objects [MAX_COMMANDS_SIZE + 1];
int num_commands = 0; 

int main(void){
    printf("start\n");
    
    char buffer[MAX_BUFFER_SIZE];  
    char *commands[MAX_COMMANDS_SIZE + 1];

    while (1)
    {   
        printf(">"); 
        if(fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL){
            // processing commands separated by semicolons
            // max commands number is 10 and min is 0
            
            if(split_line(buffer, commands, MAX_COMMANDS_SIZE, DEFAULT_DELIM) == 0){
                char *current_command;
                int counter = 0;

                while ((current_command = commands[counter++]) != NULL)
                {
                    //command is maximum 20 words (first word is command name
                    // and 19 another are arguments) arguments are separated 
                    // by one or more whitespaces
                    Command *command = (malloc(sizeof(char *) + sizeof(char *) * (MAX_ARGS_COUNT + 1)));
                    get_command(command, current_command, MAX_ARGS_COUNT, ARGS_DELIM);
                    // pushing command object to all commands

                    if((*command).program != NULL && strcmp((*command).program, "\n") != 0){
                        command_objects[num_commands++] = *command;
                    }
                }
            }

            creating_forks(command_objects, num_commands);
            clean_commands(command_objects, num_commands);
            //print statistics for command
        }else{
            printf("\n");
            break;
        }
    }
    
    return 0;
}

int creating_forks(Command commands[], int size){
    int counter = 0;
    pid_t result_pid;
    printf("creating forks in parent process\n");

    do{
        // skipping null command
        if(commands[counter].program == NULL){
            counter++;
            continue;
        }
        result_pid = fork();

        if(result_pid == 0){
            int result = execute_command(&(commands[counter]));
            printf("process %d executed result: %d\n", getpid(), result);
            exit(0);
        }
        counter++;
    }while((result_pid != 0 && result_pid != -1) && (counter < size));

    //waiting for all child processes
    if(result_pid > 0){
        int status = 0;
        int wpid;

        while((wpid = wait(&status)) > 0){
            printf("process %d terminating\n", wpid);
        }
    }

    return 0;
}

int clean_commands(Command commands[], int size){
    for(int i = 0; i < size; i++){
        clean_command(i);
    }
    // reset counter
    num_commands = 0;

    return 0;
}

int get_command(Command *command, char *command_s, int max_args_count, char *delim){
    char *token = strtok(command_s, delim);
    int counter = 0;

    while (token != NULL && counter <= max_args_count){
        int t_size = strlen(token);
        char t_array[t_size + 1];
        char *modified_token = malloc(sizeof(char) * (t_size + 1));

        strcpy(t_array, token);
        t_array[t_size] = '\0';

        if(t_size > 0 && t_array[t_size - 1] == '\n'){
            t_array[t_size - 1] = '\0';
        }
        trim_string(t_array);
        strcpy(modified_token, t_array);

        if(t_array[0] != '\0'){
            if(counter == 0){
                command->program = modified_token;
                counter++;
            }
            command->arguments[counter - 1] = modified_token;
        }
        token = strtok(NULL, delim);
        counter++;
    }

    command->arguments[counter - 1] = NULL;

    return 0;
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

    return 0;
}

int clean_command(int n){
    if(n >= 0 && n < num_commands){
        command_objects[n].program = NULL;
        command_objects[n].arguments[0] = NULL;

        return 0;
    }

    return 1;
}
