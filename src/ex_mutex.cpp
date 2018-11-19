/* Copyright (c) Erdet Nasufi, 2018 */

#include <Arduino.h>

#include "uthread.h"
#include "umutex.h"
#include "ukernel.h"

using namespace urtos;

int count = 0;
Thread thread1;
Thread thread2;
Mutex mutex;

static void countingTask(void *dataToPass)
{
    LOOP
    {
        mutex.lock();
        count++;
        if (count == 100)
            count = 0;

        Thread::sleep(500);
        mutex.unlock();
    }
}

static void printingTask(void *dataToPass)
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println("setup");

    LOOP
    {
        mutex.lock(50);
        Serial.print("count: ");
        Serial.println(count);
        Thread::sleep(500);
        mutex.unlock();
    }
}

void setup()
{
    thread1 = Thread((ThreadCallback)countingTask, ThreadPriority::MEDIUM_PRIORITY, configMINIMAL_STACK_SIZE + 128, NULL);
    thread2 = Thread((ThreadCallback)printingTask, ThreadPriority::HIGH_PRIORITY, configMINIMAL_STACK_SIZE + 128, NULL);

    Kernel::run();
}

void loop()
{
}