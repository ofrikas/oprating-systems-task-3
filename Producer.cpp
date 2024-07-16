/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/
#include "Producer.h"
#include <random>
#include <chrono>
#include <thread>
#include <cstring>
#include <iostream>

const std::vector<std::string> Producer::types = {"SPORTS", "NEWS", "WEATHER"};

Producer::Producer(int id, int numProducts, BoundedBuffer &queue)
    : id(id), numProducts(numProducts), producerQueue(queue) {}

void Producer::produce() {
//    std::cout << "Producer " << id << " started" << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, types.size() - 1);

    for (int j = 0; j < numProducts; ++j) {
        int typeIndex = dis(gen);
        std::string message = "Producer " + std::to_string(id) + " " + types[typeIndex] + " " + std::to_string(j);
        char* msg = new char[message.size() + 1];
        std::strcpy(msg, message.c_str());
        producerQueue.insert(msg);
    }

    char* doneMsg = new char[5];
    std::strcpy(doneMsg, "DONE");
    producerQueue.insert(doneMsg);
}
