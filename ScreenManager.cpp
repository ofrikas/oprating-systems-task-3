/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/
#include "ScreenManager.h"
#include <cstring>
#include <thread>
#include <iostream>

ScreenManager::ScreenManager(BoundedBuffer &queue) : inputQueue(queue) {}

void ScreenManager::manage() {
//    std::cout << "ScreenManager started" << std::endl;
    int doneCount = 0;

    while (doneCount < 3) {
        char* message = inputQueue.remove();

        if (std::strcmp(message, "DONE") == 0) {
            ++doneCount;
            delete[] message;
//            std::cout << "ScreenManager received DONE" << std::endl;
        } else {
            std::cout << message << std::endl;
            delete[] message;
        }
    }

    std::cout << "DONE" << std::endl;
}

void ScreenManager::start() {
    std::thread(&ScreenManager::manage, this).detach();
}
