#include "shell.h"

/**
* *_copyString2 - this copy string
* @keeper: the destination string to copy to
* @place: the string source
* @num: number of characters to be copy
* Return: he string copied outcome
*/

int *_copyString2(char *keeper, char *place, int num)
{
	int z, y;
	char *s = keeper;

	z = 0;
	while (place[z] != '\0' && z < num - 1)
	{
		keeper[z] = place[z];
		z++;
	}
	if (z < num) /* instance where z is smaller than n, add NULL terminator */
	{
		y = z;
		while (y < num)
		{
			keeper[z] = '\0';
			y++;
		}
	}
	return (s);
}

/**
* *concatenateStrings2 - this join string or concatenation
* @keeper: the first string
* @place: the second string
* @num: the maximum number of bytes that will be used
* Return: the resulting concatenated or joined string
*/
char *concatenateStrings2(char *keeper, char *place, int num)
{
	int z, y;
	char *s = keeper;

	z = 0;
	y = 0;
	while (keeper[z] != '\0') /* locate the first string(keeper) end */
		z++;
	while (place[y] != '\0' && y < num)
	{
		keeper[z] = place[y]; /* char from place to keeper added */
		z++;
		y++;
	}
	if (y < num) /* if character are still present after NULL terminator add it */
		keeper[z] = '\0';
	return (s); /* return to original value of keeper */
}

/**
* *strChr - This searches or look for a character in a string
* @s: the string to be parsed
* @c: the character to be check for
* Return: pointer to memory area of the found character in the string (s)
*/
char *strChr(char *s, char c)
{
	do {
		if (*s == c)
			return (s); /* pointer back to detect character memory location */
	} while (*s++ != '\0');

	return (NULL); /* if string is not foumd then return to NULL */
}
