#include <stdio.h>
#include <stdlib.h>
#include "string_duplicate.h"
#include "string_length.h"

char* string_duplicate(char const* str)
{
	if(str == NULL)
	{
		return NULL;
	}
	char* copie;
	int l = string_length(str);
	copie = malloc(l * sizeof(char));
	for(int i = 0; i <= l; ++i)
	{
		if(i == l)
		{
			copie[i] = '\0';
			return copie;
		}
		copie[i] = str[i];
	}
	return copie;
}
