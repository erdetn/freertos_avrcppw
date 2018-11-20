/* Copyright (c) Erdet Nasufi, 2018 */

#include "usemaphore.h"

using namespace urtos;

Semaphore::Semaphore(u_byte maxSemaphores) : _max_semaphores(maxSemaphores)
{
    _is_binary = (_max_semaphores == BINARY_SEMAPHORE);

#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    if (_is_binary)
    {
        _semaphore = xSemaphoreCreateBinary();
    }
    else
    {
        _semaphore = xSemaphoreCreateCounting(_max_semaphores, 0);
    }
#else
    if (_is_binary)
    {
        _semaphore = xSemaphoreCreateBinaryStatic(&_static_semaphore);
    }
    else
    {
        _semaphore = xSemaphoreCreateCountingStatic(&_static_semaphore);
    }
#endif

    if (_semaphore != NULL)
        _is_created = true;
}

bool Semaphore::wait(u_long blockTime = 0)
{
    return (xSemaphoreTake(_semaphore, blockTime) == pdTRUE);
}

bool Semaphore::waitFromInterrupt()
{
    return (xSemaphoreTakeFromISR(_semaphore, NULL) == pdTRUE);
}

bool Semaphore::post()
{
    return (xSemaphoreGive(_semaphore) == pdTRUE);
}

bool Semaphore::postFromISR()
{
    return (xSemaphoreGiveFromISR(_semaphore, NULL) == pdTRUE);
}

bool Semaphore::isCreated() const
{
    return _is_created;
}

u_byte Semaphore::maximumSemaphores() const
{
    return (_max_semaphores);
}
