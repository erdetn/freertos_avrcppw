/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "urtos.h"

#ifndef UCOUNTINGSEMAPHORE_H
#define UCOUNTINGSEMAPHORE_H

namespace urtos
{
class CountingSemaphore
{
private:
    SemaphoreHandle_t _semaphore = NULL;
    TickType_t _blockTime = 0;
    bool _isCreated = false;

    portBASE_TYPE _maxCount;
    portBASE_TYPE _initCount;

public:
    CountingSemaphore(portBASE_TYPE maxCount, portBASE_TYPE initCount);
    CountingSemaphore(portBASE_TYPE maxCount, portBASE_TYPE initCount, TickType_t blockTime);

    TickType_t getBlockTime() const;

    bool take();
    bool give();
    bool giveFromISR(bool *isTaskUnblocked);
    bool isCreated() const;

    portBASE_TYPE maximumCount() const;
    portBASE_TYPE initialCount() const;
};
} // namespace urtos

#endif