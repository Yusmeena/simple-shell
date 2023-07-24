#include "shell.h"

/**
* copyString1 - copies a string
* @keeper: the keeper
* @place - the source
*
* Return: pointer to the end point
*/
char *copyString1(char *kepper, char *place)
{
	int z = 0;
	/* Look for exceptional circumstances, for example when the destination and end */
	/* the location are similar or the location is NULL */
	if (keeper == place || place == 0)
		return (keeper);
	/* Duplicate charactersfrom one place to another till */
	/* the NULL terminator is reach */
	while (keeper[z])
	{
		kepper[z] = place[z];
		z++;
	}
	keeper[z] = 0; /* the target string should has a null terminator added */
	return (keeper);
}


/**
* *_strdupsd - this duplicates or clone a string
* @txt: the string to be clone or duplicate
*
* Return: pointer to the clone or duplicated string
*/
char *_strdupsd(const char *txt)
{
	int length = 0;
	char *ret;
	/* be sure string entered is NULL */
	if (txt == NULL)
		return (NULL);
	/* This check entered string's length */
	while (*txt++)
		length++;
	/* Memory will be set aside for duplicated string */
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	/*Reverse-transfer entered string's characters to replicate or clone string */
	for (length++; length --;)
		ret[length] = *--txt;
	return (ret);
}

/**
* putin - display or print input or entered string
* @txt: the string to be displayed or printed
*
* Return : Nothing
*/
void putin(char *txt)
{
	int z = 0;

	if (!txt) /* be sure entered or input string is NULL */
		return;
	while (txt[z] != '\0')
	{
		_putchar(txt[z]); /* character to be diaplayed */
		z++;
	}
}
 
/**
* _putchar - this write character c to stdout
* @c: The character to display
*
* Return: On success 1
*/
int _putchar( char c)
{
	static int z;
	static char buffed[WRITE_BUFFER];
	/* Confirm the charater's flushing behavior or whether the buffer is full */
	if (c == BUFFER_FLUSHER || z >= WRITE_FLUSHER)
	{
		write(1, buffed, z); /* To standard output, send characters in the buffer */
		z = 0;
	}
	/* The character should not be a buffer flusher, si verify*/
	if (c != BUFFER_FLUSHER)
		buffed[z++] = c; /* Fill the buffer with the character */
	return (1);
}
