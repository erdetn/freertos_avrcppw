/* Copyright (c) Erdet Nasufi, 2018 */

#include "umutex.h"

using namespace urtos;

Mutex::Mutex()
{
    _waitToLock = 0;

#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    _mutex = xSemaphoreCreateMutex();
#else
    _mutex = xSemaphoreCreateMutexStatic(&_staticSemaphore);
#endif

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
#if configSUPPORT_STATIC_ALLOCATION == 1
    _staticSemaphore = mutex._staticSemaphore;
#endif
}

unsigned long Mutex::waitToLock() const
{
    return _waitToLock;
}

void Mutex::lock()
{
    _locked = (xSemaphoreTake(_mutex, pdMS_TO_TICKS(_waitToLock)) == pdTRUE);
}

void Mutex::lock(unsigned long waitToLock)
{
    _locked = (xSemaphoreTake(_mutex, pdMS_TO_TICKS(waitToLock)) == pdTRUE);
}

void Mutex::unlock()
{
    _locked = !(xSemaphoreGive(_mutex) == pdTRUE);
}

void Mutex::unlockFromInterrupt()
{
    _locked = !(xSemaphoreGiveFromISR(_mutex, NULL) == pdTRUE);
}

void Mutex::lockFromInterrupt()
{
    _locked = (xSemaphoreTakeFromISR(_mutex, NULL) == pdTRUE);
}

bool Mutex::created() const
{
    return _created;
}

bool Mutex::locked() const
{
    return _locked;
}