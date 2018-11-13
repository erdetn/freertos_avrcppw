/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "urtos.h"

#ifndef UMUTEX_H
#define UMUTEX_H

namespace urtos
{
class Mutex
{
private:
    SemaphoreHandle_t _mutex = NULL;
    unsigned long _waitToLock = 0;
    bool _created = false;

public:
    Mutex();
    Mutex(unsigned long waitToLock);
    Mutex(const Mutex &mutex);

    unsigned long waitToLock() const;

    bool lock();
    bool lock(unsigned long waitToLock);
    bool unlock();

    bool unlockFromISR(bool *isTaskUnblocked);

    bool created() const;
};
} // namespace urtos
#endif