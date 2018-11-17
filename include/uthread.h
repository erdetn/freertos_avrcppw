/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <string.h>

#include "urtos.h"

#ifndef UTHREAD_H
#define UTHREAD_H

#define THREAD_NAMING ENABLE

namespace urtos
{

enum ThreadPriority : unsigned char
{
    LOW_PRIORITY = P1,
    MEDIUM_PRIORITY = P2,
    HIGH_PRIORITY = P3,
    EXTRA_PRIORITY = P4
};

class Thread
{
private:
#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    TaskHandle_t _threadHandler;
#else
    StaticTask_t _threadHandler;
    StackType_t _taskBuffer;
#endif
    ThreadPriority _threadPriority;
    bool _created;
    Task _task;
    unsigned portSHORT _stackDepth;
    void *_paramToPass;

    bool hook();

#if THREAD_NAMING == ENABLE
    portCHAR *_threadName;
#endif

public:
    Thread();
#if THREAD_NAMING == ENABLE
    Thread(Task task,
           const portCHAR *threadName,
           ThreadPriority threadPriority,
           unsigned portSHORT stackDepth,
           void *paramToPass);
#else
    Thread(Task task,
           ThreadPriority threadPriority,
           unsigned portSHORT stackDepth,
           void *paramToPass);
#endif

    Thread(const Thread &thread);
    ~Thread();

    bool start(void *parametersToPass);
    bool created() const;

#if INCLUDE_vTaskDelete == 1
    void stop();
#endif

#if INCLUDE_vTaskSuspend == 1
    void suspend();
    void resume();
#endif

#if INCLUDE_vResumeFromISR == 1
    signed char resumeFromInterrupt();
#endif

#if INCLUDE_vTaskPrioritySet == 1
    void setPriority(ThreadPriority threadPriority);
#endif

#if INCLUDE_uxTaskPriorityGet == 1
    unsigned char priority() const;
#endif

#if INCLUDE_eTaskGetState == 1
    ThreadState getThreadState() const;
#endif

    unsigned int stackDepth() const;

#if (INCLUDE_vTaskDelayUntil == 1) || (INCLUDE_vTaskDelay == 1)
#define SLEEP_
    static void sleep(unsigned long milliseconds);
#endif

	bool unblock();

    static void yield();
};
} // namespace urtos
#endif
