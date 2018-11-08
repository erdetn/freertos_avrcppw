/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <string.h>

#include "urtos.h"

#ifndef UTASK_H
#define UTASK_H

namespace urtos
{
enum TaskPriority : unsigned char
{
    LowPriority = P1,
    MediumPriority = P2,
    HighPriority = P3,
    ExtraPriority = P4
};

class Task
{
private:
    TaskHandle_t _taskHandler;
    portCHAR *_taskName;
    TaskPriority _taskPriority;
    bool _isCreated;
	void *_function;

    unsigned portSHORT _stackDepth;

public:
    Task(void *function, const portCHAR *taskName, TaskPriority TaskPriority, unsigned portSHORT stackDepth);
    bool run(void *parametersToPass);

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
} // namespace urtos
#endif
