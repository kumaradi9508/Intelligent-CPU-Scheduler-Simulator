// Priority Scheduling Non-Preemptive (Aditya - Commit 4)
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

struct Process {
    int pid;
    int at;        // Arrival Time
    int bt;        // Burst Time
    int pr;        // Priority (lower number = higher priority)
    int ct;        // Completion
    int tat;       // Turnaround
    int wt;        // Waiting
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

    cout << "PID  AT  BT  Priority\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].pr;
    }

    int time = 0, completed = 0;
    vector<Gantt> gc;

    while (completed < n) {

        int idx = -1;
        int bestPriority = INT_MAX;

        // Pick process with highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].pr < bestPriority) {
                    bestPriority = p[i].pr;
                    idx = i;
                }
            }
        }

        // If nothing arrived ↦ IDLE
        if (idx == -1) {
            time++;
            continue;
        }

        int st = time;
        time += p[idx].bt;
        int ft = time;

        p[idx].ct = ft;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = true;
        completed++;

        gc.push_back({p[idx].pid, st, ft});
    }

    // ---------------- GANTT CHART ----------------
    cout << "\nGantt Chart:\n";
    for (auto &g : gc) {
        cout << "[P" << g.pid << " " << g.start << "-" << g.end << "] ";
    }
    cout << "\n";

    // ---------------- CLOSED TABLE ----------------
    cout << "\n+------------------------------------------------------+\n";
    cout << "| " << left << setw(6) << "PID"
         << setw(7) << "AT"
         << setw(7) << "BT"
         << setw(10) << "Priority"
         << setw(7) << "CT"
         << setw(8) << "TAT"
         << setw(7) << "WT" << " |\n";
    cout << "+------------------------------------------------------+\n";

    double avg_tat = 0, avg_wt = 0;

    for (auto &x : p) {
        cout << "| "
             << left << setw(6) << x.pid
             << setw(7) << x.at
             << setw(7) << x.bt
             << setw(10) << x.pr
             << setw(7) << x.ct
             << setw(8) << x.tat
             << setw(7) << x.wt
             << " |\n";

        avg_tat += x.tat;
        avg_wt  += x.wt;
    }

    avg_tat /= n;
    avg_wt  /= n;

    cout << "+------------------------------------------------------+\n";
    cout << "Average Turnaround Time : " << avg_tat << endl;
    cout << "Average Waiting Time    : " << avg_wt  << endl;

    return 0;
}
