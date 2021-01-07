#include "headers.h"
#include "ls.h"

void ls(char *com,char* home_dir)
{
	int len_l = strlen(com),k=1,p=0,d,r=0;
	char ls[1000][1010],dir[20][1010];
	struct dirent *dir_n;
	int c=1,o=0,l=0,x=0,y=1,fd1=0,fd2=0;		
	char inout[1000][1000],pro[100010];
	c = dup(1);
	char *buf = strtok(com," ");
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
			strcpy(ls[x],inout[i]);
			x++;
		}
		else if(l==2)
		{
			l=0;
		}
		else if(l==1)
		{
			fd1 = open(inout[i] , O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd1,1);
			y=fd1;
			l=0;
		}
		else
		{
			fd2 = open(inout[i] , O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd2,1);
			y=fd2;
			l=0;
		}
	}
	for(int i=1;i<x;i++)
	{
		if(ls[i][0]=='-')
		{
			d=strlen(ls[i]);
			if(d==1)
			{
				k=-1;
				char s1[100];
				sprintf(s1,"No Such file or directory\n");
				write(c,s1,strlen(s1)+1);
			}
			else 
			{
				for(int j=1;j<d;j++)
				{
					if(ls[i][j]!='l'&&ls[i][j]!='a')
					{
						r=-1;
						char s1[100];
						sprintf(s1,"invalid flag\n");
						write(c,s1,strlen(s1)+1);
						break;
					}
					else if(ls[i][j]=='l')
					{
						if(k==4||k==3)
						{
							k=4;
						}
						else
						{
							k=2;
						}
					}
					else
					{
						if(k==4||k==2)
						{
							k=4;
						}
						else
						{
							k=3;
						}
					}
				}
				if(r==-1)
				{
					break;
				}
			}
		}
		else
		{
			strcpy(dir[p],ls[i]);
			p++;
		}
	}
	if(r==0)
	{
		if(k==1)
		{
			if(p==0)
			{
				char buf2[10010];
				char *dir_c = getcwd(buf2,10010);
				DIR *dr = opendir(buf2);
				if(dr == NULL)
				{
					char s1[100];
					sprintf(s1,"Couldn't access the directory\n");
					write(c,s1,strlen(s1)+1);
				}
				while((dir_n = readdir(dr))!=NULL)
				{
					if((strcmp((dir_n->d_name),".")!=0)&&(strcmp((dir_n->d_name),"..")!=0))
					{
						printf("%s\n",dir_n->d_name);
					}
				}
				closedir(dr);
			}
			else
			{
				for(int j=0;j<p;j++)
				{
					if(strcmp(dir[j],"~")==0)
					{
						DIR *dr = opendir(home_dir);
						if(dr == NULL)
						{
							char s1[100];
							sprintf(s1,"Couldn't access the directory\n");
							write(c,s1,strlen(s1)+1);
						}
						else
						{
							if(p>1)
							{
								printf("%s : \n",dir[j]);
							}
							while((dir_n = readdir(dr))!=NULL)
							{
								if((strcmp((dir_n->d_name),".")!=0)&&(strcmp((dir_n->d_name),"..")!=0))
								{
									printf("%s\n",dir_n->d_name);
								}
							}
							closedir(dr);
						}
					}
					else 
					{
						char buf2[10010]; 
						char buf3[10010];
						char *dir_c = getcwd(buf2,10010);
						int b =chdir(dir[j]);
						if(b>=0)
						{
							char *dir_c1 = getcwd(buf3,10010);
							DIR *dr = opendir(buf3);
							if(dr == NULL)
							{
								char s1[100],s2[100];
								sprintf(s2,"%s : \n",dir[j]);
								sprintf(s1,"Couldn't access the directory\n");
								write(c,s2,strlen(s2)+1);
								write(c,s1,strlen(s1)+1);
							}
							else
							{
								if(p>1)
								{
									printf("%s : \n",dir[j]);
								}
								while((dir_n = readdir(dr))!=NULL)
								{
									if((strcmp((dir_n->d_name),".")!=0)&&(strcmp((dir_n->d_name),"..")!=0))
									{
										printf("%s\n",dir_n->d_name);
									}
								}
								closedir(dr);
							}
						}
						else
						{
							char s1[100],s2[100];
							sprintf(s2,"%s : \n",dir[j]);
							sprintf(s1,"No Such File/Directory exists\n");
							write(c,s2,strlen(s2)+1);
							write(c,s1,strlen(s1)+1);
						}
						chdir(buf2);
					}
				}
			}
		}
		else if(k==3)
		{
			if(p==0)
			{
				char buf2[10010];
				char *dir_c = getcwd(buf2,10010);
				DIR *dr = opendir(buf2);
				if(dr == NULL)
				{
					char s1[100];
					sprintf(s1,"Couldn't access the directory\n");
					write(c,s1,strlen(s1)+1);
				}
				while((dir_n = readdir(dr))!=NULL)
				{
					printf("%s\n",dir_n->d_name);
				}
				closedir(dr);
			}
			else
			{
				for(int j=0;j<p;j++)
				{
					if(strcmp(dir[j],"~")==0)
					{
						DIR *dr = opendir(home_dir);
						if(dr == NULL)
						{
							char s1[100];
							sprintf(s1,"Couldn't access the directory\n");
							write(c,s1,strlen(s1)+1);
						}
						else
						{
							if(p>1)
							{
								printf("%s : \n",dir[j]);
							}
							while((dir_n = readdir(dr))!=NULL)
							{
								printf("%s\n",dir_n->d_name);
							}
							closedir(dr);
						}
					}
					else 
					{
						char buf2[10010]; 
						char buf3[10010];
						char *dir_c = getcwd(buf2,10010);
						int b =chdir(dir[j]);
						if(b>=0)
						{
							char *dir_c1 = getcwd(buf3,10010);
							DIR *dr = opendir(buf3);
							if(dr == NULL)
							{
								char s1[100],s2[100];
								sprintf(s2,"%s : \n",dir[j]);
								sprintf(s1,"Couldn't access the directory\n");
								write(c,s2,strlen(s2)+1);
								write(c,s1,strlen(s1)+1);
							}
							else
							{
								if(p>1)
								{
									printf("%s : \n",dir[j]);
								}
								while((dir_n = readdir(dr))!=NULL)
								{
									printf("%s\n",dir_n->d_name);
								}
								closedir(dr);
							}
						}
						else
						{
							char s1[100],s2[100];
							sprintf(s2,"%s : \n",dir[j]);
							sprintf(s1,"No Such File/Directory exists\n");
							write(c,s2,strlen(s2)+1);
							write(c,s1,strlen(s1)+1);
						}
						chdir(buf2);
					}
				}
			}
		}
		else if(k==2)
		{
			if(p==0)
			{
				char buf2[10010];
				char *dir_c = getcwd(buf2,10010);
				DIR *dr = opendir(buf2);
				if(dr == NULL)
				{
					char s1[100];
					sprintf(s1,"Couldn't access the directory\n");
					write(c,s1,strlen(s1)+1);
				}
				while((dir_n = readdir(dr))!=NULL)
				{
					if((strcmp((dir_n->d_name),".")!=0)&&(strcmp((dir_n->d_name),"..")!=0))
					{
						struct stat st;
						char time[70];
						stat(dir_n->d_name,&st);
						printf("%c",(S_ISDIR(st.st_mode))? 'd':'-');
						printf("%c",(st.st_mode & S_IRUSR)? 'r':'-');
						printf("%c",(st.st_mode & S_IWUSR)? 'w':'-');
						printf("%c",(st.st_mode & S_IXUSR)? 'x':'-');
						printf("%c",(st.st_mode & S_IRGRP)? 'r':'-');
						printf("%c",(st.st_mode & S_IWGRP)? 'w':'-');
						printf("%c",(st.st_mode & S_IXGRP)? 'x':'-');
						printf("%c",(st.st_mode & S_IROTH)? 'r':'-');
						printf("%c",(st.st_mode & S_IWOTH)? 'w':'-');
						printf("%c",(st.st_mode & S_IXOTH)? 'x':'-');
						struct passwd *name = getpwuid(st.st_gid);
						struct group *grp = getgrgid(st.st_gid);
						printf("  %ld\t%s\t%s\t",st.st_nlink,name->pw_name,grp->gr_name);
						printf(" %ld\t",st.st_size);
						strftime(time,68,"%b  %d  %H : %M",localtime(&st.st_mtime));
						printf("%s\t%s\n",time,dir_n->d_name);
					}
				}
				closedir(dr);
			}
			else
			{
				for(int j=0;j<p;j++)
				{
					if(strcmp(dir[j],"~")==0)
					{
						DIR *dr = opendir(home_dir);
						if(dr == NULL)
						{
							char s1[100];
							sprintf(s1,"Couldn't access the directory\n");
							write(c,s1,strlen(s1)+1);
						}
						else
						{
							if(p>1)
							{
								printf("%s : \n",dir[j]);
							}
							while((dir_n = readdir(dr))!=NULL)
							{
								if((strcmp((dir_n->d_name),".")!=0)&&(strcmp((dir_n->d_name),"..")!=0))
								{
									struct stat st;
									char time[70];
									stat(dir_n->d_name,&st);
									printf("%c",(S_ISDIR(st.st_mode))? 'd':'-');
									printf("%c",(st.st_mode & S_IRUSR)? 'r':'-');
									printf("%c",(st.st_mode & S_IWUSR)? 'w':'-');
									printf("%c",(st.st_mode & S_IXUSR)? 'x':'-');
									printf("%c",(st.st_mode & S_IRGRP)? 'r':'-');
									printf("%c",(st.st_mode & S_IWGRP)? 'w':'-');
									printf("%c",(st.st_mode & S_IXGRP)? 'x':'-');
									printf("%c",(st.st_mode & S_IROTH)? 'r':'-');
									printf("%c",(st.st_mode & S_IWOTH)? 'w':'-');
									printf("%c",(st.st_mode & S_IXOTH)? 'x':'-');
									struct passwd *name = getpwuid(st.st_gid);
									struct group *grp = getgrgid(st.st_gid);
									printf("  %ld\t%s\t%s\t",st.st_nlink,name->pw_name,grp->gr_name);
									printf(" %ld\t",st.st_size);
									strftime(time,68,"%b  %d  %H : %M",localtime(&st.st_mtime));
									printf("%s\t%s\n",time,dir_n->d_name);
								}
							}
							closedir(dr);
						}
					}
					else 
					{
						char buf2[10010]; 
						char buf3[10010];
						char *dir_c = getcwd(buf2,10010);
						int b =chdir(dir[j]);
						if(b>=0)
						{
							char *dir_c1 = getcwd(buf3,10010);
							DIR *dr = opendir(buf3);
							if(dr == NULL)
							{
								char s1[100],s2[100];
								sprintf(s2,"%s : \n",dir[j]);
								sprintf(s1,"Couldn't access the directory\n");
								write(c,s2,strlen(s2)+1);
								write(c,s1,strlen(s1)+1);
							}
							else
							{
								if(p>1)
								{
									printf("%s : \n",dir[j]);
								}
								while((dir_n = readdir(dr))!=NULL)
								{
									if((strcmp((dir_n->d_name),".")!=0)&&(strcmp((dir_n->d_name),"..")!=0))
									{
										struct stat st;
										char time[70];
										stat(dir_n->d_name,&st);
										printf("%c",(S_ISDIR(st.st_mode))? 'd':'-');
										printf("%c",(st.st_mode & S_IRUSR)? 'r':'-');
										printf("%c",(st.st_mode & S_IWUSR)? 'w':'-');
										printf("%c",(st.st_mode & S_IXUSR)? 'x':'-');
										printf("%c",(st.st_mode & S_IRGRP)? 'r':'-');
										printf("%c",(st.st_mode & S_IWGRP)? 'w':'-');
										printf("%c",(st.st_mode & S_IXGRP)? 'x':'-');
										printf("%c",(st.st_mode & S_IROTH)? 'r':'-');
										printf("%c",(st.st_mode & S_IWOTH)? 'w':'-');
										printf("%c",(st.st_mode & S_IXOTH)? 'x':'-');
										struct passwd *name = getpwuid(st.st_gid);
										struct group *grp = getgrgid(st.st_gid);
										printf("  %ld\t%s\t%s\t",st.st_nlink,name->pw_name,grp->gr_name);
										printf(" %ld\t",st.st_size);
										strftime(time,68,"%b  %d  %H : %M",localtime(&st.st_mtime));
										printf("%s\t%s\n",time,dir_n->d_name);
									}
								}
								closedir(dr);
							}
						}
						else
						{
							char s1[100],s2[100];
							sprintf(s2,"%s : \n",dir[j]);
							sprintf(s1,"No Such File/Directory exists\n");
							write(c,s2,strlen(s2)+1);
							write(c,s1,strlen(s1)+1);
						}
						chdir(buf2);
					}
				}
			}
		}
		else if(k==4)
		{
			if(p==0)
			{
				char buf2[10010];
				char *dir_c = getcwd(buf2,10010);
				DIR *dr = opendir(buf2);
				if(dr == NULL)
				{
					char s1[100];
					sprintf(s1,"Couldn't access the directory\n");
					write(c,s1,strlen(s1)+1);
				}
				while((dir_n = readdir(dr))!=NULL)
				{
					struct stat st;
					char time[70];
					stat(dir_n->d_name,&st);
					printf("%c",(S_ISDIR(st.st_mode))? 'd':'-');
					printf("%c",(st.st_mode & S_IRUSR)? 'r':'-');
					printf("%c",(st.st_mode & S_IWUSR)? 'w':'-');
					printf("%c",(st.st_mode & S_IXUSR)? 'x':'-');
					printf("%c",(st.st_mode & S_IRGRP)? 'r':'-');
					printf("%c",(st.st_mode & S_IWGRP)? 'w':'-');
					printf("%c",(st.st_mode & S_IXGRP)? 'x':'-');
					printf("%c",(st.st_mode & S_IROTH)? 'r':'-');
					printf("%c",(st.st_mode & S_IWOTH)? 'w':'-');
					printf("%c",(st.st_mode & S_IXOTH)? 'x':'-');
					struct passwd *name = getpwuid(st.st_gid);
					struct group *grp = getgrgid(st.st_gid);
					printf("  %ld\t%s\t%s\t",st.st_nlink,name->pw_name,grp->gr_name);
					printf(" %ld\t",st.st_size);
					strftime(time,68,"%b  %d  %H : %M",localtime(&st.st_mtime));
					printf("%s\t%s\n",time,dir_n->d_name);
				}
				closedir(dr);
			}
			else
			{
				for(int j=0;j<p;j++)
				{
					if(strcmp(dir[j],"~")==0)
					{
						DIR *dr = opendir(home_dir);
						if(dr == NULL)
						{
							char s1[100];
							sprintf(s1,"Couldn't access the directory\n");
							write(c,s1,strlen(s1)+1);
						}
						else
						{
							if(p>1)
							{
								printf("%s : \n",dir[j]);
							}
							while((dir_n = readdir(dr))!=NULL)
							{
								struct stat st;
								char time[70];
								stat(dir_n->d_name,&st);
								printf("%c",(S_ISDIR(st.st_mode))? 'd':'-');
								printf("%c",(st.st_mode & S_IRUSR)? 'r':'-');
								printf("%c",(st.st_mode & S_IWUSR)? 'w':'-');
								printf("%c",(st.st_mode & S_IXUSR)? 'x':'-');
								printf("%c",(st.st_mode & S_IRGRP)? 'r':'-');
								printf("%c",(st.st_mode & S_IWGRP)? 'w':'-');
								printf("%c",(st.st_mode & S_IXGRP)? 'x':'-');
								printf("%c",(st.st_mode & S_IROTH)? 'r':'-');
								printf("%c",(st.st_mode & S_IWOTH)? 'w':'-');
								printf("%c",(st.st_mode & S_IXOTH)? 'x':'-');
								struct passwd *name = getpwuid(st.st_gid);
								struct group *grp = getgrgid(st.st_gid);
								printf("  %ld\t%s\t%s\t",st.st_nlink,name->pw_name,grp->gr_name);
								printf(" %ld\t",st.st_size);
								strftime(time,68,"%b  %d  %H : %M",localtime(&st.st_mtime));
								printf("%s\t%s\n",time,dir_n->d_name);
							}
							closedir(dr);
						}
					}
					else 
					{
						char buf2[10010]; 
						char buf3[10010];
						char *dir_c = getcwd(buf2,10010);
						int b =chdir(dir[j]);
						if(b>=0)
						{
							char *dir_c1 = getcwd(buf3,10010);
							DIR *dr = opendir(buf3);
							if(dr == NULL)
							{
								char s1[100],s2[100];
								sprintf(s2,"%s : \n",dir[j]);
								sprintf(s1,"Couldn't access the directory\n");
								write(c,s2,strlen(s2)+1);
								write(c,s1,strlen(s1)+1);
							}
							else
							{
								if(p>1)
								{
									printf("%s : \n",dir[j]);
								}
								while((dir_n = readdir(dr))!=NULL)
								{
									struct stat st;
									char time[70];
									stat(dir_n->d_name,&st);
									printf("%c",(S_ISDIR(st.st_mode))? 'd':'-');
									printf("%c",(st.st_mode & S_IRUSR)? 'r':'-');
									printf("%c",(st.st_mode & S_IWUSR)? 'w':'-');
									printf("%c",(st.st_mode & S_IXUSR)? 'x':'-');
									printf("%c",(st.st_mode & S_IRGRP)? 'r':'-');
									printf("%c",(st.st_mode & S_IWGRP)? 'w':'-');
									printf("%c",(st.st_mode & S_IXGRP)? 'x':'-');
									printf("%c",(st.st_mode & S_IROTH)? 'r':'-');
									printf("%c",(st.st_mode & S_IWOTH)? 'w':'-');
									printf("%c",(st.st_mode & S_IXOTH)? 'x':'-');
									struct passwd *name = getpwuid(st.st_gid);
									struct group *grp = getgrgid(st.st_gid);
									printf("  %ld\t%s\t%s\t",st.st_nlink,name->pw_name,grp->gr_name);
									printf(" %ld\t",st.st_size);
									strftime(time,68,"%b  %d  %H : %M",localtime(&st.st_mtime));
									printf("%s\t%s\n",time,dir_n->d_name);
								}
								closedir(dr);
							}
						}
						else
						{
							char s1[100],s2[100];
							sprintf(s2,"%s : \n",dir[j]);
							sprintf(s1,"No Such File/Directory exists\n");
							write(c,s2,strlen(s2)+1);
							write(c,s1,strlen(s1)+1);
						}
						chdir(buf2);
					}
				}
			}
		}
	}
	dup2(c,1);
	if(fd1>0)
		close(fd1);
	if(fd2>0)
		close(fd2);
	close(c);
	return;
}