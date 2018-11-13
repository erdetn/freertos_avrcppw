/*
 * Author: Erdet Nasufi <erdet.nasufi@gmail.com>
 */

#include <Arduino_FreeRTOS.h>
#include <task.h>

#include "urtos.h"

#ifndef UKERNEL_H
#define UKERNEL_H

namespace urtos
{
class Kernel
{
public:
	static void run();
	static void kill();
};
} // namespace urtos
#endif