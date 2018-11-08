/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "uthread.h"

using namespace urtos;

Thread::Thread(void *task,
             const portCHAR *threadName,
             ThreadPriority threadPriority,
             unsigned portSHORT stackDepth)
{
    _task = task;
    _threadName = new portCHAR[strlen(threadName) + 1];
    strcpy(_threadName, threadName);
    _threadName[strlen(threadName)] = 0;

    _threadPriority = threadPriority;

    if (stackDepth < configMINIMAL_STACK_SIZE)
    {
        _stackDepth = configMINIMAL_STACK_SIZE;
    }
    else
    {
        _stackDepth = stackDepth;
    }

    _isCreated = false;
}

Thread::~Thread()
{
    delete[] _threadName;
}

bool Thread::start(void *parametersToPass)
{
    _isCreated = (xTaskCreate(_task, (const portCHAR *const)_threadName,
                              _stackDepth,
                              parametersToPass,
                              _threadPriority,
                              &_threadHandler) == pdPASS);
    return _isCreated;
}

#if INCLUDE_vTaskDelete == 1
void Thread::stop()
{
    if (_threadHandler == NULL)
        return;

    vTaskDelete(_threadHandler);
}
#endif

#if INCLUDE_vTaskSuspend == 1
void Thread::suspend()
{
    vTaskSuspend(_threadHandler);
}

void Thread::resume()
{
    vTaskResume(_threadHandler);
}
#endif

#if INCLUDE_vResumeFromISR == 1
void Thread::resumeFromISR()
{
    return (xTaskResumeFromISR(_threadHandler) == pdTRUE);
}
#endif

#if INCLUDE_uxTaskPriorityGet == 1
unsigned char Thread::priority() const
{
    return (unsigned uint8_t)uxTaskPriorityGet(_threadHandler);
}
#endif

#ifdef INCLUDE_vTaskPrioritySet == 1
void Thread::setPriority(ThreadPriority threadPriority)
{
    vTaskPrioritySet(_threadHandler, (UBaseType_t)threadPriority);
}
#endif

#ifdef SLEEP_
void Thread::sleep(unsigned int milliseconds)
{
#if INCLUDE_vTaskDelayUntil == 1
    static TickType_t lastWakeTime_ = xTaskGetTickCount();
    vTaskDelayUntil(&lastWakeTime_, milliseconds / portTICK_PERIOD_MS);
#else
    vTaskDelay(milliseconds / portTICK_PERIOD_MS)
#endif
}
#endif
