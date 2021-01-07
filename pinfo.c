#include "headers.h"
#include "pinfo.h"

void pinfo(char *sp_cut)
{
	int pid,p=0,q,r=0;
	char pinfo[10][1000],file_name[10010],execu_name[10010],stat[50][1000];
	char *buf2 = (char*)calloc(10000,sizeof(char));
	char *buff = (char*)calloc(100000,sizeof(char));
	int b=1,o=0,l=0;		
	char inout[1000][1000],pro[100010];
	b = dup(1);
	char *buf = strtok(sp_cut," ");
	while(buf!=NULL)
	{
		strcpy(inout[o],buf);
		o++;
		buf = strtok(NULL," ");
	}
	for(int i=0;i<o;i++)
	{
		if(strcmp(inout[i],">")==0)
		{
			l=1;
		}
		else if(strcmp(inout[i],"<")==0)
		{
			l=2;
		}
		else if(strcmp(inout[i],">>")==0)
		{
			l=3;
		}
		else if(l==0)
		{
			strcpy(pinfo[p],inout[i]);
			p++;
		}
		else if(l==2)
		{
			l=0;
		}
		else if(l==1)
		{
			int fd1 = open(inout[i] , O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd1,1);
			close(fd1);
			l=0;
		}
		else
		{
			int fd2 = open(inout[i] , O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd2,1);
			close(fd2);
			l=0;
		}
	}
	if(p>2)
	{
		dup2(b,1);
		close(b);
		printf("Please enter valid number of arguments\n");
		return;
	}
	else if(strlen(pinfo[0])>5)
	{
		dup2(b,1);
		close(b);
		printf("please enter valid command\n");
		return;
	}
	else
	{
		if(p==2)
		{
			pid = atoi(pinfo[1]);
		}
		else
		{
			pid = getpid();
		}
		sprintf(file_name,"/proc/%d/stat",pid);
		FILE *fd = fopen(file_name,"r");
		if(fd==NULL)
		{
			dup2(b,1);
			close(b);
			printf("No such process exists\n");
			return;
		}
		else
		{
			printf("pid -- %d\n",pid);
			int fd1 = open(file_name,O_RDONLY);
			q = read(fd1,buff,100000);
			char *com = strtok(buff," \t");
			while(com!=NULL)
			{
				strcpy(stat[r],com);
				r++;
				com = strtok(NULL," \t");
			}
			printf("Process Status -- %s\n",stat[2]);
			printf("memory -- %s\n",stat[22]);
			sprintf(execu_name,"/proc/%d/exe",pid);
			int t = readlink(execu_name,buf2,10000);
			printf("Executable Path -- ");
			if(t<0)
			{
				printf("No, executable path exist\n");
			}
			else
			{
				printf("%s\n",buf2);
			}
			dup2(b,1);
			close(b);
			return;
		}
	}
}