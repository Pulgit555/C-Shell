#include "headers.h"
#include "prompt.h"
#include "input.h"
int pro_pid[1000];
char pro_name[1000][100];
int bonus1[2];
char bon[2][10000];
char fg_process[2][10000];
int bg_or_fg[2];
int shell_pid;
void backover();
void func_c();
void func_z();
int main()
{
	char *add = (char*)calloc(100000,sizeof(char));
	char home_dir[100010],home_di[100010];
	char *dir = getcwd(home_dir,sizeof(home_dir));
	strcpy(add,"~>");
	bonus1[0] = 0;
	bg_or_fg[0] =-1;
	shell_pid = getpid();
	for(int g=0;g<1000;g++)
	{
		pro_pid[g]=-1;
	}
	while(1)
	{
		signal(SIGCHLD,backover);
		signal(SIGINT,func_c);
		signal(SIGTSTP,func_z);
		prompt(add);
		add=input(add,home_dir,pro_pid,pro_name,bonus1,bon,bg_or_fg,fg_process);
	}
}
void backover()
{
	int che_st,che_pid;
	che_pid=waitpid(-1,&che_st, WNOHANG);
	if(che_pid>0)
	{
		if(WIFEXITED(che_st)>0)
		{
			for(int g=0;g<1000;g++)
			{
				if(pro_pid[g]==che_pid)
				{
					printf("%s with pid",pro_name[g]);
					printf(" %d exited normally\n",pro_pid[g]);
					pro_pid[g]=-1;
					break;
				}			
			}
		}
		else if(WIFSIGNALED(che_st)>0)
		{
			for(int g=0;g<1000;g++)
			{
				if(pro_pid[g]==che_pid)
				{
					printf("%s with pid",pro_name[g]);
					printf(" %d terminated because of unhandled signal\n",pro_pid[g]);
					pro_pid[g]=-1;
					break;
				}
			}
		}
		else if(WIFSTOPPED(che_st)>0)
		{
			for(int g=0;g<1000;g++)
			{
				if(pro_pid[g]==che_pid)
				{
					printf("%s with pid",pro_name[g]);
					printf(" %d terminated because of delivery of a signal\n",pro_pid[g]);
					pro_pid[g]=-1;
					break;
				}
			}
		}
	}
}

void func_c()
{
	int pid_p = getpid();
	if(pid_p==shell_pid&&bg_or_fg[0]!=-1)
	{
		kill(bg_or_fg[0],SIGINT);
	}
	signal(SIGINT,func_c);
}
void func_z()
{
	int st;
	int pid_p = getpid();
	if(pid_p==shell_pid&&bg_or_fg[0]!=-1)
	{
		kill(bg_or_fg[0],SIGSTOP);
		for(int g=0;g<1000;g++)
		{
			if(pro_pid[g]==-1)
			{
				pro_pid[g]=bg_or_fg[0];
				strcpy(pro_name[g],fg_process[0]);
				break;
			}
		}
	}
	signal(SIGTSTP,func_z);
}