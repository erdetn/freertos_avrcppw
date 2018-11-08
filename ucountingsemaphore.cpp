/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "CountingSemaphore.h"

CountingSemaphore::CountingSemaphore(portBASE_TYPE maxCount, portBASE_TYPE initCount)
{
    m_maxCount  = maxCount;
    m_initCount = initCount;

    m_blockTime = 0;
    m_semaphore = xSemaphoreCreateCounting(m_maxCount, m_initCount);

    if (m_semaphore != NULL)
        m_isCreated = true;
}

CountingSemaphore::CountingSemaphore(portBASE_TYPE maxCount, portBASE_TYPE initCount, TickType_t blockTime)
{
    m_maxCount  = maxCount;
    m_initCount = initCount;

    m_blockTime = blockTime;
    m_semaphore = xSemaphoreCreateCounting(m_maxCount, m_initCount);

    if (m_semaphore != NULL)
        m_isCreated = true;
}

TickType_t CountingSemaphore::getBlockTime() const
{
    return m_blockTime;
}

bool CountingSemaphore::take()
{
    return (xSemaphoreTake(m_semaphore, m_blockTime) == pdTRUE);
}

bool CountingSemaphore::give()
{
    return (xSemaphoreGive(m_semaphore) == pdTRUE);
}

bool CountingSemaphore::isCreated() const
{
    return m_isCreated;
}

bool CountingSemaphore::giveFromISR(bool *isTaskUnblocked)
{
    portBASE_TYPE isTaskUnblocked_;
    bool return_;

    return_ = xSemaphoreGiveFromISR(m_semaphore, &isTaskUnblocked_);

    if(isTaskUnblocked_ == pdTRUE)
    {
        *(isTaskUnblocked) = true;
    }
    else
    {
        *(isTaskUnblocked) = false;
    }

    return (return_ == pdTRUE);
}

portBASE_TYPE CountingSemaphore::maximumCount() const
{
    return (m_maxCount);
}

portBASE_TYPE CountingSemaphore::initialCount() const
{
    return (m_initCount);
}
