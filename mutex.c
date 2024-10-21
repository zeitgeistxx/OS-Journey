// Locking -> Critical Section Execute -> Unlocking

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUM 4

int shared_variable = 0;

// Mutex for synchronizing access to the shared resource
pthread_mutex_t mutex;

void *thread_function(void *arg)
{
    int thread_id = *(int *)arg;

    // Lock the mutex before accessing the shared resource
    pthread_mutex_lock(&mutex);

    // Critical section
    printf("Thread %d is accessing the shared variable\n", thread_id);
    shared_variable++;
    printf("Thread %d incremented shared_variable to %d\n", thread_id, shared_variable);

    // Unlock the mutex
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t threads[THREAD_NUM];
    int thread_ids[THREAD_NUM];

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        fprintf(stderr, "Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    for (int i = 0; i < THREAD_NUM; i++)
    {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0)
        {
            fprintf(stderr, "Failed to create thread %d\n", i);
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    printf("Final value of shared_variable: %d\n", shared_variable);
}