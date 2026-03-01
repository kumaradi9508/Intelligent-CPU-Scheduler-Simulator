// SJF Preemptive (SRTF) - Aditya Commit 3
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int at;    // arrival time
    int bt;    // burst time
    int rem;   // remaining time
    int ct;    // completion
    int tat;   // turnaround
    int wt;    // waiting
    bool done = false;
};

struct Gantt {
    int pid;
    int start;
    int end;
};

int main() {

    int n;
    cout << "Number of Processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "PID  AT  BT\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        p[i].rem = p[i].bt;
    }

    int time = 0, completed = 0, prev = -1;
    vector<Gantt> gc;

    while (completed < n) {

        int idx = -1;
        int mn = INT_MAX;

        // find shortest remaining burst among arrived processes
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].rem < mn) {
                    mn = p[i].rem;
                    idx = i;
                }
            }
        }

        // IDLE
        if (idx == -1) {
            time++;
            continue;
        }

        // Start new Gantt segment if process changed
        if (prev != p[idx].pid) {
            gc.push_back({p[idx].pid, time, -1}); 
        }

        // Execute for 1 unit
        time++;
        p[idx].rem--;

        // Update end time of last segment
        gc.back().end = time;
        prev = p[idx].pid;

        // If finished
        if (p[idx].rem == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt  = p[idx].tat - p[idx].bt;
            p[idx].done = true;
            completed++;
        }
    }

    // ---------------- GANTT CHART ----------------
    cout << "\nGantt Chart:\n";
    for (auto &g : gc) {
        cout << "[P" << g.pid << " " << g.start << "-" << g.end << "] ";
    }
    cout << "\n";

    // ---------------- CLOSED BORDER TABLE ----------------
    cout << "\n+---------------------------------------------+\n";
    cout << "| " << left << setw(6) << "PID"
         << setw(7) << "AT"
         << setw(7) << "BT"
         << setw(7) << "CT"
         << setw(8) << "TAT"
         << setw(7) << "WT" << " |\n";
    cout << "+---------------------------------------------+\n";

    double avg_tat = 0, avg_wt = 0;

    for (auto &x : p) {
        cout << "| "
             << left << setw(6) << x.pid
             << setw(7) << x.at
             << setw(7) << x.bt
             << setw(7) << x.ct
             << setw(8) << x.tat
             << setw(7) << x.wt
             << " |\n";

        avg_tat += x.tat;
        avg_wt  += x.wt;
    }

    avg_tat /= n;
    avg_wt  /= n;

    cout << "+---------------------------------------------+\n";
    cout << "Average Turnaround Time : " << avg_tat << endl;
    cout << "Average Waiting Time    : " << avg_wt  << endl;

    return 0;
}
