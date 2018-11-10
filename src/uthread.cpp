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
	_threadPriority = ThreadPriority::MediumPriority;
	_threadName = NULL;
	_threadHandler = NULL;
}

Thread::Thread(Task task,
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

    _created = false;
}

Thread::Thread(const Thread &thread)
{
	_threadHandler = thread._threadHandler;
	_threadName = thread._threadName;
    _threadPriority = thread._threadPriority;
    _created = thread._created;
    _task = thread._task;
    _stackDepth = thread._stackDepth;
}

Thread::~Thread()
{
    delete[] _threadName;
}

bool Thread::start(void *parametersToPass)
{
    _created = (xTaskCreate(_task, (const portCHAR *const)_threadName,
                              _stackDepth,
                              parametersToPass,
                              _threadPriority,
                              &_threadHandler) == pdPASS);
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

#ifdef SLEEP_
static void Thread::sleep(unsigned int milliseconds)
{
#if INCLUDE_vTaskDelayUntil == 1
    static TickType_t lastWakeTime_ = xTaskGetTickCount();
    vTaskDelayUntil(&lastWakeTime_, milliseconds / portTICK_PERIOD_MS);
#else
    vTaskDelay(milliseconds / portTICK_PERIOD_MS)
#endif
}
#endif
