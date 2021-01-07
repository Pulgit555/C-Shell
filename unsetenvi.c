#include "headers.h"
#include "unsetenvi.h"

void unsetenvi(char* sp_cut)
{
	int o=0;
	char input[10][1000];
	char *buf = strtok(sp_cut," \t");
	while(buf!=NULL)
	{
		strcpy(input[o],buf);
		o++;
		if(o>5)
		{
			break;
		}
		buf = strtok(NULL," \t");
	}
	if(o!=2)
	{
		printf("please enter valid number of arguments\n");
	}
	else
	{
		unsetenv(input[1]);
	}
	return;
}