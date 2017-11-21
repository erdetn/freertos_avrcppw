#include <Arduino_FreeRTOS.h>
#include <queue.h>

#if (configSUPPORT_DYNAMIC_ALLOCATION == 0)
    #error "Dynamic allocation is not configured."
#else

#ifndef QUEUE_WH
#define QUEUE_WH

class Queue
{
private:        
    QueueHandle_t m_hQueue;
    TickType_t    m_waitToSend;
    TickType_t    m_waitToReceive;
    UBaseType_t   m_length;
    UBaseType_t   m_unitSize;

public:
    Queue(UBaseType_t length, UBaseType_t unitSize);
    Queue(UBaseType_t length, UBaseType_t unitSize, TickType_t defaultSendReceiveTime);
    Queue(UBaseType_t length, UBaseType_t unitSize, TickType_t waitToSend, TickType_t waitToReceive);


    bool send(const void *data);
    bool send(const void *data, TickType_t waitToSend);

    bool receive(void *data);
    bool receive(void *data, TickType_t waitToReceive);

    bool copy(void *data);
    bool copy(void *data, TickType_t waitToCopy);

    TickType_t waitingToSendTime() const;
    TickType_t waitingToReceiveTime() const;

    UBaseType_t length() const;
    UBaseType_t unitSize() const;
};

#endif
#endif
