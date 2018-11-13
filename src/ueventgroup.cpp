/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "ueventgroup.h"

using namespace urtos;

EventGroup::EventGroup()
{
    _eventGroup = xEventGroupCreate();
}

EventFlag EventGroup::emit(Event event)
{
    return xEventGroupSetBits(_eventGroup, event);
}

EventFlag EventGroup::onEvent(TickType_t timeout, const BitMask triggerBits)
{
    return xEventGroupWaitBits(_hEvents, triggerBits, pdTRUE, pdTRUE,
                               pdMS_TO_TICKS(timeout));
}

EventFlag EventGroup::onEvent(TickType_t timeout, const BitMask triggerBits, bool reset)
{
    return xEventGroupWaitBits(_hEvents, triggerBits,
                               reset == true ? pdTRUE : pdFALSE,
                               pdTRUE,
                               pdMS_TO_TICKS(timeout));
}

EventFlag EventGroup::onEvent(TickType_t timeout, const BitMask triggerBits, bool reset, bool waitForAllBits)
{
    return xEventGroupWaitBits(_hEvents, triggerBits,
                               reset == true ? pdTRUE : pdFALSE,
                               waitForAllBits == true ? pdTRUE : pdFALSE,
                               pdMS_TO_TICKS(timeout));
}

bool EventGroup::sync(TickType_t timeout, const BitMask triggerBits, const BitMask syncBits)
{
    BitMask ret_;

    ret_ = xEventGroupSync(_hEvents, triggerBits, syncBits, pdMS_TO_TICKS(timeout));

    return (ret_ == syncBits);
}

unsigned char EventGroup::flagSize() const
{
#ifdef configUSE_16_BIT_TICKS == 1
    return 8;
#else
    return 24;
#endif
}