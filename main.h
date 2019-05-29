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

typedef struct command {
    char *program;                      // POSIX command name
    char *arguments[MAX_ARGS_COUNT + 1]; // reserve one slot for NULL
} Command;


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
/** method cleans executed command*/
int clean_command(int);

#endif
