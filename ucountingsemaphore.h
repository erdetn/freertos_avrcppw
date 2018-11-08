/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

class CountingSemaphore
{
    private:
      SemaphoreHandle_t m_semaphore  = NULL;
      TickType_t        m_blockTime  = 0;
      bool              m_isCreated  = false;
      
      portBASE_TYPE m_maxCount;
      portBASE_TYPE m_initCount;

    public:
      CountingSemaphore(portBASE_TYPE maxCount, portBASE_TYPE initCount);
      CountingSemaphore(portBASE_TYPE maxCount, portBASE_TYPE initCount, TickType_t blockTime);

      TickType_t getBlockTime() const;

      bool take();
      bool give();
      bool giveFromISR(bool *isTaskUnblocked);
      bool isCreated() const;

      portBASE_TYPE maximumCount() const;
      portBASE_TYPE initialCount() const;
};
