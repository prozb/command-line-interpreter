#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 500       // length of the one line read from user
#define MAX_COMMANDS_SIZE 10
#define MAX_ARGS_COUNT 20         // how much arguments can have one command 
#define DEFAULT_DELIM ";"         // default commands separator
#define ARGS_DELIM " "            // default arguments separator
#define TRUE 1
#define COMMAND_SIZE (sizeof(char *) + sizeof(char *) * (MAX_ARGS_COUNT + 1) + 2 * sizeof(int))

typedef struct command {
    char *program;                       // POSIX command name
    char *arguments[MAX_ARGS_COUNT + 1]; // reserve one slot for NULL
    int pid;                             // pid where command will be executed   
    int exit_code;                       // exit code
} Command;

/** adding result to command executed in process*/
int set_exit_code(Command commands[], int size, int code, int pid){
    for(int i = 0; i < size; i++){
        if(commands[i].pid == pid){
            commands[i].exit_code = code;

            return 0;
        }
    }
    return 1;
}
/** executes forks */
int creating_forks(Command commands[], int size);
/** cleand all commands in commands array*/
int clean_commands(Command commands[], int *size);
/**splitting buffer into command*/
int split_line(char buffer[], char *commands[], int commands_s, char *delim);
/**Splitting command to program name and arguments*/
int get_command(Command *command, char *command_s, int max_args_count, char *delim);
/** executing command */
int execute_command(Command *command){
    return execvp(command->program, command->arguments);    
}

/** trim leading and trailing spaces, returning new string*/
char *trim_string(char s[]){
    // skipping leading spaces
    while(isspace(*s)){
        s = s + 1;
    }

    char *end = s + strlen(s) - 1;
    while(end >= s && isspace(*end)){
        end = end - 1;
    }
    *(end + 1) = '\0';
 
    return s;
}

/** printing statistics for each command */
int print_statistics(Command commands[], int size){
    // todo: cumulative sum 
    for(int i = 0; i < size; i++){
        printf("%s: exit status: %d, pid: %d\n", commands[i].program, commands[i].exit_code, 
        commands[i].pid);
    }

    return 0;
}

#endif
