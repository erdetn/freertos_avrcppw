/* Copyright (c) Erdet Nasufi, 2018 */

#include "uevent.h"

using namespace urtos;

EventContainer::EventContainer()
{
#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    _container = xEventGroupCreate();
#else
    _container = xEventGroupCreateStatic(&_static_container);
#endif
}

bool EventContainer::clear()
{
    return (xEventGroupClearBits(_container, MAX_EVENT_MAP) == 0);
}

bool EventContainer::clearFromInterrupt()
{
    return (xEventGroupClearBitsFromISR(_container, MAX_EVENT_MAP) == 0);
}

Event::Event(EventContainer container, u_byte eventId) : _event_container(container), _event_id(eventId), _event_bit(SET_BIT(eventId))
{
    _is_assigned = _event_id <= MAX_EVENT_IDS;
}

bool Event::trigger()
{
    if (!_is_assigned)
        return false;

    uint16_t _ret;
    _ret = xEventGroupSetBits(_event_container._container, _event_bit);

    return ((_ret & _event_bit) == _event_bit);
}

bool Event::triggerFromInterrupt()
{
    if (!_is_assigned)
        return false;

    uint16_t _ret;
    _ret = xEventGroupSetBitsFromISR(_event_container._container, _event_bit, NULL);

    return ((_ret & _event_bit) == _event_bit);
}

bool Event::hasEvent(u_long timeout)
{
    if (!_is_assigned)
        return false;

    uint16_t _ret;
    _ret = xEventGroupWaitBits(_event_container._container, _event_bit, pdTRUE, pdTRUE, pdMS_TO_TICKS(timeout));

    return ((_ret & _event_bit) == _event_bit);
}

u_byte Event::id() const
{
    return _event_id;
}

bool Event::assigned() const
{
    return _is_assigned;
}
