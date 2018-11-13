/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "umutex.h"

using namespace urtos;

Mutex::Mutex()
{
    _waitToLock = 0;
    _mutex = xSemaphoreCreateMutex();

    if (_mutex != NULL)
        _created = true;
}

Mutex::Mutex(unsigned long waitToLock)
{
    _waitToLock = waitToLock;
    _mutex = xSemaphoreCreateMutex();

    if (_mutex != NULL)
        _created = true;
}

Mutex::Mutex(const Mutex &mutex)
{
    _waitToLock = mutex._waitToLock;
    _mutex = mutex._mutex;
    _created = mutex._created;
}

unsigned long Mutex::waitToLock() const
{
    return _waitToLock;
}

bool Mutex::lock()
{
    return (xSemaphoreTake(_mutex, pdMS_TO_TICKS(_waitToLock)) == pdTRUE);
}

bool Mutex::lock(unsigned long waitToLock)
{
    return (xSemaphoreTake(_mutex, pdMS_TO_TICKS(waitToLock)) == pdTRUE);
}

bool Mutex::unlock()
{
    return (xSemaphoreGive(_mutex) == pdTRUE);
}

bool Mutex::created() const
{
    return _created;
}

bool Mutex::unlockFromISR(bool *isTaskUnblocked)
{
    portBASE_TYPE isTaskUnblocked_;
    bool _return;

    _return = xSemaphoreGiveFromISR(_mutex, &isTaskUnblocked_);

    if (isTaskUnblocked_ == pdTRUE)
    {
        *(isTaskUnblocked) = true;
    }
    else
    {
        *(isTaskUnblocked) = false;
    }

    return (_return == pdTRUE);
}
