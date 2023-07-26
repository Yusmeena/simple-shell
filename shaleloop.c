#include "shell.h"

/**
 * main_shell_loop - my main shell loop
 * @data: the parameter and return data struct
 * @av: the argument vector
 *
 * Return: 0 for success, 1 for error, or an error code
 */
int main_shell_loop(info_t *data, char **av)
{
	ssize_t input_result = 0;
	int inner_ret = 0;

	while (input_result != -1 && inner_ret != -2)
	{
		clean_data(data); /* Cleanup 'data' */
		if (involve_data(data)) /* Verify whether 'data' is involved */
			putin("$ "); /* Print the prompt, obtain input and save the result in 'input_result' */
		eputword(BUFFER_FLUSHER);
		input_result = get_input(data); /* Obtain input and save the result in 'input_result' */
		if (input_result != -1)
		{
			fix_data(data, av);
			inner_ret = locate_inner(data); /* Find the inner built-in command and save the result in 'inner_ret' */
			if (inner_ret == -1)
				look_for_cmd(data);
		}
		else if (involve_data(data))
			_putchar('\n');
		free_data(data, 0); /* Free 'data' without freeing history */
	}
	generate_history(data); /* Generate history based on 'data' */
	free_data(data, 1); /* Free 'data' including history */
	if (!involve_data(data) && data->exit_status)
		exit(data->exit_status); /* Exit with 'data->exit_status' as the status */
	if (inner_ret == -2)
	{
		if (data->digit_err == -1)
			exit(data->exit_status);
		exit(data->digit_err); /* Check 'data->digit_err' on exit */
	}
	return (inner_ret);
}

/**
 * locate_inner - Locate a builtin command
 * @data: data struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int locate_inner(info_t *data)
{
	int i, inner_ret = -1;
	inner_table inner_lib[] = {
		{"exit", shell_exit},
		{"env", print_my_env},
		{"help", show_help},
		{"history", display_history},
		{"setenv", set_env_var},
		{"unsetenv", remove_env_var},
		{"cd", change_dir},
		{"alias", mine_alias},
		{NULL, NULL}
	};

	for (i = 0; inner_lib[i].type; i++)
	{
		if (_strcmps(data->argv[0], inner_lib[i].type) == 0)
		{
			data->line_count++;
			inner_ret = inner_lib[i].func(data); /* Call the matching inner_lib function and save the result in 'inner_ret' */
			break;
		}
	}
	return (inner_ret);
}

/**
 * look_for_cmd - locate a command in PATH
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void look_for_cmd(info_t *data)
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
		if (!we_believe(data->arg[i], " \t\n")) /* Check if 'data->arg[i]' contains any whitespace characters */
			k++;
	}
	if (!k)
		return;

	path = locate_path(data, find_env(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path; /* Update 'data->path' with 'path' */
		forking_cmd(data);
	}
	else
	{
		if ((involve_data(data) || find_env(data, "PATH=") || data->argv[0][0] == '/') && this_cmd(data, data->argv[0]))
			forking_cmd(data); /* Call "forking_cmd" function if certain criteria are met */
		else if (*(data->arg) != '\n')
		{
			data->exit_status = 127; /* Set 'data->exit_status' to 127 */
			display_err(data, "not found\n");
		}
	}
}

/**
 * forking_cmd - forks a new process to run a command
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void forking_cmd(info_t *data)
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
		if (execve(data->path, data->argv, get_environ(data)) == -1)
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
		/* Wait for the child process to end, then record the exit status in 'data->exit_status' */
		wait(&(data->exit_status));
		if (WIFEXITED(data->exit_status)) /* Child process terminated normally */
		{
			data->exit_status = WEXITSTATUS(data->exit_status);
			if (data->exit_status == 126)
				display_err(data, "Permission denied\n");
		}
	}
}

