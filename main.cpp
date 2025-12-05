// Menu + Input Handling (Sahil - Commit 4)
#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int pr;   // used only in priority scheduling
};

// ------ Placeholder functions (will connect to final algorithms) -----
void runFCFS(const vector<Process>& p) {
    cout << "\n[FCFS Algorithm will run here]\n";
}

void runSJF_NP(const vector<Process>& p) {
    cout << "\n[SJF Non-Preemptive Algorithm will run here]\n";
}

void runSJF_P(const vector<Process>& p) {
    cout << "\n[SJF Preemptive Algorithm will run here]\n";
}

void runPriority_NP(const vector<Process>& p) {
    cout << "\n[Priority Non-Preemptive Algorithm will run here]\n";
}

void runPriority_P(const vector<Process>& p) {
    cout << "\n[Priority Preemptive Algorithm will run here]\n";
}

void runRR_NP(const vector<Process>& p, int tq) {
    cout << "\n[RR Non-Preemptive Algorithm will run here]\n";
}

void runRR_P(const vector<Process>& p, int tq) {
    cout << "\n[RR Preemptive Algorithm will run here]\n";
}

// -----------------------------------------------------------------------

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
            cout << "\nExiting...\n";
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

        switch (choice) {
            case 1: runFCFS(p); break;
            case 2: runSJF_NP(p); break;
            case 3: runSJF_P(p); break;
            case 4: runPriority_NP(p); break;
            case 5: runPriority_P(p); break;
            case 6: runRR_NP(p, tq); break;
            case 7: runRR_P(p, tq); break;
            default: cout << "\nInvalid Choice!\n"; break;
        }
    }

    return 0;
}
