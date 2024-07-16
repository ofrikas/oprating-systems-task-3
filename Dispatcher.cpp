/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/

#include "Dispatcher.h"
#include <cstring>
#include <thread>
#include <iostream>

Dispatcher::Dispatcher(std::vector<BoundedBuffer*>& producerQueues, BoundedBuffer& sportsQueue, BoundedBuffer& newsQueue, BoundedBuffer& weatherQueue, int numProducers)
    : producerQueues(producerQueues), sportsQueue(sportsQueue), newsQueue(newsQueue), weatherQueue(weatherQueue), numProducers(numProducers) {}

void Dispatcher::dispatch() {
//    std::cout << "Dispatcher started" << std::endl;
    int doneCount = 0;

    while (doneCount < numProducers) {
        for (auto& producerQueue : producerQueues) {
            if (!producerQueue->empty()) {
                char* message = producerQueue->remove();

                if (std::strcmp(message, "DONE") == 0) {
                    ++doneCount;
                    delete[] message;
                } else {
                    if (std::strstr(message, "SPORTS") != nullptr) {
                        sportsQueue.insert(message);
                    } else if (std::strstr(message, "NEWS") != nullptr) {
                        newsQueue.insert(message);
                    } else if (std::strstr(message, "WEATHER") != nullptr) {
                        weatherQueue.insert(message);
                    }
                }
            }
        }
    }

    sportsQueue.insert("DONE");
    newsQueue.insert("DONE");
    weatherQueue.insert("DONE");
//    std::cout << "Dispatcher finished" << std::endl;
}
