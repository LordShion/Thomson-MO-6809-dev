#include "thomson.h"

void my_puts(char* s)
{
	int j = 0;
	while(s[j]) PUTC(s[j++]);
}
