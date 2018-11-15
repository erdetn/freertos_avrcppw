#include "usharedbuffer.h"

using namespace urtos;

SharedBuffer::SharedBuffer(u_size bufferSize) : _bufferSize(bufferSize)
{
    _sharedBuffer = xMessageBufferCreate(_bufferSize);
}

bool SharedBuffer::clear()
{
    return (xMessageBufferReset(_sharedBuffer) == pdPASS);
}

bool SharedBuffer::isEmpty() const
{
    return (xMessageBufferIsEmpty(_sharedBuffer) == pdTRUE);
}

bool SharedBuffer::isFull() const
{
    return (xMessageBufferIsFull(_sharedBuffer) == pdTRUE);
}

u_size SharedBuffer::available() const
{
    return xMessageBufferSpaceAvailable(_sharedBuffer);
}

u_size SharedBuffer::bufferSize() const
{
    return _bufferSize;
}

u_size SharedBuffer::write(const void *data, u_size length)
{
    xMessageBufferSend(_sharedBuffer,
                       data, length, pdMS_TO_TICKS(0));
}

u_size SharedBuffer::write(const void *data, u_size length, unsigned long timeout)
{
    xMessageBufferSend(_sharedBuffer,
                       data, length, pdMS_TO_TICKS(timeout));
}

u_size SharedBuffer::writeFromInterrupt(const void *data, u_size length)
{
    xMessageBufferSendFromISR(_sharedBuffer, data, length, NULL);
}

u_size SharedBuffer::read(void *data)
{
    return xMessageBufferReceive(_sharedBuffer, data, _bufferSize, pdMS_TO_TICKS(0));
}

u_size SharedBuffer::read(void *data, u_size length)
{
    return xMessageBufferReceive(_sharedBuffer, data, length, pdMS_TO_TICKS(0));
}

u_size SharedBuffer::read(void *data, u_size length, unsigned long timeout)
{
    return xMessageBufferReceive(_sharedBuffer, data, length, pdMS_TO_TICKS(timeout));
}

u_size SharedBuffer::readFromInterrupt(void *data, u_size length)
{
    return xMessageBufferReceiveFromISR(_sharedBuffer, data, length, NULL);
}
