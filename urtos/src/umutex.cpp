/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "umutex.h"

Mutex::Mutex()
{
  _blockTime = 0;
  _mutex = xSemaphoreCreateMutex();

  if (_mutex != NULL)
    _isCreated = true;
}

Mutex::Mutex(TickType_t blockTime)
{
  _blockTime = blockTime;
  _mutex = xSemaphoreCreateMutex();

  if (_mutex != NULL)
    _isCreated = true;
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

bool Mutex::isCreated() const
{
  return _isCreated;
}

bool Mutex::unlockFromISR(bool *isTaskUnblocked)
{
  portBASE_TYPE isTaskUnblocked_;
  bool return_;

  return_ = xSemaphoreGiveFromISR(_mutex, &isTaskUnblocked_);

  if(isTaskUnblocked_ == pdTRUE)
  {
    *(isTaskUnblocked) = true;
  }
  else
  {
    *(isTaskUnblocked) = false;
  }

  return (return_ == pdTRUE);
}
