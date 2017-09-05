#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

#define NUMP 5

pthread_mutex_t fork_mutex[NUMP];

pthread_mutex_t pickup;
pthread_mutex_t put_down;

pthread_cond_t can_eat;

int curr_eating;

int eat = 3;

int main()
{
    int i;
    pthread_t diner_thread[NUMP];
    int dn[NUMP];
    void *diner();
    

    curr_eating = 0;


    for (i = 0; i < NUMP; i++)
        pthread_mutex_init(&fork_mutex[i], NULL);
    /* TASK 1 */
    pthread_mutex_init(&pickup, NULL);
    pthread_mutex_init(&put_down, NULL);
    /* TASK 2 */
    pthread_cond_init(&can_eat, NULL);

    for (i = 0; i < NUMP; i++)
    {
        dn[i] = i;
        pthread_create(&diner_thread[i], NULL, diner, &dn[i]);
    }
    for (i = 0; i < NUMP; i++)
        pthread_join(diner_thread[i], NULL);
    pthread_exit(0);
}

void *diner(int *i)
{
    int v;
    int eating = 0;
    printf("I'm diner %d\n", *i);
    v = *i;
    while (eating < 5)
    {
        printf("%d is thinking\n", v);
        sleep(v / 2);
        printf("%d is hungry\n", v);

        pthread_mutex_lock(&pickup); 
        while (curr_eating >= eat)
        {
            pthread_cond_wait(&can_eat, &pickup);
        }
        pthread_mutex_lock(&fork_mutex[v]);
        pthread_mutex_lock(&fork_mutex[(v + 1) % NUMP]);
        pthread_mutex_unlock(&pickup); 
        printf("%d is eating\n", v);
        curr_eating++;
        eating++;
        sleep(1);
        printf("%d is done eating\n", v);
        pthread_mutex_lock(&put_down);
        curr_eating--;
        pthread_mutex_unlock(&fork_mutex[v]);
        pthread_mutex_unlock(&fork_mutex[(v + 1) % NUMP]);
        pthread_cond_broadcast(&can_eat); 
        pthread_mutex_unlock(&put_down);
    }
    pthread_exit(NULL);
}

