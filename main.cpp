#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int pid, arrival, burst, priority;
    int start = -1, finish = -1;
    int waiting = 0, turnaround = 0;
};

struct Gantt {
    int pid, s, f;
};

// ------------ PRINT RESULTS (DAY-1 ) -------------
void print_results(const vector<Process> &procs, const vector<Gantt> &g) {

    cout << "\nGantt Chart:\n";
    for (auto &seg : g) {
        if (seg.pid == 0)
            cout << "[idle:" << seg.s << "->" << seg.f << "] ";
        else
            cout << "[P" << seg.pid << ":" << seg.s << "->" << seg.f << "] ";
    }

    cout << "\n\nFCFS Result Table:\n";
    cout << "PID  Arrival  Burst  Start  Finish  Waiting  Turnaround\n";

    for (auto &p : procs) {
        cout << p.pid << "     "
             << p.arrival << "        "
             << p.burst << "      "
             << p.start << "      "
             << p.finish << "       "
             << p.waiting << "         "
             << p.turnaround << "\n";
    }
}

// =================== FCFS IMPLEMENTATION =====================
void fcfs(vector<Process> p) {

    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    int time = 0;
    vector<Gantt> g;

    for (auto &x : p) {
        if (time < x.arrival) {
            g.push_back({0, time, x.arrival});
            time = x.arrival;
        }

        x.start = time;
        time += x.burst;
        x.finish = time;

        x.turnaround = x.finish - x.arrival;
        x.waiting = x.start - x.arrival;

        g.push_back({x.pid, x.start, x.finish});
    }

    print_results(p, g);
}

// ================= Main Function=================
int main() {
    int n;

    cout << "Number of Processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "PID Arrival Burst Priority\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].arrival >> p[i].burst >> p[i].priority;
    }

    cout << "\nRunning FCFS Scheduling...\n";
    fcfs(p);

    return 0;
}
