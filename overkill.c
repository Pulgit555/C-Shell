#include "headers.h"
#include "overkill.h"

void overkill(char *sp_cut,int pro_pid[1000],char pro_name[1000][100])
{
	for(int g=0;g<1000;g++)
	{
		if(pro_pid[g]>0)
		{
			kill(pro_pid[g],9);
			pro_pid[g]=-1;
		}
	}
	return;
}