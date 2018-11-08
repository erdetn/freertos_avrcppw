#include <Arduino.h>

#include "utask.h"

using namespace urtos;

const int ledPin = 13;
Task *task1;

static void ledTask()
{
	digitalWrite(ledPin, HIGH);
	TaskDelay(500);
	digitalWrite(ledPin, LOW);
	TaskDelay(500);
}

void setup()
{
	pinMode(ledPin, OUTPUT);
    task1 = new Task(ledTask, "task1", TaskPriority::MediumPriority, 100);
}

void loop()
{
    
}