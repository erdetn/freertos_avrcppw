/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino.h>
// #include <HardwareSerial.h>

#include "uthread.h"
#include "umutex.h"
#include "ukernel.h"

using namespace urtos;

const int ledPin = 13;

Thread thread1;
Thread thread2;

static void ledTask(void *dataToPass)
{
    pinMode(ledPin, OUTPUT);
    LOOP
    {
        digitalWrite(ledPin, HIGH);
        Thread::sleep(500);
        digitalWrite(ledPin, LOW);
        Thread::sleep(500);
    }
}

static void redLedTask(void *dataToPass)
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println("setup");

    LOOP
    {
        Serial.println("Thread 2");
        Thread::sleep(1000);
    }
}

void setup()
{
    thread1 = Thread((Task)ledTask, "thread1", ThreadPriority::MEDIUM_PRIORITY, configMINIMAL_STACK_SIZE + 128, NULL);
    thread2 = Thread((Task)redLedTask, "thread2", ThreadPriority::HIGH_PRIORITY, configMINIMAL_STACK_SIZE + 128, NULL);

    Kernel::run();
}

void loop()
{
}