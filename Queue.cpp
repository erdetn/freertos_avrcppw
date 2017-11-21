/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "Queue.h"

Queue::Queue(UBaseType_t length, UBaseType_t unitSize)
{
    m_waitToReceive = DEFAULT_TICKS_TO_WAIT;
    m_waitToSend    = DEFAULT_TICKS_TO_WAIT;
    m_length        = length;
    m_unitSize      = unitSize;

    m_hQueue = xQueueCreate(m_length, m_unitSize);
}

Queue::Queue(UBaseType_t length, UBaseType_t unitSize, TickType_t defaultSendReceiveTime)
{
    m_waitToReceive = defaultSendReceiveTime/portTICK_PERIOD_MS;
    m_waitToSend    = defaultSendReceiveTime/portTICK_PERIOD_MS;
    m_length        = length;
    m_unitSize      = unitSize;

    m_hQueue = xQueueCreate(m_length, m_unitSize);
}

Queue::Queue(UBaseType_t length, UBaseType_t unitSize, TickType_t waitToSend, TickType_t waitToReceive)
{
    m_waitToReceive = waitToReceive/portTICK_PERIOD_MS;
    m_waitToSend    = waitToSend/portTICK_PERIOD_MS;
    m_length        = length;
    m_unitSize      = unitSize;

    m_hQueue = xQueueCreate(m_length, m_unitSize);
}

bool Queue::send(const void *data)
{
    return (xQueueSend(m_hQueue, data, m_waitToSend) == pdTRUE);
}

bool Queue::send(const void *data, TickType_t waitToSend)
{
    return (xQueueSend(m_hQueue, data, waitToSend) == pdTRUE);
}

bool Queue::receive(void *data)
{
    return (xQueueReceive(m_hQueue, data, m_waitToReceive) == pdTRUE);
}

bool Queue::receive(void *data, TickType_t waitToReceive)
{
    return (xQueueReceive(m_hQueue, data, waitToReceive) == pdTRUE);
}

bool Queue::copy(void *data)
{
    return (xQueuePeek(m_hQueue, data, m_waitToReceive) == pdTRUE);
}

bool Queue::copy(void *data, TickType_t waitToCopy)
{
    return (xQueuePeek(m_hQueue, data, waitToCopy) == pdTRUE);
}

TickType_t Queue::waitingToSendTime() const
{
    return m_waitToSend;
}

TickType_t Queue::waitingToReceiveTime() const
{
    return m_waitToReceive;
}

UBaseType_t Queue::length() const
{
    return m_length;
}

UBaseType_t Queue::unitSize() const
{
    return m_unitSize;
}
