/* Copyright (c) Erdet Nasufi, 2018 */

#ifndef UMESSAGEBUFFER_H
#define UMESSAGEBUFFER_H

#include <Arduino_FreeRTOS.h>
#include <message_buffer.h>

#include "urtos.h"

namespace urtos
{
class MessageBuffer
{
private:
    MessageBufferHandle_t _sharedBuffer;
    const u_size _bufferSize;

#if configSUPPORT_STATIC_ALLOCATION == 1
	StaticMessageBuffer_t _msgBuffer;
    char _buffer[];
#endif

public:
    MessageBuffer(u_size bufferSize);

    u_size write(const void *data, u_size length);
    u_size write(const void *data, u_size length, unsigned long timeout);

    u_size writeFromInterrupt(const void *data, u_size length);

    u_size read(void *data);
    u_size read(void *data, u_size length);
    u_size read(void *data, u_size length, unsigned long timeout);

    u_size readFromInterrupt(void *data, u_size length);

    bool clear();

    bool isEmpty() const;
    bool isFull() const;

    u_size available() const;
    u_size bufferSize() const;
};
} // namespace urtos

#endif
