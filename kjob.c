#include "headers.h"
#include "jobs.h"
#include "kjob.h"

void kjob(char *sp_cut ,int pro_pid[1000],char pro_name[1000][100])
{
	int o=0,k,l,m;
	char kjob[10][1000];
	char *com = strtok(sp_cut," \t");
	while(com!=NULL)
	{
		strcpy(kjob[o],com);
		o++;
		if(o==4)
		{
			break;
		}
		com = strtok(NULL," \t");
	}
	if(o!=3)
	{
		printf("Please enter valid number of arguments\n");
	}
	else
	{
		k=atoi(kjob[1]);
		l=atoi(kjob[2]);
		m = jobs(sp_cut,pro_pid,pro_name,k);
		if(m==-1)
		{
			printf("No such process with this job number exists\n");
		}
		else
		{
			kill(pro_pid[m],l);
		}
	}
}