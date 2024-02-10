#include "RoundRobinScheduler.h"

#include <algorithm>
#include <iostream>

void RoundRobinScheduler::schedule()
{
    std::vector<Process> processes(&m_processes.front(), &m_processes.front() + m_processes.size());
    std::sort(processes.begin(), processes.end(),
        [](const Process &p1, const Process &p2) {
            if (p1.arrivalTime < p2.arrivalTime) return true;
            else if (p1.arrivalTime > p2.arrivalTime) return false;
            return p1.id < p2.id;
        });

    int idx= 0;
    std::queue<Process> queue;

    int timeOfExecution, timeExecuted;
    while (idx != m_processes.size()) {
        timeOfExecution = processes[idx].arrivalTime;
        queue.push(processes[idx++]);

        while (!queue.empty()) {
            auto &process = queue.front();

            if (process.remainingTime <= m_quantum) {
                while (idx < m_processes.size()
                        && processes[idx].arrivalTime <= timeOfExecution + process.remainingTime)
                    queue.push(processes[idx++]);

                timeExecuted = process.burstTime - process.remainingTime;
                auto *m_process = &m_processes.front() + process.id - 1;
                m_process->waitTime = timeOfExecution - process.arrivalTime - timeExecuted;
                m_process->remainingTime = 0;
                timeOfExecution += process.remainingTime;
            } else {
                while (idx < m_processes.size()
                       && processes[idx].arrivalTime <= timeOfExecution + m_quantum)
                    queue.push(processes[idx++]);

                process.remainingTime -= m_quantum;
                queue.push(process);
                timeOfExecution += m_quantum;
            }

            queue.pop();
        }
    }
}

void RoundRobinScheduler::calculateAverageWaitTime()
{
    int totalWaitTime = 0;
    for (int i = 0; i < m_processes.size(); ++i) {
        auto &process = *(&m_processes.front() + i);
        totalWaitTime += process.waitTime;
    }
    std::cout << "Average Wait Time:\t  " << static_cast<float>(totalWaitTime)
        / m_processes.size() << std::endl;
}

void RoundRobinScheduler::calculateAverageTurnAroundTime()
{
    int totalTurnaroundTime = 0;
    for (int i = 0; i < m_processes.size(); ++i) {
        auto &process = *(&m_processes.front() + i);
        totalTurnaroundTime += process.waitTime + process.burstTime;
    }
    std::cout << "Average Turnaround Time:  " << static_cast<float>(totalTurnaroundTime)
        / m_processes.size() << std::endl;
}
