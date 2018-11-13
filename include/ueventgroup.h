/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

#include "urtos.h"

#ifndef UEVENTSREGISTER_H
#define UEVENTSREGISTER_H

namespace urtos
{

#ifdef configUSE_16_BIT_TICKS == 1
typedef unsigned char EventsBitmap;
#else
typedef unsigned int EventsBitmap;
#endif

#define EVENT_FLAG (EventFlag)

enum Event : EventsBitmap
{
    EVENT_1 = SET_BIT(0),
    EVENT_2 = SET_BIT(1),
    EVENT_3 = SET_BIT(2),
    EVENT_4 = SET_BIT(3),

    EVENT_5 = SET_BIT(4),
    EVENT_6 = SET_BIT(5),
    EVENT_7 = SET_BIT(6),
    EVENT_8 = SET_BIT(7)

#if configUSE_16_BIT_TICKS != 1
        ,
    EVENT_9 = SET_BIT(8),
    EVENT_10 = SET_BIT(9),
    EVENT_11 = SET_BIT(10),
    EVENT_12 = SET_BIT(11),

    EVENT_13 = SET_BIT(12),
    EVENT_14 = SET_BIT(13),
    EVENT_15 = SET_BIT(14),
    EVENT_16 = SET_BIT(15),

    EVENT_17 = SET_BIT(16),
    EVENT_18 = SET_BIT(17),
    EVENT_19 = SET_BIT(18),
    EVENT_20 = SET_BIT(19),

    EVENT_21 = SET_BIT(20),
    EVENT_22 = SET_BIT(21),
    EVENT_23 = SET_BIT(22),
    EVENT_24 = SET_BIT(23),
#endif
};

struct event_flag
{
    Byte event_1 : 1;
    Byte event_2 : 1;
    Byte event_3 : 1;
    Byte event_4 : 1;

    Byte event_5 : 1;
    Byte event_6 : 1;
    Byte event_7 : 1;
    Byte event_8 : 1;

#if configUSE_16_BIT_TICKS != 1
    Byte event_9 : 1;
    Byte event_10 : 1;
    Byte event_11 : 1;
    Byte event_12 : 1;

    Byte event_13 : 1;
    Byte event_14 : 1;
    Byte event_15 : 1;
    Byte event_16 : 1;

    Byte event_17 : 1;
    Byte event_18 : 1;
    Byte event_19 : 1;
    Byte event_20 : 1;

    Byte event_21 : 1;
    Byte event_22 : 1;
    Byte event_23 : 1;
    Byte event_24 : 1;
#endif
};
typedef struct event_flag EventFlag;

class EventGroup
{
private:
    EventGroupHandle_t _eventGroup;

public:
    EventGroup();

    EventFlag emit(Event event);
	EventFlag emitFromInterrupt(Event event);

	EventFlag hasEvent(Event event);
    EventFlag hasEvent(unsigned long timeout, Event event);
    EventFlag hasEvent(unsigned long timeout, Event event, bool reset);
    EventFlag hasEvent(unsigned long timeout, Event event, bool reset, bool waitForAllBits);

    bool sync(unsigned long timeout, Event event, const BitMask syncBits);

    unsigned char flagSize() const;
};
} // namespace urtos

#endif
