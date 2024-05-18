#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    float hrrn;
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
}pro* delete_from_maxheap(struct heap *ready, int n) {
    if (ready->N == 0)
        return NULL;

    pro* maxProcess = ready->maxheap[0]; // Store the process with maximum HRRN
    ready->N--;

    ready->maxheap[0] = ready->maxheap[ready->N];

    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < ready->N && ready->maxheap[left]->hrrn > ready->maxheap[i]->hrrn)
            largest = left;
        if (right < ready->N && ready->maxheap[right]->hrrn > ready->maxheap[largest]->hrrn)
            largest = right;

        if (largest != i) {
            swap(&ready->maxheap[i], &ready->maxheap[largest]);
            i = largest;
        } else {
            break;
        }
    }

    maxProcess->visited = 1;
    return maxProcess;
}

void calculate_HRRN(pro *process,int time)
{
    process->hrrn=(float)(time - process->at + process->bt) / process->bt;
}

void insert_into_maxheap(pro *process, struct heap *ready, int time, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (process[i].at <= time && process[i].visited == 0) {
            process[i].visited = 1;
            calculate_HRRN(&process[i], time);
            int N = ready->N;
            ready->maxheap[N] = &process[i];
            ready->N++;

            while (N != 0 && (ready->maxheap[(N - 1) / 2])->hrrn < (ready->maxheap[N])->hrrn) {
                swap(&ready->maxheap[(N - 1) / 2], &ready->maxheap[N]);
                N = (N - 1) / 2;
            }
        }
    }
}



void heapify_maxheap(struct heap *ready, int time, int n) {
    // Update HRRN values for all processes
    for (int i = 0; i < ready->N; i++) {
        calculate_HRRN(ready->maxheap[i], time);
    }

    int i = 0;
    int largest = i;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Find the largest element among the root, left child, and right child
        if (left < ready->N && ready->maxheap[left]->hrrn > ready->maxheap[i]->hrrn)
            largest = left;
        if (right < ready->N && ready->maxheap[right]->hrrn > ready->maxheap[largest]->hrrn)
            largest = right;

        if (largest != i) {
            // Swap the root with the largest child
            swap(&ready->maxheap[i], &ready->maxheap[largest]);
            i = largest;
        } else {
            break; // Heap property satisfied
        }
    }
}

void compute_HRRN(pro process[],struct heap *ready,int n)
{
    int time = 0, completed = 0;
    insert_into_maxheap(process,ready,time,n);
    while (ready->N==0)  //This is done to ensure one proces is inserted
    {
        time++;
        insert_into_maxheap(process,ready,time,n);
    }
    time=(ready->maxheap[0])->at;  //Setting time to AT of first coming process (0 or 1 or more than that)
    
    while (ready->N != 0 || completed < n) {
        insert_into_maxheap(process, ready, time, n);
        pro *p = delete_from_maxheap(ready, n);
        time += p->bt;
        heapify_maxheap(ready,time,n);
        p->ct = time;
        p->tat = p->ct - p->at;
        p->wt = p->tat - p->bt;
        printf("%d\t%d\t%d\t%d\t%d\n", p->pid, p->at, p->bt, p->ct, p->visited);
        completed++;
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
        process[i].hrrn=0.0;
    }
    compute_HRRN(process,ready,n);
    
    printf("\nProcess ID \t    AT   \t BT  \t CT   \t TAT \t     WT\n");
    for (i = 0; i < n; i++) {
        printf("%10d %10d %10d%10d%10d %10d\n", process[i].pid, process[i].at, process[i].bt, process[i].ct,process[i].tat,process[i].wt);
    }
    compute_avg_tat_wt(process,n);
    return 0;
}
