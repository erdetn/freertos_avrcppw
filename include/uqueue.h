/* Copyright (c) Erdet Nasufi, 2018 */

#ifndef UQUEUE_H
#define UQUEUE_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>

#include "urtos.h"

#if (configSUPPORT_DYNAMIC_ALLOCATION == 0)
#error "Dynamic allocation is not configured."
#else

namespace urtos
{

enum EnqueueMode : unsigned char
{
	FromBack = 0,
	FromFront,
	Overwrite,
	Default
};

class Queue
{
private:
    QueueHandle_t _queue;
    unsigned long _sendTimeout;
    unsigned long _receiveTimeout;
    const u_byte _capacity;
    const u_byte _unitSize;

#if configSUPPORT_STATIC_ALLOCATION == 1
	uint8_t *_buffer;
    StaticQueue_t _static_Queue;
#endif

public:
    Queue(u_byte capacity, u_byte unitSize);
    Queue(u_byte capacity, u_byte unitSize,
          unsigned long sendTimeout,
          unsigned long receveTimeout);
	~Queue();

	bool enqueue(const void *data);
    bool enqueue(const void *data, EnqueueMode mode);
    bool enqueue(const void *data, EnqueueMode mode, unsigned long sendTimeout);
    bool enqueueFromInterrupt(const void *data, EnqueueMode mode);

    bool dequeue(void *data);
    bool dequeue(void *data, unsigned long receiveTimeout);
    bool dequeueFromInterrupt(void *data);

    bool copy(void *data);
    bool copy(void *data, unsigned long copyTimeout);
    bool copyFromInterrupt(void *data);

	bool overwrite(const void *data);
	bool overwriteFromInterrupt(const void *data);

    void empty();

    u_byte count() const;
    u_byte countFromInterrupt() const;

    u_byte available() const;

    u_byte capacity() const;
    u_byte unitSize() const;

    bool isEmpty() const;
    bool isFull() const;
};
} // namespace urtos

#endif
#endif
