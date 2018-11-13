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
    QueueHandle_t _queue;
    unsigned long _sendTimeout;
    unsigned long _receiveTimeout;
    const Byte _capacity;
    const Byte _unitSize;

public:
    Queue(Byte capacity, Byte unitSize);
    Queue(Byte capacity, Byte unitSize,
          unsigned long sendTimeout,
          unsigned long receveTimeout);

    bool send(const void *data);
    bool send(const void *data, unsigned long sendTimeout);
	bool sendFromInterrupt(const void *data);

    bool receive(void *data);
    bool receive(void *data, unsigned long receiveTimeout);
	bool receiveFromInterrupt(void *data);

    bool copy(void *data);
    bool copy(void *data, unsigned long copyTimeout);
	bool copyFromInterrupt(void *data);

	void empty();

	Byte count() const;
	Byte countFromInterrupt() const;

	Byte available() const;

    Byte capacity() const;
    Byte unitSize() const;

	bool isEmpty() const;
	bool isFull() const;
};
} // namespace urtos

#endif
#endif
