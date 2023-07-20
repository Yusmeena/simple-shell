#include "shell.h"

/**
* independ - frees a pointer address and NULLs the addresss
* @word: addresss of the pointer to be free
*
* Return: 1 if freed, else 0
*/
int independ(void **word)
{
	if (word && *word) /* be sure memory point & pointer are correct */
	{
		free(*word); /* defragement memory pointer is pointing to*/
		*word = NULL;
		return (1); /* it display success when 1 return */
	}
	return (0); /* if pointer or memory is incorrect it return 0 */
}
