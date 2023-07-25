#include "shell.h"

/**
* showHistory - show the history list
* @data: Argument struct
* Return: Always 0
*/
int showHistory(info_t *data)
{
	showList(data->history); /* Invoke a function to display history list */
	return (0); /* If execution was executed, return 0 */
}

/**
* unsetAlias - sets an alias to string
* @data: Parameter struct
* @txt: the string alias
*
* Return: Always 0 on success, 1 on error
*/

int unsetAlias(info_t *data, char *txt)
{
	char *q, c;
	int ret;
	/* Determine where the equal sign is located in the alias string */
	q = strChr(txt, '=');
	if (!q)
		return (1);
	c = *q; /* Save the character next to the equals sign */
	*q = 0; /* The alias name should be separated from the equal */
	/* sign by null terminator */
	ret = delNodeatIndex(&(data->alias),
		get_node_index(data->alias, node_begins(data->alias, txt, -1)));
	/* Eliminate the alias node from the list of aliases */
	*q = c;
	return (ret);
}

/**
* setAlias1 - assigns an alias to a string
* @data: argument struct
* @txt: the string alias
*
* Return: Always 0 if success, 1 on error
*/
int setAlias1(info_t *data, char *txt)
{
	char *q;
	/*This determine where tte equal sign is located in the alias string */
	q = strChr(txt, '=');
	if (!q)
		return (1);
	if (!*++q) /* Whenever there is null terminator folloes an equal sign */
		return (unsetAlias(data, txt)); /* Remove alias the alias */
	/* Return the output after adding the alias to the alias list */
	return (add_node_finish(&(data->alias), txt, 0) == NULL);
}

/**
* showAlias - Print an alias string
* @list: the alias list
*
* Return: Always 0 on success, 1 on error
*/
int showAlias(list_t *list)
{
	char *q = NULL, *z = NULL;

	if (list)
	{
		q = strChr(list->txt, '=');
		/* alias name should show before equal sign */
		for (z = list->txt; z <= q; z++)
			_putchar(*z);
		_putchar('\''); /* this signify the start of the alias value, show a signle qoute */
		putin(q + 1); /* show the value alias after the equal sign */
		putin("'\n"); /* finish the output from alias, show neline character */
		return (0);
	}
	return (1); /* if tge alias can't be identified or show, return 1 */
}
int ourAlias(info_t *data)
{
	int z = 0;
	char *q = NULL;
	list_t *list = NULL;

	if (data->argc == 1) /* Confirm that no parameters are given */
	{
		list = data->alias;
		while (list)
		{
			showAlias(list); /* Show the list of aliases, one by one */
			list = list->next;
		}
		return (0); /* If the executed successsful, return 0 */
	}
	/* Analyze each parameter */
	for (z = 1; data->argv[z]; z++)
	{
		/* Confirm the equal sign is present in the parameter */
		q = strChr(data->argv[z], '=');
		if (q)
			setAlias1(data, data->argv[z]); /* Change the alias */
		else
			/* Pulish the unique alias */
			showAlias(node_begins(data->alias, data->argv[z], '='));
	}

	return (0);
}

