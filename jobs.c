#include "headers.h"
#include "jobs.h"

int func (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int jobs(char *sp_cut ,int pro_pid[1000],char pro_name[1000][100],int a)
{
	int job[1000],bgpro[1000],k=0,l=0,d=0;
	char bg_na[1000][1000];
	for(int g=0;g<1000;g++)
	{
		job[g]=pro_pid[g];
	}
	qsort(job,1000,sizeof(int),func);
	for(int i=0;i<1000;i++)
	{
		if(job[i]>0)
		{
			for(int j=0;j<999;j++)
			{
				if(job[i]==pro_pid[j]&&job[i]!=job[i+1])
				{
					bgpro[k]=pro_pid[j];
					strcpy(bg_na[k],pro_name[j]);
					k++;
					break;
				}
			}
		}
	}
	for(int i=0;i<k;i++)
	{
		int p=0,q;
		char file_name[10010],stat[50][1000];
		sprintf(file_name,"/proc/%d/stat",bgpro[i]);
		char *buff = (char*)calloc(100000,sizeof(char));
		FILE *fd = fopen(file_name,"r");
		if(fd!=NULL)
		{
			int fd1 = open(file_name,O_RDONLY);
			q = read(fd1,buff,100000);
			char *com = strtok(buff," \t");
			while(com!=NULL)
			{
				strcpy(stat[p],com);
				p++;
				if(p==3)
				{
					break;
				}
				com = strtok(NULL," \t");
			}
			if(strcmp(stat[2],"R")==0||strcmp(stat[2],"S")==0)
			{
				l++;
				if(a==0)
				{
					printf("[ %d ] Running %s [ %d ]\n",l,bg_na[i],bgpro[i]);
				}
				else
				{
					if(l==a)
					{
						d++;
						return i;
					}
				}
			}
			else if(strcmp(stat[2],"T")==0)
			{
				l++;
				if(a==0)
				{
					printf("[ %d ] Stopped %s [ %d ]\n",l,bg_na[i],bgpro[i]);
				}
				else
				{
					if(l==a)
					{
						d++;
						return i;
					}
				}
			}
		}
	}
	return -1;
}