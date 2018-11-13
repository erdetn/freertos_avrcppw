/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "umutex.h"

using namespace urtos;

Mutex::Mutex()
{
  _blockTime = 0;
  _mutex = xSemaphoreCreateMutex();

  if (_mutex != NULL)
    _created = true;
}

Mutex::Mutex(TickType_t blockTime)
{
  _blockTime = blockTime;
  _mutex = xSemaphoreCreateMutex();

  if (_mutex != NULL)
    _created = true;
}

Mutex::Mutex(const Mutex& mutex)
{
	_blockTime = mutex._blockTime;
	_mutex = mutex._mutex;
	_created = mutex._created;
}

TickType_t Mutex::getBlockTime() const
{
  return _blockTime;
}

bool Mutex::lock()
{
  return (xSemaphoreTake(_mutex, _blockTime) == pdTRUE);
}

bool Mutex::unlock()
{
  return (xSemaphoreGive(_mutex) == pdTRUE);
}

bool Mutex::created() const
{
  return _created;
}

bool Mutex::unlockFromISR(bool *isTaskUnblocked)
{
  portBASE_TYPE isTaskUnblocked_;
  bool _return;

  _return = xSemaphoreGiveFromISR(_mutex, &isTaskUnblocked_);

  if(isTaskUnblocked_ == pdTRUE)
  {
    *(isTaskUnblocked) = true;
  }
  else
  {
    *(isTaskUnblocked) = false;
  }

  return (_return == pdTRUE);
}
