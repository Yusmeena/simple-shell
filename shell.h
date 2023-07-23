#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER 1024
#define WRITE_BUFFER 10224
#define VBUFFER_FLUSHER -1
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CONVERT_LOWER 1
#define CONVERT_UNSIGNED 2
#define GETLINES 0
#define JIST_FILED	".simple_shell_history"
#define JIST_OVERFLOW 4096

extern char **environ;

/**
* struct listNode - string linked list
* @num: the number in field
* @txt: a string
* @next: points to the next line
*/
typedef struct listNode
{
	int num;
	char *txt;
	struct listNode *next;
} list_t;

/**
* struct takeData - holds simulated parameters to pass into a function to make it a consistent function pointer structure
* @arg: a string got from getline with parameters
* @line_count: this count error
* @argv: an array of strings collected from arg
* @path: a string place for the right now cmf
* @argc: a parameter count
* @digit_err: the error code value used to exit()s in shell
* @linecount_flag: if count this line of input, if not left alone
* @environ: custom changed copy of environment from LL env
* @env_changed: on if environ was changed
* @history: the history list within the shell
* @fname: filename, simple
* @alias: the alias list within the current shell
* @readingFd: the fd frkm the read line input
* @env: linked list local copy of environment of computer
* @worth: the return value of the last executed command
* @cmd_buf: address of pointer to cmd_buf, on if chaining
* @cmdBufType: CMD_type ||, && ;
* @histcount: the history line number count
*/
