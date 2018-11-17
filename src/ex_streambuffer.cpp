/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino.h>

#include "uthread.h"
#include "ustreambuffer.h"
#include "ukernel.h"

using namespace urtos;

struct MyData
{
    int a;
    int b;
    int c;
} U_PACKED;

int count = 0;
Thread sendingThread;
Thread receivingThread;
StreamBuffer streamBuffer(5 * sizeof(struct MyData), sizeof(struct MyData));

static void sendingTask(u_object dataToPass)
{
    u_size _len;
    _len = sizeof(struct MyData);
    struct MyData data = {10, 20, 30};

    LOOP
    {
		BEGIN_CRITICAL_REGION();
        data.a++;
        data.b++;
        data.c++;
		END_CRITICAL_REGION();
		
        streamBuffer.write((const void *)&data, _len);

        Thread::sleep(1000);
    }
}

static void receivingTask(u_object dataToPass)
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println("setup");

    struct MyData data;
    u_size _len = sizeof(struct MyData);

    LOOP
    {
        streamBuffer.read(&data, _len);

        Serial.print("a = ");
        Serial.print(data.a);
        Serial.print(", b = ");
        Serial.print(data.b);
        Serial.print(", c = ");
        Serial.println(data.c);

        Thread::sleep(500);
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