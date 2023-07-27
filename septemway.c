#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to the head of the list
 * @text: text field of the node
 * @num: list index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *text, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t)); /* allocate memory for new node */
	if (!new_head)
		return (NULL);
	fillMem((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (text)
	{
		new_head->txt = _strdupsd(text);
		if (!new_head->txt)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head; /* Set new node's 'next' pointer to the current head */
	*head = new_head; /* Update the head pointer to the new node */
	return (new_head);
}

/**
 * add_node_finish - adds a node to the end of the list
 * @head: address of pointer to the head of the list
 * @text: text field of the node
 * @num: list index used by history
 *
 * Return: size of list
 */
list_t *add_node_finish(list_t **head, const char *text, int num)
{
	list_t *new_node, *list;

	if (!head) /* make sure head pointer is not NULL */
		return (NULL);

	list = *head; /* list should be assigned the head pointer's value */
	new_node = malloc(sizeof(list_t)); /* allocate memory for new node */
	if (!new_node)
		return (NULL);

	fillMem((void *)new_node, 0, sizeof(list_t));
	new_node->num = num; /* set new node's "num" value */

	if (text)
	{
		/* 'text' should be duplicated and assigned to 'new_node->txt' */
		new_node->txt = _strdupsd(text);
		if (!new_node->txt)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (list) /* make sure list is not empty */
	{
		while (list->next) /* Navigate to the end of the list */
			list = list->next;
		list->next = new_node;
	}
	else
		*head = new_node; /* If the list is empty, update head pointer to new node */
	return (new_node);
}

/**
 * showListString - prints only the 'txt' element of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of list
 */
size_t showListString(const list_t *h)
{
	size_t size = 0;

	/* Set the initial value of the counter 'size' to 0 */
	while (h)
	{
		/* Cycle through the list until 'h' is NULL */
		/* If h->txt is not NULL, print the text using the "putin" function */
		putin(h->txt ? h->txt : "(nil)");
		putin("\n"); /* Add a newline character */
		h = h->next;
		size++; /* Increment the counter 'size' */
	}
	return (size);
}

/**
 * delNodeatIndex - Remove node at given index
 * @head: First node
 * @index: index of node to remove
 *
 * Return: 1 on success, 0 on failure
 */
int delNodeatIndex(list_t **head, unsigned int index)
{
	list_t *list, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index) /* Make sure index is 0 */
	{
		/* Delete the first node if the index is 0 */
		/* 'list' should be assigned the head pointer's value */
		list = *head;
		*head = (*head)->next;
		free(list->txt);
		free(list);
		return (1); /* Return 1 to indicate successful removal */
	}

	list = *head;
	while (list)
	{
		if (i == index) /* Check if index 'i' matches the requested index */
		{
			/* Delete the node if the index matches */
			prev_node->next = list->next;
			free(list->txt);
			free(list);
			return (1);
		}
		i++;
		prev_node = list; /* Update 'prev_node' to the current node */
		list = list->next;
	}
	return (0);
}

/**
 * freeList - frees all nodes of a list
 * @headPtr: address of pointer to the head of the list
 *
 * Return: void
 */
void freeList(list_t **headPtr)
{
	list_t *list, *next_node, *head;

	/* Check whether the list is empty or the headPtr contains NULL */
	if (!headPtr || !*headPtr)
		return;

	head = *headPtr;
	list = head;
	while (list) /* Traverse the list and free each node's memory */
	{
		/* After freeing the current node, save the pointer to the */
		/* next node to avoid losing it */
		next_node = list->next;
		free(list->txt);
		free(list);
		list = next_node;
	}
	/* Set head pointer to NULL */
	*headPtr = NULL;
}

