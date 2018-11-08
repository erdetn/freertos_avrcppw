/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "urtos.h"

#ifndef USEMAPHORE_H
#define USEMAPHORE_H

namespace urtos
{
class Semaphore
{
private:
    SemaphoreHandle_t _semaphore = NULL;
    TickType_t _blockTime = 0;
    bool _isCreated = false;

public:
    Semaphore();
    Semaphore(TickType_t blockTime);

    TickType_t getBlockTime() const;

    bool take();
    bool give();
    bool isCreated() const;
    bool giveFromISR(bool *isTaskUnblocked);
};
} // namespace urtos

#endif