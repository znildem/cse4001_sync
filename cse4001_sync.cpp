#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "semaphore_class.h"

static const int NUM_READERS = 5;
static const int NUM_WRITERS = 5;
static const int NUM_PHILOSOPHERS = 5;
static const int ITERATIONS = 5;

int random_delay() {
    return (rand() % 3) + 1;
}

class Lightswitch {
public:
    Lightswitch() : counter(0), mutex(1) {}

    void lock(Semaphore &sem) {
        mutex.wait();
        counter++;
        if (counter == 1) {
            sem.wait();
        }
        mutex.signal();
    }

    void unlock(Semaphore &sem) {
        mutex.wait();
        counter--;
        if (counter == 0) {
            sem.signal();
        }
        mutex.signal();
    }

private:
    int counter;
    Semaphore mutex;
};

// ==================== PROBLEM 1 ====================

Lightswitch p1_readSwitch;
Semaphore p1_roomEmpty(1);
Semaphore p1_turnstile(1);

void* p1_reader_thread(void* arg) {
    long id = (long) arg;

    for (int i = 0; i < ITERATIONS; i++) {
        printf("[P1] Reader %ld: wants to read\n", id);

        p1_turnstile.wait();
        p1_turnstile.signal();

        p1_readSwitch.lock(p1_roomEmpty);
        printf("[P1] Reader %ld: reading\n", id);
        sleep(random_delay());
        printf("[P1] Reader %ld: done\n", id);
        p1_readSwitch.unlock(p1_roomEmpty);

        sleep(random_delay());
    }

    printf("[P1] Reader %ld finished\n", id);
    return NULL;
}

void* p1_writer_thread(void* arg) {
    long id = (long) arg;

    for (int i = 0; i < ITERATIONS; i++) {
        printf("[P1] Writer %ld: wants to write\n", id);

        p1_turnstile.wait();
        p1_roomEmpty.wait();

        printf("[P1] Writer %ld: writing\n", id);
        sleep(random_delay());
        printf("[P1] Writer %ld: done\n", id);

        p1_roomEmpty.signal();
        p1_turnstile.signal();

        sleep(random_delay());
    }

    printf("[P1] Writer %ld finished\n", id);
    return NULL;
}

void run_problem1() {
    printf("Running problem 1\n");

    pthread_t r[NUM_READERS], w[NUM_WRITERS];

    for (long i = 0; i < NUM_READERS; i++)
        pthread_create(&r[i], NULL, p1_reader_thread, (void*)i);

    for (long i = 0; i < NUM_WRITERS; i++)
        pthread_create(&w[i], NULL, p1_writer_thread, (void*)i);

    for (int i = 0; i < NUM_READERS; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < NUM_WRITERS; i++)
        pthread_join(w[i], NULL);

    printf("Problem 1 complete\n");
}

// ==================== PROBLEM 2 ====================
// Writer-priority readers-writers

Semaphore p2_roomEmpty(1);
Semaphore p2_readTry(1);
Semaphore p2_rmutex(1);
Semaphore p2_wmutex(1);
int p2_readCount = 0;
int p2_writeCount = 0;

void* p2_reader_thread(void* arg) {
    long id = (long) arg;

    for (int i = 0; i < ITERATIONS; i++) {
        printf("[P2] Reader %ld: wants to read\n", id);

        p2_readTry.wait();
        p2_rmutex.wait();
        p2_readCount++;
        if (p2_readCount == 1) {
            p2_roomEmpty.wait();
        }
        p2_rmutex.signal();
        p2_readTry.signal();

        printf("[P2] Reader %ld: reading\n", id);
        sleep(random_delay());
        printf("[P2] Reader %ld: done\n", id);

        p2_rmutex.wait();
        p2_readCount--;
        if (p2_readCount == 0) {
            p2_roomEmpty.signal();
        }
        p2_rmutex.signal();

        sleep(random_delay());
    }

    printf("[P2] Reader %ld finished\n", id);
    return NULL;
}

void* p2_writer_thread(void* arg) {
    long id = (long) arg;

    for (int i = 0; i < ITERATIONS; i++) {
        printf("[P2] Writer %ld: wants to write\n", id);

        p2_wmutex.wait();
        p2_writeCount++;
        if (p2_writeCount == 1) {
            p2_readTry.wait();
        }
        p2_wmutex.signal();

        p2_roomEmpty.wait();

        printf("[P2] Writer %ld: writing\n", id);
        sleep(random_delay());
        printf("[P2] Writer %ld: done\n", id);

        p2_roomEmpty.signal();

        p2_wmutex.wait();
        p2_writeCount--;
        if (p2_writeCount == 0) {
            p2_readTry.signal();
        }
        p2_wmutex.signal();

        sleep(random_delay());
    }

    printf("[P2] Writer %ld finished\n", id);
    return NULL;
}

void run_problem2() {
    printf("Running problem 2\n");

    pthread_t r[NUM_READERS], w[NUM_WRITERS];

    for (long i = 0; i < NUM_READERS; i++)
        pthread_create(&r[i], NULL, p2_reader_thread, (void*)i);

    for (long i = 0; i < NUM_WRITERS; i++)
        pthread_create(&w[i], NULL, p2_writer_thread, (void*)i);

    for (int i = 0; i < NUM_READERS; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < NUM_WRITERS; i++)
        pthread_join(w[i], NULL);

    printf("Problem 2 complete\n");
}

// Helper functions for fork indices
int left_fork(int i) {
    return i;
}

int right_fork(int i) {
    return (i + 1) % NUM_PHILOSOPHERS;
}

// ==================== PROBLEM 3 ====================
// Dining philosophers #1 (footman / multiplex)

Semaphore p3_footman(4);  // allow at most 4 philosophers to sit
Semaphore* p3_forks[NUM_PHILOSOPHERS];

void p3_take_forks(int i) {
    p3_footman.wait();
    p3_forks[right_fork(i)]->wait();
    p3_forks[left_fork(i)]->wait();
}

void p3_put_forks(int i) {
    p3_forks[left_fork(i)]->signal();
    p3_forks[right_fork(i)]->signal();
    p3_footman.signal();
}

void* p3_philosopher(void* arg) {
    long id = (long) arg;

    for (int i = 0; i < ITERATIONS; i++) {
        printf("[P3] Philosopher %ld: thinking\n", id);
        sleep(random_delay());

        printf("[P3] Philosopher %ld: hungry\n", id);
        p3_take_forks((int)id);

        printf("[P3] Philosopher %ld: eating\n", id);
        sleep(random_delay());

        p3_put_forks((int)id);
        printf("[P3] Philosopher %ld: done eating\n", id);
    }

    printf("[P3] Philosopher %ld finished\n", id);
    return NULL;
}

void run_problem3() {
    printf("Running problem 3\n");

    // allocate fork semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        p3_forks[i] = new Semaphore(1);
    }

    pthread_t ph[NUM_PHILOSOPHERS];

    for (long i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_create(&ph[i], NULL, p3_philosopher, (void*)i);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(ph[i], NULL);

    printf("Problem 3 complete\n");

    // free semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        delete p3_forks[i];
    }
}

// ==================== PROBLEM 4 ====================
// Dining philosophers #2 (lefty/righty)

Semaphore* p4_forks[NUM_PHILOSOPHERS];

void p4_take_forks(int i) {
    if (i % 2 == 0) {
        // even philosophers: right then left
        p4_forks[right_fork(i)]->wait();
        p4_forks[left_fork(i)]->wait();
    } else {
        // odd philosophers: left then right
        p4_forks[left_fork(i)]->wait();
        p4_forks[right_fork(i)]->wait();
    }
}

void p4_put_forks(int i) {
    p4_forks[left_fork(i)]->signal();
    p4_forks[right_fork(i)]->signal();
}

void* p4_philosopher(void* arg) {
    long id = (long) arg;

    for (int i = 0; i < ITERATIONS; i++) {
        printf("[P4] Philosopher %ld: thinking\n", id);
        sleep(random_delay());

        printf("[P4] Philosopher %ld: hungry\n", id);
        p4_take_forks((int)id);

        printf("[P4] Philosopher %ld: eating\n", id);
        sleep(random_delay());

        p4_put_forks((int)id);
        printf("[P4] Philosopher %ld: done eating\n", id);
    }

    printf("[P4] Philosopher %ld finished\n", id);
    return NULL;
}

void run_problem4() {
    printf("Running problem 4\n");

    // allocate fork semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        p4_forks[i] = new Semaphore(1);
    }

    pthread_t ph[NUM_PHILOSOPHERS];

    for (long i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_create(&ph[i], NULL, p4_philosopher, (void*)i);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(ph[i], NULL);

    printf("Problem 4 complete\n");

    // free semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        delete p4_forks[i];
    }
}

// ==================== main ====================

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));

    if (argc != 2) {
        printf("Usage: %s <problem#>\n", argv[0]);
        printf("  1: no-starve readers-writers\n");
        printf("  2: writer-priority readers-writers\n");
        printf("  3: dining philosophers #1 (footman)\n");
        printf("  4: dining philosophers #2 (lefty/righty)\n");
        return 1;
    }

    int problem = atoi(argv[1]);

    switch (problem) {
        case 1:
            run_problem1();
            break;
        case 2:
            run_problem2();
            break;
        case 3:
            run_problem3();
            break;
        case 4:
            run_problem4();
            break;
        default:
            printf("Unknown problem number %d\n", problem);
            return 1;
    }

    return 0;
}
