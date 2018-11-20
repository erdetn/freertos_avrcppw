/* Copyright (c) Erdet Nasufi, 2018 */

#ifndef UMUTEX_H
#define UMUTEX_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "urtos.h"

namespace urtos
{
class Mutex
{
private:
    SemaphoreHandle_t _mutex = NULL;
    unsigned long _waitToLock = false;
    bool _created = false;
    bool _locked = false;
	
	const bool _isRecursive = false;

	bool createMutex();

#if configSUPPORT_STATIC_ALLOCATION == 1
    StaticSemaphore_t _staticSemaphore;
#endif

public:
    Mutex(bool isRecursive, unsigned long waitToLock = 0);
    Mutex(const Mutex &mutex);

    unsigned long waitToLock() const;

    void lock(unsigned long waitToLock = 0);
    void unlock();

    void unlockFromInterrupt();
    void lockFromInterrupt();

    bool locked() const;
    bool created() const;
	bool isRecursive() const;
};
} // namespace urtos
#endif