/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <message_buffer.h>

#include "urtos.h"

namespace urtos
{
class SharedBuffer
{
private:
	MessageBufferHandle_t _sharedBuffer;
	const size_t _bufferSize;

public:
    SharedBuffer(size_t bufferSize);

	size_t attach(const void *payload, size_t length);
	size_t attach(const void *payload, size_t length, unsigned long timeout);

	size_t attachFromInterrupt(const void *payload, size_t length);
	size_t attachFromInterrupt(const void *payload, size_t length, unsigned long timeout);

	size_t detach(const void *payload, size_t length);
	size_t detach(const void *payload, size_t length, unsigned long timeout);

	size_t detachFromInterrupt(const void *payload, size_t length);
	size_t detachFromInterrupt(const void *payload, size_t length, unsigned long timeout);

	bool clear();

	bool isEmpty() const;
	bool isFull() const;

	size_t available() const;

	size_t bufferSize() const;
};
} // namespace urtos

#endif
#endif
