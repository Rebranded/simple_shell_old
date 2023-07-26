#include "my_simple_shell.h"

int main() {
	char* input;
	char* command;
	char* arguments[MAX_ARGUMENT_S];
	while (1) {
		input = simple_shell_read_line();
		if (input == NULL) {
			/* EOF reached (e.g., Ctrl+D) */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		simple_shell_split_line(input, &command, arguments);

		if (command != NULL)
		{
			if (my_simstrcmp(command, "exit") == 0)
			{
				/* Exit the shell */
				free(input);
				break;			}		
			else if (my_simstrcmp(command, "cd") == 0)
			{
				/* Handle 'cd' command */	
				if (arguments[0] != NULL)
				{	if (chdir(arguments[0]) != 0)	     	
					{ 
						perror("cd failed");
					}	
				}
				else		
				{	
					write(STDOUT_FILENO, "Usage: cd <directory>\n", 22);	
				}	
			}
			else	
			{
				/* Execute other commands */	
				simple_shell_exec(command, arguments);	 
			}				

		}	
		free(input);
	} 

	return 0;
}
