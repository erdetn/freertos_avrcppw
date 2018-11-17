/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <task.h>

#include "urtos.h"

#ifndef UKERNEL_H
#define UKERNEL_H

#ifndef BEGIN_CRITICAL_REGION
#define BEGIN_CRITICAL_REGION() \
    taskENTER_CRITICAL();       \
    {
#endif

#ifndef END_CRITICAL_REGION
#define END_CRITICAL_REGION() \
    }                         \
    taskEXIT_CRITICAL();
#endif

#ifndef BEGIN_INTERRUPT_CRITICAL_REGION
#define BEGIN_INTERRUPT_CRITICAL_REGION() \
    taskENTER_CRITICAL_FROM_ISR();        \
    {
#endif

#ifndef END_INTERRUPT_CRITICAL_REGION
#define END_INTERRUPT_CRITICAL_REGION() \
    }                                   \
    taskEXIT_CRITICAL_FROM_ISR(savedInterruptStatus);
#endif

#ifndef ENABLE_INTERRUPT
#define ENABLE_INTERRUPT() taskENABLE_INTERRUPTS()
#endif

#ifndef DISABLE_INTERRUPT
#define DISABLE_INTERRUPT() taskDISABLE_INTERRUPTS()
#endif

namespace urtos
{
class Kernel
{
public:
    static void run();
    static void kill();
    static void suspend();
    static void resume();

    static u_byte numberOfThreads();
};
} // namespace urtos
#endif