/* Copyright (c) Erdet Nasufi, 2018 */

#include <Arduino.h>

#include "uthread.h"
#include "usemaphore.h"
#include "ukernel.h"

using namespace urtos;

int count = 0;
Thread thread1;
Thread thread2;
Semaphore sem(BINARY_SEMAPHORE);

static void countingTask(void *dataToPass)
{
    LOOP
    {
        count++;
        if (count == 100)
            count = 0;
		sem.post();
        Thread::sleep(1000);
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
        sem.wait(200);
        Serial.print("count: ");
        Serial.println(count);
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