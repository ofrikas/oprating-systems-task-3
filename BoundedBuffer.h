/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/

#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H

#include <queue>
#include <semaphore.h>

class BoundedBuffer {
public:
    BoundedBuffer(int size);
    ~BoundedBuffer();

    void insert(const char* s);
    char* remove();
    bool empty();

private:
    int maxSize;
    std::queue<char*> buffer;
    sem_t semEmpty;
    sem_t semFull;
    sem_t mutex;

    // Private methods for internal synchronization
    void waitCounting(sem_t &sem1, sem_t &sem2);
    void signalCounting(sem_t &sem1, sem_t &sem2);
};

#endif // BOUNDEDBUFFER_H
