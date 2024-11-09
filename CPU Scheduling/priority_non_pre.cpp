#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;         // Process ID
    int burstTime;  // Burst time of the process
    int priority;   // Priority of the process (lower number = higher priority)
    int waitingTime;  // Waiting time of the process
    int turnaroundTime;  // Turnaround time of the process
};

// Comparison function to sort processes by priority (and ID if priority is the same)
bool compareByPriority(const Process &a, const Process &b) {
    if (a.priority == b.priority)
        return a.id < b.id;
    return a.priority < b.priority;
}

void calculateWaitingTime(vector<Process> &processes) {
    processes[0].waitingTime = 0;  // First process has 0 waiting time
    for (size_t i = 1; i < processes.size(); ++i) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void calculateTurnaroundTime(vector<Process> &processes) {
    for (size_t i = 0; i < processes.size(); ++i) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void printProcessInfo(const vector<Process> &processes) {
    cout << "Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes) {
        cout << process.id << "\t\t"
             << process.burstTime << "\t\t"
             << process.priority << "\t\t"
             << process.waitingTime << "\t\t"
             << process.turnaroundTime << "\n";
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input processes information
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process " << processes[i].id << " (lower number = higher priority): ";
        cin >> processes[i].priority;
    }

    sort(processes.begin(), processes.end(), compareByPriority);
    
    calculateWaitingTime(processes);
    calculateTurnaroundTime(processes);

    // Print process information
    printProcessInfo(processes);

    // Calculate average waiting time and turnaround time
    double avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (const auto &process : processes) {
        avgWaitingTime += process.waitingTime;
        avgTurnaroundTime += process.turnaroundTime;
    }

    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << "\n";
    cout << "Average Turnaround Time: " << avgTurnaroundTime << "\n";

    return 0;
}
