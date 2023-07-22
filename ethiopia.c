/**
* *fillMem - fills memmory with a constant byte
* @s: the pointer to the memory address
* @b: the byte to fill *s with
* @num: the amount of byte to be filled
* Return: (s) a pointer to the memory addres s
*/
char *fillMem(char *s, char y, unsigned int num)
{
	unsigned int z;

	for (z = 0; z < num; z++) /* iterate from 0 to 'num - 1' & assign value to 'z' */
	s[z] = y; /* Set value of 'y' to member at index 'z' in array 's' */
	return (s); /* Return the edited array 's' */
}

/**
* freeStrArray - frees a string of strings
* @pp: string of strings
*/
void freeStrArray(char **pp)
{
	char **z = pp;

	if (!pp) /* 'pp' is null pointer, exit the function */
		return;
	while (*pp) /* value pointed to by 'pp' is not null */
		free(*pp++);
	free(z);
}

/**
* reallocateMem - reallocates a block of memmory
* @word: pointer to previous malloc block
* @old: byte size of previous block
* @new: byte size of fresh block
*
* Return: pointer to da block name
*/
void *reallocateMem(void *word, unsigned int old, unsigned int new)
{
	char *q;

	if (!word) /* 'word' is a null pointer */
		return (malloc(new)); /* Allocate memory size to 'new' and return pointer */
	if (!new) /* 'new' is zero */
		return (free(word), NULL);
	if (new == old) /* 'new' is equal to 'old' */
		return (word); /* Return the original 'word' pointer without any changes */
	q = malloc(new); /*Allocate memory of size 'new' & assign pointer to 'q' */
	if (!q) /* 'q' is null pointer (allocation failed) */
		return (NULL);

	old = old < new ? old : new; /* determine smaller size between 'old' & 'new' */
	while (old--) /* iterate 'old' number of times */
		q[old] = ((char *)word)[old]; /* Copy each character from 'word' to 'q' */
	free(word); /* Free memory pointed to by 'word' */
	return (q);
}

