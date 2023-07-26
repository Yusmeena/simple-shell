#include "shell.h"

/**
 * hsh - my main shell loop
 * @data: the parameter and return data struct
 * @av: the argument vector
 *
 * Return: 0 for success, 1 for error, or an error code
 */
int hsh(info_t *data, char **av)
{
	ssize_t input_result = 0;
	int innerRet = 0;

	while (input_result != -1 && innerRet != -2)
	{
		releaseData(data); /* Cleanup 'data' */
		if (intmode(data)) /* Verify whether 'data' is involved */
			putin("$ "); /* Print the prompt, obtain input and save the result in 'input_result' */
		eputword(BUFFER_FLUSHER);
		input_result = getopt(data); /* Obtain input and save the result in 'input_result' */
		if (input_result != -1)
		{
			fixData(data, av);
			innerRet = locateInner(data); /* Find the inner built-in command and save the result in 'inner_ret' */
			if (innerRet == -1)
				lookForCmd(data);
		}
		else if (intmode(data))
			_putchar('\n');
		releaseData(data, 0); /* Free 'data' without freeing history */
	}
	genHistory(data); /* Generate history based on 'data' */
	releaseData(data, 1); /* Free 'data' including history */
	if (!intmode(data) && data->worth)
		exit(data->worth); /* Exit with 'data->exit_status' as the status */
	if (innerRet == -2)
	{
		if (data->digit_err == -1)
			exit(data->worth);
		exit(data->digit_err); /* Check 'data->digit_err' on exit */
	}
	return (innerRet);
}

/**
 * locateInner - Locate a builtin command
 * @data: data struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int locateInner(info_t *data)
{
	int i, inner_ret = -1;
	innerTable innerLib[] = {
		{"exit", exitShell},
		{"env", printMyEnv},
		{"help", displayHelp},
		{"history", displayHistory},
		{"setenv", setEnVar},
		{"unsetenv", removeEnvVar},
		{"cd", Dirchange},
		{"alias", mineAlias},
		{NULL, NULL}
	};

	for (i = 0; innerLib[i].type; i++)
	{
		if (_strcmps(data->argv[0], innerLib[i].type) == 0)
		{
			data->line_count++;
			inner_ret = innerLib[i].func(data); /* Call the matching inner_lib function and save the result in 'inner_ret' */
			break;
		}
	}
	return (inner_ret);
}

/**
 * lookForCmd - locate a command in PATH
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void lookForCmd(info_t *data)
{
	char *path = NULL;
	int i, k;

	data->path = data->argv[0]; /* Set 'data->path' to the first argument of 'data' */
	if (data->linecount_flag == 1) /* 'data->linecount_flag' is 1 */
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, k = 0; data->arg[i]; i++)
	{
		if (!our_believe(data->arg[i], " \t\n")) /* Check if 'data->arg[i]' contains any whitespace characters */
			k++;
	}
	if (!k)
		return;

	path = locate_path(data, findEnv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path; /* Update 'data->path' with 'path' */
		forkingCmd(data);
	}
	else
	{
		if ((intmode(data) || findEnv(data, "PATH=") || data->argv[0][0] == '/') && thisCmd(data, data->argv[0]))
			forkingCmd(data); /* Call "forking_cmd" function if certain criteria are met */
		else if (*(data->arg) != '\n')
		{
			data->worth = 127; /* Set 'data->exit_status' to 127 */
			display_err(data, "not found\n");
		}
	}
}

/**
 * forkingCmd - forks a new process to run a command
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void forkingCmd(info_t *data)
{
	pid_t child_pid;

	child_pid = fork(); /* Create a child process and save the process ID in 'child_pid' */
	if (child_pid == -1) /* fork() returns -1 (indicating an error) */
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}

	if (child_pid == 0) /* Child process */
	{
		/* Execute the command using execve() */
		if (execve(data->path, data->argv, getEnviron(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES) /* Error is due to permission denied */
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else /* Parent process */
	{
		/* Wait for the child process to end, then record the exit status in 'data->worth' */
		wait(&(data->worth));
		if (WIFEXITED(data->worth)) /* Child process terminated normally */
		{
			data->worth = WEXITSTATUS(data->worth);
			if (data->worth == 126)
				display_err(data, "Permission denied\n");
		}
	}
}

