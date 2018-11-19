/* Copyright (c) Erdet Nasufi, 2018 */

#include <Arduino.h>

#include "uthread.h"
#include "ukernel.h"

using namespace urtos;

const int LED_PIN = 13;

Thread thread1;
Thread thread2;

void ledTask(void *dataToPass)
{
    pinMode(LED_PIN, OUTPUT);
    LOOP
    {
        digitalWrite(LED_PIN, HIGH);
        Thread::sleep(500);
        digitalWrite(LED_PIN, LOW);
        Thread::sleep(500);
    }
}

void redLedTask(void *dataToPass)
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println("setup");

    LOOP
    {
        Serial.print("Num of threads: ");
        Serial.println(Kernel::numberOfThreads());

        Thread::sleep(1000);
    }
}

void setup()
{
    thread1 = Thread((ThreadCallback)ledTask, ThreadPriority::MEDIUM_PRIORITY, 128, NULL);
    thread2 = Thread((ThreadCallback)redLedTask, ThreadPriority::HIGH_PRIORITY, 128, NULL);

    Kernel::run();
}

void loop()
{
}