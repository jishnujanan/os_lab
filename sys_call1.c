#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()

{
	int n;
	printf("enter n : ");
	scanf("%d",&n);
	int f1=0,f2=1,f3; 
	int value=fork();
	if(value==0)
	{
		printf("\nChild proces id : %d \n",getpid());
		printf("Fibonacci series :");
		printf("0 1 ");
		int flag=0;
		while(flag!=1)
		{
				f3=f1+f2;
				if(f3<=n)
				{	printf("%d ",f3);
					f1=f2;
					f2=f3;
				}
				else
					flag=1;
		}
	}
	else if(value>0)
	{
		wait(NULL);
		printf("\nParent proces id : %d \n",getppid());
		int i=2,j;
		int count;
		printf("Prime Numbers :");
		while(i<=n)
		{
			j=1;
			count=0;
			while(j<=i)
			{
				if(i%j==0)
				{
					count++;
				}
				j++;
				
			}
			if(count==2)
				printf("%d ",i);
			i++; 
		}
		printf("\n");
		
	}
	else
	{
		printf("failed creating child process");
	}
	
	return 0;
}
