#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* Maximum length for user input 
#define MAX_COMMAND_LENGTH_S 100 */

/* Maximum number of argument */
#define MAX_ARGUMENT_S 10

/** boolean definition
 * * #define _Bool char
 * * #define bool _Bool
 * * #define true 1
 * * #define false 0
 * *
 * **/


/* Header files */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*function to read line of input */
char* simple_shell_read_line ();

/*function to split line into token */
void simple_shell_split_line (char* inputs, char** command, char** arguments);

/* function to execute a command represented by token */
int simple_shell_exec(const char* command, char* const arguments[]);

/* custom strcmp function */
int my_simstrcmp(const char* str1, const char* str2);

#endif /* SIMPLE_SHELL_H */
