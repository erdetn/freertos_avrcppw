/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>

#ifndef URTOS_H
#define URTOS_H

#define ENABLE 1
#define DISABLE 0

#define LOOP while (1)

#define DEFAULT_TICKS_TO_WAIT (500 / portTICK_PERIOD_MS) //500 [ms]
#define TICK_PERIOD_MS portTICK_PERIOD_MS
#define infinite for (;;)
#define TaskDelay(X) vTaskDelay(X / portTICK_PERIOD_MS)

#define Task TaskFunction_t

#ifdef configMAX_PRIORITIES
#if configMAX_PRIORITIES == 1
#define P1 1
#define P2 1
#define P3 1
#define P4 1
#endif

#if configMAX_PRIORITIES == 2
#define P1 1
#define P2 1
#define P3 2
#define P4 2
#endif

#if configMAX_PRIORITIES == 3
#define P1 1
#define P2 2
#define P3 3
#define P4 3
#endif

#if configMAX_PRIORITIES > 3
#define P1 1
#define P2 2
#define P3 3
#define P4 4
#endif
#else
#error "Number of priorities not configured."
#endif

#define BitMask EventBits_t

#if configUSE_16_BIT_TICKS == 1
#define BITMASK_MAP 0xFF
#else
#define BITMASK_MAP 0xFFFFFF
#endif

#define SET_BIT(_b) (1 << _b)
#define CLEAR_BIT(_b) ~(1 << _b)

typedef unsigned char Byte;

#if INCLUDE_eTaskGetState == 1
namespace urtos
{
enum ThreadState : unsigned char
{
    RUNNING = eRunning,
    READY = eReady,
    BLOCKED = Blocked,
    SUSPENDED = eSuspended,
    DELETED = eDeleted
};
}
#endif

#endif