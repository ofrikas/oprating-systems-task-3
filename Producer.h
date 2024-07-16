/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/
#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"
#include <vector>
#include <string>

class Producer {
public:
    Producer(int id, int numProducts, BoundedBuffer& queue);
    void produce();
    static const std::vector<std::string> types;

private:
    int id;
    int numProducts;
    BoundedBuffer& producerQueue;
};

#endif // PRODUCER_H
