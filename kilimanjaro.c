#include "shell.h"

/**
* showMyEnv - shows the current environment
* @data: Struct argument
* Return: Always 0
*/
int showMyEnv(info_t data)
{
	showListString(data->env); /* Show the contents of the "env" List */
	return (0); /* Return 0 to indicate successful execution */
}

/**
* findEnv - get the value of an enviro variable
* @data: Struct argument
* @name: env var name
*
* Return:
*/

char *findEnv(info_t *data, const char *name)
{
	list_t *list = data->env;
	char *q;

	while (list) /* loop through the list till it reaches end (NULL) */
	{
		q = beginWith(list->txt, name);
		if (q && *q) /* "q" is not NULL & value points to is not null terminator */
		list = list->next;
	}
	return (NULL);
}
/**
* setEnvVar1 - Initialize a new environment variable or modify existing or present one
* @data: Struct argument
* Return: Aleays 0
*/
int setEnvVar1(info_t *data)
{
	if (data->argc != 3)
	{
		/* Show an error message meaning invalid number of parameter */
		eputin("Incorrect number of arguments\n");
		return (0); /* Return 1 to show an error situation*/
	}
	if (fixEnv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}
