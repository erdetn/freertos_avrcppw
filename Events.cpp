/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "Events.h"

Events::Events()
{
    m_hEvents = xEventGroupCreate();
}

BitMask Events::trigger(const BitMask eventBits)
{
    return xEventGroupSetBits(m_hEvents, eventBits);
}

BitMask Events::onEvent(TickType_t timeout, const BitMask triggerBits)
{
    return xEventGroupWaitBits(m_hEvents, triggerBits, pdTRUE, pdTRUE, 
                        pdMS_TO_TICKS(timeout));
}

BitMask Events::onEvent(TickType_t timeout, const BitMask triggerBits, bool reset)
{
    return xEventGroupWaitBits(m_hEvents, triggerBits,
                        reset == true ? pdTRUE : pdFALSE, 
                        pdTRUE, 
                        pdMS_TO_TICKS(timeout));
}

BitMask Events::onEvent(TickType_t timeout, const BitMask triggerBits, bool reset, bool waitForAllBits)
{
    return xEventGroupWaitBits(m_hEvents, triggerBits,
                        reset == true ? pdTRUE : pdFALSE, 
                        waitForAllBits == true ? pdTRUE : pdFALSE, 
                        pdMS_TO_TICKS(timeout));
}

bool Events::sync(TickType_t timeout, const BitMask triggerBits, const BitMask syncBits)
{
    BitMask ret_;

    ret_ = xEventGroupSync(m_hEvents, triggerBits, syncBits, pdMS_TO_TICKS(timeout));

    return (ret_ == syncBits);
}

unsigned char Events::bitMaskSize() const
{
    #ifdef configUSE_16_BIT_TICKS == 1
        return 8;
    #else
        return 24;
    #endif
}
    
