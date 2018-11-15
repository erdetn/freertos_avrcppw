/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "ukernel.h"

using namespace urtos;

static void Kernel::run()
{
    vTaskStartScheduler();
}

static void Kernel::kill()
{
    vTaskEndScheduler();
}

static u_byte Kernel::numberOfThreads()
{
    return (u_byte)xTaskGetSchedulerState();
}