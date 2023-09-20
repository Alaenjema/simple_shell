#include "shell.h"

/**
 * is_builtin - check if a command is bsm
 * @command: the command to cms
 * Return: 1 if the command null
*/
int is_builtin(char *command)
{
	int i;
	char *builtins[] = {
		"exit", "env", "setenv",
		"unsetenv", "cd",
		NULL
	};

	for (i = 0; builtins[i]; i++)
	{
		if (_strcmp(command, builtins[i]) == 0)
			return (1);
	}
	return (0);
}

/**
 * handle_builtin - handle cmd
 * @command: the builtin css
 * @argv: argum
 * @status: exit
 * @idx: index
 * @new_env: new_environment vble
 * Return: 1 if the comma null
*/
void handle_builtin(char **command, char **argv, int *status, int idx,
char **new_env)
{
	int i;
	builtins B[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", change_directory},
		{NULL, NULL}
	};

	for (i = 0; B[i].builtin; i++)
	{
		if (_strcmp(B[i].builtin, command[0]) == 0)
		{
			B[i].f(command, argv, status, idx, new_env);
			break;
		}
	}
}

/**
 * exit_shell - exit out
 * this function exits demo
 * @command: the builtin cmd
 * @argv: argumente
 * @status: exit statu glo
 * @idx: index of the cmd
 * @new_env: new_environment global
 * Return: <void>
*/
void exit_shell(char **command, char **argv, int *status, int idx,
char **new_env)
{
	int exit_status = (*status);
	char *index, mssg[] = ": exit: Illegal number: ";

	if (command[1])
	{
		if (!is_positive_number(command[1]))
		{
			index = _itoa(idx);
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, index, _strlen(index));
			write(STDERR_FILENO, mssg, _strlen(mssg));
			write(STDERR_FILENO, command[1], _strlen(command[1]));
			write(STDERR_FILENO, "\n", 1);
			free(index), free2Darray(command), free((*new_env));
			(*status) = 2;
			return;
		}
		else
			exit_status = _atoi(command[1]);
	}
	free2Darray(command), free((*new_env));
	exit(exit_status);
}

/**
 * print_env - print environement vrm
 * @command: the builtin comd
 * @argv: argumene
 * @status: exit statts
 * @idx: index of the cmd
 * @new_env: new_environment 
 * Return: <void>
*/
void print_env(char **command, char **argv, int *status, int idx,
char **new_env)
{
	int i;
	(void) argv;
	(void) idx;
	(void) new_env;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	(*status) = 0;
	free2Darray(command);
}
