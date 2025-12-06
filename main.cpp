// Menu + Algorithm Integration (Sahil - Commit 5)
// It connects the menu system to the actual scheduling algorithms.

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int pr;   // priority
};

// ---------------- External Algorithm Functions ----------------
// These will be filled from Aditya's and Sahil's algorithm branches.

void fcfs_run(const vector<Process>& p);
void sjf_np_run(const vector<Process>& p);
void sjf_preemptive_run(const vector<Process>& p);
void priority_np_run(const vector<Process>& p);
void priority_preemptive_run(const vector<Process>& p);
void rr_np_run(const vector<Process>& p, int tq);
void rr_preemptive_run(const vector<Process>& p, int tq);

// ----------------------------------------------------------------

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    int choice;

    while (true) {
        cout << "\n================ Scheduling Menu ================\n";
        cout << "1. FCFS\n";
        cout << "2. SJF Non-Preemptive\n";
        cout << "3. SJF Preemptive (SRTF)\n";
        cout << "4. Priority Non-Preemptive\n";
        cout << "5. Priority Preemptive\n";
        cout << "6. Round Robin Non-Preemptive\n";
        cout << "7. Round Robin Preemptive\n";
        cout << "0. Exit\n";
        cout << "-------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "\nExiting Scheduling Simulator...\n";
            break;
        }

        int n;
        cout << "\nEnter number of processes: ";
        cin >> n;

        vector<Process> p(n);
        cout << "Enter PID, Arrival Time, Burst Time, Priority(if needed):\n";

        for (int i = 0; i < n; i++) {
            cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].pr;
        }

        int tq = 0;
        if (choice == 6 || choice == 7) {
            cout << "Enter Time Quantum: ";
            cin >> tq;
        }

        cout << "\n-------------------- RESULT --------------------\n";

        switch (choice) {
            case 1: fcfs_run(p); break;
            case 2: sjf_np_run(p); break;
            case 3: sjf_preemptive_run(p); break;
            case 4: priority_np_run(p); break;
            case 5: priority_preemptive_run(p); break;
            case 6: rr_np_run(p, tq); break;
            case 7: rr_preemptive_run(p, tq); break;
            default: cout << "\nInvalid Choice!\n"; break;
        }

        pauseScreen();
    }

    return 0;
}
