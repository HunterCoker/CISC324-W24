#ifndef PROCESS_H
#define PROCESS_H

struct Process
{
    int id;        // Process ID
    int burstTime; // CPU Burst Time
    int arrivalTime;
    int waitTime;
    int remainingTime;

    Process(int id, int burstTime)
        : id(id), burstTime(burstTime), arrivalTime(0), waitTime(0), remainingTime(burstTime) { }
    Process(int id, int burstTime, int arrivalTime)
        : id(id), burstTime(burstTime), arrivalTime(arrivalTime), waitTime(0), remainingTime(burstTime) { }
};

#endif // PROCESS_H
