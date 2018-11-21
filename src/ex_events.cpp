/* Copyright (c) Erdet Nasufi, 2018 */

#include <Arduino.h>

#include "uthread.h"
#include "uevent.h"
#include "ukernel.h"

using namespace urtos;

Thread thread1;
Thread thread2;

EventContainer container;
Event event(container, 2);

static void countingTask(void *dataToPass)
{
    LOOP
    {
        Thread::sleep(1000);
        event.trigger();
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
        if (event.hasEvent(1100))
        {
            Serial.println("On event triggered.");
        }
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