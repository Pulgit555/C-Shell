#include "headers.h"
#include "pwd.h"

void pwd(char *sp_cut)
{
	int b=1,o=0,l=0,k=0;		
	char inout[1000][1000],pro[100010];
	b = dup(1);
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
			for(int j=0;j<strlen(inout[i]);j++)
			{
				pro[k]=inout[i][j];
				k++;
			}
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
	if(k>3)
	{
		printf("Please enter valid command\n");
		dup2(b,1);
		close(b);
		return;
	}
	else
	{
		char buf[10000];
		char *dir = getcwd(buf,sizeof(buf));
		printf("%s\n",buf);
		dup2(b,1);
		close(b);
		return;
	}
}