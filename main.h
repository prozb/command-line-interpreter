#ifndef _MAIN_H_
#define _MAIN_H_

#define MAX_BUFFER_SIZE 500
#define MAX_COMMAND_SIZE 21
#define DEFAULT_DELIM ";"

//splitting buffer into command
int split_line(char buffer[], int buffer_s, char *commands[], int commands_s, char *delim);

#endif