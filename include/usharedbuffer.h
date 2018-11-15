/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <message_buffer.h>

#include "urtos.h"

#ifndef USHAREDBUFFER_H
#define USHAREDBUFFER_H

namespace urtos
{
class SharedBuffer
{
private:
    MessageBufferHandle_t _sharedBuffer;
    const u_size _bufferSize;

public:
    SharedBuffer(u_size bufferSize);

    u_size write(const void *data, u_size length);
    u_size write(const void *data, u_size length, unsigned long timeout);

    u_size writeFromInterrupt(const void *data, u_size length);

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
