/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino.h>
#include "utimer.h"
#include "ukernel.h"
#include "uthread.h"

using namespace urtos;

bool ledState;
const int ledPin = 13;

Timer ledTimer;

static void toggleLed(TimerHandler sender)
{
    if (ledState)
    {
        digitalWrite(ledPin, HIGH);
        ledState = false;
    }
    else
    {
        digitalWrite(ledPin, LOW);
        ledState = true;
    }
}

void setup()
{
    pinMode(ledPin, OUTPUT);

    ledTimer = Timer(toggleLed, 500, true);
    ledTimer.start();

    Kernel::run();
}

void loop()
{
}