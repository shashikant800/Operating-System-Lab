#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};

bool compareByArrival(Process a, Process b) {
    return a.arrival < b.arrival;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
    }

    sort(processes.begin(), processes.end(), compareByArrival);

    int time = 0;
    int completed = 0;

    while (completed != n) {
        int idx = -1;
        int maxRemaining = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0) {
                if (processes[i].remaining > maxRemaining) {
                    maxRemaining = processes[i].remaining;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            processes[idx].remaining--;
            time++;

            if (processes[idx].remaining == 0) {
                processes[idx].completion = time;
                processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
                processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
                completed++;
            }
        } else {
            time++;
        }
    }

    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t"
             << processes[i].arrival << "\t"
             << processes[i].burst << "\t"
             << processes[i].completion << "\t\t"
             << processes[i].turnaround << "\t\t"
             << processes[i].waiting << "\n";
    }

    return 0;
}