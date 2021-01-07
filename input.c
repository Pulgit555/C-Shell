#include "headers.h"
#include "input.h"
#include "pwd.h"
#include "echo.h"
#include "history.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "nightswatch.h"
#include "process.h"
#include "setenvi.h"
#include "unsetenvi.h"
#include "overkill.h"
#include "jobs.h"
#include "fg.h"
#include "kjob.h"
#include "bg.h"

char* input(char *add, char *home_dir, int pro_pid[1000],char pro_name[1000][100],int bonus1[2],char bon[2][10000],int bg_or_fg[2], char fg_process[2][10000])
{
	int l,k=0,m,n,o=0,p,q=100000000,r,z=0,h=0;
	ssize_t x=0;
	char *s = (char*)calloc(100010,sizeof(char));
	char *st = (char*)calloc(100010,sizeof(char));
	char *buf2= (char*)calloc(100000000,sizeof(char));
	char *buf3= (char*)calloc(100010,sizeof(char));
	char history_f[100010];
	char his_com[25][100010] = {0},command[250][1000];
	strcpy(history_f,home_dir);
	strcat(history_f,"/history.txt");
	int fd1 = open(history_f,O_RDWR);
	if(fd1<0)
	{
		fd1= open(history_f,O_WRONLY | O_CREAT | O_APPEND,0744);
	}
	p=read(fd1,buf2,q);
	char *com1 = strtok(buf2,"\n");
	while(com1!=NULL)
	{
		if(strlen(com1)!=0)
		{
			strcpy(his_com[o],com1);
			strcat(his_com[o],"\n");
			o++;
			com1 = strtok(NULL,"\n");
		}
		else
		{
			com1 = strtok(NULL,"\n");
		}
	}
	if(fgets(s ,100010, stdin)==NULL)
	{
		printf("\n");
		exit(0);
	}
	n=strlen(s);
	s[n-1]='\0';
	n--;
	if(n!=0)
	{
		for(int i=0;i<n;i++)
		{
			st[i]=s[i];
		}
		st[n]='\n';
		n++;
		strcpy(his_com[o],st);
		o++;
	}
	if(o>=20)
	{
		remove(history_f);
		fd1= creat(history_f, 0744);
		for(int i=0;i<20;i++)
		{
			char *buf= (char*)calloc(100010,sizeof(char));
			sprintf(buf,"%s",his_com[o-20+i]);
			r=write(fd1,buf,strlen(buf));
			free(buf);
		}
	}
	else if(n!=1)
	{
		char *buf= (char*)calloc(100010,sizeof(char));
		sprintf(buf,"%s",his_com[o-1]);
		r=write(fd1,buf,strlen(buf));
		free(buf);
	}
	free(buf2);
	char *com = strtok(s,";");
	while(com!=NULL)
	{
		strcpy(command[z],com);
		z++;
		com = strtok(NULL,";");
	}
	for(int j=0;j<z;j++)
	{
		int pp=0,aa=0,bb=1,ee=0,ff=1;
		char pip[1000][1000];
		char *buf1 = strtok(command[j],"|");
		while(buf1!=NULL)
		{
			strcpy(pip[pp],buf1);
			pp++;
			buf1 = strtok(NULL,"|");
		}
		for(int jj=0;jj<pp;jj++)
		{
			int pipy[2];
			int h = pipe(pipy);
			aa = dup(0);
			bb = dup(1);		
			if(jj==0&&pp>1)
			{
				dup2(pipy[1],1);
				close(pipy[1]);
			}
			else if(pp>1&&jj!=pp-1)
			{
				dup2(ee,0);
				close(ee);
				dup2(pipy[1],1);
				close(pipy[1]);
			}
			else if(jj==pp-1)
			{
				dup2(ee,0);
				close(ee);
			}
			char *sp_cut = (char*)calloc(100010,sizeof(char));
			k=0;
			l=strlen(pip[jj]);
			char *com1 = strtok(pip[jj]," \t");
			buf3 = com1;
			while(com1!=NULL)
			{
				strcat(sp_cut,com1);
				strcat(sp_cut," ");
				com1 = strtok(NULL," \t");
			}
			sp_cut[strlen(sp_cut)-1]='\0';
			if(strstr(buf3,"echo")!=NULL)
			{
				echo(sp_cut);
			}
			else if(strstr(buf3,"pwd")!=NULL)
			{
				pwd(sp_cut);
			}
			else if(strstr(buf3,"pinfo")!=NULL)
			{
				pinfo(sp_cut);
			}
			else if(strstr(buf3,"ls")!=NULL)
			{
				ls(sp_cut,home_dir);
			}
			else if(strstr(buf3,"cd")!=NULL)
			{
				add=cd(sp_cut,home_dir,add,bonus1,bon);
			}
			else if(strstr(buf3,"history")!=NULL)
			{
				history(sp_cut,home_dir);
			}
			else if(strstr(buf3,"nightswatch")!=NULL)
			{
				nightswatch(sp_cut);
			}
			else if(strstr(buf3,"unsetenv")!=NULL)
			{
				unsetenvi(sp_cut);
			}
			else if(strstr(buf3,"setenv")!=NULL)
			{
				setenvi(sp_cut);
			}
			else if(strstr(buf3,"overkill")!=NULL)
			{
				overkill(sp_cut,pro_pid,pro_name);
			}
			else if(strstr(buf3,"quit")!=NULL)
			{
				exit(0);
			}
			else if(strstr(buf3,"kjob")!=NULL)
			{
				kjob(sp_cut,pro_pid,pro_name);
			}
			else if(strstr(buf3,"jobs")!=NULL)
			{
				h=jobs(sp_cut,pro_pid,pro_name,0);
			}
			else if(strstr(buf3,"fg")!=NULL)
			{
				fg(sp_cut,pro_pid,pro_name,bg_or_fg,fg_process);
			}
			else if(strstr(buf3,"bg")!=NULL)
			{
				bg(sp_cut,pro_pid,pro_name);
			}
			else
			{
				process(sp_cut,pro_pid,pro_name,bg_or_fg,fg_process);
			}
			free(sp_cut);
			if(j!=z-1)
			{
				printf("\n");
			}
			ee = dup(pipy[0]);
			dup2(aa,0);
			dup2(bb,1);
			close(pipy[0]);
			close(aa);
			close(bb);
		}
	}
	return add;
}