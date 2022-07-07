#include <stdio.h>
#include "my_put_string.h"
#include "my_put_char.h"

void my_put_string(char const* str)
{
	if (str == NULL)
	{
		return;
	}		
	else
	{
		for(int i = 0;str[i]; ++i)
		{
			my_put_char(str[i]);
	
		}
	
	}
}
