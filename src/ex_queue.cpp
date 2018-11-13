/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino.h>

#include "uthread.h"
#include "uqueue.h"
#include "ukernel.h"

using namespace urtos;

const int qCapacity = 10;

int count = 0;
Thread sendingThread;
Thread receivingThread;
Queue queue(qCapacity, sizeof(int));

static void sendingTask(void *dataToPass)
{
    int _array[] = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    int i = 0;
    LOOP
    {
        queue.send((const void *)&_array[i]);
        i++;
        if (i == 9)
            i = 0;
        Thread::sleep(250);
    }
}

static void receivingTask(void *dataToPass)
{
    int val;
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println("setup");

    LOOP
    {
        while (queue.count() > 0)
        {
            queue.receive(&val);
            Serial.print("val = ");
            Serial.print(val);
            Serial.print(" [");
            Serial.print(queue.count());
            Serial.println("]");
        }
        Thread::sleep(750);
    }
}

void setup()
{
    sendingThread = Thread((Task)sendingTask, "thread1", ThreadPriority::MEDIUM_PRIORITY, configMINIMAL_STACK_SIZE + 128, NULL);
    receivingThread = Thread((Task)receivingTask, "thread2", ThreadPriority::HIGH_PRIORITY, configMINIMAL_STACK_SIZE + 128, NULL);

    Kernel::run();
}

void loop()
{
}