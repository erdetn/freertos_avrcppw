#include "usharedbuffer.h"

using namespace urtos;

SharedBuffer::SharedBuffer(size_t bufferSize) : _bufferSize(bufferSize)
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

size_t SharedBuffer::available() const
{
	return xMessageBufferSpacesAvailable(_sharedBuffer);
}

size_t SharedBuffer::bufferSize() const
{
	return _bufferSize;
}