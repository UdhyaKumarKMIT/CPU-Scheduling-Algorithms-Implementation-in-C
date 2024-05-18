#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int visited;
 
};
typedef struct process pro;

struct heap {
    int N;
    pro *maxheap[20];
};


void swap(pro **p1, pro **p2) {   //p1 is a pointer that holds an address we are swapping the address stored in two adresses.
    pro *temp = NULL;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
void insert_maxheap(pro process[],int n,int time,struct heap *ready){
    int i;
     for (i = 0; i < n; i++) {
        if (process[i].at <= time && process[i].visited == 0) {
            process[i].visited=1;
            int N = ready->N;
            ready->maxheap[N] = &process[i];
            printf("\nThe time is  : %d",time);
            printf("\nThe Inserted is %d %d %d \n",process[i].pid,process[i].at,process[i].bt);
           ready->N++;
          while (N > 0 && (ready->maxheap[(N - 1) / 2])->bt < (ready->maxheap[N])->bt) {
                swap(&ready->maxheap[(N - 1) / 2], &ready->maxheap[N]);
                N = (N - 1) / 2;
            }
        }
    }
}

void compute_avg_tat_wt(pro *p,int n)
{
    float stat=0.0,swt=0.0;
    int i;
    for(i=0;i<n;i++)
    {
        stat+=(p+i)->tat;
        swt+=(p+i)->wt;

    }
    printf("\nThe average TAT is %.3f ",(float)stat/n);
    printf("\nThe avergae WT is %.3f ",(float)swt/n);

}


/*

void heapify(struct heap *ready, int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && ready->maxheap[left]->rbt > ready->maxheap[largest]->rbt) {
        largest = left;
    }

    if (right < n && ready->maxheap[right]->rbt > ready->maxheap[largest]->rbt) {
        largest = right;
    }

    if (largest != i) {
        swap(&ready->maxheap[i], &ready->maxheap[largest]);
        heapify(ready, largest, n);
    }
}*/
void heapify(struct heap *ready, int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && 
        (ready->maxheap[left]->bt > ready->maxheap[largest]->bt || 
         (ready->maxheap[left]->bt == ready->maxheap[largest]->bt && ready->maxheap[left]->at < ready->maxheap[largest]->at))) {
        largest = left;
    }

    if (right < n && 
        (ready->maxheap[right]->bt > ready->maxheap[largest]->bt || 
         (ready->maxheap[right]->bt == ready->maxheap[largest]->bt && ready->maxheap[right]->at < ready->maxheap[largest]->at))) {
        largest = right;
    }

    if (largest != i) {
        swap(&ready->maxheap[i], &ready->maxheap[largest]);
        heapify(ready, largest, n);
    }
}

pro *extract_max(struct heap *ready){
    
       pro *p= ready->maxheap[0];  
       int N=ready->N; 
       ready->maxheap[0]=ready->maxheap[N - 1];
       ready->maxheap[N - 1]=p;
       ready->N--;
       heapify(ready, 0, N - 1);
      return p;
}

void printing(struct heap *ready){
    int i;
    printf("The arry is \n");
    for(i=0;i<ready->N;i++)
    {
        printf("\t %d ",(ready->maxheap[i])->pid);
    }
}
void compute_LJF(pro process[],int n,struct heap * ready)
{   
    int time=0;
    int completed=n;
    while(completed>0)
    {   printing(ready);
        while (ready->N<1)
        {
            time++;
            insert_maxheap(process,n,time,ready);
        }
        
        pro *p=extract_max(ready);
        printf("\nThe deleted is %d %d %d",p->pid,p->at,p->bt);
        p->visited=1;
        time=time+p->bt;
        p->ct =time;
        p->tat=time - p->at;
        p->wt=p->tat - p->bt;
        insert_maxheap(process,n,time,ready);
        completed--;
    }
}



int main() {
    struct heap *ready = (struct heap *)malloc(sizeof(struct heap));
    ready->N = 0; // ready is the ptr variable
    int n;
    printf("\nEnter the number of process :");
    scanf("%d", &n);
    pro *process;
    process = (pro *)malloc(sizeof(pro) * n);
    int i, tq;
    for (i = 0; i < n; i++) {
        process[i].pid = i + 1;
        printf("\nEnter the arrival time for %d  :", process[i].pid);
        scanf("%d", &process[i].at);
        printf("Enter the burst time for %d  :", process[i].pid);
        scanf("%d", &process[i].bt);
   
        process[i].visited = 0;
        process[i].ct = 0;
    }
    compute_LJF(process,n,ready);
    printf("\nProcess ID \t    AT   \t BT  \t CT   \t TAT \t    WT\n");
    for (i = 0; i < n; i++) {
        printf("%10d %10d %10d%10d%10d %10d\n", process[i].pid, process[i].at, process[i].bt, process[i].ct,process[i].tat,process[i].wt);
    }
   compute_avg_tat_wt(process,n);
    return 0;
}
