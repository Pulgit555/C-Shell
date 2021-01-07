#include "headers.h"
#include "prompt.h"

void prompt(char *add)
{
	char * name;
	char sys_name[1025];
	int d;
	name = getlogin();
	d = gethostname(sys_name,1024);
	printf("%s@%s:%s",name,sys_name,add);
	return;
}