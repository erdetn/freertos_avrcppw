#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <string.h>

#define LOOP     for(;;)

#define TaskDelay(X) vTaskDelay(X/portTICK_PERIOD_MS)

enum TaskPriority
{
    Zero = 0,
    Low = 1,
    Medium = 2,
    High = 3
};

class Task
{
private:
    TaskHandle_t  m_taskHandler;
    portCHAR     *m_taskName;
    TaskPriority  m_taskPriority;
    bool          m_isCreated;

    unsigned portSHORT m_stackDepth;

public:
    Task(const portCHAR *taskName, TaskPriority TaskPriority, unsigned portSHORT stackDepth);
    bool run(TaskFunction_t task, void *parametersToPass);
    void kill();
    void suspend();
    void resume();
    void resumeFromISR();

    void setPriority(TaskPriority taskPriority);
    unsigned char priority() const;

    unsigned portSHORT stackDepth() const;

    void sleep(unsigned int milliseconds);
};
