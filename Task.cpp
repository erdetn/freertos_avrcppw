#include "Task.h"

Task::Task(const portCHAR *taskName, TaskPriority taskPriority, unsigned portSHORT stackDepth)
{
    m_taskName = new portCHAR[strlen(taskName)+1];
    strcpy(m_taskName, taskName);
    m_taskName[strlen(taskName)] = 0;

    m_taskPriority = taskPriority;

    if(stackDepth < configMINIMAL_STACK_SIZE)
    {
        m_stackDepth = configMINIMAL_STACK_SIZE;
    }
    else
    {
        m_stackDepth = stackDepth;
    }

    m_isCreated  = false;
}

bool Task::run(TaskFunction_t task, void *parametersToPass)
{
    m_isCreated = (xTaskCreate(task, (const portCHAR *const)m_taskName,
                                m_stackDepth,
                                parametersToPass,
                                m_taskPriority,
                                &m_taskHandler) == pdPASS);
    return m_isCreated;
}

#if INCLUDE_vTaskDelete == 1
    void Task::kill()
    {
        if(m_taskHandler == NULL) return;

        vTaskDelete(m_taskHandler);
    }
#endif

#if INCLUDE_vTaskSuspend == 1
    void Task::suspend()
    {
        vTaskSuspend(m_taskHandler);
    }

    void Task::resume()
    {
        vTaskResume(m_taskHandler);
    }
#endif

#if INCLUDE_vResumeFromISR == 1
    void Task::resumeFromISR()
    {
        return (xTaskResumeFromISR(m_taskHandler) == pdTRUE);
    }
#endif

#if INCLUDE_uxTaskPriorityGet == 1
    unsigned char Task::priority() const
    {
        return (unsigned uint8_t)uxTaskPriorityGet(m_taskHandler);
    }
#endif

#ifdef INCLUDE_vTaskPrioritySet == 1
    void Task::setPriority(TaskPriority taskPriority)
    {
        vTaskPrioritySet(m_taskHandler, (UBaseType_t) taskPriority);
    }
#endif

#ifdef SLEEP_
    void Task::sleep(unsigned int milliseconds)
    {
        #if INCLUDE_vTaskDelayUntil == 1
            static TickType_t lastWakeTime_ = xTaskGetTickCount();
            vTaskDelayUntil(&lastWakeTime_, milliseconds/portTICK_PERIOD_MS);
        #else
            vTaskDelay(milliseconds/portTICK_PERIOD_MS)
        #endif
    }
#endif
