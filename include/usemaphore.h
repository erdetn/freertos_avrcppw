/* Copyright (c) Erdet Nasufi, 2018 */

#ifndef UCOUNTINGSEMAPHORE_H
#define UCOUNTINGSEMAPHORE_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "urtos.h"

#define MAX_UBYTE 0xff
#define BINARY_SEMAPHORE 1

namespace urtos
{
class Semaphore
{
private:
    SemaphoreHandle_t _semaphore = NULL;
    u_long _block_time = 0;
    bool _is_created = false;
    u_byte _max_semaphores;
	bool _is_binary;

#if configSUPPORT_STATIC_ALLOCATION == 1
	StaticSemaphore_t _static_semaphore;
#endif

public:
    Semaphore(u_byte maxSemaphores);

    bool wait(u_long blockTime = 0);
    bool waitFromInterrupt();

    bool post();
    bool postFromISR();

    bool isCreated() const;
    u_byte maximumSemaphores() const;
};
} // namespace urtos

#endif