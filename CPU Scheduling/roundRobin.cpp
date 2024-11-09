#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void roundRobinScheduling(vector<Process>& processes, int timeQuantum) {
    queue<int> processQueue;  // Queue to hold process IDs in RR order
    int currentTime = 0;      // Tracks the current time in scheduling
    
    // Initialize the queue with process IDs and set initial waiting/turnaround times
    for (int i = 0; i < processes.size(); ++i) {
        processQueue.push(i);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }
    
    // Run until the queue is empty
    while (!processQueue.empty()) {
        int i = processQueue.front();
        processQueue.pop();
        
        // Calculate time to process this task in current round
        int timeSpent = min(processes[i].remainingTime, timeQuantum);
        currentTime += timeSpent;
        processes[i].remainingTime -= timeSpent;

        // If process still has remaining time, put it back in the queue
        if (processes[i].remainingTime > 0) {
            processQueue.push(i);
        } else {
            // Process completed, calculate turnaround and waiting times
            processes[i].turnaroundTime = currentTime;
            processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        }
    }
    
    // Calculate average waiting and turnaround times
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (const auto& p : processes) {
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }
    double avgWaitingTime = (double)totalWaitingTime / processes.size();
    double avgTurnaroundTime = (double)totalTurnaroundTime / processes.size();
    
    // Display results
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& p : processes) {
        cout << "P" << p.id << "\t" << p.burstTime << "\t\t"
             << p.waitingTime << "\t\t" << p.turnaroundTime << "\n";
    }
    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

int main() {
    int n, timeQuantum;
    
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;
    
    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter burst time for process P" << processes[i].id << ": ";
        cin >> processes[i].burstTime;
    }
    
    roundRobinScheduling(processes, timeQuantum);
    
    return 0;
}
