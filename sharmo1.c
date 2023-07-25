#include "shell.h"

/**
 * printInput - Displays the input string to the standard error.
 * @input: The string to be displayed.
 * Return: None.
 */
void printInput(char *input)
{
	int i = 0;

	if (!input) /* Check if 'input' is null or empty */
		return;

	/* Iterate through 'input' array until the null terminator is reached */
	while (input[i] != '\0')
	{
		printCharacter(input[i]);
		i++; /* Increment counter variable 'i' to move to the next element of 'input' */
	}
}

/**
 * printCharacter - Outputs the character 'c' to the standard error.
 * @c: The character to be outputted.
 * Return: On success 1.
 * On error, returns -1 and sets errno accordingly.
 */
int printCharacter(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER];

	/* If the character is a BUFFER_FLUSHER or the buffer is full */
	if (c == BUFFER_FLUSHER || index >= WRITE_BUFFER)
	{
		write(2, buffer, index);
		index = 0; /* Reset the buffer position to 0 */
	}

	if (c != BUFFER_FLUSHER)
		buffer[index++] = c;

	return 1; /* Return 1 to indicate success or completion of the function */
}

/**
 * writeToFD - Writes the character 'c' to the specified file descriptor 'fd'.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 * Return: On success 1.
 * On error, returns -1 and sets errno accordingly.
 */
int writeToFD(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUFFER];

	if (c == BUFFER_FLUSHER || index >= WRITE_BUFFER)
	{
		/* Write the contents of the buffer to the specified file descriptor */
		write(fd, buffer, index);
		index = 0; /* Reset the buffer position to 0 */
	}

	if (c != BUFFER_FLUSHER)
		buffer[index++] = c; /* Keep the character in the buffer and increment buffer position */

	return 1;
}

/**
 * printToFd - Writes the input string 'str' to the specified file descriptor 'fd'.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters written.
 * On error, returns -1 and sets errno accordingly.
 */
int printToFd(char *str, int fd)
{
	int count = 0;

	if (!str) /* Check if 'str' is null or empty, return 0 */
		return 0;

	while (*str) /* Process characters of 'str' until a null terminator is encountered */
	{
		/* Call the 'writeToFD' function with the current character of 'str',
		   increment the pointer, and add the result to 'count' */
		count += writeToFD(*str++, fd);
	}

	return count;
}

