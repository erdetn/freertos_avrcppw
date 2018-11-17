/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include "ukernel.h"

using namespace urtos;

void Kernel::run()
{
    vTaskStartScheduler();
}

void Kernel::kill()
{
    vTaskEndScheduler();
}

void Kernel::suspend()
{
	vTaskSuspendAll();
}

void Kernel::resume()
{
	xTaskResumeAll();
}

u_byte Kernel::numberOfThreads()
{
    return (u_byte)xTaskGetSchedulerState();
}
