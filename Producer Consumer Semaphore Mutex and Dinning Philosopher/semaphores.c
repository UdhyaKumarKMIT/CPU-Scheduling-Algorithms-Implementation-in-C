#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>


#define maxitems 5
#define BufferSize 5


sem_t empty;
sem_t full;
int in=0;         //index to produce data
int out=0;        //index to condsume data
int buffer[BufferSize];

pthread_mutex_t mutex;  //pthread_mutex_t is the inbuilt datatype mutex is the variable name


void *producer(void *pno)
{
        int item;
        for(int i=0;i<maxitems;i++){
                item = rand()%100;
                //wait/sleep when there are no empty slots
                sem_wait(&empty);//wait() operation to test
                pthread_mutex_lock(&mutex);
                buffer[in]=item;
                printf("Producer %d Produced %d at %d \n",*((int *)pno),buffer[in],in);
                in=(in+1)%BufferSize;
                pthread_mutex_unlock(&mutex);
                sem_post(&full);  //signal /wake to consumer that buffer has some data that can be consumed

        }
}



void *consumer(void *cno)
{
        for(int i=0;i<maxitems;i++)
        {
                sem_wait(&full); // wait/sleep when there are no slots to consume
                //enter CS so locking using pthread_mutex_lock inbuilt method
                pthread_mutex_lock(&mutex);
                int item=buffer[out];
                printf("Consumer %d consumer item %d from %d\n",*((int *)cno),item,out);
                out=(out+1)%BufferSize;
                pthread_mutex_unlock(&mutex);
                //exit CS so unlocking using pthread_mutex_unlock inbuilt function
                sem_post(&empty);    //signal/wake to the producer that there are empty slots
        }
}



int main()
{
        pthread_t pro[5],con[5];
        pthread_mutex_init(&mutex,NULL);
        sem_init(&empty,0,BufferSize);
        sem_init(&full,0,0);

        int a[5]={1,2,3,4,5};
        for(int i=0;i<5;i++)
                pthread_create(&pro[i],NULL,(void *)producer,(void *)&a[i]);

        for(int i=0;i<5;i++)
                 pthread_create(&con[i],NULL,(void *)consumer,(void *)&a[i]);

        for(int i=0;i<5;i++)
                pthread_join(pro[i],NULL);
        for(int i=0;i<5;i++)
                pthread_join(con[i],NULL);

        pthread_mutex_destroy(&mutex);
        sem_destroy(&empty);
        sem_destroy(&full);

        return 0;
}