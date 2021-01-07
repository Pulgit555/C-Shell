#include "headers.h"
#include "cd.h"

char *cd(char *sp_cut,char*home_dir,char* add,int bonus1[2],char bon[2][10000])
{
	int len_c = strlen(sp_cut),o=0;
	char cd[10][10010],str[100010];
	char *buf5 = (char*)calloc(10000,sizeof(char));
	char *buf2 = (char*)calloc(10000,sizeof(char));
	char *str1 = (char*)calloc(10000,sizeof(char));
	char *buf1 = strtok(sp_cut," \t");
	while(buf1!=NULL)
	{
		strcpy(cd[o],buf1);
		o++;
		buf1 = strtok(NULL," \t");
	}
	char *diri = getcwd(buf5,10000);
	if(o>2)
	{
		printf("Please enter valid number of arguments\n");
		return add;
	}
	else if(o==1)
	{
		if(strlen(cd[0])!=2)
		{
			printf("Please enter valid command\n");
			return add;
		}
		else if(chdir(home_dir)>=0)
		{	
			strcpy(buf2,"~>");
			strcpy(bon[0],buf5);
			return buf2;
		}
		else
		{
			printf("cannot access this file\n");
			return add;
		}
	}
	else
	{
		if(strcmp(cd[o-1],"~")==0)
		{
			//bonus1[0]++;
			strcpy(buf2,"~>");
			chdir(home_dir);
			strcpy(bon[0],buf5);
			return buf2;
		}
		else if(strcmp(cd[o-1],"-")==0)
		{
			if(bonus1[0]>0)
			{
				if(strcmp(bon[0],home_dir)==0)
				{
					printf("~\n");
				}
				else if(strstr(bon[0],home_dir)!=NULL)
				{
					int l= strlen(home_dir);
					for(int i=l;i<strlen(bon[0]);i++)
					{
						str1[i-l]=bon[0][i];
					}
					strcpy(buf2,"~");
					strcat(buf2,str1);
					printf("%s\n",buf2);
				}
				else
				{
					printf("%s\n",bon[0]);
				}
			}
			else
			{
				printf("~\n");
			}
			if(chdir(bon[0])>=0&&bonus1[0]>0)
			{
				char *dir = getcwd(str,100010);
				bonus1[0]++;
				if(strcmp(str,home_dir)==0)
				{
					strcpy(buf2,"~>");
					chdir(home_dir);
					strcpy(bon[0],buf5);
					return buf2;
				}
				else if(strstr(str,home_dir)!=NULL)
				{
					int l= strlen(home_dir);
					for(int i=l;i<strlen(str);i++)
					{
						str1[i-l]=str[i];
					}
					strcpy(buf2,"~");
					strcat(buf2,str1);
					strcat(buf2,">");
					strcpy(bon[0],buf5);
					return buf2;
				}
				else 
				{
					if(add[0]=='/')
					{
						strcpy(buf2,str);
						strcat(buf2,">");
						strcpy(bon[0],buf5);
						return buf2;
					}
					else
					{
						strcpy(buf2,str);
						strcat(buf2,">");
						strcpy(bon[0],buf5);
						return buf2;
					}
				}
			}
			else
			{
				return add;
			}
		}
		else if(chdir(cd[o-1])>=0)
		{
			char *dir = getcwd(str,100010);
			if(strcmp(str,home_dir)==0)
			{
				strcpy(buf2,"~>");
				chdir(home_dir);
				strcpy(bon[0],buf5);
				return buf2;
			}
			else if(strstr(str,home_dir)!=NULL)
			{
				bonus1[0]++;
				int l= strlen(home_dir);
				for(int i=l;i<strlen(str);i++)
				{
					str1[i-l]=str[i];
				}
				strcpy(buf2,"~");
				strcat(buf2,str1);
				strcat(buf2,">");
				strcpy(bon[0],buf5);
				return buf2;
			}
			else 
			{
				bonus1[0]++;
				if(add[0]=='/')
				{
					strcpy(buf2,str);
					strcat(buf2,">");
					strcpy(bon[0],buf5);
					return buf2;
				}
				else
				{
					strcpy(buf2,str);
					strcat(buf2,">");
					strcpy(bon[0],buf5);
					return buf2;
				}
			}
		}
		else
		{
			printf("cannot access this file\n");
			strcpy(bon[0],buf5);
			return add;
		}
	}
}