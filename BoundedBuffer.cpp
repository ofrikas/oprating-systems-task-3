/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/

#include "BoundedBuffer.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

BoundedBuffer::BoundedBuffer(int size) : maxSize(size) {
    if (sem_init(&semEmpty, 0, size) != 0 ||
        sem_init(&semFull, 0, 0) != 0 ||
        sem_init(&mutex, 0, 1) != 0) {
        throw std::runtime_error("Failed to initialize semaphores");
    }
}

BoundedBuffer::~BoundedBuffer() {
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    sem_destroy(&mutex);

    // Clean up remaining items in the buffer
    while (!buffer.empty()) {
        char* item = buffer.front();
        buffer.pop();
        delete[] item;
    }
}

void BoundedBuffer::insert(const char* s) {
    sem_wait(&semEmpty);
    sem_wait(&mutex);

    char* newItem = new char[strlen(s) + 1];
    strcpy(newItem, s);
    buffer.push(newItem);

    sem_post(&mutex);
    sem_post(&semFull);
}

char* BoundedBuffer::remove() {
    sem_wait(&semFull);
    sem_wait(&mutex);

    if (buffer.empty()) {
        sem_post(&mutex);
        sem_post(&semEmpty);
        return nullptr;
    }

    char* item = buffer.front();
    buffer.pop();

    sem_post(&mutex);
    sem_post(&semEmpty);
    return item;
}

bool BoundedBuffer::empty() {
    sem_wait(&mutex);
    bool isEmpty = buffer.empty();
    sem_post(&mutex);
    return isEmpty;
}
