#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;           // Process ID
    int burstTime;     // Burst Time
    int arrivalTime;   // Arrival Time
    
    Process(int id, int bt, int at) : pid(id), burstTime(bt), arrivalTime(at) {}
};

bool compareArrival(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

void FCFS(vector<Process> &processes) {
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    int n = processes.size();
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int currentTime = 0;

    cout << "PID\tArrival\tBurst\tStart\tFinish\tWait\tTurnaround" << endl;

    for (Process &p : processes) {
        // Calculate Start Time: max(currentTime, arrivalTime)
        int startTime = max(currentTime, p.arrivalTime);
        
        // Calculate Finish Time: startTime + burstTime
        int finishTime = startTime + p.burstTime;
        
        // Calculate Wait Time: startTime - arrivalTime
        int waitTime = startTime - p.arrivalTime;
        
        // Calculate Turnaround Time: finishTime - arrivalTime
        int turnaroundTime = finishTime - p.arrivalTime;

        // Update total wait and turnaround times
        totalWaitTime += waitTime;
        totalTurnaroundTime += turnaroundTime;
        
        // Update current time to the finish time of this process
        currentTime = finishTime;

        cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t" 
             << startTime << "\t" << finishTime << "\t" << waitTime << "\t" << turnaroundTime << endl;
    }
    
    // Calculate and display average wait and turnaround times
    cout << "Average wait time: " << (double)totalWaitTime / n << endl;
    cout << "Average turnaround time: " << (double)totalTurnaroundTime / n << endl;
}

int main() {
    vector<Process> processes = {{1, 6, 0}, {2, 8, 1}, {3, 7, 2}, {4, 3, 3}};
    FCFS(processes);
    return 0;
}
