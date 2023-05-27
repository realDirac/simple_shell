#include "shell.h"

/**
 * read_line - Read a line of input from the user
 *
 * Return: The input line
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		} else
		{
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}

/**
 * split_line - Split a line into arguments
 * @line: The input line
 *
 * Return: An array of arguments
 */
char **split_line(char *line)
{
	int bufsize = BUFFER_SIZE;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("split_line");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, DELIMITERS);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("split_line");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIMITERS);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * execute - Execute a command
 * @args: An array of arguments
 *
 * Return: 1 if the shell should continue, 0 otherwise
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execute");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
