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
    bool _locked = false;

public:
    Mutex();
    Mutex(unsigned long waitToLock);
    Mutex(const Mutex &mutex);

    unsigned long waitToLock() const;

    void lock();
    void lock(unsigned long waitToLock);
    void unlock();

    void unlockFromInterrupt();
    void lockFromInterrupt();

    bool locked() const;
    bool created() const;
};
} // namespace urtos
#endif