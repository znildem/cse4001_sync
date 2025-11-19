#ifndef SEMAPHORE_CLASS_H
#define SEMAPHORE_CLASS_H

#include <semaphore.h>
#include <stdexcept>

class Semaphore {
public:
    explicit Semaphore(unsigned int value = 0) {
        if (sem_init(&mSemaphore, 0, value) != 0) {
            throw std::runtime_error("sem_init failed");
        }
    }

    ~Semaphore() {
        sem_destroy(&mSemaphore);
    }

    void wait() {
        sem_wait(&mSemaphore);
    }

    void signal() {
        sem_post(&mSemaphore);
    }

    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

private:
    sem_t mSemaphore;
};

#endif // SEMAPHORE_CLASS_H

