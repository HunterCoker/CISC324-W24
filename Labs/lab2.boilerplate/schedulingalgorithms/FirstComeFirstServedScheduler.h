#ifndef FIRSTCOMEFIRSTSERVEDSCHEDULER_H
#define FIRSTCOMEFIRSTSERVEDSCHEDULER_H

#include <queue>
#include "Process.h"
#include "CPUScheduler.h"
using namespace std;

class FirstComeFirstServedScheduler : public CPUScheduler
{
public:
    FirstComeFirstServedScheduler(queue<Process> processes, int quantum)
        :m_processes(std::move(processes)), m_quantum(quantum) {}
    void schedule() override;
    void calculateAverageWaitTime() override;
    void calculateAverageTurnAroundTime() override;
private:
    queue<Process> m_processes;
    int m_quantum;
};

#endif
