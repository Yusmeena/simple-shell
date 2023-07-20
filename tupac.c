#include "shell.h"

/**
 * main - Entry point of the custom shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
    ShellInfo shell_data[] = { SHELL_INFO_INIT };
    int file_descriptor = 2;

    /* Add 3 to the value in the "file_descriptor" variable */
    asm ("mov %1, %0\n\t"
         "add $3, %0"
         : "=r" (file_descriptor) /* Output constraint: assign the modified value back to "file_descriptor" */
         : "r" (file_descriptor)); /* Input constraint: use the value of "file_descriptor" as input */

    if (argc == 2) /* Check if the number of command-line arguments is 2 */
    {
        file_descriptor = open(argv[1], O_RDONLY);
        if (file_descriptor == -1) /* Check if opening the file encountered an error */
        {
            if (errno == EACCES) /* Check if the error is due to access permissions */
                exit(126);
            if (errno == ENOENT) /* Check if the error is due to the file not found */
            {
                print_error_name(argv[0]); /* Print the name of the program */
                print_error(": 0: Can't open "); /* Print error message */
                print_error(argv[1]); /* Print the name of the file */
                print_error_word('\n'); /* Print a newline character */
                print_error_word(BUFFER_FLUSHER);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        shell_data->reading_fd = file_descriptor;
    }

    fill_environment_list(shell_data); /* Fill the environment list in the shell_data structure */
    compress_history_entries(shell_data); /* Compress the history entries in the shell_data structure */
    custom_shell(shell_data, argv); /* Call the custom shell function */
    return (EXIT_SUCCESS);
}

