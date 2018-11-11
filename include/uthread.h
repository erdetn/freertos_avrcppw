/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <string.h>

#include "urtos.h"

#ifndef UTHREAD_H
#define UTHREAD_H

#define THREAD_NAMING DISABLE

namespace urtos
{
enum ThreadPriority : unsigned char
{
    LowPriority = P1,
    MediumPriority = P2,
    HighPriority = P3,
    ExtraPriority = P4
};

class Thread
{
private:
    TaskHandle_t _threadHandler;
    ThreadPriority _threadPriority;
    bool _created;
    Task _task;
    unsigned portSHORT _stackDepth;

#if THREAD_NAMING == ENABLE
    portCHAR *_threadName;
#endif

public:
    Thread();
#if THREAD_NAMING == ENABLE
    Thread(Task task,
           const portCHAR *threadName,
           ThreadPriority threadPriority,
           unsigned portSHORT stackDepth);
#else
    Thread(Task task,
           ThreadPriority threadPriority,
           unsigned portSHORT stackDepth);
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
    signed char resumeFromISR();
#endif

#if INCLUDE_vTaskPrioritySet == 1
    void setPriority(ThreadPriority threadPriority);
#endif

#if INCLUDE_uxTaskPriorityGet == 1
    unsigned char priority() const;
#endif

    unsigned portSHORT stackDepth() const;

#if (INCLUDE_vTaskDelayUntil == 1) || (INCLUDE_vTaskDelay == 1)
#define SLEEP_
    static void sleep(unsigned int milliseconds);
#endif
};
} // namespace urtos
#endif
