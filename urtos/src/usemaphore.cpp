/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "usemaphore.h"

Semaphore::Semaphore()
{
  _blockTime = 0;
  vSemaphoreCreateBinary(_semaphore);

  if (_semaphore != NULL)
    _isCreated = true;
}

Semaphore::Semaphore(TickType_t blockTime)
{
  _blockTime = blockTime;
  vSemaphoreCreateBinary(_semaphore);

  if (_semaphore != NULL)
    _isCreated = true;
}

TickType_t Semaphore::getBlockTime() const
{
  return _blockTime;
}

bool Semaphore::take()
{
  return (xSemaphoreTake(_semaphore, _blockTime) == pdTRUE);
}

bool Semaphore::give()
{
  return (xSemaphoreGive(_semaphore) == pdTRUE);
}

bool Semaphore::isCreated() const
{
  return _isCreated;
}

bool Semaphore::giveFromISR(bool *isTaskUnblocked)
{
  portBASE_TYPE isTaskUnblocked_;
  bool return_;

  return_ = xSemaphoreGiveFromISR(_semaphore, &isTaskUnblocked_);

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
