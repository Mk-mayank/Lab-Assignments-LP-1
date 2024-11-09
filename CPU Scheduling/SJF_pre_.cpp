#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
struct Process {
    int pid;            // Process ID
    int burstTime;      // Total time required to complete the process
    int arrivalTime;    // Time at which process arrives in the system
    int remainingTime;  // Time left for the process to complete

    Process(int id, int bt, int at) : pid(id), burstTime(bt), arrivalTime(at), remainingTime(bt) {}
};

bool compareArrival(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

// Function to perform Shortest Remaining Time First (SRTF) scheduling
void SRTF(vector<Process> &processes) {
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    int n = processes.size();      // Number of processes
    int currentTime = 0;           // Current time of the CPU
    int completed = 0;             // Count of completed processes
    int totalWaitTime = 0;         // Total wait time for all processes
    int totalTurnaroundTime = 0;   // Total turnaround time for all processes
    vector<bool> isCompleted(n, false);  // Tracks whether each process is completed

    // Loop until all processes are completed
    while (completed != n) {
        int idx = -1;              // Index of the selected process to execute
        int minRemainingTime = INT_MAX; // Minimum remaining time of processes that have arrived

        // Find the process with the shortest remaining time among those that have arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && // Process has arrived
                !isCompleted[i] &&                         // Process is not completed
                processes[i].remainingTime < minRemainingTime) { // Process has the shortest remaining time
                minRemainingTime = processes[i].remainingTime;
                idx = i; // Select this process
            }
        }

        // Check if a process was found
        if (idx != -1) {
            // Execute the selected process for one time unit
            processes[idx].remainingTime--;
            currentTime++;

            // If the process is completed
            if (processes[idx].remainingTime == 0) {
                completed++;                // Increment count of completed processes
                isCompleted[idx] = true;    // Mark process as completed
                int finishTime = currentTime; // Time at which process finished
                int turnaround = finishTime - processes[idx].arrivalTime; // Calculate turnaround time
                int wait = turnaround - processes[idx].burstTime; // Calculate wait time

                totalWaitTime += wait;       // Add to total wait time
                totalTurnaroundTime += turnaround; // Add to total turnaround time

                // Output the results for this process
                cout << "PID: " << processes[idx].pid
                     << ", Arrival: " << processes[idx].arrivalTime 
                     << ", Burst: " << processes[idx].burstTime 
                     << ", Finish: " << finishTime 
                     << ", Wait: " << wait 
                     << ", Turnaround: " << turnaround << endl;
            }
        }
        else {
            // No process available to run; increment currentTime to move forward
            currentTime++;
        }
    }
    
    // Calculate and display average wait and turnaround times
    cout << "Average wait time: " << (double)totalWaitTime / n << endl;
    cout << "Average turnaround time: " << (double)totalTurnaroundTime / n << endl;
}

int main() {
    // List of processes with PID, burst time, and arrival time
    vector<Process> processes = {{1, 6, 0}, {2, 8, 1}, {3, 7, 2}, {4, 3, 3}};
    
    // Execute SRTF scheduling
    SRTF(processes);
    return 0; 
}
