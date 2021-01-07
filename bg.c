#include "headers.h"
#include "bg.h"
#include "jobs.h"

void bg(char *sp_cut ,int pro_pid[1000],char pro_name[1000][100])
{
	int o=0,k,l,m;
	char bg[10][1000];
	char *com = strtok(sp_cut," \t");
	while(com!=NULL)
	{
		strcpy(bg[o],com);
		o++;
		if(o==4)
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
		k=atoi(bg[1]);
		m = jobs(sp_cut,pro_pid,pro_name,k);
		if(m==-1)
		{
			printf("No such process with this job number exists\n");
		}
		else
		{
			/*int p=0,q;
			char file_name[10010],stat[50][1000];
			sprintf(file_name,"/proc/%d/stat",m);
			char *buff = (char*)calloc(100000,sizeof(char));
			FILE *fd = fopen(file_name,"r");
			if(fd!=NULL)
			{
				int fd1 = open(file_name,O_RDONLY);
				q = read(fd1,buff,100000);
				char *com1 = strtok(buff," \t");
				while(com1!=NULL)
				{
					strcpy(stat[p],com);
					p++;
					if(p==3)
					{
						break;
					}
					com1 = strtok(NULL," \t");
				}
			}
			printf("%d %s\n",pro_pid[m],stat[2]);
			//if(strcmp(stat[2],"T")==0)
			//{*/
				//kill(pro_pid[m],SIGTTIN);
			kill(pro_pid[m],SIGCONT);
			//}
		}
	}
}