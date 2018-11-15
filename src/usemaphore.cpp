/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "usemaphore.h"

using namespace urtos;

Semaphore::Semaphore()
{
  _blockTime = 0;
  vSemaphoreCreateBinary(_semaphore);

  if (_semaphore != NULL)
    _isCreated = true;
}

Semaphore::Semaphore(unsigned long blockTime)
{
  _blockTime = blockTime;
  vSemaphoreCreateBinary(_semaphore);

  if (_semaphore != NULL)
    _isCreated = true;
}

unsigned long Semaphore::getBlockTime() const
{
  return _blockTime;
}

bool Semaphore::take()
{
  return (xSemaphoreTake(_semaphore, pdMS_TO_TICKS(_blockTime)) == pdTRUE);
}

bool Semaphore::take(unsigned long blockTime)
{
	return (xSemaphoreTake(_semaphore, pdMS_TO_TICKS(blockTime)) == pdTRUE );
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
