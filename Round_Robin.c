#include<stdio.h>
#include<stdlib.h>

struct process{
        int pid;
        int at;
        int bt;
        int rbt;
        int ct;
        int tat;
        int wt;
        int in;
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
        queue[rear]=p;
}else{
rear++;
queue[rear]=p;
}}

process* dequeue()
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
void appendreadyqueue(process pro[],int time,int n)
{
  int i;
  for(i=0;i<n;i++)
  {
          if(pro[i].at<=time &&  pro[i].visited==0 && pro[i].in==0)
           {
                   pro[i].visited=1;
                    pro[i].in=1;
                   enqueue(&pro[i]);
                  
                printf("\nenqueued at apend %d\n",pro[i].pid);
           }
}
}

void computeroundrobin(process pro[],int n,int tq)
{
       int time=pro[0].at;
       int completed=0;
       pro[0].in=1;
       process *t=&pro[0];
       enqueue(t);
       printf("\nInitial enqueue %d %d %d\n",pro[0].pid,front,rear);
       while(!(front==-1 && rear==-1)  || completed<n)
       {
             while(front==-1)
             {
                time++;
                appendreadyqueue(pro,time,n);
             }
              process *w=dequeue();
              w->in=0;
              printf("dequeued %d\n",w->pid);
              if(w->rbt > tq)
              {
              time=time+tq;
              w->rbt=w->rbt-tq;
              }
              else
              {
                   time=time+w->rbt;
                   w->ct=time;
                   completed++;
                   printf("\nPid : %d CT : %d\n",w->pid,w->ct);
                   w->rbt=0;
              }
              w->visited=1;
              //printf("%d \t\t\t%d\n",front,rear);
              appendreadyqueue(pro,time,n);
               if(w->rbt>0){
                    w->visited=0;
                    enqueue(w);
                    w->in=1;
                    printf("\nenqueued at remain %d\n",w->pid);

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
        int n;
        printf("\nEnter the number of process :");
        scanf("%d",&n);
        process *pro;
        queue=(process **)malloc(sizeof(process *)*100);
        pro=(process *)malloc(sizeof(process)*n);
        int i,tq;
        for(i=0;i<n;i++)
        {
                pro[i].pid=i+1;
                printf("\nEnter the arrival time for %d  :",pro[i].pid);
                scanf("%d",&pro[i].at);
                printf("\nEnter the burst time for %d  :",pro[i].pid);
                scanf("%d",&pro[i].bt);
                pro[i].rbt=pro[i].bt;
                pro[i].visited=0;
                pro[i].in=0;
        }
        printf("\nEnter the time quantum:");
        scanf("%d",&tq);
        computeroundrobin(pro,n,tq);
        tat_and_wt(pro,n);
 printf("\nProcess ID \t    AT  \t BT \t CT \t  TAT  \t WT\n");
        for(i=0;i<n;i++)
        {
 printf("%10d %10d %13d %7d  %7d  %7d\n",pro[i].pid,pro[i].at,pro[i].bt,pro[i].ct,pro[i].tat,pro[i].wt);

}
}



/* 
CHECK THE CODE BY USING PRINT STATEMENTS 


WHEN ARRAY IS PASSED BY VALUE THE CHANGES MADE WILL NOT BE REFLECTED IN THE ORGINAL ARRAY SO CALL BY CALL BY REFERENCE

PROCESS **QUEUE;
QUEUE IS ARRAY OF ARRAYS OF ADDRESS

queue=(process **)malloc(sizeof(process *)*100);


use p[i].in=1 or 0 to identify whether the process is already in the queue or not r
*/