/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/

#include "CoEditor.h"
#include <chrono>
#include <thread>
#include <cstring>
#include <iostream>

CoEditor::CoEditor(BoundedBuffer& inputQueue, BoundedBuffer& outputQueue)
    : inputQueue(inputQueue), outputQueue(outputQueue) {}

void CoEditor::edit() {
//    std::cout << "CoEditor started" << std::endl;
    while (true) {
        char* message = inputQueue.remove();

        if (std::strcmp(message, "DONE") == 0) {
            outputQueue.insert("DONE");
            delete[] message;
//            std::cout << "CoEditor finished" << std::endl;
            return;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            outputQueue.insert(message);
        }
    }
}

void CoEditor::start() {
    std::thread(&CoEditor::edit, this).detach();
}
