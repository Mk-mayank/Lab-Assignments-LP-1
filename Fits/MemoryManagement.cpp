#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function for First Fit allocation
void firstFit(vector<int>& blockSize, int numBlocks, vector<int>& processSize, int numProcesses) {
    vector<int> allocation(numProcesses, -1);  // Store allocation result (-1 means not allocated)

    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];  // Reduce available memory in the block
                break;
            }
        }
    }

    cout << "\nFirst Fit Allocation Result:\n";
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// Function for Next Fit allocation
void nextFit(vector<int>& blockSize, int numBlocks, vector<int>& processSize, int numProcesses) {
    vector<int> allocation(numProcesses, -1);
    int lastAllocatedBlock = 0;

    for (int i = 0; i < numProcesses; i++) {
        for (int j = lastAllocatedBlock; j < numBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastAllocatedBlock = j;
                break;
            }
        }
    }

    cout << "\nNext Fit Allocation Result:\n";
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// Function for Worst Fit allocation
void worstFit(vector<int>& blockSize, int numBlocks, vector<int>& processSize, int numProcesses) {
    vector<int> allocation(numProcesses, -1);

    for (int i = 0; i < numProcesses; i++) {
        int worstIndex = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex]) {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    cout << "\nWorst Fit Allocation Result:\n";
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// Function for Best Fit allocation
void bestFit(vector<int>& blockSize, int numBlocks, vector<int>& processSize, int numProcesses) {
    vector<int> allocation(numProcesses, -1);

    for (int i = 0; i < numProcesses; i++) {
        int bestIndex = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex]) {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blockSize[bestIndex] -= processSize[i];
        }
    }

    cout << "\nBest Fit Allocation Result:\n";
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
}
}

int main() {
    int numBlocks, numProcesses, choice;

    do {
        cout << "\nMemory Allocation Strategies Menu\n";
        cout << "1. First Fit\n";
        cout << "2. Next Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Best Fit\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 5) break;

        cout << "Enter number of memory blocks: ";
        cin >> numBlocks;
        vector<int> blockSize(numBlocks);

        cout << "Enter sizes of each block:\n";
        for (int i = 0; i < numBlocks; i++) {
            cout << "Block " << i + 1 << ": ";
            cin >> blockSize[i];
        }

        cout << "\nEnter number of processes: ";
        cin >> numProcesses;
        vector<int> processSize(numProcesses);

        cout << "Enter memory size required for each process:\n";
        for (int i = 0; i < numProcesses; i++) {
            cout << "Process " << i + 1 << ": ";
            cin >> processSize[i];
        }

        // Call the appropriate function based on user choice
        switch (choice) {
            case 1:
                firstFit(blockSize, numBlocks, processSize, numProcesses);
                break;
            case 2:
                nextFit(blockSize, numBlocks, processSize, numProcesses);
                break;
            case 3:
                worstFit(blockSize, numBlocks, processSize, numProcesses);
                break;
            case 4:
                bestFit(blockSize, numBlocks, processSize, numProcesses);
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }

    } while (choice != 5);

    cout << "Exiting the program...\n";
    return 0;
}
