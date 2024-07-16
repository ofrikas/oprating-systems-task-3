/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/
#include "BoundedBuffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include <vector>
#include <thread>
#include <iostream>
#include <fstream> // For file operations
#include <sstream> // For string stream operations

// Function to parse and initialize producers from a file
void initializeProducers(std::vector<Producer>& producers, std::vector<BoundedBuffer*>& producerQueues, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line.find("PRODUCER") == std::string::npos)
            continue;

        // Parse PRODUCER line
        int id;
        std::istringstream iss(line);
        std::string producerLabel;
        iss >> producerLabel >> id;

        // Read number of products
        int numProducts;
        std::getline(file, line); // Read next line for numProducts
        std::istringstream issNumProducts(line.substr(line.find(" ") + 1));
        issNumProducts >> numProducts;

        // Read queue size
        int queueSize;
        std::getline(file, line); // Read next line for queue size
        std::istringstream issQueueSize(line.substr(line.find("=") + 2));
        issQueueSize >> queueSize;

        // Create bounded buffer for this producer
        BoundedBuffer* buffer = new BoundedBuffer(queueSize);
        producerQueues.push_back(buffer);

        // Create producer and store in vector
        producers.emplace_back(id, numProducts, *buffer);
    }

    file.close();
}

// Function to parse and initialize co-editor queue size
int parseCoEditorQueueSize(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line.find("Co-Editor") == std::string::npos)
            continue;

        // Parse Co-Editor queue size
        int queueSize;
        std::istringstream iss(line.substr(line.find("=") + 2));
        iss >> queueSize;

        file.close();
        return queueSize;
    }

    file.close();
    return -1;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    std::string configFile = argv[1];

    // Initialize your buffers and other necessary components
    std::vector<BoundedBuffer*> producerQueues;
    std::vector<Producer> producers;

    // Initialize producers from config file
    initializeProducers(producers, producerQueues, configFile);

    // Start producer threads
    std::vector<std::thread> producerThreads;
    for (auto& producer : producers) {
        producerThreads.emplace_back(&Producer::produce, &producer);
    }

    // Initialize other queues (sports, news, weather)
    BoundedBuffer sportsQueue(5);  // Example size, adjust as needed
    BoundedBuffer newsQueue(5);    // Example size, adjust as needed
    BoundedBuffer weatherQueue(5); // Example size, adjust as needed

    // Start dispatcher
    int numProducers = producers.size();
    Dispatcher dispatcher(producerQueues, sportsQueue, newsQueue, weatherQueue, numProducers);
    std::thread dispatcherThread(&Dispatcher::dispatch, &dispatcher);

    // Start co-editor threads (example for sports queue)
    int coEditorQueueSize = parseCoEditorQueueSize(configFile);
    if (coEditorQueueSize == -1) {
        std::cerr << "Error parsing Co-Editor queue size from config file." << std::endl;
        return 1;
    }
    BoundedBuffer outputQueue(coEditorQueueSize);  // Example output queue size, adjust as needed
    CoEditor coEditor1(sportsQueue, outputQueue);
    std::thread coEditor1Thread(&CoEditor::edit, &coEditor1);

    CoEditor coEditor2(newsQueue, outputQueue);
    std::thread coEditor2Thread(&CoEditor::edit, &coEditor2);

    CoEditor coEditor3(weatherQueue, outputQueue);
    std::thread coEditor3Thread(&CoEditor::edit, &coEditor3);

    // Start screen manager thread
    ScreenManager screenManager(outputQueue);
    std::thread screenManagerThread(&ScreenManager::manage, &screenManager);

    // Join all threads to ensure they complete before main finishes
    for (auto& thread : producerThreads) {
        thread.join();
    }
    dispatcherThread.join();
    coEditor1Thread.join();
    coEditor2Thread.join();
    coEditor3Thread.join();
    screenManagerThread.join();

    return 0;
}
