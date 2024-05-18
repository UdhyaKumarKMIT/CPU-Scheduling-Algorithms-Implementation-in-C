#include<stdio.h>
#include<stdlib.h>

void sort(int arr[],int n)
{
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
void cscan_total_head_movement(int arr[],int n,int initial,int tot_disk)
{
    int a=initial;
    int i,move,index,total_head=0;
    for(i=0;i<n;i++)
    {
        if(a<arr[i])
        {
            index=i;
            break;
        }
    }
    printf("\nEnter 1 for moving towards higher value(left to right) \nenter 0 for moving towards lower value(right to left) :");
    scanf("%d",&move);
    if(move==1)
    {
        for(i=index;i<n;i++)
        {  
            total_head+=(abs(arr[i]-a));
            a=arr[i];
             printf("%d  ",a);
            }    
            total_head=total_head+abs(tot_disk - arr[i-1] - 1);
            printf("%d  ",tot_disk-1);
            total_head+=abs(tot_disk -1 - 0);
            a=0;
            printf("%d  ",a);
            for(i=0;i<index;i++)
            {  
                total_head=total_head+(abs(arr[i]-a));
                a=arr[i];
                 printf("%d  ",a);
            }
            
            }
    else //if movement is towards low value
    {
        for(i=index-1;i>=0;i--)
        {   
            total_head+=(abs(arr[i]-a));
            a=arr[i];
            printf("%d  ",a);
        }
        total_head+=(abs(arr[i+1]-0));   //moving to 0 Here we nee to arr[i+1] becoz in the previous loop i is decremented
        total_head+=(abs(tot_disk-1 -0));
        printf("%d  ",0);
        a=tot_disk-1; //moving other end
        printf("%d  ",a); 
        for(i=n-1;i>=index;i--)
        {
            total_head+=(abs(arr[i]-a));
            a=arr[i];
            printf("%d  ",a);
        }

    }
            printf("\nthe total head movement for Cscan is %d\n",total_head);
}


void clook_total_head_movement(int arr[],int n,int initial,int tot_disk)
{
    int a=initial;
    int i,move,index,total_head=0;
    for(i=0;i<n;i++)
    {
        if(a<arr[i])
        {
            index=i;
            break;
        }
    }
    printf("\nEnter 1 for moving towards higher value(left to right) \nenter 0 for moving towards lower value(right to left) :");
    scanf("%d",&move);
    if(move==1)
    {
        for(i=index;i<n;i++)
        {  
            total_head+=(abs(arr[i]-a));
            a=arr[i];
             printf("%d  ",a);
            }    
            for(i=0;i<index;i++)
            {  
                total_head=total_head+(abs(arr[i]-a));
                a=arr[i];
                 printf("%d  ",a);
            }
            
            }
    else //if movement is towards low value
    {
        for(i=index-1;i>=0;i--)
        {   
            total_head+=(abs(arr[i]-a));
            a=arr[i];
            printf("%d  ",a);
        }
        for(i=n-1;i>=index;i--)
        {
            total_head+=(abs(arr[i]-a));
            a=arr[i];
            printf("%d  ",a);
        }

    }
            printf("\nthe total head movement for Clook is %d",total_head);
}
int main()
{
    int *arr,n;
    printf("enter the number of requests :");
    scanf("%d",&n);
    arr=(int *)malloc(sizeof(int)*n);
    int i=0,initial,tot_disk;
    printf("Enter the request\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",(arr+i));
    }
    printf("\nenter the initial position of head :");
    scanf("%d",&initial);
    printf("\nenter the number of total disk :");
    scanf("%d",&tot_disk);
    sort(arr,n);
    for(i=0;i<n;i++)
    {
        printf("%d  ",*(arr+i));
    }
    cscan_total_head_movement(arr,n,initial,tot_disk);
    
    clook_total_head_movement(arr,n,initial,tot_disk);
    return 0;
}