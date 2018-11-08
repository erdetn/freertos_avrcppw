/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "uqueue.h"

using namespace urtos;

Queue::Queue(UBaseType_t length, UBaseType_t unitSize)
{
    _waitToReceive = DEFAULT_TICKS_TO_WAIT;
    _waitToSend    = DEFAULT_TICKS_TO_WAIT;
    _length        = length;
    _unitSize      = unitSize;

    _hQueue = xQueueCreate(_length, _unitSize);
}

Queue::Queue(UBaseType_t length, UBaseType_t unitSize, TickType_t defaultSendReceiveTime)
{
    _waitToReceive = defaultSendReceiveTime/portTICK_PERIOD_MS;
    _waitToSend    = defaultSendReceiveTime/portTICK_PERIOD_MS;
    _length        = length;
    _unitSize      = unitSize;

    _hQueue = xQueueCreate(_length, _unitSize);
}

Queue::Queue(UBaseType_t length, UBaseType_t unitSize, TickType_t waitToSend, TickType_t waitToReceive)
{
    _waitToReceive = waitToReceive/portTICK_PERIOD_MS;
    _waitToSend    = waitToSend/portTICK_PERIOD_MS;
    _length        = length;
    _unitSize      = unitSize;

    _hQueue = xQueueCreate(_length, _unitSize);
}

bool Queue::send(const void *data)
{
    return (xQueueSend(_hQueue, data, _waitToSend) == pdTRUE);
}

bool Queue::send(const void *data, TickType_t waitToSend)
{
    return (xQueueSend(_hQueue, data, waitToSend) == pdTRUE);
}

bool Queue::receive(void *data)
{
    return (xQueueReceive(_hQueue, data, _waitToReceive) == pdTRUE);
}

bool Queue::receive(void *data, TickType_t waitToReceive)
{
    return (xQueueReceive(_hQueue, data, waitToReceive) == pdTRUE);
}

bool Queue::copy(void *data)
{
    return (xQueuePeek(_hQueue, data, _waitToReceive) == pdTRUE);
}

bool Queue::copy(void *data, TickType_t waitToCopy)
{
    return (xQueuePeek(_hQueue, data, waitToCopy) == pdTRUE);
}

TickType_t Queue::waitingToSendTime() const
{
    return _waitToSend;
}

TickType_t Queue::waitingToReceiveTime() const
{
    return _waitToReceive;
}

UBaseType_t Queue::length() const
{
    return _length;
}

UBaseType_t Queue::unitSize() const
{
    return _unitSize;
}
