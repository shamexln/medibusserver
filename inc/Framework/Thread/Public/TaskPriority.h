#pragma once

namespace DFL
{
namespace Thread
{
/**
 * @brief Provides an enumeration of task priorities based on task response time requirements.
 *
 * For fast periodical tasks, the rate can correspond to the period.
 * For episodic respective event driven tasks, the rate should correspond to the response time.
 *
 * @warning But for every task holds, that the chosen rate should never be exceeded.
 */
class TaskPriority
{
public:
    /**
     * @brief Type of rate to priority values.
     */
    typedef enum
    {
        Rate500us = 0,

        Rate1ms = 1,
        Rate2ms = 2,
        Rate5ms = 5,

        Rate10ms = 10,
        Rate20ms = 20,
        Rate50ms = 50,

        Rate100ms = 100,
        Rate200ms = 110,
        Rate500ms = 120,

        Rate1s = 130,
        Rate2s = 135,
        Rate5s = 140,

        Rate10s = 150,
        Rate20s = 155,
        Rate50s = 160,

        Rate1min = 170,
        Rate2min = 175,
        Rate5min = 180,

        RateNoTimeout = 254,
    } Enum;

private:
    TaskPriority();
    ~TaskPriority();
};
}
}
