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