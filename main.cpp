// FCFS Scheduling Algorithm (Aditya - Commit 1)

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int at;     // arrival time
    int bt;     // burst time
    int ct;     // completion time
    int tat;    // turnaround time
    int wt;     // waiting time
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

    cout << "PID AT BT\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }

    // sort by arrival time (FCFS rule)
    sort(p.begin(), p.end(), [](auto &a, auto &b){
        return a.at < b.at;
    });

    int time = 0;
    vector<Gantt> gc;

    for (auto &x : p) {

        // CPU idle → wait until process arrives
        if (time < x.at) {
            gc.push_back({0, time, x.at}); // idle
            time = x.at;
        }

        int st = time;
        time += x.bt;
        int ft = time;

        x.ct  = ft;
        x.tat = x.ct - x.at;
        x.wt  = x.tat - x.bt;

        gc.push_back({x.pid, st, ft});
    }

    // ---------------- GANTT CHART ----------------
    cout << "\nGantt Chart:\n";
    for (auto &g : gc) {
        if (g.pid == 0)
            cout << "[idle " << g.start << "-" << g.end << "] ";
        else
            cout << "[P" << g.pid << " " << g.start << "-" << g.end << "] ";
    }
    cout << "\n";

    // ---------------- CLOSED BORDER TABLE ----------------
    cout << "\n+--------------------------------------------+\n";
    cout << "| " << left << setw(6) << "PID"
         << setw(7) << "AT"
         << setw(7) << "BT"
         << setw(7) << "CT"
         << setw(8) << "TAT"
         << setw(7) << "WT" << " |\n";
    cout << "+--------------------------------------------+\n";

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

    cout << "+--------------------------------------------+\n";
    
    cout << "Average Turnaround Time : " << avg_tat / n << endl;
    cout << "Average Waiting Time    : " << avg_wt  / n << endl;

    return 0;
}
