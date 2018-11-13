/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

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

#if THREAD_NAMING == ENABLE
    _threadName = NULL;
#endif

    //_created = hook();
}

#if THREAD_NAMING == ENABLE
Thread::Thread(Task task,
               const portCHAR *threadName,
               ThreadPriority threadPriority,
               unsigned portSHORT stackDepth,
               void *paramToPass)
{
    _task = task;
    _threadName = new portCHAR[strlen(threadName) + 1];
    strcpy(_threadName, threadName);
    _threadName[strlen(threadName)] = 0;
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
#else
Thread::Thread(Task task,
               ThreadPriority threadPriority,
               unsigned portSHORT stackDepth,
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
#endif

Thread::Thread(const Thread &thread)
{
    _threadHandler = thread._threadHandler;
    _threadPriority = thread._threadPriority;
    _created = thread._created;
    _task = thread._task;
    _stackDepth = thread._stackDepth;
    _paramToPass = thread._paramToPass;

#if THREAD_NAMING == ENABLE
    _threadName = thread._threadName;
#endif

    _created = hook();
}

Thread::~Thread()
{
#if THREAD_NAMING == ENABLE
    delete[] _threadName;
#endif
}

bool Thread::hook()
{
#if THREAD_NAMING == ENABLE
    _created = (xTaskCreate(_task, (const portCHAR *const)_threadName,
                            _stackDepth,
                            _paramToPass,
                            _threadPriority,
                            &_threadHandler) == pdPASS);
#else
    _created = (xTaskCreate(_task, (const portCHAR *const)NULL,
                            _stackDepth,
                            _paramToPass,
                            _threadPriority,
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
signed char Thread::resumeFromISR()
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

static byte Thread::numberOfThread()
{
    return (byte)xTaskGetSchedulerState();
}

#ifdef SLEEP_
static void Thread::sleep(unsigned long milliseconds)
{
    #if INCLUDE_vTaskDelay == 1
        vTaskDelay((milliseconds * configTICK_RATE_HZ) / 1000L);
    #else
    #error "No task delay configuration set."
    #endif
}
#endif
