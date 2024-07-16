/*
    Bar Shwarts - 207274358
    Ofri Kastenbaum - 208708768
*/
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "BoundedBuffer.h"

class ScreenManager {
public:
    ScreenManager(BoundedBuffer& queue);
    void manage();
    void start();

private:
    BoundedBuffer& inputQueue;
};

#endif // SCREENMANAGER_H
