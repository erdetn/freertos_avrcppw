/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <string.h>

#ifndef TASK_H
#define TASK_H

#define DEFAULT_TICKS_TO_WAIT   (500/portTICK_PERIOD_MS)  //500 [ms]
#define TICK_PERIOD_MS          portTICK_PERIOD_MS
#define infinite_loop           for(;;)
#define TaskDelay(X)            vTaskDelay(X/portTICK_PERIOD_MS)

#ifdef configMAX_PRIORITIES
    #ifdef configMAX_PRIORITIES == 1
        #define P1 1
        #define P2 1
        #define P3 1
        #define P4 1
    #endif

    #ifdef configMAX_PRIORITIES == 2
        #define P1 1
        #define P2 1
        #define P3 2
        #define P4 2
    #endif

    #ifdef configMAX_PRIORITIES == 3
        #define P1 1
        #define P2 2
        #define P3 3
        #define P4 3
    #endif

    #ifdef configMAX_PRIORITIES > 3
        #define P1 1
        #define P2 2
        #define P3 3
        #define P4 4
    #endif
#else
    #error "Number of priorities not configured."
#endif

enum TaskPriority
{
    LowPriority    = P1,
    MediumPriority = P2,
    HighPriority   = P3,
    ExtraPriority  = P4
};

class Task
{
private:
    TaskHandle_t  m_taskHandler;
    portCHAR     *m_taskName;
    TaskPriority  m_taskPriority;
    bool          m_isCreated;

    unsigned portSHORT m_stackDepth;

public:
    Task(const portCHAR *taskName, TaskPriority TaskPriority, unsigned portSHORT stackDepth);
    bool run(TaskFunction_t task, void *parametersToPass);

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

#endif
