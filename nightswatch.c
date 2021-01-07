#include "headers.h"
#include "nightswatch.h"
void fun(int);
int val=0;
void nightswatch(char *sp_cut)
{
	int o=0,a,p=0,q=0;
	val=0;
	char night[5][1000],cp[1000],new[10][1000],interr[20][1000];
	char *buf1 = (char*)calloc(100000,sizeof(char));
	char *buf = strtok(sp_cut," \t");
	while(buf!=NULL)
	{
		strcpy(night[o],buf);
		o++;
		if(o>4)
		{
			break;
		}
		buf = strtok(NULL," \t");
	}
	if(o>4||o<4)
	{
		printf("Please enter valid number of arguments\n");
	}
	else
	{
		if(strcmp(night[1],"-n")!=0)
		{
			printf("Please enter valid command\n");
		}
		else
		{
			a= atoi(night[2]);
			if(strcmp(night[3],"interrupt")==0)
			{
				strcpy(buf1,"/proc");
				strcat(buf1,"/interrupts");
				for(int i=0;i<8;i++)
				{
					sprintf(cp,"CPU%d",i);
					if(i==0)
						printf("%s",cp);
					else
						printf("\t%s",cp);
				}
				printf("\n");
				ssize_t x=0;
				FILE *fd = fopen(buf1,"r");
				char *s = (char*)calloc(100010,sizeof(char));
				getline(&s,&x,fd);
				int k=0;
				while(1)
				{
					k++;
					char *s1 = (char*)calloc(100010,sizeof(char));
					getline(&s1,&x,fd);
					q=0;
					char *com1 = strtok(s1," \t\n");
					while(com1!=NULL)
					{
						strcpy(interr[q],com1);
						q++;
						com1=strtok(NULL," \t\n");
					}
					signal(SIGINT,fun);
					if(val==1)
					{
						break;
					}
					if(val==0)
					{
						for(int i=1;i<=8;i++)
						{
							if(i==1)
							{
								printf("%d",atoi(interr[i]));
							}
							else
							{
								printf("\t%d",atoi(interr[i]));
							}
						}
						printf("\n");
					}
					
					sleep(a);
					free(s1);
				}

			}
			else if(strcmp(night[3],"newborn")==0)
			{
				strcpy(buf1,"/proc");
				strcat(buf1,"/loadavg");
				int k=0;
				while(1)
				{
					ssize_t x=0;
					FILE *fd = fopen(buf1,"r");
					char *s = (char*)calloc(100010,sizeof(char));
					getline(&s,&x,fd);
					char *com = strtok(s," \n");
					p=0;
					k++;
					while(com!=NULL)
					{
						strcpy(new[p],com);
						com= strtok(NULL," \n");
						p++;
					}
					if(val==0)
					{
						printf("%d\n",atoi(new[4]));
					}
					signal(SIGINT,fun);
					if(val==1)
					{
						break;
					}
					sleep(a);
					free(s);
					fclose(fd);
				}

			}
			else
			{
				printf("Please enter valid command\n");
			}
		}
	}
}
void fun(int z)
{
	char c;
	signal(z, SIG_IGN);
	printf("If you want to quit this function?,Press q\n");
	c = getchar();
	if(c=='q')
	{
		val =1;
	}
	return ;
}