#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>

static Command command_objects [MAX_COMMANDS_SIZE + 1];
static int num_commands = 0; 
static struct tms proc_time;

int main(void){
    printf("start\n");
    char buffer[MAX_BUFFER_SIZE];  
    char *commands[MAX_COMMANDS_SIZE + 1];

    while (TRUE)
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
                    Command *command = (malloc(COMMAND_SIZE));
                    get_command(command, current_command, MAX_ARGS_COUNT, ARGS_DELIM);
                    // pushing command object to all commands

                    if((*command).program != NULL && strcmp((*command).program, "\n") != 0){
                        command_objects[num_commands++] = *command;
                    }
                }
            }

            creating_forks(command_objects, num_commands);
            print_statistics(command_objects, num_commands);
            clean_commands(command_objects, &num_commands);
        }else{
            printf("\n");
            break;
        }
    }
    
    return 0;
}

int clean_commands(Command commands[], int *size){
    for(int i = 0; i < *size; i++){
        commands[i].program = NULL;
        commands[i].arguments[0] = NULL;
    }
    *size = 0;

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

        if(result_pid < 0){
            printf("error: not enough memory to create new process");
        }if(result_pid > 0){
            commands[counter].pid = result_pid;
        }else if(result_pid == 0){
            waste_time(getpid());

            int result = execute_command(&(commands[counter]));
            exit(result);
        }
        counter++;
    }while((result_pid != 0 && result_pid != -1) && (counter < size));

    //waiting for all child processes
    if(result_pid > 0){
        int status = 0;
        int wpid;

        while(TRUE){
            start_clock(&proc_time);
            clock_t start_time = proc_time.tms_cutime;
            if((wpid = wait(&status)) > 0){
                end_clock(&proc_time);

                clock_t end_time = proc_time.tms_cutime;
                int exit_status  = WEXITSTATUS(status);

                long user_time = end_time - start_time;

                set_exit_code(command_objects, num_commands, exit_status, wpid, user_time);
            }else{
                break;
            }
        }
    }

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


