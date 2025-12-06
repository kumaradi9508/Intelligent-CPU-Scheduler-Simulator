// Priority Preemptive Scheduling (Aditya - Commit 5)
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

struct Process {
    int pid;
    int at;     // arrival
    int bt;     // burst
    int rem;    // remaining
    int pr;     // priority (lower = higher priority)
    int ct;     // completion
    int tat;    // turnaround
    int wt;     // waiting
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
    cout << "PID AT BT Priority\n";

    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].pr;
        p[i].rem = p[i].bt;
    }

    int time = 0, completed = 0, prevPID = -1;
    vector<Gantt> gc;

    while (completed < n) {

        int idx = -1;
        int bestPr = INT_MAX;

        // Find highest priority arrived process
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].pr < bestPr) {
                    bestPr = p[i].pr;
                    idx = i;
                }
            }
        }

        // CPU Idle
        if (idx == -1) {
            time++;
            continue;
        }

        // Start new Gantt segment when process switches
        if (prevPID != p[idx].pid) {
            gc.push_back({p[idx].pid, time, -1});
        }

        p[idx].rem--;
        time++;

        gc.back().end = time;
        prevPID = p[idx].pid;

        // Process finished
        if (p[idx].rem == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = true;
            completed++;
        }
    }

    // ------------ Gantt Chart ------------
    cout << "\nGantt Chart:\n";
    for (auto &g : gc) {
        cout << "[P" << g.pid << " " << g.start << "-" << g.end << "] ";
    }
    cout << "\n";

    // ------------ Closed Table ------------
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
        cout << "| " << left << setw(6) << x.pid
             << setw(7) << x.at
             << setw(7) << x.bt
             << setw(10) << x.pr
             << setw(7) << x.ct
             << setw(8) << x.tat
             << setw(7) << x.wt << " |\n";

        avg_tat += x.tat;
        avg_wt += x.wt;
    }

    cout << "+-------------------------------------------------------+\n";
    cout << "Average Turnaround Time : " << avg_tat / n << endl;
    cout << "Average Waiting Time    : " << avg_wt / n << endl;

    return 0;
}
