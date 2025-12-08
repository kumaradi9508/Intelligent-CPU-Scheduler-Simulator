#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int pr;
    int ct;
    int tat;
    int wt;
    int rem;
};

void printGantt(const vector<pair<int, pair<int,int>>> &g) {
    cout << "\nGantt Chart:\n";
    for (auto &x : g) {
        cout << "[P" << x.first << " " << x.second.first << "-" << x.second.second << "] ";
    }
    cout << "\n\n";
}

void printTable(const vector<Process> &p) {
    cout << "+---------------------------------------------------------+\n";
    cout << "| PID | AT  | BT  | PR |  CT  |  TAT  |  WT  |\n";
    cout << "+---------------------------------------------------------+\n";

    double totalWT = 0, totalTAT = 0;
    for (auto &x : p) {
        cout << "| " << setw(3) << x.pid << " | "
             << setw(3) << x.at << " | "
             << setw(3) << x.bt << " | "
             << setw(2) << x.pr << " | "
             << setw(4) << x.ct << " | "
             << setw(5) << x.tat << " | "
             << setw(4) << x.wt << " |\n";

        totalWT += x.wt;
        totalTAT += x.tat;
    }

    cout << "+---------------------------------------------------------+\n";
    cout << "Average Turnaround Time: " << totalTAT / p.size() << endl;
    cout << "Average Waiting Time: " << totalWT / p.size() << endl << endl;
}

void fcfs(vector<Process> p) {
    sort(p.begin(), p.end(), [](auto &a, auto &b){
        return a.at < b.at;
    });

    vector<pair<int,pair<int,int>>> g;
    int time = 0;

    for (auto &x : p) {
        if (time < x.at) time = x.at;
        int start = time;
        time += x.bt;
        int end = time;

        x.ct = end;
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;

        g.push_back({x.pid, {start, end}});
    }

    printGantt(g);
    printTable(p);
}

void sjf_np(vector<Process> p) {
    int n = p.size();
    vector<pair<int,pair<int,int>>> g;
    vector<int> done(n, 0);
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, minBT = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        int start = time;
        time += p[idx].bt;
        int end = time;

        p[idx].ct = end;
        p[idx].tat = end - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;

        g.push_back({p[idx].pid, {start, end}});
    }

    printGantt(g);
    printTable(p);
}

void srtf(vector<Process> p) {
    int n = p.size();
    for (auto &x : p) x.rem = x.bt;

    vector<pair<int,pair<int,int>>> g;
    int time = 0, completed = 0, prev = -1;

    while (completed < n) {
        int idx = -1, minR = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rem > 0 && p[i].rem < minR) {
                minR = p[i].rem;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (prev != p[idx].pid) 
            g.push_back({p[idx].pid, {time, time+1}});
        else 
            g.back().second.second = time+1;

        p[idx].rem--;
        time++;
        prev = p[idx].pid;

        if (p[idx].rem == 0) {
            p[idx].ct = time;
            p[idx].tat = time - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }

    printGantt(g);
    printTable(p);
}


void priority_np(vector<Process> p) {
    int n = p.size();
    vector<pair<int,pair<int,int>>> g;
    vector<int> done(n, 0);
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, best = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].pr < best) {
                best = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) { time++; continue; }

        int start = time;
        time += p[idx].bt;
        int end = time;

        p[idx].ct = end;
        p[idx].tat = end - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;

        g.push_back({p[idx].pid, {start, end}});
    }

    printGantt(g);
    printTable(p);
}


void priority_p(vector<Process> p) {
    int n = p.size();
    for (auto &x : p) x.rem = x.bt;

    vector<pair<int,pair<int,int>>> g;
    int time = 0, completed = 0, prev = -1;

    while (completed < n) {
        int idx = -1, best = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rem > 0 && p[i].pr < best) {
                best = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (prev != p[idx].pid)
            g.push_back({p[idx].pid, {time, time+1}});
        else
            g.back().second.second = time+1;

        p[idx].rem--;
        time++;
        prev = p[idx].pid;

        if (p[idx].rem == 0) {
            p[idx].ct = time;
            p[idx].tat = time - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }

    printGantt(g);
    printTable(p);
}


void rr(vector<Process> p, int qt) {
    sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.at < b.at; });

    int n = p.size();
    for (auto &x : p) x.rem = x.bt;

    vector<pair<int,pair<int,int>>> g;
    vector<int> q;
    int idx = 0, time = 0, completed = 0;

    while (completed < n) {
        while (idx < n && p[idx].at <= time) q.push_back(idx++);

        if (q.empty()) {
            time++;
            continue;
        }

        int id = q.front();
        q.erase(q.begin());

        int start = time;
        int run = min(qt, p[id].rem);
        time += run;
        p[id].rem -= run;
        int end = time;

        g.push_back({p[id].pid, {start, end}});

        while (idx < n && p[idx].at <= time) q.push_back(idx++);

        if (p[id].rem == 0) {
            p[id].ct = time;
            p[id].tat = p[id].ct - p[id].at;
            p[id].wt = p[id].tat - p[id].bt;
            completed++;
        } else {
            q.push_back(id);
        }
    }

    printGantt(g);
    printTable(p);
}


// MAIN MENU

int main() {
    while (true) {
        cout << "\n================ Scheduling Menu ================\n";
        cout << "1. FCFS\n";
        cout << "2. SJF Non-Preemptive\n";
        cout << "3. SJF Preemptive (SRTF)\n";
        cout << "4. Priority Non-Preemptive\n";
        cout << "5. Priority Preemptive\n";
        cout << "6. Round Robin\n";
        cout << "0. Exit\n";
        cout << "-------------------------------------------------\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting...\n";
            return 0;
        }

        int n;
        cout << "Enter number of processes: ";
        cin >> n;

        vector<Process> p(n);
        cout << "Enter: PID  AT  BT  Priority\n";
        for (int i = 0; i < n; i++) {
            cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].pr;
        }

        if (choice == 6) {
            int qt;
            cout << "Enter Time Quantum: ";
            cin >> qt;
            rr(p, qt);
        }
        else if (choice == 1) fcfs(p);
        else if (choice == 2) sjf_np(p);
        else if (choice == 3) srtf(p);
        else if (choice == 4) priority_np(p);
        else if (choice == 5) priority_p(p);
        else cout << "Invalid Choice\n";
    }
}
