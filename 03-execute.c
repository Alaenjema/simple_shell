#include "shell.h"

/**
 * _execute - a function that executes glo
 * @command: the command demo
 * @argv: argume dem
 * @idx: command ind cmd
 * Return: the exit status of child proc dem
 * or 127 if the command does not sorti
*/
int _execute(char **command, char **argv, int idx)
{
	pid_t child;
	char *cmd;
	int status;

	/* Get the path of the first command argument */
	cmd = _getpath(command[0]);

	if (!cmd)  /* If the command does not exist dont call fork */
	{
		print_error(argv[0], idx, command[0]);
		free2Darray(command);
		return (127);
	}
	child = fork();
	if (child == 0)
	{
		if (execve(cmd, command, environ) == -1)
		{
			free2Darray(command);
			free(cmd), cmd = NULL;
		}
	}
	else
	{
		waitpid(child, &status, 0);
		free2Darray(command);
		free(cmd), cmd = NULL;
	}

	return (WEXITSTATUS(status));
}
