#include "shell.h"

/**
 * list_len - determines the length of a linked list
 * @h: pointer to the first node of the list
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	/* Loop while 'h' is not NULL (assuming 'h' is a pointer to a linked list node) */
	size_t count = 0;

	while (h)
	{
		h = h->next; /* Move to the next node in the linked list */
		count++; /* Increase the count */
	}
	return (count);
}

/**
 * list_to_strings - returns an array of strings from the list->txt
 * @head: pointer to the first node of the list
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *list = head;
	size_t list_size = list_len(head), index;
	char **strings_array;
	char *text;

	if (!head || !list_size)
		return (NULL);

	strings_array = malloc(sizeof(char *) * (list_size + 1));
	if (!strings_array) /* Memory allocation fails, return NULL */
		return (NULL);

	for (index = 0; list; list = list->next, index++) /* Loop through the linked list */
	{
		text = malloc(list_len(list->txt) + 1);
		if (!text)
		{
			for (size_t i = 0; i < index; i++)
				free(strings_array[i]);
			free(strings_array);
			return (NULL);
		}

		text = copyString(text, list->txt); /* Copy content of 'list->txt' to 'text' */
		strings_array[index] = text; /* Assign 'text' to the current position in 'strings_array' */
	}
	strings_array[index] = NULL; /* Set the last element of 'strings_array' to NULL */
	return (strings_array);
}

/**
 * displayList - displays all elements of a list_t linked list
 * @h: pointer to the first node of the list
 *
 * Return: size of list
 */
size_t displayList(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		putin(changeNUm(h->num, 10, 0)); /* Print the modified value of 'h->num' */
		putchar(':'); /* Print a colon character */
		putchar(' '); /* Print a space character */
		putin(h->txt ? h->txt : "(nil)");
		putin("\n"); /* Print a newline character */
		h = h->next; /* Move to the next node in the linked list */
		count++;
	}
	return (count);
}

/**
 * node_begins - returns a node whose string starts with prefix
 * @list: pointer to the list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or null
 */
list_t *node_begins(list_t *list, char *prefix, char c)
{
	char *q = NULL;

	while (list)
	{
		/* Check if 'list->txt' starts with 'prefix' and assign the result to 'q' */
		q = beginWith(list->txt, prefix);
		if (q && ((c == -1) || (*q == c)))
			/* 'q' is not NULL & either 'c' is -1 or the first character of 'q' matches 'c' */
			return (list);
		list = list->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node in a list
 * @head: pointer to the list head
 * @list: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *list)
{
	size_t index = 0;

	while (head)
	{
		if (head == list) /* 'head' is equal to 'list', return the current count 'index' */
			return (index);
		head = head->next;
		index++;
	}
	return (-1); /* Return -1 if the loop finishes without finding 'list' */
}

