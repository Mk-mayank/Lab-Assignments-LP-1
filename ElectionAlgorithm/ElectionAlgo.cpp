#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

// Candidate class to represent each candidate in the election
class Candidate {
public:
    int id;  // ID of the candidate
    bool act;  // Whether the candidate is active or failed

    Candidate() : id(0), act(true) {}

    // Function to add a new candidate's ID
    void addCandidate() {
        cout << "Enter the ID of new Candidate: ";
        cin >> id;
    }
};

// Election class to manage the election process
class Election {
public:
    vector<Candidate> v;  // Vector to store the candidates
    int currindex;  // Index of the current coordinator

    // Function to get a new candidate
    void getCandidate() {
        Candidate c;
        c.addCandidate();  // Call the addCandidate method to set the candidate's ID
        v.push_back(c);  // Add the candidate to the vector
    }

    // Function to simulate the failure of the current coordinator
    void addFailure() {
        int max = 0;
        // Find the current coordinator (the one with the highest ID)
        for (int i = 0; i < v.size(); i++) {
            if (v[i].id > max && v[i].act) {
                max = v[i].id;
                currindex = i;
            }
        }
        // Announce the current coordinator
        cout << "Current Coordinator is " << v[currindex].id << endl;
        sleep(2);
        cout << "Current Coordinator Failed" << endl;
        cout << "Detected by: " << v[(currindex - 1 + v.size()) % v.size()].id << endl;
        v[currindex].act = false;  // Mark the current coordinator as inactive
        sleep(2);
        cout << "Election Initialized" << endl;
    }

    // Ring Election Algorithm
    void RingElection() {
        int old = currindex;  // Store the current coordinator's index
        int new1 = (old - 1 + v.size()) % v.size();  // Move to the previous node (candidate)
        int cnt = 0;

        while (new1 != old) {
            int next = (new1 + 1) % v.size();  // Wrap around if needed (ring structure)
            if (v[next].act) {
                sleep(2);
                cout << "Message passed from " << v[new1].id << " to " << v[next].id << endl;
            }
            new1 = next;
        }

        // After the loop, find the new coordinator (the one with the highest ID)
        int max = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v[i].id > max && v[i].act) {
                max = v[i].id;
                currindex = i;
            }
        }
        cout << "New Coordinator is " << v[currindex].id << endl;
    }

    // Bully Election Algorithm
    void bullyElection() {
        int max = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v[i].id > max && v[i].act) {
                max = v[i].id;
                currindex = i;
            }
        }
        cout << "Current Coordinator is " << v[currindex].id << endl;
        sleep(1);
        cout << "Current Coordinator Failed" << endl;

        int new1 = (currindex - 1 + v.size()) % v.size();
        cout << "Detected by " << v[new1].id << endl;
        v[currindex].act = false;

        sleep(2);
        cout << "Election Initialized" << endl;

        bool foundCoordinator = false;
        for (int i = new1; i != currindex; i = (i + 1) % v.size()) {
            if (v[i].act && v[i].id > v[currindex].id) {
                cout << "Message passed from " << v[new1].id << " to " << v[i].id << endl;
                currindex = i;
                foundCoordinator = true;
                break;
            }
        }

        if (!foundCoordinator) {
            cout << "Coordinator is " << v[currindex].id << endl;
        }
    }
};

// Main function to interact with the user and run the election
int main() {
    Election e;  // Create an Election object
    bool loop = true;

    while (loop) {
        int n;
        cout << "Enter the number of candidates: ";
        cin >> n;

        // Add candidates
        for (int i = 0; i < n; i++) {
            e.getCandidate();  // Add each candidate to the election process
        }

        cout << "Choose an election algorithm: \n";
        cout << "1. Ring Algorithm\n2. Bully Algorithm\n3. Exit\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                e.addFailure();  // Simulate coordinator failure
                e.RingElection();  // Run Ring Election Algorithm
                break;
            case 2:
                e.addFailure();  // Simulate coordinator failure
                e.bullyElection();  // Run Bully Election Algorithm
                break;
            case 3:
                loop = false;  // Exit the loop if the user chooses 3
                break;
            default:
                cout << "Invalid choice! Please select again.\n";
        }
    }
    return 0;
}
