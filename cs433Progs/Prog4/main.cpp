// ===========================================================================
// Name: Oscar Lopez
// Date: 04/10/25
// Course: CS433 - Operating Systems Section 1
// Assignment: 4 - Multi-threaded Programing for the Producer-Consumer Problem 
// File type: main.cpp - driver file
// ===========================================================================
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h>
#include "buffer.h"

// semaphores needed for synchronization
pthread_mutex_t mutex;  // mutex lock
sem_t full;             // counting semaphore
sem_t empty;            // counting semaphore

// forward declarations used in producer consumer functions
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void display();

// PURPOSE: produces an item in the buffer.
// PARAMETER: *param = used to pass pthread_create function
void* producer(void *param)
{
    // Get producer ID from param (starting at 1)
    long producer_id = (long)param;
    buffer_item item = producer_id;  // Producer inserts its own ID

    while (true) {
        // Sleep for random time under 1 second (1,000,000 microseconds)
        usleep(rand() % 1000000);
        
        sem_wait(&empty);                   // acquire the semaphore, wait till not full
        pthread_mutex_lock(&mutex);         // enforce the mutex to access critical section

        // critical section ...
        if (insert_item(item) == 0) {
            std::cout << "Producer " << producer_id << ": Inserted item " << item << std::endl;
            std::cout << "Buffer: ";
            display();
        }
        else {
            std::cout << "Producer " << producer_id << ": Error inserting item" << std::endl;
        }
        // end of critical section ...

        pthread_mutex_unlock(&mutex);       // unlock the mutex
        sem_post(&full);                    // release the semaphore, increment full
    }
}

// PURPOSE: consumes an item in the buffer.
// PARAMETER: *param = used to pass pthread_create function
void *consumer(void *param)
{
    // Get consumer ID from param
    long consumer_id = (long)param;
    buffer_item item;

    while (true) {
        // Sleep for random time under 1 second (1,000,000 microseconds)
        usleep(rand() % 1000000);
        
        sem_wait(&full);                    // acquire the semaphore, wait til not empty
        pthread_mutex_lock(&mutex);         // enforce the mutex to access critical section

        // critical section ...
        if (remove_item(&item) == 0) {
            std::cout << "Consumer " << consumer_id << ": Removed item " << item << std::endl;
            std::cout << "Buffer: ";
            display();
        }
        else {
            std::cout << "Consumer " << consumer_id << ": Error removing item" << std::endl;
        }
        // end of critical section ...

        pthread_mutex_unlock(&mutex);       // unlock the mutex
        sem_post(&empty);                   // release the semaphore, decrement empty
    }
}

// This is the driver to test out the implementation for solving the producer consumer problem.
int main(int argc, char *argv[])
{
    // input handling
    if (argc != 4) {
        std::cout << "Usage: ./prog4 <sleeptime> <pthreadc> <cthreadc>" << std::endl;
        exit(1);
    }

    srand(time(NULL));

    // 1. Get command line arguments argv[1], argv[2], argv[3]
    int sleeptime = atoi(argv[1]);      // 1st arg is the sleep time
    int pthreadc = atoi(argv[2]);       // 2nd arg is the # of producer threads
    int cthreadc = atoi(argv[3]);       // 3rd arg is the # of consumer threads

    // 2. Initialize buffer / threads / semaphores
    pthread_t producer_threads[pthreadc];
    pthread_t consumer_threads[cthreadc];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);   // empty initialized to buffer size
    sem_init(&full, 0, 0);              // full initialized to 0

    // 3. Create producer thread(s)
    for (int i = 0; i < pthreadc; i++)
        pthread_create(&producer_threads[i], NULL, producer, (void*)(long)(i+1));  // IDs start from 1

    // 4. Create consumer thread(s)
    for (int i = 0; i < cthreadc; i++)
        pthread_create(&consumer_threads[i], NULL, consumer, (void*)(long)(i+1));  // IDs start from 1

    // 5. Sleep 
    sleep(sleeptime);

    std::cout << "\nThreads finished! Exiting... \n";

    // 6. Destroy the mutex and semaphores before exiting
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    // 7. Exit 
    exit(0);
}
