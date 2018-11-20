/* Copyright (c) Erdet Nasufi, 2018 */

#include "umutex.h"

using namespace urtos;

Mutex::Mutex(bool isRecursive, unsigned long waitToLock = 0) : _isRecursive(isRecursive)
{
    _waitToLock = waitToLock;

    _created = this->createMutex();
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

bool Mutex::createMutex()
{
#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    if (_isRecursive)
    {
        _mutex = xSemaphoreCreateRecursiveMutex();
    }
    else
    {
        _mutex = xSemaphoreCreateMutex();
    }
#else
    if (_isRecursive)
    {
        _mutex = xSemaphoreCreateRecursiveMutexStatic(&_staticSemaphore);
    }
    else
    {
        _mutex = xSemaphoreCreateMutexStatic(&_staticSemaphore);
    }
#endif

    return (_mutex != NULL);
}

unsigned long Mutex::waitToLock() const
{
    return _waitToLock;
}

void Mutex::lock(unsigned long waitToLock = 0)
{
    if (_isRecursive)
    {
        _locked = (xSemaphoreTakeRecursive(_mutex, pdMS_TO_TICKS(waitToLock)) == pdTRUE);
        return;
    }

    _locked = (xSemaphoreTake(_mutex, pdMS_TO_TICKS(waitToLock)) == pdTRUE);
}

void Mutex::unlock()
{
    if (_isRecursive)
    {
        _locked = !(xSemaphoreGiveRecursive(_mutex) == pdTRUE);
        return;
    }
    _locked = !(xSemaphoreGive(_mutex) == pdTRUE);
}

void Mutex::unlockFromInterrupt()
{
    if (_isRecursive)
        return;
    _locked = !(xSemaphoreGiveFromISR(_mutex, NULL) == pdTRUE);
}

void Mutex::lockFromInterrupt()
{
    if (_isRecursive)
        return;
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

bool Mutex::isRecursive() const
{
    return _isRecursive;
}