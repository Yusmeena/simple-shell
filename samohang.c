#include "shell.h"

/**
 * convertStringToInt - Convert a string to an integer
 * @str: The string to be converted
 *
 * Return: 0 if no numbers in the string, converted number otherwise
 *       -1 on error
 */
int convertStringToInt(char *str)
{
	int index = 0;
	unsigned long int answer = 0;

	if (*str == '+')
		str++; /* TODO: why does this make main return 255? */

	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9') /* Make sure the character is a digit */
		{
			answer *= 10;
			answer += (str[index] - '0'); /* Convert the character to the linked number value */
			if (answer > INT_MAX)
				return (-1); /* Return -1 to indicate overflow */
		}
		else
			return (-1);
	}
	return (answer);
}

/**
 * printError - Output an error message
 * @data: The parameter and return data struct
 * @errorMsg: String containing the specified error type
 */
void printError(info_t *data, char *errorMsg)
{
	eputin(data->fileName); /* Print the file name found in data->fileName */
	eputin(": "); /* Print a colon and a space */
	printDecimal(data->line_count, STDERR_FILENO); /* Output the line count that is recorded in data->lineCount */
	eputin(": ");
	eputin(data->argv[0]); /* Display the first argument from data->argv */
	eputin(": ");
	eputin(errorMsg); /* Print the supplied error message */
}

/**
 * printDecimal - Display a decimal (integer) number in base 10
 * @input: The number to be displayed
 * @fd: The file descriptor to write the output to
 *
 * Return: The number of characters printed
 */
int printDecimal(int input, int fd)
{
	int (*putCharFunc)(char) = _putchar;
	int index, count = 0;
	unsigned int absoluteValue, current;

	if (fd == STDERR_FILENO)
		putCharFunc = eputword;

	if (input < 0)
	{
		absoluteValue = -input;
		putCharFunc('-');
		count++;
	}
	else
		absoluteValue = input;

	current = absoluteValue;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absoluteValue / index)
		{
			putCharFunc('0' + current / index);
			count++;
		}
		current %= index;
	}
	putCharFunc('0' + current);
	count++;

	return (count);
}

/**
 * changeNumberToString - Converts a number to a string representation
 * @num: Number to be converted
 * @base: Base for conversion
 * @flags: Argument flags
 *
 * Return: String
 */
char *changeNumberToString(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char negative = 0;
	char *word;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		negative = '-';
	}

	array = flags & CONVERT_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	word = &buffer[49];
	*word = '\0';

	do	{
		*--word = array[n % base];
		n /= base;
	} while (n != 0);

	if (negative)
		*--word = negative;

	return (word);
}

/**
 * removeComments - Replaces first instance of '#' with '\0'
 * @buffer: Address of the string to be changed
 */
void removeComments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}

