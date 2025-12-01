#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int pid, arrival, burst, priority;
};

int main() {

    cout << "================ CPU Scheduler Input Format ================\n\n";

    int n;

    // ---- Number of processes ----
    cout << "Number of Processes: ";
    cin >> n;

    while (n <= 0) {
        cout << "Invalid input! Number of processes must be greater than 0.\n";
        cout << "Re-enter Number of Processes: ";
        cin >> n;
    }

    vector<Process> p(n);

    // ---- Process Details Header ----
    cout << "\nProcess Details:\n";
    cout << "PID  Arrival_Time  Burst_Time  Priority\n";

    // ---- Taking input with validation ----
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> p[i].pid >> p[i].arrival >> p[i].burst >> p[i].priority;

        // Validation
        while (p[i].arrival < 0 || p[i].burst <= 0 || p[i].priority < 0) {
            cout << "Invalid input! (Arrival >= 0, Burst > 0, Priority >= 0)\n";
            cout << "Re-enter Process " << i + 1 << ": ";
            cin >> p[i].pid >> p[i].arrival >> p[i].burst >> p[i].priority;
        }
    }

    cout << "\nInput section created successfully (Sahil’s Commit 1)\n";

    return 0;
}
