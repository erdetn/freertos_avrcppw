/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "uqueue.h"

using namespace urtos;

Queue::Queue(u_byte capacity, u_byte unitSize) : _capacity(capacity), _unitSize(unitSize)
{
    _receiveTimeout = DEFAULT_TICKS_TO_WAIT;
    _sendTimeout = DEFAULT_TICKS_TO_WAIT;

    _queue = xQueueCreate(_capacity, _unitSize);
}

Queue::Queue(u_byte capacity, u_byte unitSize,
             unsigned long sendTimeout,
             unsigned long receveTimeout) : _capacity(capacity), _unitSize(unitSize)
{
    _receiveTimeout = receveTimeout;
    _sendTimeout = sendTimeout;

    _queue = xQueueCreate(_capacity, _unitSize);
}

bool Queue::enqueue(const void *data)
{
    return (xQueueSend(_queue, data, pdMS_TO_TICKS(_sendTimeout)) == pdTRUE);
}

bool Queue::enqueue(const void *data, unsigned long sendTimeout)
{
    return (xQueueSend(_queue, data, pdMS_TO_TICKS(sendTimeout)) == pdTRUE);
}

bool Queue::enqueueFromInterrupt(const void *data)
{
	return (xQueueSendFromISR(_queue, data, NULL) == pdTRUE);
}

bool Queue::dequeue(void *data)
{
    return (xQueueReceive(_queue, data, pdMS_TO_TICKS(_receiveTimeout)) == pdTRUE);
}

bool Queue::dequeue(void *data, unsigned long receiveTimeout)
{
    return (xQueueReceive(_queue, data, pdMS_TO_TICKS(receiveTimeout)) == pdTRUE);
}

bool Queue::dequeueFromInterrupt(void *data)
{
	return (xQueueReceiveFromISR(_queue, data, NULL) == pdTRUE);
}

bool Queue::copy(void *data)
{
    return (xQueuePeek(_queue, data, pdMS_TO_TICKS(_receiveTimeout)) == pdTRUE);
}

bool Queue::copy(void *data, unsigned long copyTimeout)
{
    return (xQueuePeek(_queue, data, pdMS_TO_TICKS(copyTimeout)) == pdTRUE);
}

bool Queue::copyFromInterrupt(void *data)
{
	return (xQueuePeekFromISR(_queue, data) == pdTRUE);
}

void Queue::empty()
{
    xQueueReset(_queue);
}

u_byte Queue::count() const
{
	return uxQueueMessagesWaiting((const QueueHandle_t) _queue);
}

u_byte Queue::countFromInterrupt() const
{
	return uxQueueMessagesWaitingFromISR((const QueueHandle_t) _queue);
}

u_byte Queue::available() const
{
	return uxQueueSpacesAvailable((const QueueHandle_t) _queue);
}

u_byte Queue::capacity() const
{
    return _capacity;
}

u_byte Queue::unitSize() const
{
    return _unitSize;
}

bool Queue::isEmpty() const
{
	return (xQueueIsQueueEmptyFromISR((const QueueHandle_t) _queue) == pdTRUE);
}

bool Queue::isFull() const
{
	return (xQueueIsQueueFullFromISR((const QueueHandle_t) _queue) == pdTRUE);
}