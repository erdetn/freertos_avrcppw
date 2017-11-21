/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

class Mutex
{
  private:
    SemaphoreHandle_t m_mutex      = NULL;
    TickType_t        m_blockTime  = 0;
    bool              m_isCreated  = false;

  public:
    Mutex();
    Mutex(TickType_t blockTime);

    TickType_t getBlockTime() const;

    bool lock();
    bool unlock();
    bool unlockFromISR(bool *isTaskUnblocked);
    bool isCreated() const;
};
