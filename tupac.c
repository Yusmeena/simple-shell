#include "shell.h"
/**
 * main - Entry point of the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
	info_t data[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
	    "add $3, %0" /* Add 3 to the value in the register */
	    : "=r"(fd) /* Output constraint: assign the modified value back to "fd" */
	    : "r"(fd)); /* Input constraint: use the value of "fd" as input */

	if (argc == 2) /* Check if the number of command-line arguments is 2 */
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1) /* Check if opening the file encountered an error */
		{
			if (errno == EACCES) /* Check if the error is due to access permissions */
				exit(126);
			if (errno == ENOENT) /* Check if the error is due to the file not found */
			{
				eputin(argv[0]); /* Print the name of the program */
				eputin(": 0: Can't open "); /* Print error message */
				eputin(argv[1]); /* Print the name of the file */
				eputword('\n'); /* Print a newline character */
				eputword(BUFFER_FLUSHER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readingFd = fd;
	}

	filEnvList(data); /* Fill the environment list in the data structure */
	cramHis(data); /* Compress the history entries in the data structure */
	hsh(data, argv);
	return (EXIT_SUCCESS);
}
