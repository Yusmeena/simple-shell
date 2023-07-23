#include "custom_shell.h"

/**
 * getStrLength - Get the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
int getStrLength(char *str)
{
	int length = 0;

	if (!str) /* Check if input string is empty or NULL */
		return (0);

	while (*str++) /* Iterate through the characters of the string */
		length++; /* Increment length for each character */

	return (length);
}

/**
 * compareStrings - Perform lexicographic comparison of two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: Negative value if str1 < str2, positive value if str1 > str2,
 *         zero if str1 == str2.
 */
int compareStrings(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);

		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * startsWith - Check if the 'str' starts with 'substr'.
 * @str: The input string to search.
 * @substr: The substring to find.
 *
 * Return: Address of the next character of 'str' or NULL if no match found.
 */
char *startsWith(const char *str, const char *substr)
{
	while (*substr) /* Iterate through the characters of the substring */
	{
		if (*substr++ != *str++)
			return (NULL); /* If characters are different, return NULL */
	}

	return ((char *)str); /* Return the address of the next character of 'str' */
}

/**
 * concatenateStrings - Concatenate two strings.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: Pointer to the destination buffer.
 */
char *concatenateStrings(char *dest, char *src)
{
	char *result = dest;

	while (*dest) /* Move the destination pointer to the end of the buffer */
		dest++;

	while (*src) /* Copy characters from source to destination buffer */
		*dest++ = *src++;

	*dest = *src; /* Null-terminate the concatenated string */
	return (result); /* Return the pointer to the destination buffer */
}

