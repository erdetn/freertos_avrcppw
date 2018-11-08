/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

#include "urtos.h"

#ifndef EVENTS_H
#define EVENTS_H

#define BitMask EventBits_t

#ifdef configUSE_16_BIT_TICKS == 1
    #define BITMASK_MAP  0xFF
#else
    #define BITMASK_MAP  0xFFFFFF
#endif

#define SetBit(_b)      (1<_b)
#define ClearBit(_b)   ~(1<_b)

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

#endif
