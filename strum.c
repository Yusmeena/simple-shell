#include "shell.h"

/**
 * isExecutableCommand - checks if a file is an executable command
 * @data: the data struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutableCommand(info_t *data, char *path)
{
	struct stat st;

	(void)data; /* Turn off the "data" unused parameter alert */
	if (!path || stat(path, &st)) /* If 'path' is NULL or 'stat' fails */
		return (0);

	if (st.st_mode & S_IFREG) /* Regular file is indicated by file mode in 'st' */
	{
		return (1);
	}
	return (0);
}

/**
 * duplicateSubstring - duplicates characters from a substring
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to the duplicated substring
 */
char *duplicateSubstring(char *pathstr, int start, int stop)
{
	static char buffed[1024];
	int a = 0, k = 0;

	for (k = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':') /* Character at 'pathstr[a]' is not ':' */
			buffed[k++] = pathstr[a]; /* Copy character to 'buffed' and increment 'k' */
	buffed[k] = '\0';
	return (buffed);
}

/**
 * findCommandInPath - Locates a command in the PATH string
 * @data: the data struct
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of the command if found or NULL
 */
char *findCommandInPath(info_t *data, char *pathstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	/* If 'cmd' has a length greater than 2 and starts with "./" */
	if ((stringLen(cmd) > 2) && beginWith(cmd, "./"))
	{
		if (isExecutableCommand(data, cmd)) /* Verify "cmd" corresponds to a legit command */
			return (cmd);
	}

	while (1) /* Loop indefinitely */
	{
		/* End of 'pathstr' is reached or ':' delimiter is found */
		if (!pathstr[a] || pathstr[a] == ':')
		{
			/* Utilizing "curr_pos" and "a," separate the substring from "pathstr" */
			/* store it in "path" */
			path = duplicateSubstring(pathstr, curr_pos, a);
			if (!*path) /* Path is an empty string */
				strConcat(path, cmd);
			else
			{
				strConcat(path, "/");
				strConcat(path, cmd);
			}

			if (isExecutableCommand(data, path)) /* Verify 'path' relates to a valid command */
				return (path);

			if (!pathstr[a]) /* End of 'pathstr' is reached */
				break;

			curr_pos = a; /* Put the current position in 'curr_pos' */
		}
		a++;
	}
	return (NULL);
}

