
#include <Arduino_FreeRTOS.h>

#ifndef URTOS_H
#define URTOS_H

#define DEFAULT_TICKS_TO_WAIT (500 / portTICK_PERIOD_MS) //500 [ms]
#define TICK_PERIOD_MS portTICK_PERIOD_MS
#define infinite for (;;)
#define TaskDelay(X) vTaskDelay(X / portTICK_PERIOD_MS)

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

#endif