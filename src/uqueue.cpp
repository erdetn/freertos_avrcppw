/* Copyright (c) Erdet Nasufi, 2018 */

#include "uqueue.h"

using namespace urtos;

Queue::Queue(u_byte capacity, u_byte unitSize) : _capacity(capacity), _unitSize(unitSize)
{
    _receiveTimeout = DEFAULT_TICKS_TO_WAIT;
    _sendTimeout = DEFAULT_TICKS_TO_WAIT;

#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    _queue = xQueueCreate(_capacity, _unitSize);
#else
    _buffer = new uint8_t[(_capacity + 1) * _unitSize];
    _queue = xQueueCreateStatic(_capacity, _unitSize,
                                _buffer, &_staticBuffer);
#endif
}

Queue::Queue(u_byte capacity, u_byte unitSize,
             unsigned long sendTimeout,
             unsigned long receveTimeout) : _capacity(capacity), _unitSize(unitSize)
{
    _receiveTimeout = receveTimeout;
    _sendTimeout = sendTimeout;

#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    _queue = xQueueCreate(_capacity, _unitSize);
#else
    _buffer = new uint8_t[(_capacity + 1) * _unitSize];
    _queue = xQueueCreateStatic(_capacity, _unitSize,
                                _buffer, &_staticBuffer);
#endif
}

Queue::~Queue()
{
    vQueueDelete(_queue);
#if configSUPPORT_STATIC_ALLOCATION == 1
    delete[] _buffer;
#endif
}

bool Queue::enqueue(const void *data)
{
    return (xQueueSend(_queue, data, pdMS_TO_TICKS(_sendTimeout)) == pdTRUE);
}

bool Queue::enqueue(const void *data, EnqueueMode mode)
{
    if (mode == FromBack)
        return (xQueueSendToBack(_queue, data, pdMS_TO_TICKS(_sendTimeout)) == pdTRUE);
    if (mode == FromFront)
        return (xQueueSendToFront(_queue, data, pdMS_TO_TICKS(_sendTimeout)) == pdTRUE);
    if (mode == Overwrite)
        return (xQueueOverwrite(_queue, data) == pdTRUE);
    if (mode == Default)
        return (xQueueSend(_queue, data, pdMS_TO_TICKS(_sendTimeout)) == pdTRUE);
    return false;
}

bool Queue::enqueue(const void *data, EnqueueMode mode, unsigned long sendTimeout)
{
    if (mode == FromBack)
        return (xQueueSendToBack(_queue, data, pdMS_TO_TICKS(sendTimeout)) == pdTRUE);
    if (mode == FromFront)
        return (xQueueSendToFront(_queue, data, pdMS_TO_TICKS(sendTimeout)) == pdTRUE);
    if (mode == Overwrite)
        return (xQueueOverwrite(_queue, data) == pdTRUE);
    if (mode == Default)
        return (xQueueSend(_queue, data, pdMS_TO_TICKS(sendTimeout)) == pdTRUE);
    return false;
}

bool Queue::enqueueFromInterrupt(const void *data, EnqueueMode mode)
{
    if (mode == FromBack)
        return (xQueueSendToBackFromISR(_queue, data, NULL) == pdTRUE);
    if (mode == FromFront)
        return (xQueueSendToFrontFromISR(_queue, data, NULL) == pdTRUE);
    if (mode == Overwrite)
        return (xQueueOverwriteFromISR(_queue, data, NULL) == pdTRUE);
    if (mode == Default)
        return (xQueueSendFromISR(_queue, data, NULL) == pdTRUE);
    return false;
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
    return uxQueueMessagesWaiting((const QueueHandle_t)_queue);
}

u_byte Queue::countFromInterrupt() const
{
    return uxQueueMessagesWaitingFromISR((const QueueHandle_t)_queue);
}

u_byte Queue::available() const
{
    return uxQueueSpacesAvailable((const QueueHandle_t)_queue);
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
    return (xQueueIsQueueEmptyFromISR((const QueueHandle_t)_queue) == pdTRUE);
}

bool Queue::isFull() const
{
    return (xQueueIsQueueFullFromISR((const QueueHandle_t)_queue) == pdTRUE);
}