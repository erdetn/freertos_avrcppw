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
    unsigned long _blockTime = 0;
    bool _isCreated = false;

public:
    Semaphore();
    Semaphore(unsigned long blockTime);

    unsigned long getBlockTime() const;

    bool take();
	bool take(unsigned long blockTime);
    bool give();
    bool isCreated() const;
    bool giveFromISR(bool *isTaskUnblocked);
};
} // namespace urtos

#endif