#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int at;
    int bt;
    int rbt;
    int ct;
    int tat;
    int wt;
    int visited;
    int in;
};
typedef struct process pro;

struct heap {
    int N;
    pro *minheap[20];
};

void swap(pro **p1, pro **p2) {   //p1 is a pointer that holds an address we are swapping the address stored in two adresses.
    pro *temp = NULL;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

pro* delete_from_minheap(struct heap *ready, int n) {
    if (ready->N == 0) // If heap is empty
        return NULL;

    pro* minProcess = ready->minheap[0]; // Store the process with minimum burst time
    ready->N--;

    // Replace the root with the last element
    ready->minheap[0] = ready->minheap[ready->N];

    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        // Find the smallest among the root, left child, and right child
        if (left < ready->N && ready->minheap[left]->bt < ready->minheap[i]->bt)
            smallest = left;
        if (right < ready->N && ready->minheap[right]->bt < ready->minheap[smallest]->bt)
            smallest = right;

        if (smallest != i) {
            // Swap the root with the smallest child
            swap(&ready->minheap[i], &ready->minheap[smallest]);
            i = smallest;
        } else {
            break; // Heap property satisfied
        }
    }

    minProcess->visited = 1; // Mark the process as visited
    return minProcess;
}

void insert_into_minheap(pro *process, struct heap *ready, int time, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (process[i].at <= time && process[i].in == 0 && process[i].rbt>0) {
            process[i].visited=1;
            process[i].in=1;
            int N = ready->N;
            ready->minheap[N] = &process[i];
            printf("\nThe time is  : %d",time);
            printf("\nThe Inserted is %d %d %d %d\n",process[i].pid,process[i].at,process[i].bt,process[i].rbt);
            
            ready->N++;

            while (N != 0 && (ready->minheap[(N - 1) / 2])->bt > (ready->minheap[N])->bt) {
                swap(&ready->minheap[(N - 1) / 2], &ready->minheap[N]);
                N = (N - 1) / 2;
            }
        }
    }
}
/*
void compute_SRTF(pro process[], struct heap *ready, int n) {
    int time = 0, completed = 0;
    
    while (completed < n) {
        // Check if no processes are ready to execute
        if (ready->N == 0) {
            insert_into_minheap(process, ready, time, n);
            time++;
            continue; // Move to the next iteration
        }
    

        // Delete the process with the shortest remaining burst time
        pro *p = delete_from_minheap(ready, n);
        printf("\nThe deleted is %d %d %d %d", p->pid, p->at, p->bt,p->rbt);

        p->in = 0;
        printf("The time before executeio is %d",time);
        time = time + 1;
        p->rbt = p->rbt - 1;

        // If process completes execution
        if (p->rbt == 0) {
            p->ct = time;
            p->tat = p->ct - p->at;
            p->wt = p->tat - p->bt;
            completed++;
        } else { // If process still needs CPU time, insert it back into the ready queue
            insert_into_minheap(process, ready, time, n);
        }
        
        printf("%d\t%d\t%d\t%d\t%d\n", p->pid, p->at, p->bt, p->ct, p->visited);
    }
}
*/
void compute_SRTF(pro process[], struct heap *ready, int n) {
    int time=0,completed=0;
    
    while(ready->N == 0) {   //inserting one process
        insert_into_minheap(process, ready, time, n); // If no processes are ready to execute
            time++; // Move to the next time unit
    }
    time=(ready->minheap[0])->at;     //setting time of arrival of first process
    
    while (ready->N != 0 || completed<n) {
        pro *p = delete_from_minheap(ready, n);
        printf("\nThe deleted is %d %d %d",p->pid,p->at,p->bt);
     
        p->in=0;
        printf("\nThe time before 1 unit exe %d\n",time);
        time = time + 1;
        p->rbt=p->rbt - 1;
        if(p->rbt==0)
        {
        p->ct = time;
        p->tat=p->ct - p->at;
        p->wt=p->tat - p->bt;
        }
      
       //  printf("%d\t%d\t%d\t%d\t%d\n", p->pid, p->at, p->bt, p->ct,p->visited);
        insert_into_minheap(process, ready, time, n);
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
        process[i].rbt=process[i].bt;
        process[i].in=0;
        process[i].visited = 0;
        process[i].ct = 0;
    }
    compute_SRTF(process, ready, n);
    printf("\nProcess ID \t    AT   \t BT  \t CT   \t TAT \t    WT\n");
    for (i = 0; i < n; i++) {
        printf("%10d %10d %10d%10d%10d %10d\n", process[i].pid, process[i].at, process[i].bt, process[i].ct,process[i].tat,process[i].wt);
    }
    compute_avg_tat_wt(process,n);
    return 0;
}
