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
    TickType_t _blockTime = 0;
    bool _created = false;

public:
    Mutex();
    Mutex(TickType_t blockTime);
    Mutex(const Mutex &mutex);

    TickType_t getBlockTime() const;

    bool lock();
    bool unlock();
    bool unlockFromISR(bool *isTaskUnblocked);
    bool created() const;
};
} // namespace urtos
#endif