/* Copyright (c) Erdet Nasufi, 2018 */

#include "uthread.h"

using namespace urtos;

Thread::Thread()

{
    _created = false;
    _task = NULL;
    _stackDepth = 0;
    _threadPriority = ThreadPriority::MEDIUM_PRIORITY;
    _threadHandler = NULL;
    _paramToPass = NULL;
}

Thread::Thread(ThreadCallback task,
               ThreadPriority threadPriority,
               unsigned int stackDepth,
               void *paramToPass)
{
    _task = task;
    _paramToPass = paramToPass;
    _threadPriority = threadPriority;

    if (stackDepth < configMINIMAL_STACK_SIZE)
    {
        _stackDepth = configMINIMAL_STACK_SIZE;
    }
    else
    {
        _stackDepth = stackDepth;
    }

    _created = hook();
}

Thread::Thread(const Thread &thread)
{
    _threadHandler = thread._threadHandler;
    _threadPriority = thread._threadPriority;
    _created = thread._created;
    _task = thread._task;
    _stackDepth = thread._stackDepth;
    _paramToPass = thread._paramToPass;

    _created = hook();
}

Thread::~Thread()
{
}

bool Thread::hook()
{
#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    _created = (xTaskCreate(_task,
                            (const portCHAR *const)NULL,
                            _stackDepth,
                            _paramToPass,
                            _threadPriority,
                            &_threadHandler) == pdPASS);
#else
    _created = (xTaskCreateStatic(_task,
                                  (const portCHAR *const)NULL,
                                  _stackDepth,
                                  _paramToPass,
                                  _threadPriority,
                                  &_taskBuffer,
                                  &_threadHandler) == pdPASS);
#endif
    return _created;
}

bool Thread::created() const
{
    return _created;
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
signed char Thread::resumeFromInterrupt()
{
    return (xTaskResumeFromISR(_threadHandler) == pdTRUE);
}
#endif

#if INCLUDE_uxTaskPriorityGet == 1
unsigned char Thread::priority() const
{
    return (unsigned char)uxTaskPriorityGet(_threadHandler);
}
#endif

#if INCLUDE_vTaskPrioritySet == 1
void Thread::setPriority(ThreadPriority threadPriority)
{
    vTaskPrioritySet(_threadHandler, (UBaseType_t)threadPriority);
}
#endif

#if INCLUDE_eTaskGetState == 1
ThreadState Thread::getThreadState() const
{
    return (ThreadState)eTaskGetState(_threadHandler);
}
#endif

unsigned int Thread::stackDepth() const
{
    return _stackDepth;
}

#ifdef SLEEP_
void Thread::sleep(unsigned long milliseconds)
{
#if INCLUDE_vTaskDelay == 1
    vTaskDelay(pdMS_TO_TICKS(milliseconds)); // (milliseconds * configTICK_RATE_HZ) / 1000L);
#else
#error "No task delay configuration set."
#endif
}
#endif

#if INCLUDE_xTaskAbortDelay == 1
bool Thread::unblock()
{
    return (xTaskAbortDelay(_threadHandler) == pdPASS);
}
#endif

void Thread::yield()
{
    taskYIELD();
}