#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("enter n :");
	int n;
	scanf("%d",&n);
	printf("PARENT PROCESS PID : %d at level 0\n",getpid());
	int i=1;
	while(i<=n)
	{
		int value=fork();
		if(value==0)
		{
			printf("CHILD PROCESS => Pid : %d , Parent pid : %d at level %d\n",getpid(),getppid(),i);
			
		}
		else if(value>0)
		{
			printf("CHILD PROCESS => Pid : %d  Parent pid : %d  at level %d\n",getpid(),getppid(),i);
			
		}
		else
		{
			printf("error");
		}
		sleep(1);
		i++;
	}
	return 0;
}
