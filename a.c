#include<stdlib.h>
#include<stdio.h>

void main()
{
	pid_t pid ;
	
	char* data[] =  {"./b.out","1","2","3",NULL} ;
	
	pid = fork() ;
	
	if(pid == 0)
	{
		printf("child id = %d",getpid());
		execl(data[0],data[0],data[1],data[2],data[3],NULL) ;
	}
	else
	{
		wait() ;
	}
}
