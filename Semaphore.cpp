#include "Semaphore.h"

Semaphore::Semaphore()
{
  m_blockTime = 0;
  vSemaphoreCreateBinary(m_semaphore);

  if (m_semaphore != NULL)
    m_isCreated = true;
}

Semaphore::Semaphore(TickType_t blockTime)
{
  m_blockTime = blockTime;
  vSemaphoreCreateBinary(m_semaphore);

  if (m_semaphore != NULL)
    m_isCreated = true;
}

TickType_t Semaphore::getBlockTime() const
{
  return m_blockTime;
}

bool Semaphore::take()
{
  return (xSemaphoreTake(m_semaphore, m_blockTime) == pdTRUE);
}

bool Semaphore::give()
{
  return (xSemaphoreGive(m_semaphore) == pdTRUE);
}

bool Semaphore::isCreated() const
{
  return m_isCreated;
}

bool Semaphore::giveFromISR(bool *isTaskUnblocked)
{
  portBASE_TYPE isTaskUnblocked_;
  bool return_;

  return_ = xSemaphoreGiveFromISR(m_semaphore, &isTaskUnblocked_);

  if(isTaskUnblocked_ == pdTRUE)
  {
    *(isTaskUnblocked) = true;
  }

  return (return_ == pdTRUE);
}
