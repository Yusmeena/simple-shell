#include "shell.h"

/**
* bufferEnter - this store or keep chained command in a buffer
* @data: argument struct
* @buffed: address of fender
* @len: address of length variable
*
* Return: number of byte that is read
*/

ssize_t bufferEnter(info_t *data, char **buffed, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if there nothing inside fender, fill it */
	{
		/* Free the memory allocated to data->cmd_buf */
		independ((void **)data->cmd_buf);
		free(*buffed);
		*buffed = NULL;
		signal(SIGINT, blockCtrlC); /* Set signal handler for SIGINT to blockCtrlC */
#if GETLINES
		r = getline(buffed, &len_p, stdin);
#else
		r = getNexLine(data, buffed, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffed)[r - 1] == '\n')
			{
				(*buffed)[r - 1] = '\0'; /* remove trailing newline */
				r--; /* Reduce the length of the string by 1 */
			}
			data->linecount_flag = 1;
			vanishComments(*buffed); /* Remove comments from the input line */
			towerPisa(data, *buffed, data->histcount++);
			/* if (strChr(*buffed, ';')) is this command chain ? */
			{
				*len = r; /* Set the length of the line */
				data->cmd_buf = buffed; /* Update data->cmd_buf to point to buffed */
			}
		}
	}
	return (r);
}

/**
* getEnter - collects a line ecluding the newline character
* @data: argument struct
*
* Return: number of bytes read
*/
ssize_t getEnter(info_t *data)
{
	static char *buffed; /* the ';' command chain fender */
	static size_t z, y, len;
	ssize_t r = 0;
	char **buffer_ps = &(data->arg), *q;

	_putchar(BUFFER_FLUSHER);
	r = bufferEnter(data, &buffed, &len);
	if (r == -1) /*EOF */
		return (-1);
	if (len)  /* we have commands remain in the chain fender */
	{
		y = z; /* ry fresh iterator to current buffed index */
		q = buffed + z; /* get pointer for return */

		valChar(data, buffed, &y, z, len);
		while (y < len) /* iterate to semicolon or end */
		{
			if (isChaindelimi(data, buffed, &y))
				break;
			y++;
		}

		z = y + 1; /* increment past nulled ';' */
		if (z >= len) /* reached end of fender? */
		{
			z = len = 0; /* reset index and len */
			data->cmdBufType = CMD_NORM;
		}

		*buffer_ps = q; /* pass back ointer to current command index */
		return (stringLen(q)); /* return len of current command */
	}

	*buffer_ps = buffed;
	return (r); /* return len of fender from getNextLine() */
}

/**
* readFender1 - This reads a fender
* @data: argument struct
* @buffed: fender
* @z: size
*
* Return: r
*/

ssize_t readFender1(info_t *data, char *buffed, size_t *z)
{
	ssize_t r = 0; /* variable to store output operation */

	if (*z)
		return (0); /* valur pointed to 'z' is non-zero, return 0 */
	/* Using maximum length of READ_BUFFER, read buffed from data->readingFd */
	r = read(data->readingFd, buffed, READ_BUFFER);
	if (r >= 0)
		*z = r;
	return (r);
}
/**
* getNexLine - retrives the next line of input from STDIN
* @data: argument struct
* @word: address of pointer to fender, preallocated or NULL
* @length: size of preallocated word fender if not NULL
*
* Return: s
*/
int getNexLine(info_t *data, char **word, size_t *length)
{
	static char buffed[READ_BUFFER];
	static size_t z, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *q = NULL, *new_p = NULL, *c;

	q = *word; /* Give 'q' the value that 'word' is pointing at */
	if (q && length)
		s = *length;
	if (z == len)
		z = len = 0; /* 'z' is equal to 'len', set both 'z' and 'len' to 0 */

	r = readFender1(data, buffed, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strChr(buffed + z, '\n');
	k = c ? 1 + (unsigned int)(c - buffed) : len;
	new_p = reallocateMem(q, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (q ? free(q), -1 : -1);

	if (s)
		concatenate_strings(new_p, buffed + z, k - z);
	else
		_copystring2(new_p, buffed + z, k - z + 1);

	s += k - z; /* Update 's' by adding the difference between 'k' and 'z' */
	z = k; /* Update 'z' with 'k' */
	q = new_p; /* Transfer 'new_p' to w 'q' */

	if (length)
		*length = s;
	*word = q; /* transfer 'q' to the value pounted to by 'word' */
	return (s);
}

/**
* blockCtrlC - blocks ctrl-C
* @sig_num: the signal number
*
* Return: void
*/
void blockCtrlC(__attribute__((unused))int sig_num)
{
	putin("\n"); /*output newline character will showed */
	putin("$ "); /* U should output the display symbol "$" */
	_putchar(BUFFER_FLUSHER);
}

