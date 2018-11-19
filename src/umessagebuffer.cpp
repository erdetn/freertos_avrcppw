/* Copyright (c) Erdet Nasufi, 2018 */

#include "umessagebuffer.h"

using namespace urtos;

MessageBuffer::MessageBuffer(u_size bufferSize) : _bufferSize(bufferSize)
{
#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    _sharedBuffer = xMessageBufferCreate(_bufferSize);
#elif configSUPPORT_STATIC_ALLOCATION == 1
    _buffer = new char[_bufferSize + 1];
    _sharedBuffer = xMessageBufferCreateStatic(_bufferSize, &_buffer, &_msgBuffer);
#else
#error "Missing dynamic/static allocation configuration"
#endif
}

MessageBuffer::~MessageBuffer()
{
#if configSUPPORT_STATIC_ALLOCATION == 1
    delete[] _buffer;
#endif
    vMessageBufferDelete(_sharedBuffer);
}

bool MessageBuffer::clear()
{
    return (xMessageBufferReset(_sharedBuffer) == pdPASS);
}

bool MessageBuffer::isEmpty() const
{
    return (xMessageBufferIsEmpty(_sharedBuffer) == pdTRUE);
}

bool MessageBuffer::isFull() const
{
    return (xMessageBufferIsFull(_sharedBuffer) == pdTRUE);
}

u_size MessageBuffer::available() const
{
    return xMessageBufferSpaceAvailable(_sharedBuffer);
}

u_size MessageBuffer::bufferSize() const
{
    return _bufferSize;
}

u_size MessageBuffer::write(const void *data, u_size length)
{
    return xMessageBufferSend(_sharedBuffer,
                              data, length, pdMS_TO_TICKS(0));
}

u_size MessageBuffer::write(const void *data, u_size length, unsigned long timeout)
{
    return xMessageBufferSend(_sharedBuffer,
                              data, length, pdMS_TO_TICKS(timeout));
}

u_size MessageBuffer::writeFromInterrupt(const void *data, u_size length)
{
    return xMessageBufferSendFromISR(_sharedBuffer, data, length, NULL);
}

u_size MessageBuffer::read(void *data)
{
    return xMessageBufferReceive(_sharedBuffer, data, _bufferSize, pdMS_TO_TICKS(0));
}

u_size MessageBuffer::read(void *data, u_size length)
{
    return xMessageBufferReceive(_sharedBuffer, data, length, pdMS_TO_TICKS(0));
}

u_size MessageBuffer::read(void *data, u_size length, unsigned long timeout)
{
    return xMessageBufferReceive(_sharedBuffer, data, length, pdMS_TO_TICKS(timeout));
}

u_size MessageBuffer::readFromInterrupt(void *data, u_size length)
{
    return xMessageBufferReceiveFromISR(_sharedBuffer, data, length, NULL);
}
