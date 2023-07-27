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
#define BUFFER_FLUSHER -1
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

typedef struct takeData
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int digit_err;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int worth;

	char **cmd_buf;
	int cmdBufType;
	int readingFd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0,NULL, \
	0, 0, 0}

/**
*struct builtin - contain a builtin string and related function
* @type: the builtin command onOff
* @func: the functiom
*/
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} innerTable;

int hsh(info_t *, char **);
int locateInner(info_t *);
void lookForCmd(info_t *);
void forkingCmd(info_t *);
int thisCmd(info_t *, char *);
char *duplicateSubstring(char *, int, int);
char *locate_path(info_t *, char *, char *);
int roundHsh(char **);
void eputin(char *);
int eputword(char);
int putFd(char c, int fd);
int putsFdk(char *txt, int fd);
int stringLen(char *);
int _strcmps(char *, char *);
char *beginWith(const char *, const char *);
char *strConcat(char *, char *);
char *copyString(char *, char *);
char *_strdupsd(const char *);
void putin(char *);
int _putchar(char);
char *_copystring2(char *, char *, int);
char *concatenate_strings(char *, char *, int);
char *strChr(char *, char);
char **strSplit(char *, char *);
char **strSplited1(char *, char);
char *fillMem(char *, char, unsigned int);
void freeStrArray(char **);
int independ(void **word);
void *reallocateMem(void *, unsigned int, unsigned int);
int intmode(info_t *);
int our_believe(char, char *);
int isLetter(int);
int convertToIntger(char *);
int errAtoi(char *);
void display_err(info_t *, char *);
int printDD(int, int);
char *changeNUm(long int, int, int);
void vanishComments(char *);
int exitShell(info_t *);
int Dirchange(info_t *);
int displayHelp(info_t *);
int displayHistory(info_t *);
int mineAlias(info_t *);
ssize_t getEnter(info_t *);
int getNexLine(info_t *, char **, size_t *);
void blockCtrlC(int);
void initializeData(info_t *);
void prepareData(info_t *, char **);
void releaseData(info_t *, int);
char *findEnv(info_t *, const char *);
int printMyEnv(info_t *);
int setEnVar(info_t *);
int removeEnvVar(info_t *);
int filEnvList(info_t *);
char **getEnviron(info_t *);
int remEnv(info_t *, char *);
int fixEnv(info_t *, char *, char *);
char *get_history_file(info_t *data);
int genHistory(info_t *data);
int cramHis(info_t *data);
int towerPisa(info_t *data, char *buffed, int linecount);
int numKimbad(info_t *data);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_finish(list_t **, const char *, int);
size_t showListString(const list_t *);
int delNodeatIndex(list_t **, unsigned int);
void freeList(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t displayList(const list_t *);
list_t *node_begins(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int isChaindelimi(info_t *, char *, size_t *);
void valChar(info_t *, char *, size_t *, size_t, size_t);
int substitutedAlias(info_t *);
int substituteVari(info_t *);
int substitutedString(char **, char *);

#endif

