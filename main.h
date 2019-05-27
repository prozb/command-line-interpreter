#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 500       // length of the one line read from user
#define MAX_COMMANDS_SIZE 21
#define MAX_ARGS_COUNT 19         // how much arguments can have one command 
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

#endif