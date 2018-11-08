/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "ucountingsemaphore.h"

CountingSemaphore::CountingSemaphore(portBASE_TYPE maxCount, portBASE_TYPE initCount)
{
    _maxCount  = maxCount;
    _initCount = initCount;

    _blockTime = 0;
    _semaphore = xSemaphoreCreateCounting(_maxCount, _initCount);

    if (_semaphore != NULL)
        _isCreated = true;
}

CountingSemaphore::CountingSemaphore(portBASE_TYPE maxCount, portBASE_TYPE initCount, TickType_t blockTime)
{
    _maxCount  = maxCount;
    _initCount = initCount;

    _blockTime = blockTime;
    _semaphore = xSemaphoreCreateCounting(_maxCount, _initCount);

    if (_semaphore != NULL)
        _isCreated = true;
}

TickType_t CountingSemaphore::getBlockTime() const
{
    return _blockTime;
}

bool CountingSemaphore::take()
{
    return (xSemaphoreTake(_semaphore, _blockTime) == pdTRUE);
}

bool CountingSemaphore::give()
{
    return (xSemaphoreGive(_semaphore) == pdTRUE);
}

bool CountingSemaphore::isCreated() const
{
    return _isCreated;
}

bool CountingSemaphore::giveFromISR(bool *isTaskUnblocked)
{
    portBASE_TYPE isTaskUnblocked_;
    bool return_;

    return_ = xSemaphoreGiveFromISR(_semaphore, &isTaskUnblocked_);

    if(isTaskUnblocked_ == pdTRUE)
    {
        *(isTaskUnblocked) = true;
    }
    else
    {
        *(isTaskUnblocked) = false;
    }

    return (return_ == pdTRUE);
}

portBASE_TYPE CountingSemaphore::maximumCount() const
{
    return (_maxCount);
}

portBASE_TYPE CountingSemaphore::initialCount() const
{
    return (_initCount);
}
