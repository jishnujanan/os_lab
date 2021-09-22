#include<stdio.h>
int main()
{
	int m,n;
	printf("enter the number of processes : ");
	scanf("%d",&m);
	printf("enter the number of resources : ");
	scanf("%d",&n);
	int max[m][n];
	int alloc[m][n];
	int available[n];
	int need[m][n];
	printf("enter max matrix\n");
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
	printf("enter allocation matrix\n");
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%d",&alloc[i][j]);
		}
	}
	printf("enter available matrix\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&available[i]);
	}
	printf("================MAX MATRIX===========\n");
	printf("=====================================\n");
	for(int i=0;i<m;i++)
	{
		printf("P[%d]	",i);
		for(int j=0;j<n;j++)
		{
			printf("%d	",max[i][j]);
		}
		printf("\n");
	}
	printf("============ALLOCATION MATRIX========\n");
	printf("=====================================\n");
	for(int i=0;i<m;i++)
	{
		printf("P[%d]	",i);
		for(int j=0;j<n;j++)
		{
			printf("%d	",alloc[i][j]);
		}
		printf("\n");
	}
	printf("==========AVAILABILITY MATRIX========\n");
	printf("=====================================\n");
	for(int i=0;i<n;i++)
	{
		printf("%d	",available[i]);
	}
	printf("\n");
	
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			need[i][j]=max[i][j]-alloc[i][j];
		}
	}
	printf("=============NEED MATRIX=============\n");
	printf("=====================================\n");
	for(int i=0;i<m;i++)
	{
		printf("P[%d]	",i);
		for(int j=0;j<n;j++)
		{
			printf("%d	",need[i][j]);
		}
		printf("\n");
	}
	
	//calculate need
	int executed[m];
	int safe[m];
	int index=0;
	int k=0;
	int flag=0;
	
	for(int i=0;i<m;i++)
	{
		executed[i]=0;
	}

	while(k<m)
	{
		for(int i=0;i<m;i++)
		{
			int count=0;
			if(executed[i]==0)
			{
				for(int j=0;j<n;j++)
				{
					if(need[i][j]<=available[j])
						count++;
				}
				
				if(count==n)
				{
					for(int l=0;l<n;l++)
					{
						available[l]+=alloc[i][l];
					}
					safe[index++]=i;
					executed[i]=1;
				}
			}
		}
		k++;
	}
	for(int i=0;i<m;i++)
	{
		if(executed[i]==0)
		{
			flag=1;
		}
	}
	if(flag==1)
	{
		printf("\nunsafe state\n");
	}
	else
	{
		printf("\nsafe state and safe sequence is : ");
		for(int i=0;i<m;i++)
		{
			printf("P[%d]  ",safe[i]);
		}
		printf("\n");
		
	}
	return 0;
}

