#include "shell.h"

/**
 * errAtoi - Convert a string to an integer
 * @str: The string to be converted
 *
 * Return: 0 if no numbers in the string, converted number otherwise
 *       -1 on error
 */
int errAtoi(char *str)
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
 * display_err - Output an error message
 * @data: The parameter and return data struct
 * @errorMsg: String containing the specified error type
 */
void display_err(info_t *data, char *estr)
{
	eputin(data->fname); /* Print the file name found in data->fileName */
	eputin(": "); /* Print a colon and a space */
	printDD(data->line_count, STDERR_FILENO); /* Output the line count that is recorded in data->lineCount */
	eputin(": ");
	eputin(data->argv[0]); /* Display the first argument from data->argv */
	eputin(": ");
	eputin(estr); /* Print the supplied error message */
}

/**
 * printDD - Display a decimal (integer) number in base 10
 * @input: The number to be displayed
 * @fd: The file descriptor to write the output to
 *
 * Return: The number of characters printed
 */
int printDD(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = eputword;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + current / index);
			count++;
		}
		current %= index;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * changeNUm - Converts a number to a string representation
 * @num: Number to be converted
 * @base: Base for conversion
 * @flags: Argument flags
 *
 * Return: String
 */
char *changeNUm(long int num, int base, int flags)
{
	static char *array;
	static char fender[50];
	char ivan = 0;
	char *word;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		ivan = '-';
	}

	array = flags & CONVERT_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	word = &fender[49];
	*word = '\0';

	do	{
		*--word = array[n % base];
		n /= base;
	} while (n != 0);

	if (ivan)
		*--word = ivan;

	return (word);
}

/**
 * vanishComments - Replaces first instance of '#' with '\0'
 * @buffer: Address of the string to be changed
 */
void vanishComments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}

