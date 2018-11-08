/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <queue.h>

#include "urtos.h"

#if (configSUPPORT_DYNAMIC_ALLOCATION == 0)
#error "Dynamic allocation is not configured."
#else

#ifndef UQUEUE_H
#define UQUEUE_H

namespace urtos
{
class Queue
{
private:
    QueueHandle_t _hQueue;
    TickType_t _waitToSend;
    TickType_t _waitToReceive;
    UBaseType_t _length;
    UBaseType_t _unitSize;

public:
    Queue(UBaseType_t length, UBaseType_t unitSize);
    Queue(UBaseType_t length, UBaseType_t unitSize, TickType_t defaultSendReceiveTime);
    Queue(UBaseType_t length, UBaseType_t unitSize, TickType_t waitToSend, TickType_t waitToReceive);

    bool send(const void *data);
    bool send(const void *data, TickType_t waitToSend);

    bool receive(void *data);
    bool receive(void *data, TickType_t waitToReceive);

    bool copy(void *data);
    bool copy(void *data, TickType_t waitToCopy);

    TickType_t waitingToSendTime() const;
    TickType_t waitingToReceiveTime() const;

    UBaseType_t length() const;
    UBaseType_t unitSize() const;
};
} // namespace urtos

#endif
#endif
