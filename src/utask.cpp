/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "utask.h"

using namespace urtos;

Task::Task(void *function, const portCHAR *taskName, TaskPriority taskPriority, unsigned portSHORT stackDepth)
{
	_function = function;
    _taskName = new portCHAR[strlen(taskName)+1];
    strcpy(_taskName, taskName);
    _taskName[strlen(taskName)] = 0;

    _taskPriority = taskPriority;

    if(stackDepth < configMINIMAL_STACK_SIZE)
    {
        _stackDepth = configMINIMAL_STACK_SIZE;
    }
    else
    {
        _stackDepth = stackDepth;
    }

    _isCreated  = false;
}

bool Task::run(void *parametersToPass)
{
    _isCreated = (xTaskCreate(_function, (const portCHAR *const)_taskName,
                                _stackDepth,
                                parametersToPass,
                                _taskPriority,
                                &_taskHandler) == pdPASS);
    return _isCreated;
}

#if INCLUDE_vTaskDelete == 1
    void Task::kill()
    {
        if(_taskHandler == NULL) return;

        vTaskDelete(_taskHandler);
    }
#endif

#if INCLUDE_vTaskSuspend == 1
    void Task::suspend()
    {
        vTaskSuspend(_taskHandler);
    }

    void Task::resume()
    {
        vTaskResume(_taskHandler);
    }
#endif

#if INCLUDE_vResumeFromISR == 1
    void Task::resumeFromISR()
    {
        return (xTaskResumeFromISR(_taskHandler) == pdTRUE);
    }
#endif

#if INCLUDE_uxTaskPriorityGet == 1
    unsigned char Task::priority() const
    {
        return (unsigned uint8_t)uxTaskPriorityGet(_taskHandler);
    }
#endif

#ifdef INCLUDE_vTaskPrioritySet == 1
    void Task::setPriority(TaskPriority taskPriority)
    {
        vTaskPrioritySet(_taskHandler, (UBaseType_t) taskPriority);
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
