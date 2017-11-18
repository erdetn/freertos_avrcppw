#include <Arduino_FreeRTOS.h>
#include <semphr.h>

class Semaphore
{
  private:
    SemaphoreHandle_t m_semaphore  = NULL;
    TickType_t        m_blockTime  = 0;
    bool              m_isCreated  = false;

  public:
    Semaphore();
    Semaphore(TickType_t blockTime);

    TickType_t getBlockTime() const;

    bool take();
    bool give();
    bool isCreated() const;
    bool giveFromISR(bool *isTaskUnblocked);
};
