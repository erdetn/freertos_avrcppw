#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <string.h>

#define LOOP     for(;;)

#define TaskDelay(X) vTaskDelay(X/portTICK_PERIOD_MS)

enum TaskPriority
{
    Zero = 0,
    Low = 1,
    Medium = 2,
    High = 3
};

class Task
{
private:
    TaskHandle_t  m_taskHandler;
    portCHAR     *m_taskName;
    TaskPriority  m_taskPriority;
    bool          m_isCreated;

    unsigned portSHORT m_stackDepth;

public:
    Task(const portCHAR *taskName, TaskPriority TaskPriority, unsigned portSHORT stackDepth);
    bool run(TaskFunction_t task, void *parametersToPass);

    #if INCLUDE_vTaskDelete == 1
        void kill();
    #endif

    #if INCLUDE_vTaskSuspend == 1
        void suspend();
        void resume();
    #endif
    
    #if INCLUDE_vResumeFromISR == 1
        void resumeFromISR();
    #endif

    #ifdef INCLUDE_vTaskPrioritySet == 1
        void setPriority(TaskPriority taskPriority);
    #endif

    #if INCLUDE_uxTaskPriorityGet == 1
        unsigned char priority() const;
    #endif

    unsigned portSHORT stackDepth() const;

    #if (INCLUDE_vTaskDelayUntil == 1) || (INCLUDE_vTaskDelay == 1)
        #define SLEEP_
        void sleep(unsigned int milliseconds);
    #endif
};
