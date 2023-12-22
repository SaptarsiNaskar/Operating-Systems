#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// A struct that represents a reader-writer lock
typedef struct {
    // A mutex that protects the shared data and the counters
    pthread_mutex_t mutex;
    // A condition variable that signals when the lock is available
    pthread_cond_t cv;
    // A counter that keeps track of the number of active readers
    int readers;
    // A flag that indicates whether there is an active writer
    int writer;
} rwlock_t;

// A function that initializes a reader-writer lock
void rwlock_init(rwlock_t *lock) {
    // Initialize the mutex
    pthread_mutex_init(&lock->mutex, NULL);
    // Initialize the condition variable
    pthread_cond_init(&lock->cv, NULL);
    // Initialize the number of active readers to zero
    lock->readers = 0;
    // Initialize the flag of active writer to zero
    lock->writer = 0;
}

// A function that acquires a read lock
void readLock(rwlock_t *lock) {
    // Lock the mutex
    //write your code
    pthread_mutex_lock(&lock->mutex);
    
    // Wait until there is no active writer
    //write your code
    while(lock->writer > 0) {
        pthread_cond_wait(&lock->cv, &lock->mutex);
    }
    
    // Increment the number of active readers
    //write your code
    lock->writer++;

    // Unlock the mutex
    //write your code;
    pthread_mutex_unlock(&lock->mutex);
}

// A function that releases a read lock
void readUnlock(rwlock_t *lock) {
    // Lock the mutex
    //write your code
    pthread_mutex_lock(&lock->mutex);

    // Decrement the number of active readers
    //write your code
    lock->writer--;

    // If there are no more active readers, signal the condition variable. Think carefully between pthread_cond_signal() and pthread_cond_broadcast()
    //write your code
    if(lock->readers == 0) {
        pthread_cond_signal(&lock->cv);
    }


    // Unlock the mutex
    //write your code
    pthread_mutex_unlock(&lock->mutex);
}

// A function that acquires a write lock
void writeLock(rwlock_t *lock) {
    // Lock the mutex
    //write your code
    pthread_mutex_lock(&lock->mutex);

    // Wait until there is no active writer or reader
    //write your code
    while(lock->writer > 0 && lock->readers > 0) {
        pthread_cond_wait(&lock->cv, &lock->mutex);
    }

    // Set the writer flag with appropriate value
    //write your code
    lock->writer = 1;

    // Unlock the mutex
    //write your code
    pthread_mutex_unlock(&lock->mutex);
}

// A function that releases a write lock
void writeUnlock(rwlock_t *lock) {
    // Lock the mutex
    //write your code
    pthread_mutex_lock(&lock->mutex);

    // Set the writer flag with appropriate value
    //write your code
    lock->writer = 0;

    // Signal the condition variable. Think carefully between pthread_cond_signal() and pthread_cond_broadcast()
    //write your code
    pthread_cond_broadcast(&lock->cv);

    // Unlock the mutex
    //write your code
    pthread_mutex_unlock(&lock->mutex);
    
}

// global variables that represent the shared data
// open a file named "file.txt" in read-write mode, creating it if it doesn't exist. Also ensure everytime you write it should follow append.
// the opened file descriptor should consider as a global variable.
// write your code
//#define fd1 {(open("file.txt", O_RDWR|O_APPEND))}
int fd1;


char c[1000];

int data = 0;

// A global variable that represents the reader-writer lock
rwlock_t lock;

// A function that simulates a reader thread
void *reader(void *arg) {
    // Get the thread id from the argument
    int id = *(int *)arg;

    // Acquire a read lock
    //write your code
    readLock(&lock);

    printf("Reader %d: data = %d\n", id, data);

    // Read the shared data
    // Read the file and print it's content in the terminal with the reader thread id (id) and data. (you can work with a fixed sized buffer. Minimum length 100)
    //  [Example Format:(Reader thread id: 1 -> with data: 1 -> file content: content of the file)]
    // write your code
    //char* c = (char*)calloc(100000, sizeof(char)); 
    int sz = read(fd1, c, sizeof(c));
    printf("Reader thread id: %d -> with data: %d -> file content: %s\n", id, data, c);
    /*
    for(int i = 0; i < sizeof(c); i++) {
        printf("%c", c[i]);
    }
    printf("\n");
    */
    
    

    // Release a read lock
    // write your code
    readUnlock(&lock);

    return NULL;
}

// A function that simulates a writer thread
void *writer(void *arg) {
    // Get the thread id from the argument
    int id = *(int *)arg;

    // Acquire a write lock
    // write your code
    writeLock(&lock);

    data++;
    printf("Writer %d: data = %d\n", id, data);

    // Write to the shared data
    // write the writer thread id (id) to the file with data. You should write with append. [Example Format: (Writer thread : 1 with data: 1)]
    // also add a new line when you perform a write operation
    // write your code
    
    /*
    int sz = write(fd1, "Writer thread:  ", sizeof("Writer thread: "));
    int sz1 = write(fd1, &id, sizeof(id));
    int sz2 = write(fd1, " with data: ", sizeof(" with data: "));
    int sz3 = write(fd1, &data, sizeof(data));
    int sz4 = write(fd1, " \n", sizeof(" \n"));
    */
   //char d[1000];
   snprintf(c, sizeof(c), "Writer thread : %d with data: %d\n", id, data);
   int sz = write(fd1, c, sizeof(c));
    
    

    // Release a write lock
    // write your code
    writeUnlock(&lock);
    
    
    return NULL;
}

// A constant that defines the number of reader threads
#define NUM_READERS 5

// A constant that defines the number of writer threads
#define NUM_WRITERS 3

// The main function
int main(int argc, char *argv[]) {
    // Initialize the reader-writer lock
    // write your code
    rwlock_init(&lock);
    fd1 = open("file.txt", O_RDWR|O_APPEND|O_CREAT, 0666);
    

    // Create an array of reader thread ids
    // write your code
    int threadReadersID[NUM_READERS];
    
    // Create an array of writer thread ids
    // write your code
    int threadWritersID[NUM_WRITERS];

    // Create an array of reader thread handles
    // write your code
    pthread_t threadReadersHandle[NUM_READERS];
    /*
    for(int i = 0; i < NUM_READERS; i++) {
        nReaders[i] = i;
    }
    */

    
    // Create an array of writer thread handles
    // write your code 
    pthread_t threadWritersHandle[NUM_WRITERS];
    /*
    for(int i = 0; i < NUM_WRITERS; i++) {
        nWriters[i] = i;
    }
    */
    

    // Loop through the writer thread ids
    for (int i = 0; i < NUM_WRITERS; i++) {
        // Assign the id to the current index
        // update the value of writer thread ids array
        // write your code 
        threadWritersID[i] = i + 1;
        
        // Create a writer thread with the corresponding id
        // write your code
        pthread_create(&threadWritersHandle[i], NULL, writer, &threadWritersID[i]);
    }

    // Loop through the reader thread ids
    for (int i = 0; i < NUM_READERS; i++) {
        // Assign the id to the current index
        // update the value of reader thread ids array 
        // write your code
        threadReadersID[i] = i + 1;
        
        // Create a reader thread with the corresponding id
        // write your code
        pthread_create(&threadReadersHandle[i], NULL, reader, &threadReadersID[i]);
    }

    // Loop through the writer thread handles
    for (int i = 0; i < NUM_WRITERS; i++) {
        // Join the writer thread
        // write your code
        pthread_join(threadWritersHandle[i], NULL);
    }

    // Loop through the reader thread handles
    for (int i = 0; i < NUM_READERS; i++) {
        // Join the reader thread
        // write your code
        pthread_join(threadReadersHandle[i], NULL);
        
    }

    close(fd1);
    
    
    return 0;
}