#include "my_simple_shell.h"
#include "sys/wait.h"

/*char* simple_shell_read_line()
  { 
  char* buffer = (char*)malloc(MAX_COMMAND_LENGTH_S * sizeof(char));
  if (!buffer) {
  perror("malloc has failed, out of memory");
  exit(EXIT_FAILURE);
  }      
  write(STDOUT_FILENO, "Simple_Shell$ ", 14);	

  if (read(STDIN_FILENO, buffer, MAX_COMMAND_LENGTH_S) == -1) {
  free(buffer);
  return NULL;
  }

  return buffer;
  }
  */

char* simple_shell_read_line() { 
	size_t MAX_COMMAND_LENGTH_S = 100000;
	char* buffer = (char*)malloc(MAX_COMMAND_LENGTH_S * sizeof(char));
	if (!buffer) {
		perror("malloc has failed, out of memory");
		exit(EXIT_FAILURE);
	}

	write(STDOUT_FILENO, "Simple_Shell$ ", 14);

	if (getline(&buffer, &MAX_COMMAND_LENGTH_S, stdin) == -1) {
		free(buffer);
		return NULL;
	}

	return buffer;
}

/* Function to parse input and get command and arguments */
void simple_shell_split_line(char* input, char** command, char** arguments) {
	*command = strtok(input, " \n\t\r");
	if (*command == NULL)
	{
		return;

	}

	for (int i = 0; i < MAX_ARGUMENT_S; ++i)
	{
		arguments[i] = strtok(NULL, " \n\t\r");
		if (arguments[i] == NULL) {
			break;
		}
	}
}

/* fUNCTION TO EXECUTE THE SHELL FUNCTION */

int simple_shell_exec(const char* command, char* const arguments[]) {
	if (command == NULL) {
		/* Return an error value to indicate a problem */       
		return -1; 
	}

	pid_t child_pid = fork();

	if (child_pid == -1) {
		perror("fork");
		return -1;
	} 
	else if (child_pid == 0) {
		/* Child process */
		if (execve(command, arguments, NULL) == -1) {
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else {
		/* Parent process */
		int status;
		waitpid(child_pid, &status, 0); // Use waitpid with 0 for simple blocking
		if (WIFEXITED(status)) {
			int exit_status = WEXITSTATUS(status);
			return exit_status; // Return the exit status of the child process
		} else {
			/* Indicate that the child process terminated abnormally */
			return -1; 
		}
	}
}


/* Custom strcmp function */
int my_simstrcmp(const char* str1, const char* str2) {
	while (*str1 && *str2) {
		if (*str1 != *str2) {
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
