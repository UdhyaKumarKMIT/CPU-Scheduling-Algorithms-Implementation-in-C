#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t chopstick[5];

void eat(int ph)
{
        printf("Philosopher %d begins to eat\n",ph);
}
void *philos(void *n)
{
        int ph=*(int *)n;
        printf("Philosopher %d wants to eat\n",ph);

        printf("Philosopher %d tries to pick left chopstick\n",ph);
        sem_wait(&chopstick[ph]);
        printf("philosopher %d picks the left chopstick\n",ph);

        printf("philosopher %d tries to pick the right chopstick\n",ph);
        sem_wait(&chopstick[(ph+1)%5]);
        printf("philosopher %d picks the right chopstick\n",ph);

        eat(ph);
        sleep(2);
        printf("Philosopher %d finished eating \n",ph);

        sem_post(&chopstick[(ph+1)%5]);
        printf("Philosopher %d leaves the right chopstick\n",ph);

        sem_post(&chopstick[ph]);
        printf("Philosopher %d leaves the left chopstick\n",ph);
}



int main()
{
        int i,n[5]={1,2,3,4,5};

        pthread_t thread[5];
        for(i=0;i<5;i++)
        {
                sem_init(&chopstick[i],0,1); //shared =0 global  //value is one so chopstick is free
        }
        for(i=0;i<5;i++)
        {
                pthread_create(&thread[i],NULL,philos,(void *)&n[i]);
        }
        for(i=0;i<5;i++)
        {
                pthread_join(thread[i],NULL);
        }

}
