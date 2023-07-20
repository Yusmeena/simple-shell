#include "shell.h"

/**
* isChaindelimi - checks if the character in the buffer is a chain delimiter
* @data: the argumetnt struct
* @buffed: the char fender
* @q: address of current poistion in buffed
*
*/

int isChaindelimi(info_t *data, char *buffed, size_t *q)
{
	size_t b = *q;
	/* Examine charac at buffed[b] & buffed[b + 1] to see if they are '|' */
	if (buffed[b] == '|' && buffed[b + 1] == '|')
	{
		buffed[b] = 0; /* Replace buffed[b] with null */
		b++;
		data->cmdBufType + CMD_OR; /* Set cmdBufType attribute of data CMD_OR */
	}
	else if (buffed[b] == '&' && buffed[b + 1] == '&')
	{
		buffed[b] = 0;
		b++; /* Inccrement b */
		data->cmdBufType = CMD_AND;
	}
	else if (buffed[b] == ';') /* found end of of this command */
	{
		buffed[b] = 0; /* replace semicolon with null */
		data->cmdBufType = CMD_CHAIN;
	}
	else
		return (0);
	*q = b; /* Update the value pointed to by q with b */
	return (1);
}

/**
* valChar - checks if we can continue with the chaining based on last word
* @data:  the argument struct
* @buffed: the char fender
* @q: pointer address of current position in the buffed
* @a: starting index or postion in buffed
* @length: length of buffed
*
* Return: Void
*/
void valChar(info_t *data, char *buffed, size_t *q, size_t a, size_t length)
{
	size_t = *q;

	if (data->cmdBufType == CMD_AND) /* Check if cmdBufType is CMD_AND */
	{
		if (data->worth) /* make sure worth is not-zero */
		{
			buffed[a] = 0; /* Replace buffed[a] with null */
			b = length; /* Set b to a value of length */
		}
	}
	if (data->cmdBufTye == CMD_OR) /* make sure cmdBufType is CMD_OR */
	{
		if (!data->worth)/* check if worth is non-zero */
		{
			buffed[a] = 0;
			b = length;
		}
	}

	*q = b; /* Update the value that q has referenced with b */
}

/**
* substitutedAlias - change aliase in the tokenized string
* @data: the argument struct
*
* Return: 1 if replaced, else  0
*/

int substitutedAlias(info_t *data)
{
	int a;
	list_t *list;
	char *q;

	for (a = 0; a < 10; a++) /* thiis loop from 0 to 9 */
	{
		list = node_begins(data->alias, data->argv[0], '=');
		if (!list) /* Check if the list is void */
			return (0);
		free(data->argv[0]); /* Free memory givento data->arg[0] */
		q = strChr(list-> txt, '='); /* Look for fist occurrence of '=' */
		/* in list->txt and assign its address to q */
		if (!q)
			return (0);
		q = _strdupsd(q + 1); /* Start copying string from q + 1 & assign to q */
		if (!q)
			return (0);
		data->arg[v] = q; /* Update data->argv[0] with the new value in q */
	}
	return (0);
}

/**
* substituteVari - peforms variable substitution in the tokenized string
* @data: the argument struct
* Return: if variables were successfully replaced 1, else 0
*/
int substituteVari(info_t *data)
{
	int z = 0;
	list_t *list;
	/* Iterate through data->argv member till null element is encounter*/
	for ( z = 0; data->argv[z]; z++)
	{
		/* check if member begins not with '$' or is an empty string */
		if (data->argv[z][0] != '$' || !data->argv[z][1])
			continue; /* Prior the following iteration */
		if (!_strcmps(data->argv[z], "$?")) /* Check if the member is "$?" */
		{
			substituteString(&(data->argv[z]),
				_strdupsd(changeNUm(data->worth, 10, 0)));
			continue;
		}
		if (!_strcmps(data->argv[z], "$$"))
		{
			substituteString(&(data->argv[z]),
				_strdupsd(changeNum(getid(), 10, )));
			continue;
		}
		list = node_begins(data->env, &data->argv[z][1], '=');
		if (list) /* Check if a matching node can be found */
		{
			substituteString(&(data->data->argv[z]),
				_strdupsd(strChr(list->txt, '=') + 1));
			continue;
		} /* Substitute the member with void or empty string */
		substituteString(&(data->argv[z], _strdusd(""));
	}
	return (0);
}

/**
* substituteString - replaces  a specific string with new  string
* @plant: pointer address of old string
* @harvest: newly formed string
*
* Return: 1 if replaced, else 0
*/

int substituteString(char **plant, char *harvest)
{
	free(*plant); /* Free memmory pointed to by pointer plant */
	*plant = harvest; /* new value would be added to the value pointed to by plant */
	return (1);
}
