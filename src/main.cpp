/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino.h>

#include "uthread.h"

using namespace urtos;

const int ledPin = 13;
const int redLedPin = 12;

Thread *thread1;
Thread *thread2;
Thread thread3;

void ledTask()
{
    digitalWrite(ledPin, HIGH);
    Thread::sleep(500);
    digitalWrite(ledPin, LOW);
    Thread::sleep(500);
}

void redLedTask()
{
    digitalWrite(redLedPin, HIGH);
    Thread::sleep(500);
    digitalWrite(redLedPin, LOW);
    Thread::sleep(500);
}

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);

    thread1 = new Thread((Task)ledTask, ThreadPriority::MediumPriority, 100);
    thread2 = new Thread((Task)redLedTask, ThreadPriority::LowPriority, 100);

    thread3 = *thread2;

    thread1->start(NULL);
    thread2->start(NULL);
    thread3.start(NULL);
}

void loop()
{
}