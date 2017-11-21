/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "Mutex.h"

Mutex::Mutex()
{
  m_blockTime = 0;
  m_mutex = xSemaphoreCreateMutex();

  if (m_mutex != NULL)
    m_isCreated = true;
}

Mutex::Mutex(TickType_t blockTime)
{
  m_blockTime = blockTime;
  m_mutex = xSemaphoreCreateMutex();

  if (m_mutex != NULL)
    m_isCreated = true;
}

TickType_t Mutex::getBlockTime() const
{
  return m_blockTime;
}

bool Mutex::lock()
{
  return (xSemaphoreTake(m_mutex, m_blockTime) == pdTRUE);
}

bool Mutex::unlock()
{
  return (xSemaphoreGive(m_mutex) == pdTRUE);
}

bool Mutex::isCreated() const
{
  return m_isCreated;
}

bool Mutex::unlockFromISR(bool *isTaskUnblocked)
{
  portBASE_TYPE isTaskUnblocked_;
  bool return_;

  return_ = xSemaphoreGiveFromISR(m_mutex, &isTaskUnblocked_);

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
