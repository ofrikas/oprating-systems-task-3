/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/

#ifndef COEDITOR_H
#define COEDITOR_H

#include "BoundedBuffer.h"

class CoEditor {
public:
    CoEditor(BoundedBuffer& inputQueue, BoundedBuffer& outputQueue);
    void edit();
    void start();

private:
    BoundedBuffer& inputQueue;
    BoundedBuffer& outputQueue;
};

#endif // COEDITOR_H
