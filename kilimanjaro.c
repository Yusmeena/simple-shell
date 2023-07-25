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

/**
* removeEnvVar - remove the environment variable shell
* @data: Struct entail impotant parameters. use to maintain constant function prototype
* Return: Always 0
*/
int removeEnvVar(info_t *data)
{
	int z;

	if (data->argc == 1) /* Check parameter count stored in "data" is equal to 1 */
	{
		eputin("Too few argument. \n");
		return (1); /* Return 1 to show an error condition */
	}
	for (z = 1; z <= data->argc; z++)
		/* Call the remove()" function with the cureent parameter from data */
		remEnv(data, data->argv[a]);

	return (0);
}

/**
* filEnvList - populated environment linked list
* @data: Stuct entaining important parameter. Used to maintain constant function prototype
* Return: Always 0
*/
int filEnvList(info_t *data)
{
	list_t *list = NULL;
	size_t z;
	/* Loop through "environ" araay until a null terminator is encounteered */
	for (z = 0; environ[z]; z++)
		add_node_finish(&list, environ[z], 0);
	data->env = list; /* Assign created "list" to "env" field in "data" structure */
	return (0);
}
