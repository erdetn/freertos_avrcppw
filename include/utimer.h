/* Copyright (c) Erdet Nasufi, 2018 */

#ifndef UTIMER_H
#define UTIMER_H

#include <Arduino_FreeRTOS.h>

#include <timers.h>
#include <string.h>

#include "urtos.h"

#if !(configUSE_TIMERS == 1)
#warning "Timer use is not configured"
#else
namespace urtos
{

typedef TimerCallbackFunction_t TimerCallback;
typedef TimerHandle_t TimerHandler;

class Timer
{
private:
    u_long _period;
    bool _autoReload;
    TimerCallbackFunction_t _callback;
    TimerHandle_t _timer;
#if configSUPPORT_STATIC_ALLOCATION == 1
    StaticTimer_t _timerBuffer;
#endif

public:
    Timer();
    Timer(TimerCallback callback, u_long period, bool autoReload);
    Timer(const Timer &timer);
	~Timer();

    // functions
    void start();
    void start(u_long blockTime);
    void stop();
    void stop(u_long blockTime);
    void reset();
    void reset(u_long blockTime);

    void startFromInterrupt();
    void stopFromInterrupt();
    void resetFromInterrupt();

    bool isRunning() const;

    //  get properties
    u_long period() const;
    bool isAutoReload() const;

    // set properties
    void setPeriod(u_long period);

    u_ticks expiredTime() const;
};

} // namespace urtos
#endif
#endif