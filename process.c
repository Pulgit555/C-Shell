#include "headers.h"
#include "process.h"

void process(char *sp_cut ,int pro_pid[1000],char pro_name[1000][100],int bg_or_fg[2],char fg_process[2][10000])
{
	char inout[1000][1000];
	char **pro = (char**)malloc(10010);
	char *strin = (char*)calloc(10000,sizeof(char));
	int aa = dup(0);
	int bb = dup(1);
	int k=0,o=0,l=0,d=0;		
	char *buf2 = strtok(sp_cut," ");
	while(buf2!=NULL)
	{
		strcpy(inout[o],buf2);
		o++;
		buf2 = strtok(NULL," ");
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
			if(strcmp(inout[i],"&")==0)
			{
				d=1;
			}
			else
			{
				pro[k]=inout[i];
				strcat(strin,inout[i]);
				strcat(strin," ");
				k++;
			}
		}
		else if(l==2)
		{
			int fd = open(inout[i] , O_RDONLY);
			if(fd<0)
			{
				printf("This input file does not exist\n");
				return;
			}
			dup2(fd,0);
			close(fd);
		}
		else if(l==1)
		{
			int fd1 = open(inout[i] , O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd1,1);
			close(fd1);
		}
		else
		{
			int fd2 = open(inout[i] , O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd2,1);
			close(fd2);
		}
	}
	pro[k]='\0';
	pid_t pid = fork();
	if(pid<0)
	{
		char s[100];
		sprintf(s,"Child can't be forked right now\n");
		int z = write(1,s,100);
		return;
	}
	else if(pid==0)
	{
		if(d==1)
		{
			setpgid(0,0);
		}
		if(execvp(pro[0],pro)<0)
		{
			perror("exec");
			return;
		}
		exit(0);
	}
	else
	{
		if(d==0)
		{
			int st;
			bg_or_fg[0]=pid;
			strcpy(fg_process[0],strin);
			waitpid(pid,&st,WUNTRACED);
		}
		else
		{
			bg_or_fg[0]=-1;
			for(int g=0;g<1000;g++)
			{
				if(pro_pid[g]==-1)
				{
					pro_pid[g]=pid;
					strcpy(pro_name[g],pro[0]);
					for(int j=1;j<k;j++)
					{
						strcat(pro_name[g],pro[j]);
					}
					g++;
					break;
				}
			}
		}
		dup2(aa,0);
		dup2(bb,1);
		close(aa);
		close(bb);
	}
	return ; 
}