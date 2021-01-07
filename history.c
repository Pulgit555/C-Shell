#include "headers.h"
#include "history.h"

void history(char *his,char *home_dir)
{
	int len_h = strlen(his),o=0,q=100000000,p;
	char his_com[25][1010],history_f[100010];
	char *buf2= (char*)calloc(100000000,sizeof(char));
	strcpy(history_f,home_dir);
	strcat(history_f,"/history.txt");
	int fd1 = open(history_f,O_RDWR);
	if(fd1<0)
	{
		int fd1= open(history_f,O_WRONLY | O_CREAT | O_APPEND,0744);
	}
	p=read(fd1,buf2,q);
	char *com = strtok(buf2,"\n");
	while(com!=NULL)
	{
		char *buf1= (char*)calloc(100000,sizeof(char));
		com[strlen(com)]='\n';
		//printf("%s",com);
		for(int i=0;i<strlen(com);i++)
		{
			if(com[i]!='\n')
			{
				buf1[i]=com[i];
			}
			else
			{
				break;
			}
		}
		buf1[strlen(buf1)]='\n';
		strcpy(his_com[o],buf1);
		o++;
		com = strtok(NULL,"\n");
		if(buf1!=NULL)
			free(buf1);
	}
	if(len_h==7)
	{
		if(o>10)
		{
			for(int i=o-10;i<o;i++)
			{
				printf("%s",his_com[i]);
			}
		}
		else
		{
			for(int i=0;i<o;i++)
			{
				printf("%s",his_com[i]);
			}
		}
	}
	else if(len_h<=10)
	{
		if(his[7]==' ')
		{
			char *d=(char*)calloc(10,sizeof(char));
			d[0]=his[8];
			if(len_h>9)
			{
				d[1]=his[9];
			}
			int y = atoi(d);
			if(y>20)
			{
				printf("Shell can print maximum of 20 previous commands only , if it has less than 20 commands then it will print only them.\n");
				if(o>20)
				{
					for(int i=o-20;i<o;i++)
					{
						printf("%s",his_com[i]);
					}
				}
				else
				{
					for(int i=0;i<o;i++)
					{
						printf("%s",his_com[i]);
					}
				}
			}
			else if(y>o)
			{
				for(int i=0;i<o;i++)
				{
					printf("%s",his_com[i]);
				}
			}
			else
			{
				for(int i=o-y;i<o;i++)
				{
					printf("%s",his_com[i]);
				}
			}
		}
		else
		{
			printf("Please enter valid command.\n");
		}
	}
}