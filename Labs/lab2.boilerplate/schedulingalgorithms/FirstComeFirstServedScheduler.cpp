#include "FirstComeFirstServedScheduler.h"

#include <algorithm>
#include <iostream>

void FirstComeFirstServedScheduler::schedule()
{
    // create new queue object of processes sorted by arrival time
    auto processes = m_processes;
    std::sort(&processes.front(), &processes.front() + processes.size(),
        [](const Process &p1, const Process &p2) {
            if (p1.arrivalTime < p2.arrivalTime) return true;
            else if (p1.arrivalTime > p2.arrivalTime) return false;
            return p1.id < p2.id;
        });

    // run the scheduling algorithm
    int timeOfExecution = 0;
    while (!processes.empty()) {
        auto &process = processes.front();

        /* change time Of execution in the case that there is a gap
            between process ending and starting execution times */
        if (timeOfExecution < process.arrivalTime)
            timeOfExecution = process.arrivalTime;

        // change the data in the member process queue
        auto *m_process = &m_processes.front() + process.id - 1;
        m_process->waitTime += timeOfExecution - process.arrivalTime;
        m_process->remainingTime = 0;

        timeOfExecution += process.burstTime;
        processes.pop();
    }
}

void FirstComeFirstServedScheduler::calculateAverageWaitTime()
{
    int totalWaitTime = 0;
    for (int i = 0; i < m_processes.size(); ++i) {
        auto &process = *(&m_processes.front() + i);
        totalWaitTime += process.waitTime;
    }
    std::cout << "Average Wait Time:\t  " << static_cast<float>(totalWaitTime)
        / m_processes.size() << std::endl;
}

void FirstComeFirstServedScheduler::calculateAverageTurnAroundTime()
{
    int totalTurnaroundTime = 0;
    for (int i = 0; i < m_processes.size(); ++i) {
        auto &process = *(&m_processes.front() + i);
        totalTurnaroundTime += process.waitTime + process.burstTime;
    }
    std::cout << "Average Turnaround Time:  " << static_cast<float>(totalTurnaroundTime)
        / m_processes.size() << std::endl;
}

