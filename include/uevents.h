/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

#include "urtos.h"

#ifndef UEVENTS_H
#define UEVENTS_H

namespace urtos
{
class Events
{
private:
    EventGroupHandle_t _hEvents;

public:
    Events();
    
    BitMask trigger(const BitMask eventBits);

    BitMask onEvent(TickType_t timeout, const BitMask triggerBits);
    BitMask onEvent(TickType_t timeout, const BitMask triggerBits, bool reset);
    BitMask onEvent(TickType_t timeout, const BitMask triggerBits, bool reset, bool waitForAllBits);

    bool sync(TickType_t timeout, const BitMask triggerBits, const BitMask syncBits);

    unsigned char bitMaskSize() const;
};
}

#endif
