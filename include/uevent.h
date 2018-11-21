/* Copyright (c) Erdet Nasufi, 2018 */

#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

#include "urtos.h"

#ifndef UEVENT_H
#define UEVENT_H

#define CLEAR_EVENT_CONTAINER(ec) xEventGroupClearBits(ec, 0xff)

#if configUSE_16_BIT_TICKS == 1
#define MAX_EVENT_IDS 8
#define MAX_EVENT_MAP 0xff
#else
#define MAX_EVENT_IDS 24
#define MAX_EVENT_MAP 0xfffff
#endif

namespace urtos
{

class EventContainer
{
private:
    EventGroupHandle_t _container;
#if configSUPPORT_STATIC_ALLOCATION == 1
    StaticEventGroup_t _static_container;
#endif

    friend class Event;

public:
    EventContainer();
    bool clear();
	bool clearFromInterrupt();
};

class Event
{
private:
    EventContainer _event_container;
    const u_byte _event_id;
    const uint16_t _event_bit;
    bool _is_assigned;

public:
    Event(EventContainer container, u_byte eventId);

    bool trigger();
    bool triggerFromInterrupt();

    bool hasEvent(u_long timeout);

    u_byte id() const;
    bool assigned() const;
};

} // namespace urtos

#endif