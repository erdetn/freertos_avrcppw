#include "utimer.h"

using namespace urtos;

Timer::Timer()
{
    _period = 0;
    _autoReload = false;
    _callback = NULL;
}

Timer::Timer(TimerCallback callback, u_long period, bool autoReload)
{
    _callback = callback;
    _period = period;
    _autoReload = autoReload;

#if configSUPPORT_DYNAMIC_ALLOCATION == 1
    _timer = xTimerCreate((const char *const)NULL,
                          pdMS_TO_TICKS(_period),
                          _autoReload == true ? pdTRUE : pdFALSE,
                          (void *const)NULL,
                          _callback);
#else
    _timer = xTimerCreateStatic((const char *const)NULL,
                                pdMS_TO_TICKS(_period),
                                _autoReload == true ? pdTRUE : pdFALSE,
                                (void *const)NULL,
                                _callback,
                                &_timerBuffer);
#endif
}

Timer::Timer(const Timer &timer)
{
	_period = timer._period;
	_autoReload = timer._autoReload;
	_callback = timer._callback;
	_timer = timer._timer;
#if configSUPPORT_STATIC_ALLOCATION == 1
    _timerBuffer = timer._timerBuffer;
#endif
}

// functions
void Timer::start()
{
    xTimerStart(_timer, pdMS_TO_TICKS(0));
}

void Timer::start(u_long blockTime)
{
    xTimerStart(_timer, pdMS_TO_TICKS(blockTime));
}

void Timer::stop()
{
    xTimerStop(_timer, pdMS_TO_TICKS(0));
}

void Timer::stop(u_long blockTime)
{
    xTimerStop(_timer, pdMS_TO_TICKS(blockTime));
}

void Timer::reset()
{
    xTimerReset(_timer, pdMS_TO_TICKS(0));
}

void Timer::reset(u_long blockTime)
{
    xTimerReset(_timer, pdMS_TO_TICKS(blockTime));
}

void Timer::startFromInterrupt()
{
    xTimerStartFromISR(_timer, NULL);
}

void Timer::stopFromInterrupt()
{
    xTimerStopFromISR(_timer, NULL);
}

void Timer::resetFromInterrupt()
{
    xTimerResetFromISR(_timer, NULL);
}

bool Timer::isRunning() const
{
    return (xTimerIsTimerActive(_timer) == pdTRUE);
}

u_long Timer::period() const
{
    return _period;
}

bool Timer::isAutoReload() const
{
    return _autoReload;
}

void Timer::setPeriod(u_long period)
{
    bool _return;

    _return = (xTimerChangePeriod(_timer, period, pdMS_TO_TICKS(0)) == pdTRUE);
    if (_return)
        _period = period;
}

u_ticks Timer::expiredTime() const
{
    return xTimerGetExpiryTime(_timer);
}