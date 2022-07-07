#include <stdio.h>
#include "my_put_number.h"
#include "my_put_char.h"

void my_put_number(int num)
{
	unsigned int multiplicator = 1;

	if(num < 0)
	{
		my_put_char('-');
		num *= -1;
	}

	while(num/multiplicator > 9)
	{
		multiplicator *= 10;
	}
	
	while(multiplicator != 1)
	{
		my_put_char((num/multiplicator) + '0');
		num %= multiplicator;
		multiplicator /= 10;
	}
	
	my_put_char((num/multiplicator) + '0');	
	
	
}
