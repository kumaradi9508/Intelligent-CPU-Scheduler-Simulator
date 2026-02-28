// Round Robin Non-Preemptive Scheduling Algorithm(Sahil - Commit 2)
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int at;        // arrival time
    int bt;        // burst time
    int ct;        // completion time
    int tat;       // turnaround time
    int wt;        // waiting time
    int rem;       // remaining burst time
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

    int tq;
    cout << "Enter Time Quantum: ";
    cin >> tq;

    // Sort by arrival time
    sort(p.begin(), p.end(), [](auto &a, auto &b){
        return a.at < b.at;
    });

    queue<int> q;
    int time = 0;
    int completed = 0;
    int idx = 0;

    vector<Gantt> gc;

    // add first arrived processes
    while (idx < n && p[idx].at <= time) {
        q.push(idx);
        idx++;
    }

    while (completed < n) {

        if (q.empty()) {
            time++;
            while (idx < n && p[idx].at <= time) {
                q.push(idx);
                idx++;
            }
            continue;
        }

        int id = q.front();
        q.pop();

        int st = time;
        int run = min(tq, p[id].rem);

        time += run;
        p[id].rem -= run;

        gc.push_back({p[id].pid, st, time});

        // Insert new arrivals
        while (idx < n && p[idx].at <= time) {
            q.push(idx);
            idx++;
        }

        if (p[id].rem == 0) {
            p[id].ct = time;
            p[id].tat = p[id].ct - p[id].at;
            p[id].wt  = p[id].tat - p[id].bt;
            completed++;
        } else {
            q.push(id);
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
