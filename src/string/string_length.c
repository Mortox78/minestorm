#include <stdio.h>
#include "string_length.h"

unsigned int string_length(char const* str)
{
	int i = 0;
	if(str != NULL)
	while(str[i] != '\0')
	{
		++i;
	}
	return i;

}
