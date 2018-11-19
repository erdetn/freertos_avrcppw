/* Copyright (c) Erdet Nasufi, 2018 */

#ifndef USTREAMBUFFER_H
#define USTREAMBUFFER_H

#include <Arduino_FreeRTOS.h>
#include <stream_buffer.h>

#include "urtos.h"

namespace urtos
{
class StreamBuffer
{
private:
    StreamBufferHandle_t _streamBuffer;
    const u_size _bufferSize;
	u_size _triggerLevel;

#if configSUPPORT_STATIC_ALLOCATION == 1
	StaticStreamBuffer_t _ssBuffer;
    char _buffer[];
#endif

public:
    StreamBuffer(u_size bufferSize, u_size triggerLevel);
	~StreamBuffer();
	
    u_size write(const void *data, u_size length);
    u_size write(const void *data, u_size length, unsigned long timeout);

    u_size writeFromInterrupt(const void *data, u_size length);

    u_size read(void *data);
    u_size read(void *data, u_size length);
    u_size read(void *data, u_size length, unsigned long timeout);

    u_size readFromInterrupt(void *data, u_size length);

	bool setThreshold(u_size triggerLevel);

    bool clear();

    bool isEmpty() const;
    bool isFull() const;

	u_size dataAvailable() const;
    u_size spaceAvailable() const;
    u_size bufferSize() const;
	u_size threshold() const;
};
} // namespace urtos

#endif
