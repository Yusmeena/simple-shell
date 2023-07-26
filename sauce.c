#include "shell.h"

/**
 * initializeData - Initializes the info_t struct.
 * @data: Pointer to the struct address.
 */
void initializeData(info_t *data)
{
	/* Set the 'arg' member of 'data' to NULL */
	data->arg = NULL;
	/* Set the 'argv' member of 'data' to NULL */
	data->argv = NULL;
	/* Set the 'path' member of 'data' to NULL */
	data->path = NULL;
	/* Set the 'argc' member of 'data' to 0 */
	data->argc = 0;
}

/**
 * prepareData - Initializes the info_t struct.
 * @data: Pointer to the struct address.
 * @arg_vector: Argument vector.
 */
void prepareData(info_t *data, char **arg_vector)
{
	int i = 0;
	/* Set the 'fname' component of 'data' to the 'arg_vector's first element */
	data->fname = arg_vector[0];
	/* Verify that the 'arg' member of the 'data' is not NULL */
	if (data->arg)
	{
		/* 'arg' is divided into an array of strings using spaces & tabs as delimiters */
		data->argv = strSplit(data->arg, " \t");
		/* Check if 'argv' is still NULL after splitting 'arg' */
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdupsd(data->arg);
				data->argv[1] = NULL; /* Set the second element of 'argv' to NULL */
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		replaceAlias(data); /* Replace aliases where necessary */
		replaceVariables(data); /* Substitute variables as necessary */
	}
}

/**
 * releaseData - Frees info_t struct fields.
 * @data: Pointer to the struct address.
 * @all: True if freeing all fields.
 */
void releaseData(info_t *data, int all)
{
	freeStringArray(data->argv);
	data->argv = NULL;
	data->path = NULL;
	/* Make sure the 'all' argument is true */
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			freeList(&(data->env));
		if (data->history)
			freeList(&(data->history));
		if (data->alias)
			freeList(&(data->alias));
		freeStringArray(data->environ);
		data->environ = NULL;
		independ((void **)data->cmd_buf);
		/* Check if 'readingFd' member of 'data' is greater than 2 and */
		/* close the file descriptor */
		if (data->readingFd > 2)
			close(data->readingFd);
		_putchar(BUFFER_FLUSHER);
	}
}

