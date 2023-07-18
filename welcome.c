#include "shell.h"

/**
* *_copyString1 - thicopy string
* @keeper: the destination string to copy to
* @place: the string source
* @num: number of characters to be copy
* Return: he string copied outcome
*/

int *_copyString1(char *keeper, char *place, int num)
{
	int z, y;
	char *s = keeper;

	z = 0;
	while (place[z] != '\0' && z < num - 1)
	{
		keeper[z] = place[z];
		z++;
	}
	if (z < num) /* instance where z is smaller than n, add NULL terminator */
	{
		y = z;
		while (y < num)
		{
			keeper[a] = '\0';
			y++;
		}
	}
	return (s);
}
