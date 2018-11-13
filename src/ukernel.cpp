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

static byte Kernel::numberOfThread()
{
    return (byte)xTaskGetSchedulerState();
}