/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "BoundedBuffer.h"
#include <vector>

class Dispatcher {
public:
    Dispatcher(std::vector<BoundedBuffer*>& producerQueues, BoundedBuffer& sportsQueue, BoundedBuffer& newsQueue, BoundedBuffer& weatherQueue, int numProducers);
    void dispatch();

private:
    std::vector<BoundedBuffer*>& producerQueues;
    BoundedBuffer& sportsQueue;
    BoundedBuffer& newsQueue;
    BoundedBuffer& weatherQueue;
    int numProducers;
};

#endif // DISPATCHER_H
