/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino.h>

#include "uthread.h"
#include "usharedbuffer.h"
#include "ukernel.h"

using namespace urtos;

int count = 0;
Thread sendingThread;
Thread receivingThread;
SharedBuffer sharedBuffer(20);

static void sendingTask(u_object dataToPass)
{
    char _str[] = "hello thread";
    u_size _length = strlen((const char *)_str);
    LOOP
    {
        if (sharedBuffer.isEmpty())
        {
            sharedBuffer.write(_str, _length, 100);
        }
        Thread::sleep(500);
    }
}

static void receivingTask(u_object dataToPass)
{
    int val;
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println("setup");

    char _str[50];
    u_size _len;

    LOOP
    {
        if (!sharedBuffer.isEmpty())
        {
            _len = sharedBuffer.read(_str, 20);
            _str[_len] = 0;
            if (_len > 0)
            {
                Serial.print("read: ");
                Serial.println(_str);
            }
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