#include<stdio.h>
#include<stdlib.h>

struct process{
        int pid;
        int at;
        int bt; 
        int ct;
        int tat;
        int wt;
        int visited;
};
typedef struct process process;

process **queue;
int front=-1,rear=-1;

void enqueue(process *p)
{
        if(front==-1 && rear==-1)
        {
                front=0;
                rear=0;
        }
        else{
                rear++;
        }
        queue[rear]=p;
}
process * dequeue()
{
        process *q=queue[front];
        front++;
        if(front>rear)
        {
              front=-1;
              rear=-1;
              
                         }
return q;
}

void computeFCFS(process pro[],int n,int cs)
{
         enqueue(&pro[0]);
         process *t;
        int i,time=pro[0].at;
         pro[0].visited=1;
         while(!(front==-1 && rear==-1))
         {
             t=dequeue();
             time+=t->bt;
             t->ct=time;
             time+=cs;
             
             for(i=0;i<n;i++)
             {
                if(pro[i].at<=time && pro[i].visited==0)
                {
                        enqueue(&pro[i]);
                        pro[i].visited=1;
                }
             }

         }
}

void sort(process pro[],int n)
{
        int i,j;
        for(i=0;i<n-1;i++)
        {
                for(j=0;j<n-1-i;j++)
                {
                    if(pro[j].at > pro[j+1].at)
                   {
                        process temp=pro[j];
                        pro[j]=pro[j+1];
                        pro[j+1]=temp;

                   }
                   

                }
        }
}

void tat_and_wt(process pro[],int n)
{
        int i; 
        float stat=0.0,swt=0.0;
        for(i=0;i<n;i++)
        {
                pro[i].tat=pro[i].ct - pro[i].at;
                pro[i].wt=pro[i].tat - pro[i].bt;
                stat+=pro[i].tat;
                swt+=pro[i].wt;

        }
        printf("\n The Average TAT is %f",(float)stat/n);
        printf("\nThe Average Wt is %f\n",(float)swt/n);
}
int main()
{
        int n,i,cs;
        printf("\nEnter the number of process :");
        scanf("%d",&n);
        
        process *pro;
        queue=(process **)malloc(sizeof(process *)*100);
        pro=(process *)malloc(sizeof(process)*n);
       
        for(i=0;i<n;i++)
        {
                pro[i].pid=i+1;
                printf("\nEnter the arrival time for %d  :",pro[i].pid);
                scanf("%d",&pro[i].at);
                printf("\nEnter the burst time for %d  :",pro[i].pid);
                scanf("%d",&pro[i].bt);
                pro[i].visited=0;
                
        }
        printf("\nEnter the context switching time :");
        scanf("%d",&cs);
        sort(pro,n);
        
        computeFCFS(pro,n,cs);
        tat_and_wt(pro,n);





 printf("\nProcess ID \t    AT  \t BT \t CT \t  TAT  \t   WT\n");
        for(i=0;i<n;i++)
        {
 printf("%10d %10d %13d %7d  %7d  %7d\n",pro[i].pid,pro[i].at,pro[i].bt,pro[i].ct,pro[i].tat,pro[i].wt);

}
}

