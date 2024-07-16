# oprating-systems-task-3
This C++ project simulates a multithreaded news broadcasting system, demonstrating skills in concurrent programming and synchronization using semaphores and thread-safe bounded buffers.

# Concurrent Programming and Synchronization Mechanisms Assignment

## Overview
This project simulates a news broadcasting system to demonstrate concurrent programming and synchronization mechanisms. The system consists of Producers, a Dispatcher, Co-Editors, and a Screen Manager, all communicating via bounded buffers.

## Project Structure
- **Producer**: Generates news stories of types SPORTS, NEWS, and WEATHER and sends them to the Dispatcher through private queues.
- **Dispatcher**: Uses a Round Robin algorithm to fetch messages from Producers' queues and distributes them to Co-Editors' queues based on message type.
- **Co-Editors**: Process messages from the Dispatcher and send them to the Screen Manager.
- **Screen Manager**: Displays the messages and signifies the end of processing once all messages are handled.

## Bounded Buffer
A thread-safe bounded buffer is implemented to facilitate message passing between components. It supports the following operations:
- **Bounded_Buffer(int size)**: Constructor that creates a new bounded buffer with `size` places to store objects.
- **void insert(char* s)**: Inserts a new object into the bounded buffer.
- **char* remove()**: Removes the first object from the bounded buffer and returns it to the user.

## Configuration File
The configuration file specifies the number of products each producer creates and the sizes of their respective queues. The Co-Editors' queue size is also specified.

### Example Configuration File
```txt
PRODUCER 1
30
queue size = 5

PRODUCER 2
25
queue size = 3

PRODUCER 3
16
queue size = 30

Co-Editor queue size = 17
