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

