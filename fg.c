#include "headers.h"
#include "fg.h"
#include "jobs.h"

int fg(char *sp_cut ,int pro_pid[1000],char pro_name[1000][100],int bg_or_fg[2],char fg_process[2][10000])
{
	int o=0,k,m,n=0;
	char fg[100][1000];
	char **pro = (char**)malloc(10010);
	char *com = strtok(sp_cut," \t");
	while(com!=NULL)
	{
		strcpy(fg[o],com);
		o++;
		if(o==3)
		{
			break;
		}
		com = strtok(NULL," \t");
	}
	if(o!=2)
	{
		printf("Please enter valid number of arguments\n");
	}
	else
	{
		int st;
		k=atoi(fg[1]);
		if(k>0)
		{
			m= jobs(sp_cut,pro_pid,pro_name,k);
			if(m==-1)
			{
				printf("No such process with this job number exists\n");
			}
			else
			{
				bg_or_fg[0]=pro_pid[m];
				strcpy(fg_process[0],pro_name[m]);
				//signal(SIGTTOU, SIG_IGN);
				//tcsetpgrp(0,0);
				kill(pro_pid[m],SIGCONT);
				waitpid(pro_pid[m],&st,WUNTRACED);
			}
		}
		else
		{
			printf("No such process with this job number\n");
		}
	}
}