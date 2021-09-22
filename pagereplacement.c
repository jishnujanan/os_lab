#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    int index;
    struct node *rlink;
    struct node *llink;
};
struct lfu
{
    int data;
    int index;
    int freq;
    int order;
};
struct node* head=NULL;
struct node* ptr;
struct node* ptr1;
struct node* temp;
void printframe(int frame[],int f)
{
    int flag=0;
    int i=0;
    while(flag!=1&&i<f)
    {
        if(frame[i]!=-1)
        {
            printf("%d ",frame[i]);
        }
        else
        {
            flag=1;
        }
        i++;
    }
    printf("\n");

}
int search(int f,int key,int frame[])
{
    int i=0;
    int flag=0;
    while(i<f&&flag==0)
    {
        if(key==frame[i])
        {
            flag=1;
        }
        i++;
    }
    if(flag==1)
        return 1;
    else
        return 0;
}

int fifo(int ref[],int n,int f)
{
    printf("FIRST IN FIRST OUT\n");
    int *frame=(int *)malloc(sizeof(int)*f);
    for(int i=0; i<f; i++)
        frame[i]=-1;
    int count=0;
    int i=0,j=0;

    while(j<n)
    {
        int isPresent=search(f,ref[j],frame);
        if(isPresent==0)
        {
            frame[(i+f)%f]=ref[j];
            count++;
            printframe(frame,f);
            i++;
        }
        j++;
    }
    return count;
}
int leastRecentUsed(int ref[],int n,int f)
{
    printf("LEAST RECENTLY USED\n");
    int *frame=(int *)malloc(sizeof(int)*f);
    int i,count;
    for(int i=0; i<f; i++)
        frame[i]=-1;
    i=0;
    count=0;
    int k=0;
    while(i<n)
    {
        if(k<f)
        {
            int isPresent=search(f,ref[i],frame);
            if(isPresent==0)
            {
                frame[k]=ref[i];
                struct node* newnode=(struct node*)malloc(sizeof(struct node));
                newnode->data=ref[i];
                newnode->index=i;
                if(head==NULL)
                {
                    newnode->llink=NULL;
                    newnode->rlink=NULL;
                    head=newnode;
                    ptr=head;
                }
                else
                {
                    ptr->rlink=newnode;
                    ptr->rlink->llink=ptr;
                    ptr=ptr->rlink;
                    ptr->rlink=NULL;
                }
                count++;
                k++;
                printframe(frame,f);
            }
            else
            {
                struct node *ptr1=head;
                int flag=0;
                while(flag!=1&&ptr1!=NULL)
                {
                    if(ptr1->data==ref[i])
                    {
                        flag=1;
                    }
                    else
                    {
                        ptr1=ptr1->rlink;
                    }
                }
                if(flag==1)
                {
                    if(ptr1->rlink!=NULL)
                    {
                        int tempIndex=ptr1->index;
                        int tempData=ptr1->data;
                        if(ptr1->llink!=NULL)
                        {
                            ptr1->llink->rlink=ptr1->rlink;
                            ptr1->rlink->llink=ptr1->llink;
                            free(ptr1);
                        }
                        else if(ptr1->llink==NULL)
                        {
                            head=head->rlink;
                            head->llink=NULL;
                        }
                        struct node* newnode=(struct node*)malloc(sizeof(struct node));
                        newnode->data=tempData;
                        newnode->index=tempIndex;
                        ptr->rlink=newnode;
                        newnode->llink=ptr;
                        newnode->rlink=NULL;
                        ptr=ptr->rlink;
                    }
                }
            }
        }
        else
        {
            int isPresent=search(f,ref[i],frame);
            //printf("%d is present %d",ref[i],isPresent);
            if(isPresent==0)
            {
                frame[head->index]=ref[i];
                struct node*newnode=(struct node*)malloc(sizeof(struct node));
                newnode->data=ref[i];
                newnode->index=head->index;
                temp=head;
                head=head->rlink;
                head->llink=NULL;
                free(temp);
                ptr->rlink=newnode;
                newnode->llink=ptr;
                newnode->rlink=NULL;
                ptr=ptr->rlink;
                printframe(frame,f);
                count++;
            }
            else
            {
                struct node *ptr1=head;
                int flag=0;
                while(flag!=1&&ptr1!=NULL)
                {
                    if(ptr1->data==ref[i])
                    {
                        flag=1;
                    }
                    else
                    {
                        ptr1=ptr1->rlink;
                    }
                }
                if(flag==1)
                {
                    if(ptr1->rlink!=NULL)
                    {
                        int tempIndex=ptr1->index;
                        int tempData=ptr1->data;
                        if(ptr1->llink!=NULL)
                        {
                            ptr1->llink->rlink=ptr1->rlink;
                            ptr1->rlink->llink=ptr1->llink;
                        }
                        else if(ptr1->llink==NULL)
                        {
                            head=head->rlink;
                            head->llink=NULL;
                        }
                        struct node* newnode=(struct node*)malloc(sizeof(struct node));
                        newnode->data=tempData;
                        newnode->index=tempIndex;
                        ptr->rlink=newnode;
                        newnode->llink=ptr;
                        newnode->rlink=NULL;
                        ptr=ptr->rlink;
                    }
                }
            }
        }
        i++;
    }
    return count;
}
int getLeastIndex(struct lfu frame[],int f)
{
    int min=0;
    int i=1;
    while(i<f)
    {

        if(frame[i].freq<frame[min].freq)
        {
        	min=i; 
        }
        else if(frame[i].freq=frame[min].freq)
        {
        	if(frame[i].order<frame[min].order)
        	{
        		min=i;
        	}       
        }
        i++;
    }
    return min;
}
int getIndex(struct lfu frame[],int f,int key)
{
    int i=0;
    int flag=0;
    while(flag==0&&i<f)
    {
        if(frame[i].data==key)
        {
            flag=1;
        }
        i++;
    }
    i--;
    return i;
}
int leastFrequentlyUsed(int ref[],int n,int f)
{
    printf("LEAST FREQUENTLY USED\n");
    int *frame=(int *)malloc(sizeof(int)*f);
    int i,count,k=0;
    i=0;
    struct lfu* fList=(struct lfu *)malloc(sizeof(struct lfu)*f);
    for(int i=0; i<f; i++)
    {
        frame[i]=-1;
        fList[i].index=-1;
        fList[i].freq=0;
        fList[i].order=0;
        fList[i].data=-1;
    }
    count=0;
    while(i<n)
    {
        if(k<f)
        {
            int isPresent=search(f,ref[i],frame);
            if(isPresent==0)
            {
                frame[k]=ref[i];
                fList[k].data=ref[i];
                fList[k].index=i;
                fList[k].freq+=1;
                fList[k].order=i;
                printframe(frame,f);
                k++;
                count++;
            }
            else
            {
                int position=getIndex(fList,f,ref[i]);
                //printf("position %d",position);
                fList[position].freq+=1;
            }
        }
        else
        {
            int isPresent=search(f,ref[i],frame);
            int least=getLeastIndex(fList,f);
            //printf("\n least %d\n",least);
            if(isPresent==0)
            {
		frame[fList[least].index]=ref[i];
		fList[least].data=ref[i];
		fList[least].freq=1;
		fList[least].order=i;
		int flag=0;
		int i=0;
		while(flag!=1&&i<f)
		{
			if(fList[i].data!=-1)
			{
		   		printf("%d ",fList[i].data);
			}
			else
			{
		    		flag=1;
			}
			i++;
		}
		printf("\n");
               count++;
            }
            else
            {
                int position=getIndex(fList,f,ref[i]);
                fList[position].freq+=1;
                //printf("\n frequency of flist[position] %d\n",fList[position].freq);
            }
        }
        i++;
    }
    return count;
}
void main()
{
    printf("enter the number of pages : ");
    int n,f;
    scanf("%d",&n);
    printf("enter the frame size : ");
    scanf("%d",&f);
    int *ref=(int *)malloc(sizeof(int)*n);
    printf("enter the  pages : ");
    for(int i=0; i<n; i++)
        scanf("%d",&ref[i]);
    int pfFifo=fifo(ref,n,f);
    int pfLru=leastRecentUsed(ref,n,f);
    int pfLfu=leastFrequentlyUsed(ref,n,f);
    printf("Page fault in fifo is %d\n",pfFifo);
    printf("Page fault in lru is %d\n",pfLru);
    printf("Page fault in LFU is %d\n",pfLfu);
}

