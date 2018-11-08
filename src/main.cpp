#include <Arduino.h>

#include "uthread.h"

using namespace urtos;

const int ledPin = 13;
const int redLedPin = 12;

Thread *thread1;
Thread *thread2;

static void ledTask()
{
    digitalWrite(ledPin, HIGH);
    TaskDelay(500);
    digitalWrite(ledPin, LOW);
    TaskDelay(500);
}

static void redLedTask()
{
    digitalWrite(redLedPin, HIGH);
    TaskDelay(500);
    digitalWrite(redLedPin, LOW);
    TaskDelay(500);
}

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);

    thread1 = new Thread(ledTask, "task1", ThreadPriority::MediumPriority, 100);
    thread2 = new Thread(redLedTask, "task2", ThreadPriority::LowPriority, 100);

    thread1->start(NULL);
    thread2->start(NULL);
}

void loop()
{
}