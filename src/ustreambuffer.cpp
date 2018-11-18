/* Copyright (c) Erdet Nasufi, 2018 */

#include "ustreambuffer.h"

using namespace urtos;

StreamBuffer::StreamBuffer(u_size bufferSize, size_t triggerLevel) : _bufferSize(bufferSize)
{
    _triggerLevel = triggerLevel;
#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    _streamBuffer = xStreamBufferCreate(_bufferSize, _triggerLevel);
#elif configSUPPORT_STATIC_ALLOCATION == 1
    _buffer = new char[_bufferSize + 1];
    _streamBuffer = xStreamBufferCreateStatic(_bufferSize, &_buffer, &_ssBuffer);
#else
#error "Missing dynamic/static allocation configuration"
#endif
}

u_size StreamBuffer::write(const void *data, u_size length)
{
    return xStreamBufferSend(_streamBuffer, data, length, pdMS_TO_TICKS(0));
}

u_size StreamBuffer::write(const void *data, u_size length, unsigned long timeout)
{
    return xStreamBufferSend(_streamBuffer, data, length, pdMS_TO_TICKS(timeout));
}

u_size StreamBuffer::writeFromInterrupt(const void *data, u_size length)
{
    return xStreamBufferSendFromISR(_streamBuffer, data, length, NULL);
}

u_size StreamBuffer::read(void *data)
{
    return xStreamBufferReceive(_streamBuffer, data, _bufferSize, pdMS_TO_TICKS(0));
}

u_size StreamBuffer::read(void *data, u_size length)
{
    return xStreamBufferReceive(_streamBuffer, data, length, 0);
}

u_size StreamBuffer::read(void *data, u_size length, unsigned long timeout)
{
    return xStreamBufferReceive(_streamBuffer, data, length, pdMS_TO_TICKS(timeout));
}

u_size StreamBuffer::readFromInterrupt(void *data, u_size length)
{
    return xStreamBufferReceiveFromISR(_streamBuffer, data, length, NULL);
}

bool StreamBuffer::setThreshold(u_size triggerLevel)
{
    _triggerLevel = triggerLevel;
    return (xStreamBufferSetTriggerLevel(_streamBuffer, _triggerLevel) == pdPASS);
}

bool StreamBuffer::clear()
{
    return (xStreamBufferReset(_streamBuffer) == pdPASS);
}

bool StreamBuffer::isEmpty() const
{
    return (xStreamBufferIsEmpty(_streamBuffer) == pdTRUE);
}

bool StreamBuffer::isFull() const
{
    return (xStreamBufferIsFull(_streamBuffer) == pdTRUE);
}

u_size StreamBuffer::dataAvailable() const
{
    return xStreamBufferBytesAvailable(_streamBuffer);
}

u_size StreamBuffer::spaceAvailable() const
{
    return xStreamBufferSpacesAvailable(_streamBuffer);
}

u_size StreamBuffer::bufferSize() const
{
    return _bufferSize;
}

u_size StreamBuffer::threshold() const
{
    return _triggerLevel;
}
