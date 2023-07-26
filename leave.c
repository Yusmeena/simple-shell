#include "shell.h"

/**
 * _copystring - copies string.
 * @dest: The destination the copies string will go.
 * @src: The source for the string.
 * @n: The number of characters that are supposed to be copied.
 * Return: The resulting copied string.
 */
char *_copystring(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * concatenate_strings - this here performs string concatenation.
 * @dest: first srting.
 * @src: second string.
 * @n: The maximum number of bytes which are gonna be used.
 * Return: The resulting concatenated string.
 */
char *concatenate_strings(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0') /* locate first string(destina) end */
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
		if (j < n)
		dest[i] = '\0';
		return (s);
}

/**
 * *strChr - Searches for a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: Pointer to the memory area of the found character in the string (s).
 */
char *strChr(char *s, char c)
{
	do {
		if (*s == c)
		return (s);
	} while (*s++ != '\0');
	return (NULL);
}

