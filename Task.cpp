#include "Task.h"

Task::Task(const portCHAR *taskName, TaskPriority taskPriority, unsigned portSHORT stackDepth)
{
    m_taskName = new portCHAR[strlen(taskName)+1];
    strcpy(m_taskName, taskName);
    m_taskName[strlen(taskName)] = 0;

    m_taskPriority = taskPriority;

    m_stackDepth = stackDepth;
    m_isCreated  = false;
}

bool Task::run(TaskFunction_t task, void *parametersToPass)
{
    m_isCreated == (xTaskCreate(task, (const portCHAR *const)m_taskName,
                                m_stackDepth, parametersToPass,
                                m_taskPriority,
                                &m_taskHandler) == pdPASS);
    return m_isCreated;
}

void Task::kill()
{
    if(m_taskHandler == NULL) return;

    vTaskDelete(m_taskHandler);
}

void Task::suspend()
{
    vTaskSuspend(m_taskHandler);
}

void Task::resume()
{
    vTaskResume(m_taskHandler);
}

void Task::resumeFromISR()
{
    return (xTaskResumeFromISR(m_taskHandler) == pdTRUE);
}

unsigned char Task::priority() const
{
    return (unsigned uint8_t)uxTaskPriorityGet(m_taskHandler);
}

void Task::setPriority(TaskPriority taskPriority)
{
    vTaskPrioritySet(m_taskHandler, (UBaseType_t) taskPriority);
}

void Task::sleep(unsigned int milliseconds)
{
    #if INCLUDE_vTaskDelayUntil == 1
        static TickType_t lastWakeTime_ = xTaskGetTickCount();
        vTaskDelayUntil(&lastWakeTime_, milliseconds/portTICK_PERIOD_MS);
    #else
        vTaskDelay(milliseconds/portTICK_PERIOD_MS)
    #endif
}
