#include <Arduino.h>

#include "utask.h"

using namespace urtos;

const int ledPin = 13;
const int redLedPin = 12;

Task *task1;
Task *task2;

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

    task1 = new Task(ledTask, "task1", TaskPriority::MediumPriority, 100);
	task2 = new Task(redLedTask, "task2", TaskPriority::LowPriority, 100);

	task1->run(NULL);
	task2->run(NULL);
}

void loop()
{
    
}