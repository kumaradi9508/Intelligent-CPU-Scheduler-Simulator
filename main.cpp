// SJF Non-Preemptive (Aditya - Commit 2)
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int at;       // arrival time
    int bt;       // burst time
    int ct;       // completion time
    int tat;      // turnaround time
    int wt;       // waiting time
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
    }

    int time = 0, completed = 0;
    vector<Gantt> gc;

    // SJF Non-preemptive logic
    while (completed < n) {

        int idx = -1;
        int mn = INT_MAX;

        // choose the process with smallest BT among arrived ones
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].bt < mn) {
                    mn = p[i].bt;
                    idx = i;
                }
            }
        }

        // CPU idle
        if (idx == -1) {
            time++;
            continue;
        }

        int start_time = time;
        time += p[idx].bt;
        int end_time = time;

        p[idx].ct = end_time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
        p[idx].done = true;
        completed++;

        gc.push_back({p[idx].pid, start_time, end_time});
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
