#include "headers.h"
#include "setenvi.h"

void setenvi(char * sp_cut)
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
	if(o>3||o<2)
	{
		printf("please enter valid number of arguments\n");
	}
	else 
	{
		if(o==2)
		{
			if(setenv(input[1]," ",1)<0)
			{
				printf("not able to change the variable\n");
			}
		}
		else
		{
			if(setenv(input[1],input[2],1)<0)
			{
				printf("not able to change the variable\n");
			}
		}
	}
	return ;
}